#include "bsp_resources.h"
#include "bsp_lump18.h"
#include "bsp_lump35.h"
#include "bsp_lump45.h"

#define fileofs_desc "Offset of the lump's data."
#define fourCC_desc "Identifier, XBOX / PS3 lumps only(?)"
#define mapRevision_desc "VMF Save Count"

////////////////////////////////////////////////////////////////////////////////////
// JavaScript
////////////////////////////////////////////////////////////////////////////////////

// This is necessary because JS can use globals lol
javascript
{
	var LumpBindArraySize = 0;
	function SetLumpBindArraySize(size)
	{
		LumpBindArraySize = size;
	}
	function GetLumpBindArraySize()
	{
		return LumpBindArraySize;
	}
	function BindLumpTypeAt(typeID, offset)
	{
		const HEADER_LUMPS = 64;
		if( typeID <= HEADER_LUMPS )
		{
			switch( typeID )
			{
				case 18:
					parser.bind("struct LUMP_BRUSHES", "brusheslump_container", offset);
					break;
				case 35:
					parser.bind("struct LUMP_GAME_LUMP", "gamelumps_container", offset);
					break;
				case 45:
					parser.bind("struct LUMP_OVERLAYS", "overlayslump_container", offset);
					break;
				default:
					parser.abort("Lump ID: ".concat(typeID, " does not have its own header yet."));
			}
		}
		else
		{
			parser.abort("Invalid Lump ID: ".concat(typeID, ", IDs must be 0-64."));
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////
// Neo's Custom Standard C
////////////////////////////////////////////////////////////////////////////////////
//--------------------
// Lumps
//--------------------
[display(format("Offset: {}", fileofs))]
struct lump_t
{
	int	version;	// lump format version

	[description(fileofs_desc), color_scheme("Characteristics")]
	int	fileofs;	// offset into file (bytes)
	int	filelen;	// length of lump (bytes)

	[description(fourCC_desc)]
	char fourCC[4];	// lump ident code

//--------------------
// Auto Binder, etc.
	if( array_index <= 63 )
	{
		$print("Lump Type", LumpTypes[array_index]);
		switch( array_index )
		{
			case 18:
				var size = filelen / 12;
				SetLumpBindArraySize(size);
				break;
			case 22:
			case 23:
			case 24:
			case 25:
				$print("Lump Note", "UNUSED - Reported always empty, despite having an offset.");
				$print("Lump Note #2", "Was this experimental indev code?");
				break;
			case 32:
				$print("Lump Note", "UNUSED - Before Source 2006, It supposedly had actual data.");
				break;
			case 45:
				var size = filelen / 352;
				SetLumpBindArraySize(size);
				break;
			case 49:
				$print("Lump Note", "DEPRECATED - Win-32 compressed Havok terrain surface collision data");
				break;
			case 55:
				$print("Lump Note", "This data overrides part of the data stored in LUMP_LEAFS");
				break;
			case 56:
				$print("Lump Note", "This data overrides part of the data stored in LUMP_LEAFS");
				break;
			case 57:
				$print("Lump Note", "DEPRECATED - In Xbox, was to replace PAK with XZip");
				break;
			case 60:
				$print("Lump Note", "Overlay fade distances");
				break;
			case 61:
				$print("Lump Note", "Likely, 'minmax' Shader/Effects level settings");
				break;
		}
		BindLumpTypeAt(array_index, fileofs);
	}
};

//--------------------
// Headers
//--------------------
// Resources
struct dheaderbsp_t
{
	char ident[4];                // BSP file identifier
	int	version;              // BSP file version
	lump_t lumps[64];  // lump directory array

	$assert(version == 21, "Bind only v21 BSPs! [Left 4 Dead 2]");
	[description(mapRevision_desc), color_scheme("Characteristics")]
	int	mapRevision;		// the map's revision (iteration, version) number
};
[display(format("Offset: {}", fileofs))]
struct dheaderlumpsingle_t
{
	[description(fileofs_desc), color_scheme("Characteristics")]
	int	fileofs;
	[color_scheme("Characteristics")]
	int lumpID;
	if( lumpID <= 64 )
	{
		$print("Lump Type", LumpTypes[lumpID]);
		BindLumpTypeAt(lumpID, fileofs);
	}
	
	[description(fourCC_desc)]
	char fourCC[4];
	int filelen;
	
	[description(mapRevision_desc)]
	int	mapRevision;
};

// To be binded
public struct BSP_HEADER
{
	dheaderbsp_t header;
};
public struct LUMPSINGLE_HEADER
{
	dheaderlumpsingle_t header;
};

//--------------------
// Lumps's Headers
//--------------------
// LUMP #18
[display(format("Brushes: {}", count))]
private struct LUMP_BRUSHES
{
	var count = GetLumpBindArraySize();
	dbrush_t brush[count];
};

// LUMP #35
[display(format("Game Lumps: {}", lumpCount))]
private struct LUMP_GAME_LUMP
{
	int lumpCount;	// number of game lumps
	dgamelump_t gamelump[lumpCount];
	StaticPropDictLump_t static_prop_modelsdict;
	StaticPropLeafLump_t  static_prop_leavesdict;
	StaticPropBlockLumps_t static_prop_entries;
};

// LUMP #45
[display(format("Overlays: {}", count))]
private struct LUMP_OVERLAYS
{
	var count = GetLumpBindArraySize();
	doverlay_t overlay[count];
};
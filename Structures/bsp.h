#include "bsp_resources.h"
#include "bsp_lump3.h"
#include "bsp_lump18.h"
#include "bsp_lump35.h"
#include "bsp_lump45.h"

#define fileofs_desc "Offset of the lump's data."
#define fourCC_desc "Identifier, XBOX / PS3 lumps only(?)"
#define mapRevision_desc "VMF Save Count"

// This is necessary because JS can use globals lol
//// Moved to "bsp_resources.h", and external script
#pragma script("bsp.js")

//--------------------------
// Lumps - Headers BASE
//--------------------------
[display(format("Offset: {}", fileofs))]
struct lump_t
{
	int	version;	// lump format version
	IncludeBSPScheme();
	[color_scheme("z_Member"), description(fileofs_desc)]
	int	fileofs;	// offset into file (bytes)
	int	filelen;	// length of lump (bytes)

	[description(fourCC_desc)]
	char fourCC[4];	// lump ident code

	if( array_index < HEADER_LUMPS )
	{
		$print("Lump Type", LumpTypes[array_index]);
		DoLumpBind(array_index, filelen, fileofs);
	}
};

//--------------------------
// BSP - Headers BASE
//--------------------------
// Resources
struct dheaderbsp_t
{
	char ident[4];                // BSP file identifier
	int	version;              // BSP file version
	IncludeBSPScheme(); [color_scheme("z_Array")]
	lump_t lumps[64];  // lump directory array

	$assert(version == 21, "Bind only v21 BSPs [and only Left 4 Dead 2's please]");
	[description(mapRevision_desc)]
	int	mapRevision;		// the map's revision (iteration, version) number
};
[display(format("Offset: {}", fileofs))]
struct dheaderlumpsingle_t
{
	IncludeBSPScheme();
	[color_scheme("z_Member"), description(fileofs_desc)]
	int	fileofs;
	[color_scheme("z_Member")]
	int lumpID;
	
	[description(fourCC_desc)]
	char fourCC[4];
	int filelen;
	
	[description(mapRevision_desc)]
	int	mapRevision;
	
	if( lumpID < HEADER_LUMPS )
	{
		$print("Lump Type", LumpTypes[lumpID]);
		DoLumpBind(lumpID, filelen, fileofs);
	}
};

// BSP - Headers
//--------------------------
public struct BSP_HEADER
{
	dheaderbsp_t header;
};
public struct LUMPSINGLE_HEADER
{
	dheaderlumpsingle_t header;
};

//--------------------------
// Lumps - Headers
//--------------------------
// LUMP #3
//[display(format("Vertexes: {}", count))]
public struct LUMP_VERTEXES
{
//	var count = GetBindArraySize();
	dvertex_t vertex[37];
};

// LUMP #18
[display(format("Brushes: {}", count))]
public struct LUMP_BRUSHES
{
	var count = GetBindArraySize();
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
	var count = GetBindArraySize();
	doverlay_t overlay[count];
};

// Helpers
//====================
const HEADER_LUMPS = 64;
[nooptimize]
function DoLumpBind( typeID, filelen, offset )
{
	if( typeID < HEADER_LUMPS )
	{
		// THIS should not be here!!!
		// You expect an error, BUT THIS CRASHED ME FOR 2 DAYS STRAAAAAIGHT Im mad
	//	$print("Lump Type", LumpTypes[typeID]);
		switch( typeID )
		{
			case 3:
				var size = int(filelen / 12);
				SetBindArraySize(size);
				$bind("struct LUMP_VERTEXES", "vertexlump", offset);
				break;
		/*	case 18:
				var size = int(filelen / 12);
				SetBindArraySize(size);
				$bind("struct LUMP_BRUSHES", "brusheslump", offset);
				break;
			case 22:
			case 23:
			case 24:
			case 25:
				$print("Lump Note", "UNUSED - Reported always empty, despite having an offset.");
				$print("Lump Note #2", "Was this experimental indev code?");
				break;
			case 29:
				$print("Lump Note", "VPhysics [Havok collision data]");
				break;
			case 32:
				$print("Lump Note", "UNUSED - Before Source 2006, It supposedly had actual data.");
				break;
			case 35:
				// Don't need a size for this one
				$bind("struct LUMP_GAME_LUMP", "gamelumps_container", offset);
				break;
			case 45:
				var size = int(filelen / 352);
				SetBindArraySize(size);
				$bind("struct LUMP_OVERLAYS", "overlayslump", offset);
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
				break; */
		}
	}
}
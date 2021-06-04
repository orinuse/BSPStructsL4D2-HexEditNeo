#include "bsp_resources.h"
#include "bsp_lump3.h"
#include "bsp_lump18.h"
#include "bsp_lump35.h"
#include "bsp_lump45.h"

#define fileofs_desc "Offset of the lump's data."
#define fourCC_desc "Identifier, XBOX / PS3 lumps only(?)"
#define mapRevision_desc "VMF Save Count"

const HEADER_LUMPS = 64;

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
		$print("Lump Type", LumpTypes[array_index]);
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
		$print("Lump Type", LumpTypes[lumpID]);
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
[display(format("Binded Vertexes: {}", count))]
public struct LUMP_VERTEXES
{
	var count = 37;
	dvertex_t vertex[count];
};

// LUMP #18
[display(format("Binded Brushes: {}", count))]
public struct LUMP_BRUSHES
{
	var count = 37;
	dbrush_t brush[count];
};

// LUMP #35
[display(format("Game Lumps: {}", lumpCount))]
public struct LUMP_GAME_LUMP
{
	int lumpCount;	// number of game lumps
	dgamelump_t gamelump[lumpCount];
	StaticPropDictLump_t static_prop_modelsdict;
	StaticPropLeafLump_t  static_prop_leavesdict;
	StaticPropBlockLumps_t static_prop_entries;
};

// LUMP #45
[display(format("Binded Overlays: {}", count))]
public struct LUMP_OVERLAYS
{
	var count = 37;
	doverlay_t overlay[count];
};
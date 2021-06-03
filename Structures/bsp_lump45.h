//===============================================
// LUMP_OVERLAYS (#45) 
//===============================================
#include "bsp_resources.h"
#pragma once

////////////////////////////////////////////////////////////////////////////////////
//	Tsuey's Notes:
//
// 45_LUMP_OVERLAYS.bin is the "info_overlay data array". Unlike simplier decals
// (i.e. infodecal entities), info_overlays are removed from the entity lump and
// stored separately in the Overlay Lump (index 45). The structure is reflective
// of the entity's properties in Hammer almost exactly.
//
// Valve Wiki Note:
//
// "The FaceCountAndRenderOrder member is split into two parts; the lower 14 bits
// are the number of faces that the overlay appears on, with the top 2 bits being
// the render order of the overlay (for overlapping decals). The Ofaces array,
// which is 64 elements in size (OVERLAY_BSP_FACE_COUNT) are the indices into the
// face array indicating which map faces the overlay should be displayed on. The
// other elements set the texture, scale, and orientation of the overlay decal.
// There is no enforced limit on overlays inside the engine. VBSP enforces a limit
// of 512 (MAX_MAP_OVERLAYS, 1024 in <Counter-Strike: Global Offensive>), but custom
// compilers can circumvent this."
//
// Where the 64 refers to "OVERLAY_BSP_FACE_COUNT", usually declared as a constant.
//
////////////////////////////////////////////////////////////////////////////////////

#define OVERLAY_BSP_FACE_COUNT 64

////////////////////////////////////////////////////////////////////////////////////
// JavaScript
////////////////////////////////////////////////////////////////////////////////////
javascript
{
	function tostring_RenderOrder(num)
	{
		switch( num )
		{
			case 0:
				return "First (0)"
			case 1:
				return "Second (1)"
			case 2:
				return "Third (2)"
			case 3:
				return "Fourth (3)"
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////
// Neo's Custom Standard C
////////////////////////////////////////////////////////////////////////////////////

// Enums
//====================
enum RenderOrder : unsigned short
{
	First = 0,
	Second = 1,
	Third = 2,
	Fourth = 3,
};

// Structs
//====================
[display( format("Face count: {}, RenderOrder: {}", FaceCount,
tostring_RenderOrder(RenderOrder) ) )]
union FaceCountAndRenderOrder_t
{
	[description("Count of faces that's touching")]
	unsigned short	FaceCount:14;
	[description("Higher values render after lower values")]
	RenderOrder RenderOrder:2;
};

[display( format( "UStart: {p2}, UEnd: {p2}; VStart: {p2}, VEnd: {p2}", U[0], U[1], V[0], V[1] ) )]
struct UV_t
{
	[description("1st - Starting U point, 2nd - Ending U point")]
	float U[2];
	[description("1st - Starting V point, 2nd - Ending V point")]
	float V[2];
};

[display( format( "TexInfo Indice: {}", TexInfo ) )]
private struct doverlay_t
{	
	int		Index;
	IncludeBSPScheme();
	[color_scheme("z_Member"), description("Indice to access the used Texdata struct")]
	short		TexInfo;

	FaceCountAndRenderOrder_t FaceCountAndRenderOrder;
	[color_scheme("z_Array"), description("Indices to access the touched Faces's struct")]
	int		OnFaces[ OVERLAY_BSP_FACE_COUNT ];
	UV_t UV;

	[description("Faces the Overlay is touching")]
	Vector		UVPoints[ 4 ];
	Vector		Origin;
	[description("Don't know yet")]
	Vector		BasisNormal;
};

//====================
// Archived comment
////
/*
// Map c2m4 has 175 info_overlays, so its array is 0-174... but setting to 200 still
// lists only 175. It's likely possible to set LUMP 18 to some very high number, such
// as 4028 (or w/e the maximum number of brushes allowed is), same for overlays, and
// stop selecting it uniquely per-map... for LUMP 18 each block is exactly 12 bytes,
// and for the above doverlay_t structure each info_overlay is exactly 352 bytes. So,
// the same per-map math could be done here, but since this lump's data is back-to-back
// contiguous, the array can be set arbitrarily high to account a theoretical maximum.
// Contrast this with the Game Lump which 100% necessarily needs to know the number of
// dictionary entries or prop_statics since its format isn't as uniform, which is likely
// why that Game Lump has the exact number of those entries built-in.

/*public struct c2m4_overlays
{
	doverlay_t overlay[ 175 ];
};
*/
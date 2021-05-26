//===============================================
// Lumps use some custom data types
//===============================================
#pragma once // it says it loads this header ONCE, but it also doesnt show up in that header menu thing?

////////////////////////////////////////////////////////////////////////////////////
// JavaScript
////////////////////////////////////////////////////////////////////////////////////

// By Tsuey
//// Orin:
//// JavaScript doesn't need semicolons, normally for
//// a language like these, I advise against the use
//// of it in languages like these, This file however, is 
//// for a program that uses the C language.
////
//// Personally, I would do it for the sake of consistency.
javascript
{
	function IncludeBSPScheme()
	{
		// For every clip, prop, or other major asset within each lump, draw it
		// with white text over a dark midnight purple background, black outline,
		// and no round edges to help visually separate them in Structure Viewer.

		/*
		** Orin - Color names are from :
		** https://www.color-blindness.com/color-name-hue/
		*/
		var Remark_Gainsboro = { r:225, g:225, b:225, a:255 };
		var Remark_Nero = { r:30, g:30, b:30, a:255 };
		
		var Remark_Sapphire = { r:32, g:0, b:64, a:230 };
		var Remark_DarkTangerine = { r:255, g:170, b:0, a:225 };
	
		var Remark_Denim = { r:16, g:116, b:216, a:230 };

		parser.add_coloring_scheme( "z_Array",
			Remark_Gainsboro,
			Remark_Sapphire,
			Remark_Denim,
		false );

		// For referential information like fileOfs, or targets of user modification
		// like flags, draw attention to them with black text over a blue background,
		// with a black outline and no round edges.

		parser.add_coloring_scheme( "z_Member",
			Remark_Nero,
			Remark_DarkTangerine,
			Remark_Sapphire,
		false );
	}
}

////////////////////////////////////////////////////////////////////////////////////
// Neo's Custom Standard C
////////////////////////////////////////////////////////////////////////////////////

// Custom Types
//====================
[display(format("{p2}, {p2}, {p2} [XYZ]", x, y, z))]
struct Vector
{
	float x;
	float y;
	float z;
};
[display(format("{p2}, {p2}, {p2} [PYR]", pitch, yaw, roll))]
struct QAngle
{
	float pitch;
	float yaw;
	float roll;
};
[display(format("{}, {}, {}, {} [RGBA]", red, green, blue, alpha))]
struct color32
{
	unsigned char red;
	unsigned char green;
	unsigned char blue;
	unsigned char alpha;
};
struct bool_32bit
{
	visible:
		bool value;
	
	hidden:
		// never implemented a compiler that turns bools into 4 byted ones, maybe this is right
		[description("Not important; Memory Alignment Stuff")]
		char padding_char;
		[description("Not important; Memory Alignment Stuff")]
		short padding_short;
};

// Enums
//====================
// Ya i copy pasted off the SDK 2013
//// was an 'enum' before, but bsp.h needed this as a const array
const LumpTypes[] =
{
	"LUMP_ENTITIES",						// 0
	"LUMP_PLANES",							// 1
	"LUMP_TEXDATA",							// 2
	"LUMP_VERTEXES",						// 3
	"LUMP_VISIBILITY",						// 4
	"LUMP_NODES",							// 5
	"LUMP_TEXINFO",							// 6
	"LUMP_FACES",							// 7
	"LUMP_LIGHTING",						// 8
	"LUMP_OCCLUSION",						// 9
	"LUMP_LEAFS",							// 10
	"LUMP_FACEIDS",							// 11
	"LUMP_EDGES",							// 12
	"LUMP_SURFEDGES",						// 13
	"LUMP_MODELS",							// 14
	"LUMP_WORLDLIGHTS",						// 15
	"LUMP_LEAFFACES",						// 16
	"LUMP_LEAFBRUSHES",						// 17
	"LUMP_BRUSHES",							// 18
	"LUMP_BRUSHSIDES",						// 19
	"LUMP_AREAS",							// 20
	"LUMP_AREAPORTALS",						// 21
	"LUMP_PROPCOLLISION",							// 22
	"LUMP_PROPHULLS",							// 23
	"LUMP_PROPHULLVERTS",							// 24
	"LUMP_PROPTRIS",							// 25
	"LUMP_DISPINFO",						// 26
	"LUMP_ORIGINALFACES",					// 27
	"LUMP_PHYSDISP",						// 28
	"LUMP_PHYSCOLLIDE",						// 29
	"LUMP_VERTNORMALS",						// 30
	"LUMP_VERTNORMALINDICES",				// 31
	"LUMP_DISP_LIGHTMAP_ALPHAS",			// 32 - DEPRECATED since source 2006
	"LUMP_DISP_VERTS",						// 33
	"LUMP_DISP_LIGHTMAP_SAMPLE_POSITIONS",	// 34
	"LUMP_GAME_LUMP",						// 35
	"LUMP_LEAFWATERDATA",					// 36
	"LUMP_PRIMITIVES",						// 37
	"LUMP_PRIMVERTS",						// 38
	"LUMP_PRIMINDICES",						// 39
	"LUMP_PAKFILE",							// 40
	"LUMP_CLIPPORTALVERTS",					// 41
	"LUMP_CUBEMAPS",						// 42
	"LUMP_TEXDATA_STRING_DATA",				// 43
	"LUMP_TEXDATA_STRING_TABLE",			// 44
	"LUMP_OVERLAYS",						// 45
	"LUMP_LEAFMINDISTTOWATER",				// 46
	"LUMP_FACE_MACRO_TEXTURE_INFO",			// 47
	"LUMP_DISP_TRIS",						// 48
	"LUMP_PHYSCOLLIDESURFACE",				// 49 - DEPRECATED, was win32 specific compressed Havok terrain surface collision data
	"LUMP_WATEROVERLAYS",					// 50
	"LUMP_LEAF_AMBIENT_INDEX_HDR",			// 51
	"LUMP_LEAF_AMBIENT_INDEX",				// 52
	"LUMP_LIGHTING_HDR",					// 53
	"LUMP_WORLDLIGHTS_HDR",					// 54
	"LUMP_LEAF_AMBIENT_LIGHTING_HDR",		// 55
	"LUMP_LEAF_AMBIENT_LIGHTING",			// 56
	"LUMP_XZIPPAKFILE",						// 57 - DEPRECATED Xbox lump
	"LUMP_FACES_HDR",						// 58
	"LUMP_MAP_FLAGS",						// 59
	"LUMP_OVERLAY_FADES",					// 60
	"LUMP_OVERLAY_SYSTEM_LEVELS",		// VDC - 61
	"LUMP_PHYSLEVEL",		// VDC - 62
	"LUMP_UNUSED4", // 63
};
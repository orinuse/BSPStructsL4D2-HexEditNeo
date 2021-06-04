//===============================================
// LUMP_GAME_LUMP (#35) stores static and detail props
// Ask around for info about flags, or unmystify the SDK 2013
//===============================================
#include "bsp_resources.h"
#define STATIC_PROP_NAME_LENGTH 128
#pragma once

/*
Notes are at the very bottom
////////////////////////////////////////////////////////////////////////////////////
// Orin's Notes:
//
//	This lump is a peculiar one, its goal is to contain lumps prone to constant
//	change throughout multiple games. A Developer even had a short-lived
//	idea, "// FIXME: Eventually, all lumps could use the game lump system".
//
//	As a quick resummary; Across all Valve games, there are only 4 possible contents:
// * Static Props
// * Detail Props
// * Detail Prop Lighting
// * Detail Prop Lighting (HDR)
//
//	Despite so, there is a roadblock in editing LUMP_GAME_LUMP. Custom lumps
//	of this do not accommodate the offset value defined in the game lump's
//	header's offset. Leaving it to defaults result in it pointing to the BSP's
//	default props.... Not sure how we'll approach this.
////////////////////////////////////////////////////////////////////////////////////
*/
#pragma script("bsp_lump35.js")

//===============================================
// Enums!
// These are for the "StaticPropLump_t" struct
//{
		enum CPULevel : unsigned char // For 'SystemLevelChoice' related entity KVs
		{
			NoRestrictions = 0,
			Low = 1,
			Normal = 2,
			High = 3,
		};
		enum GPULevel : unsigned char // For 'SystemLevelChoice' related entity KVs
		{
			NoRestrictions = 0,
			Low = 1,
			Normal = 2,
			High = 3,
			VeryHigh = 4,
		};
		enum PropSolid : unsigned char // For 'solid' KV
		{
			None = 0,
			BSP = 1,
			Bounding_Box = 2,
			Oriented_BBox = 3,
			Oriented_BBox_YawConstrained = 4,
			Custom = 5,
			VPhysics = 6,
		};
		enum StaticPropFlags : unsigned char
		{
			//-----------------------------------------------------------------------------
			// Orin:
			//
			// All of them had the prefix ''STATIC_PROP_" and I abbreivated it cause it was bloat
			//// Please note there are flags relevant to VRAD's "-StaticPropPolys" only!
			//
			//	* SP_NO_PER_VERTEX_LIGHTING
			//	* SP_NO_SELF_SHADOWING
			//
			//	Reference: https://nodraw.net/2010/12/lighting-compile-options/
			//
			//	Trivia: Back in 2009, people were discouraging against "-StaticPropPolys" usage!
			//	Reasons? For file size. Needs a lot more testing to be sure though.
			//	https://tf2maps.net/threads/staticproplighting-and-why-not-to-use-it.5077/
			//-----------------------------------------------------------------------------

			// "These are automatically computed"
			SP_FLAG_FADES = 0x1,
			SP_USE_LIGHTING_ORIGIN	= 0x2,
			SP_NO_DRAW = 0x4,
			
			// "These are set in WC" not sure what this means, 'WorldCraft'? lol
			SP_IGNORE_NORMALS = 0x8,
			SP_NO_SHADOW = 0x10,
			SP_SCREEN_SPACE_FADE	= 0x20,
			
			SP_NO_PER_VERTEX_LIGHTING = 0x40,				// "in vrad, compute lighting at lighting origin, not for each vertex"
			SP_NO_SELF_SHADOWING = 0x80,					// "disable self shadowing in vrad"
			SP_WC_MASK		= 0xd8,							// "all flags settable in hammer (?)"
		};
//}

//===============================================
// Structs
// The big Static Prop struct that constantly changes in versions

////////////////////////////////////////////////////////////////////////////////////
// Tsuey:
//
// The prop_static Data Block structure.
//
// L4D1 is V7/8 and L4D2 is V9. This means that members that were exclusive to older
// versions or newer versions are not present. MinDXLevel & MaxDXLevel are V6/7 only.
// An "unsigned int Flags", LightmapResX, and LightmapResY are V7-only. V10-only is
// a "unsigned int FlagsEx", and V11-only is "float UniformScale" (prop scale) -- all
// those are ignored below. In V11 the Xbox 360 flags were removed.
//
// SIZE :: Always 72 bytes each prop_static, but "propEntries" makes this trivia only.
////////////////////////////////////////////////////////////////////////////////////
[display(format("Model Index: {}, Leaf Index: {}", ModelIndex, LeafIndex))]
struct StaticPropLump_t
{
	// v4
	//-----------------------------------------------------------------------------
	Vector Origin;            // origin
	[description("Orientation (Pitch Yaw Roll)")]
	QAngle Angles;

	IncludeBSPScheme();
	[color_scheme("z_Member"), description("Index into Model Dictionary")]
	unsigned short  ModelIndex;
	[description("Index into Visleaf Dictionary")]
	unsigned short  LeafIndex;
	unsigned short  LeafCount;
	[exact_only]
	PropSolid   Solid;             // solidity type

	// every version except v7, but tf2's
	//-----------------------------------------------------------------------------
	StaticPropFlags   Flags;
	
	// v4 still
	//-----------------------------------------------------------------------------
	[description("Model skin number(s?)")]
	int             Skin;
	[onread(format("{p2}", FadeMinDist)), description("KVs 'fademindist'")]
	float           FadeMinDist;
	[onread(format("{p2}", FadeMaxDist)), description("KVs 'fademaxdist'")]
	float           FadeMaxDist;
	Vector          LightingOrigin;    // for lighting
	// since v5
	[onread(format("{p2}", ForcedFadeScale)), description("KVs 'fadescale'")]
	float           ForcedFadeScale;   // fade distance scale

	// since v8
	//-----------------------------------------------------------------------------
	[exact_only, description("Min Effects Detail Level")]
	CPULevel   MinCPULevel;
	[exact_only, description("Max Effects Detail Level")]
	CPULevel   MaxCPULevel;
	[exact_only, description("Min Shader Detail Level")]
	GPULevel   MinGPULevel;
	[exact_only, description("Max Shader Detail Level")]
	GPULevel   MaxGPULevel;
	
	// since v7
	//-----------------------------------------------------------------------------
	[description("KVs 'rendercolor' and 'renderamt'")]
	color32         DiffuseModulation; // per instance color and alpha modulation
	// v9 and v10 only
	//-----------------------------------------------------------------------------
	bool_32bit            DisableX360;       // if true, don't show on XBox 360 (4-bytes long)
};

[display(format("Models: {}", modelEntries))]
struct StaticPropDictLump_t
{
	IncludeBSPScheme();
	[color_scheme("z_Member")]
	int	modelEntries;
	struct dstaticpropdictname_t
	{
		char modelpath[STATIC_PROP_NAME_LENGTH];
	};
	[color_scheme("z_Array")]
	dstaticpropdictname_t modelsIndexes[modelEntries];	// model name
};

[display(format("Leaves: {}", leafEntries))]
struct StaticPropLeafLump_t
{
	IncludeBSPScheme();
	[color_scheme("z_Member")]
	int leafEntries;
	[color_scheme("z_Array")]
	unsigned short	leaves[leafEntries];
};

[display(format("Static Props: {}", propEntries))]
struct StaticPropBlockLumps_t
{
	IncludeBSPScheme();
	[color_scheme("z_Member")]
	int propEntries;
	[color_scheme("z_Array")]
	StaticPropLump_t staticProps[propEntries];
};

//===============================================
// Headers

// Game lumps themselves share headers
[display( tostring_GameLumpID(id) )]
private struct dgamelump_t
{
	IncludeBSPScheme();
	[color_scheme("z_Member"), onread( tostring_GameLumpID(id) )]
	char id[4];		// gamelump ID
	[onread( flags == 1 ? "GAMELUMP_COMPRESSED" : "none" )]
	unsigned short	flags;		// flags
	unsigned short	version;	// gamelump version
	[color_scheme("z_Member")]
	int		fileofs_bsp;	// offset to this gamelump
	int		filelen;	// length
};
/*
Main Binded Header isn't in here; Check bsp.h!

////////////////////////////////////////////////////////////////////////////////////
// Tsuey's Notes:
//
// Per-map Game Lump (index 35) number of prop_statics for array count.
//
// Prop_Statics are the easiest to change in terms of editing the *.BSP and modifying
// their origin to be under the map. In terms of *.LMP files, they'll be the hardest
// if not impossible due to assumptions (which 100% work for ALL other lumps) the LMP
// file system makes. We're lucky it's even this easy, since L4D2 always has these 4
// lumps 0-bytes / empty (for EVERY map) which simplifies things significantly:
//
//	22	LUMP_PROPCOLLISION	Static props convex hull lists
//	23	LUMP_PROPHULLS		Static prop convex hulls
//	24	LUMP_PROPHULLVERTS	Static prop collision vertices
//	25	LUMP_PROPTRIS		Static prop per hull triangle index start/count
//
// This lump is not as straight-forward. Map bsp_edit_test_version2 has 6 prop_static
// in lump 35 and 1,278 fileLen (lump in byte size). BSP_EDIT_TEST has 0 prop_static
// but its lump is still 60 bytes large. Map c1m1_hotel has lump 35 at 156260 bytes,
// and 1748 prop_statics (counted in the decompiled VMF).
//
// Since this lump starts with a "model dictionary" before the prop_static structure
// (with the origins etc.), this lump has multiple structures -- so it's going to be
// more complicated than the Brush Lump, especially considering that 0 prop_static
// still results in a 60 byte file size, so counting the number of prop_static this
// time will not be as easy as dividing by 12.
//
// ADDENDUM #1:
//
//	The above sizes are for reference only. Struct StaticPropBlockLumps_t defines
//	a "int propEntries", where the StaticPropBlock starts with the total number
//	of prop_statics in the map -- so they don't need to be counted with division,
//	where in Brush Lump 18 there's no data for this.
//
//	Similarly, the model dictionary knows this with "int nameEntries".
//
// Game Lump header has its own game-specific lumps within it, where "prps" refers
// to prop_static and "prpd" prop_detail. Structure dgamelump_t defines those lumps,
// in the same way that struct lump_t defines the BSP file's overall 64 main lumps.
//
// ADDENDUM #2:
//
//	Valve Wiki refers to "prps" as "sprp" instead (still prop_static),
//	and "prpd" as "dprp" instead (still prop_detail). All of Valve's maps
//	for L4D2 will have at least these 2.
//
//	The prop lighting lump (dplt for LDR and dplh for HDR) may also exist,
//	used for prop_detail entities (i.e. grass tufts) automatically emitted
//	by certain textures when placed on displacement surfaces.
//
// It exists to allow extension with new lumps without modifying the main BSP format.
//
// Lump "prps" (for prop_statics) starts with a model dictionary that defines all
// the unique model strings used, then the prop_static structure itself with all the
// propModelIndex to that dictionary and the Origin/Angles for all the props.
////////////////////////////////////////////////////////////////////////////////////
*/

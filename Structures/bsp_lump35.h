//===============================================
// LUMP_GAME_LUMP (#35) stores static and detail props
// Ask around for info about flags, or unmystify the SDK 2013
//===============================================
#include "bsp_resources.h"
#define STATIC_PROP_NAME_LENGTH 128

#pragma once

//===============================================
// Enums!
enum PropSolid : unsigned char
{
	None = 0,
	BSP = 1,
	Bounding_Box = 2,
	Oriented_BBox = 3,
	Oriented_BBox_YawConstrained = 4,
	Custom = 5,
	VPhysics = 6,
};
enum CPULevel : unsigned char
{
	NoRestrictions = 0,
	Low = 1,
	Normal = 2,
	High = 3,
};
enum GPULevel : unsigned char
{
	NoRestrictions = 0,
	Low = 1,
	Normal = 2,
	High = 3,
	VeryHigh = 4,
};
enum StaticPropFlags : unsigned char
{
	// All of them had the prefix ''STATIC_PROP_" and I abbreivated it cause it was bloat

	// "These are automatically computed"
	SP_FLAG_FADES = 0x1,
	SP_USE_LIGHTING_ORIGIN	= 0x2,
	SP_NO_DRAW = 0x4,
	
	// "These are set in WC" not sure what this means
	SP_IGNORE_NORMALS = 0x8,
	SP_NO_SHADOW = 0x10,
	SP_SCREEN_SPACE_FADE	= 0x20,
	
	SP_NO_PER_VERTEX_LIGHTING = 0x40,				// "in vrad, compute lighting at lighting origin, not for each vertex"
	SP_NO_SELF_SHADOWING = 0x80,					// "disable self shadowing in vrad"
	SP_WC_MASK		= 0xd8,							// "all flags settable in hammer (?)"
};
enum GameLumpID : int
{
	// All of them had the prefix ''STATIC_PROP_" and I abbreivated it
	GL_STATIC_PROPS = 1936749168, // "prps"
	GL_DETAIL_PROPS = 1685090928, // "prpd"
	GL_DETAIL_PROP_LIGHTING = 1685089396, // "tlpd"
	GL_DETAIL_PROP_LIGHTING_HDR = 1685089384, // "hlpd"
};

//===============================================
// Static Prop Structs
[display(format("Model Index: {}, Leaf Index: {}", ModelIndex, LeafIndex))]
struct StaticPropLump_t
{
	// VDC - L4D2 IS V9, L4D1 IS V8
	// BSPSrc - L4D1 IS A SPECIAL V7, L4D2 IS STILL V9
	// v4
	Vector Origin;            // origin
	[description("Orientation (Pitch Yaw Roll)")]
	QAngle Angles;

	[color_scheme("Characteristics"), description("Index into Model Dictionary")]
	unsigned short  ModelIndex;
	[description("Index into Visleaf Dictionary")]
	unsigned short  LeafIndex;
	unsigned short  LeafCount;
	[exact_only]
	PropSolid   Solid;             // solidity type

	// every version except v7*
	StaticPropFlags   Flags;
	// v4 still
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
	[exact_only, description("Min Effects Detail Level")]
	CPULevel   MinCPULevel;
	[exact_only, description("Max Effects Detail Level")]
	CPULevel   MaxCPULevel;
	[exact_only, description("Min Shader Detail Level")]
	GPULevel   MinGPULevel;
	[exact_only, description("Max Shader Detail Level")]
	GPULevel   MaxGPULevel;
	// since v7
	[description("KVs 'rendercolor' and 'renderamt'")]
	color32         DiffuseModulation; // per instance color and alpha modulation
	// v9 and v10 only
	bool_32bit            DisableX360;       // if true, don't show on XBOX 360 (4-bytes long)
};

[display(format("Models: {}", modelEntries))]
struct StaticPropDictLump_t
{
	int	modelEntries;
	struct dstaticpropdictname_t
	{
		[color_scheme("Characteristics")]
		char modelpath[STATIC_PROP_NAME_LENGTH];
	};
	dstaticpropdictname_t modelsIndexes[modelEntries];	// model name
};

[display(format("Leaves: {}", leafEntries))]
struct StaticPropLeafLump_t
{
	int leafEntries;
	unsigned short	leaves[leafEntries];
};

[display(format("Static Props: {}", propEntries))]
struct StaticPropBlockLumps_t
{
	int propEntries;
	StaticPropLump_t	staticProps[propEntries];
};

//===============================================
// Headers
// These are headers of the game Lumps themselves
[display(format("Offset: {}", fileofs))]
private struct dgamelump_t
{
	[exact_only]
	GameLumpID id;		// gamelump ID
	unsigned short	flags;		// flags
	unsigned short	version;	// gamelump version
	int		fileofs_bsp;	// offset to this gamelump
	int		filelen;	// length
};
/*
Main Binded Header isn't in here; Check bsp.h!
*/
//===============================================
// LUMP_BRUSHES (#18) stores a brush's plane data
// Ask around for info about flags, or unmystify the SDK 2013
//===============================================
#include "bsp_resources.h"
#pragma once

////////////////////////////////////////////////////////////////////////////////////
// Tsuey's Notes:
//
// Brush Lump. Always 12 bytes for each brush definition in 18_LUMP_BRUSHES.
// Where 'firstSide' is an index into 19_LUMP_BRUSHSIDES, 'numSides' is
// the number of sides making up the brush, and 'contents' which is 
// currently of interest to make brushes non-solid, change PLAYERCLIP or also
// MONSTERCLIP flags, and make solids climbable.
//
// SIZE :: Always 12 bytes each brush.
////////////////////////////////////////////////////////////////////////////////////

#pragma script("bsp_lump18_js")

//===============================================
// Enums
enum BrushContents : int
{
	// CONTENTS_ prefix > CTS_ prefix.
	// Its inaccurate yes, but its to show more flags visibly in structure viewer
	
	// "contents flags are seperate bits"
	// "a given brush can contribute multiple content bits"
	// "multiple brushes can be in a single leaf"
	//
	// "lower bits are stronger, and will eat weaker brushes completely"
	CTS_EMPTY = 0,										// "No contents"
	CTS_SOLID = 0x1,									// "an eye is never valid in a solid"
	CTS_WINDOW = 0x2,								// "translucent, but not watery (glass)"
	CTS_AUX = 0x4,
	CTS_GRATE = 0x8,									// "alpha-tested "grate" textures.  Bullets/sight pass through, but solids don't"
	CTS_SLIME = 0x10,
	CTS_WATER = 0x20,
	CTS_BLOCKLOS = 0x40,							// "block AI line of sight"
	CTS_OPAQUE	= 0x80,								// "things that cannot be seen through (may be non-solid though)"
	CTS_TESTFOGVOLUME	= 0x100,
	CTS_UNUSED = 0x200,

	// This seems pretty important, even though I don't understand everything
	// "NOTE: If it's visible, grab from the top + update CTS_OPAQUE"
	// "if not visible, then grab from the bottom."
	CTS_UNUSED6 = 0x400,
	CTS_TEAM1 = 0x800,								// "per team contents used to differentiate collisions" 
	CTS_TEAM2 = 0x1000,								// "between players and objects on different teams"
	CTS_IGNORE_NODRAW_OPAQUE = 0x2000,	// "ignore CTS_OPAQUE on surfaces that have SURF_NODRAW"
	CTS_MOVEABLE = 0x4000,						// "hits entities which are MOVETYPE_PUSH (doors, plats, etc.)"

// "remaining contents are non-visible, also doesn't eat brushes"
	CTS_AREAPORTAL = 0x8000,
	CTS_PLAYERCLIP = 0x10000,
	CTS_MONSTERCLIP = 0x20000,

// The hell is this? WATER related?
// "currents can be added to any other contents, and may be mixed"
	CTS_CURRENT_0	 = 0x40000,
	CTS_CURRENT_90 = 0x80000,
	CTS_CURRENT_180 = 0x100000,
	CTS_CURRENT_270 = 0x200000,
	CTS_CURRENT_UP = 0x400000,
	CTS_CURRENT_DOWN = 0x800000,

	CTS_ORIGIN = 0x1000000,						// "removed before bsping an entity"
	CTS_MONSTER = 0x2000000,					// "should never be on a brush, only in game"
	CTS_DEBRIS = 0x4000000,
	CTS_DETAIL = 0x8000000,						// "brushes to be added after vis leafs" aka func_detail bud
	CTS_TRANSLUCENT = 0x10000000,			// "auto set if any surface has trans(parency)"
	CTS_LADDER = 0x20000000,
	CTS_HITBOX = 0x40000000,						// "use accurate hitboxes on trace"
};

//===============================================
// Structs
// hello ProdigySim's block 

[display( format( "First Side: {}, Total Sides: {}", fstside, numside ) )]
private struct dbrush_t
{
	int fstside;
	int numside;
	IncludeBSPScheme(); [color_scheme("z_Member")]
	BrushContents flags;
};
/*
Header is in bsp.h; Dependancies of greater importance are in there!
*/
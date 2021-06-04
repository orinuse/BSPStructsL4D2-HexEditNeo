//===============================================
// LUMP_VERTEXES (#3) 
//===============================================
#include "bsp_resources.h"
#pragma once

////////////////////////////////////////////////////////////////////////////////////
// Tsuey's Notes:
//
// Part of the worldspawn's beating heart. If LUMP 3 VERTEXES is zeroed
// the map remains 95% playable since all wall/roof collision remains, but ALL of the
// visible world is gone.
//	
// There is a limit of 65536 faces per map.
//
// Simple and direct: an array of coordinates of all the vertices (corners) of
// brushes in the map geometry. Each vertex is a Vector of 3 floats (x/y/z) for
// a total of 12 bytes per vertex -- so the *.LMP file's total size, minus the
// 20-byte header, should be divisible by / a multiple of 12.
//
// NOTE: Vertices can be shared between faces, if the vertices coincide exactly.
//
// DEAR DIARY: A vertex is literally a single x/y/z point out in space. Originally
// I had this as an array "point[ 3 ]" which consumed 12*3 bytes, as mentally I
// was thinking of this in terms of "polygons" (which would require 3 points).
// It literally is as freaking simple as the below. I got scared when I noticed
// I was only seeing 1/3rd of the array indices I was supposed to, which LUMP 12
// did not agree with at all!!
//
// SIZE :: Always 12 bytes each vertex.
////////////////////////////////////////////////////////////////////////////////////

private struct dvertex_t
{
	IncludeBSPScheme(); [color_scheme("z_Member")]
	Vector	point;
};
/*
Header is in bsp.h; Dependancies of greater importance are in there!
*/
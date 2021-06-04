// By Tsuey
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
		Remark_Gainsboro, Remark_Sapphire, Remark_Denim,
	false );

	// For referential information like fileOfs, or targets of user modification
	// like flags, draw attention to them with black text over a blue background,
	// with a black outline and no round edges.
	parser.add_coloring_scheme( "z_Member",
		Remark_Nero, Remark_DarkTangerine, Remark_Sapphire,
	false );
}

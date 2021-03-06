# BSP Structs for Hex Editor Neo [L4D2 Only]
Header files for visualising BSP binaries in Hex Editor Neo.

## Initialization
Place the `Structures` folder in anywhere you want (preferrably the same as where Hex Editor Neo is installed), then go to *Tools > Structure Viewer > Library > Add Structue File...*, and add all the provided header files.

Then, simply access the Structure Viewer in *Tools > Structure Viewer > Bind*, pick `bsp.h` and two headers should be available. Bind the corresponding header, and the header files will auto-bind the corresponding structures. Both must be binded at the Absolute Offset of 0.

Header | Notes
------ | -----
BSP_HEADER | Already compiled BSP files, itself consisting of multiple lumps with its own data, inside it.
LUMPSINGLE_HEADER | Single lone lump file extracted from a BSP file, either with `vbspinfo.exe`, `GCFScape` or any program capable of viewing .ZIP files, like 7-Zip.

Not all lumps support their own headers yet. A later section will present a chart of supported Lumps.

These headers are **only stable** for ![L4D2 Icon](https://developer.valvesoftware.com/w/images/9/93/L4D2-16px.png) Left 4 Dead 2's BSP files; Other games (even games also using v21 BSP files) may fail to bind in a reasonable time, so this should be done at your own risk.

## Features
- Automatic binding assist of supported lumps. See "Lump Support Status" for info on supported lumps.
- Two custom color schemes. If you want to change the colors, here are the schemes:
- - Both schemes do not use rounded edges.
- - All "remark" objects have their parameters default to 0 if not specified, except for alpha, which defaults to 255. (`a`)
### Color Names
Color Name		| Remark Data 
-----------		| -----------
Gainsboro		| r:225, g:225, b:225, a:255 
Sapphire		| r:32, g:0, b:64, a:230 
Denim			| r:16, g:116, b:216, a:230
Nero			| r:30, g:30, b:30, a:255
Dark Tangerine	| r:255, g:170, b:0, a:225

### Scheme Names
Scheme Name | Font		| Back 				| Outline 
----------- | ---- 		| ----				| -------
z_Member	| Gainsboro	| Sapphire			| Denim
z_Array		| Nero		| Dark Tangerine	| Sapphire


### Lumps Support Status
Lump Type | Status | Additional Notes
--------- | ------ | ----------------
0 - LUMP_ENTITIES | ??? | Entities accept a wide variety of values and can differ greatly in KeyValue count. A custom-built parser is more suited, and more efficient for the task. <br><br>Its contents are readable ASCII text, so simply using a text editor is able to understand its content. If you wish to edit this lump, use the [lmpfix](steamreview.org/external/vdc/lmpfix.zip) tool to correct the header. (Treat it like its a compiler)
18 - LUMP_BRUSHES | ??????
22 - LUMP_PROPCOLLISION | ??? | Always empty, despite having an offset
23 - LUMP_PROPHULLS | ??? | Always empty, despite having an offset
24 - LUMP_PROPHULLVERTS | ??? | Always empty, despite having an offset
25 - LUMP_PROPTRIS | ??? | Always empty, despite having an offset
32 - LUMP_DISP_LIGHTMAP_ALPHAS | ??? | Deprecated since Source 2006
35 - LUMP_GAME_LUMP | ?????? | Only fully supports Static Props, partially supports detail props by supporting their lump headers
45 - LUMP_OVERLAYS | ?????? | RenderOrder needs to be checked if its values are displayed properly. Low priority.
49 - LUMP_PHYSCOLLIDESURFACE | ??? | Deprecated, was win32 specific compressed VPhysics collision data
57 - LUMP_XZIPPAKFILE | ??? | Deprecated Console lump, was a PAK file replacement
63 - LUMP_UNUSED4 | ??? | Only used in ![AS Icon](https://developer.valvesoftware.com/w/images/c/c9/AS-16px.png) Alien Swarm onwards(?)


## Addendum
Only Left 4 Dead 2 BSPs will support 'plug-and-play' at the moment, and thus will be maintained for it. Therefore for safety, BSPs that are not version 21 will be rejected. To remove this check manually, view the `bsp.h` file.

## Quick BSP Version Overview
Information based on the [Source BSP File Format](https://developer.valvesoftware.com/wiki/Source_BSP_File_Format#Versions) page on the VDC.

### Games with v21 BSP files
* ![L4D2 Icon](https://developer.valvesoftware.com/w/images/9/93/L4D2-16px.png) Left 4 Dead 2
> modified: lump_t, old dbrushside_t
* ![AS Icon](https://developer.valvesoftware.com/w/images/c/c9/AS-16px.png) Alien Swarm
> modified: new LUMP_DISP_MULTIBLEND #64
* ![P2 Icon](https://developer.valvesoftware.com/w/images/7/77/Portal2-16px.png) Portal 2
> modified: StaticPropLump_t ( version = 9 ), dbrushside_t and other structs
* ![CS:GO Icon](https://developer.valvesoftware.com/w/images/3/35/Csgo.png) Counter-Strike: Global Offensive
> modified: StaticPropLump_t ( version = 10 )
* ![Esther Icon](https://developer.valvesoftware.com/w/images/2/2d/Dear_Esther.png) Dear Esther (commercial release) 
> modified: StaticPropLump_t
* ![Insurgency Icon](https://developer.valvesoftware.com/w/images/a/af/Insurgency_16x_icon.png) Insurgency (commercial release) 	
* ![Stanley Parable Icon](https://developer.valvesoftware.com/w/images/8/88/The_stanley_parable_icon.PNG) The Stanley Parable (commercial release) 	
* The Beginner's Guide 	
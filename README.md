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

## Addendum
Only Left 4 Dead 2 BSPs will support 'plug-and-play' at the moment, and thus will be maintained for it. Therefore for safety, BSPs that are not version 21 will be rejected. To remove this check manually, view the `bsp.h` file.

Other than Left 4 Dead 2, the other source game most likely to receive support is Left 4 Dead 1.  

### Supported Lumps
Lump Type | Status | Additional Notes
--------- | ------ | ----------------
0 - LUMP_ENTITIES | ❌
18 - LUMP_BRUSHES | ✔️
32 - LUMP_DISP_LIGHTMAP_ALPHAS | ❕
22 - LUMP_PROPCOLLISION | ❕ | Always empty, despite having an offset
23 - LUMP_PROPHULLS | ❕ | Always empty, despite having an offset
24 - LUMP_PROPHULLVERTS | ❕ | Always empty, despite having an offset
25 - LUMP_PROPTRIS | ❕ | Always empty, despite having an offset
32 - LUMP_DISP_LIGHTMAP_ALPHAS | ❕ | Deprecated since Source 2006
35 - LUMP_GAME_LUMP | ✔️ | .LMP file copies of this can't replace map props, due to the game lumps having vastly different and unknown offsets
45 - LUMP_OVERLAYS | ✔️ | RenderOrder needs to be checked if it displays values properly
49 - LUMP_PHYSCOLLIDESURFACE | ❕ | Deprecated, was win32 specific compressed terrain collision data
57 - LUMP_XZIPPAKFILE | ❕ | Deprecated Xbox lump, was a PAK file replacement
63 - LUMP_UNUSED4 | ❕ | Only used in ![AS Icon](https://developer.valvesoftware.com/w/images/c/c9/AS-16px.png) Alien Swarm onwards(?)

## Quick BSP Version Overview
Information based on the [Source BSP File Format](https://developer.valvesoftware.com/wiki/Source_BSP_File_Format#Versions) page on the VDC.

### Games with v21 BSP files
* ![L4D2 Icon](https://developer.valvesoftware.com/w/images/9/93/L4D2-16px.png) Left 4 Dead 2
> modified: lump_t, old dbrushside_t
* ![AS Icon](https://developer.valvesoftware.com/w/images/c/c9/AS-16px.png) Alien Swarm
> modified: new LUMP_DISP_MULTIBLEND #63 
* ![P2 Icon](https://developer.valvesoftware.com/w/images/7/77/Portal2-16px.png) Portal 2
> modified: StaticPropLump_t ( version = 9 ), dbrushside_t and other structs
* ![CS:GO Icon](https://developer.valvesoftware.com/w/images/3/35/Csgo.png) Counter-Strike: Global Offensive
> modified: StaticPropLump_t ( version = 10 )
* ![Esther Icon](https://developer.valvesoftware.com/w/images/2/2d/Dear_Esther.png) Dear Esther (commercial release) 
> modified: StaticPropLump_t
* ![Insurgency Icon](https://developer.valvesoftware.com/w/images/a/af/Insurgency_16x_icon.png) Insurgency (commercial release) 	
* ![Stanley Parable Icon](https://developer.valvesoftware.com/w/images/8/88/The_stanley_parable_icon.PNG) The Stanley Parable (commercial release) 	
* The Beginner's Guide 	

# BSP Structs for Hex Editor Neo [L4D2 Only]
Header files for visualising BSP binaries in Hex Editor Neo.

Only Left 4 Dead 2 BSPs will support 'plug-and-play' at the moment, and thus will be maintained for it. Therefore for safety, BSPs that are not version 21 will be rejected. To remove this check manually, view the `bsp.h` file.

Other than Left 4 Dead 2, the other source game most likely to receive support is Left 4 Dead 1.  

## Games with v21 BSP files
Information based on the [Source BSP File Format](https://developer.valvesoftware.com/wiki/Source_BSP_File_Format#Versions) page on the VDC.

* ![L4D2 VDC Icon](https://developer.valvesoftware.com/w/images/9/93/L4D2-16px.png) Left 4 Dead 2
> modified: lump_t, old dbrushside_t

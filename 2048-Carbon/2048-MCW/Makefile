#   Makefile for building FAT executable for Mac OS System 7-9 both M68K and PPC architectures.
#   Please use Metrowerks CodeWarrior MPW Shell instead of vanilla Apple MPW Shell.
#   See "ReadMe.md" file for configuring and building instructions.
#
#   Written by:     EXL, 20-Mar-2021
#
#   File:           Makefile
#
#   Target:         2048-MCW
#
#   Sources:        2048.c
#                   2048-MCW.cp
#
#   GX Libraries:   "{MWCIncludes}ColorLibrary.c"
#                   "{MWCIncludes}FontLibrary.c"
#                   "{MWCIncludes}OffscreenLibrary.c"
#                   "{MWCIncludes}QDLibrary.c"
#                   "{MWCIncludes}TextLibrary.c"
#                   "{MWCIncludes}TransformLibrary.c"
#                   "{MWCIncludes}TransferModeLibrary.c"
#
#   Build Commands: Directory "Mac OS 8.1:2048-MCW"
#                   Files
#                   BuildProgram "2048-MCW"

APPNAME           = '2048-MCW'
SIGNATURE         = 'MCW '

C                 = MWC68K
PPCC              = MWCPPC
CPlus             = MWC68K
PPCCplus          = MWCPPC

COptions          = -w off -sym full -intsize 2 -prefix MacHeaders68K
CPlusOptions      = -w off -sym full -bool on -intsize 2 -prefix MacHeaders68K
PPCCOptions       = -w off -sym full -prefix MacHeadersPPC
PPCCPlusOptions   = -w off -sym full -bool on -prefix MacHeadersPPC

Link              = MWLink68K
PPCLink           = MWLinkPPC
LinkOptions       = -sym full
PPCLinkOptions    = -sym full

OBJECTS           = 2048.c.o ¶
                    2048-MCW.cp.o ¶
                    "{MWCIncludes}ColorLibrary.c.o" ¶
                    "{MWCIncludes}FontLibrary.c.o" ¶
                    "{MWCIncludes}OffscreenLibrary.c.o" ¶
                    "{MWCIncludes}QDLibrary.c.o" ¶
                    "{MWCIncludes}TextLibrary.c.o" ¶
                    "{MWCIncludes}TransformLibrary.c.o" ¶
                    "{MWCIncludes}TransferModeLibrary.c.o"

OBJECTS_PPC       = 2048.c.x ¶
                    2048-MCW.cp.x ¶
                    "{MWCIncludes}ColorLibrary.c.x" ¶
                    "{MWCIncludes}FontLibrary.c.x" ¶
                    "{MWCIncludes}OffscreenLibrary.c.x" ¶
                    "{MWCIncludes}QDLibrary.c.x" ¶
                    "{MWCIncludes}TextLibrary.c.x" ¶
                    "{MWCIncludes}TransformLibrary.c.x" ¶
                    "{MWCIncludes}TransferModeLibrary.c.x"

{APPNAME} ÄÄ Makefile {OBJECTS}
	{Link} {LinkOptions} ¶
		{OBJECTS} ¶
		"{MW68KLibraries}MSL Runtime68K.Lib" ¶
		"{MW68KLibraries}MacOS.lib" ¶
		"{MW68KLibraries}MathLib68K (2i).Lib" ¶
		"{MW68KLibraries}MSL C.68K (2i).Lib" ¶
		"{MW68KLibraries}MSL C++.68K (2i).Lib" ¶
		"{MW68KLibraries}MSL SIOUX.68K.Lib" ¶
		-o {APPNAME}

{APPNAME} ÄÄ Makefile {OBJECTS_PPC}
	{PPCLink} {PPCLinkOptions} ¶
		{OBJECTS_PPC} ¶
		"{MWPPCLibraries}MSL RuntimePPC.Lib" ¶
		"{MWPPCLibraries}InterfaceLib" ¶
		"{MWPPCLibraries}MathLib" ¶
		"{MWPPCLibraries}MSL C.PPC.Lib" ¶
		"{MWPPCLibraries}MSL C++.PPC.Lib" ¶
		"{MWPPCLibraries}MSL SIOUX.PPC.Lib" ¶
		"{MWPPCLibraries}QuickDrawGXLib" ¶
		-weakLib "QuickDrawGXLib" ¶
		-t APPL ¶
		-c {SIGNATURE} ¶
		-o {APPNAME}

{APPNAME} ÄÄ Makefile 2048-MCW.r "2048-MCW.µ.rsrc"
	Rez -append -o {APPNAME} 2048-MCW.r
	SetFile {APPNAME} -t APPL -c {SIGNATURE} -a B

#
#   Motorola 68000 Object Files:
#

2048.c.o Ä Makefile 2048.c 2048.h

2048-MCW.cp.o Ä Makefile 2048-MCW.cp 2048.h

"{MWCIncludes}ColorLibrary.c.o" Ä Makefile "{MWCIncludes}ColorLibrary.c"

"{MWCIncludes}FontLibrary.c.o" Ä Makefile "{MWCIncludes}FontLibrary.c"

"{MWCIncludes}OffscreenLibrary.c.o" Ä Makefile "{MWCIncludes}OffscreenLibrary.c"

"{MWCIncludes}QDLibrary.c.o" Ä Makefile "{MWCIncludes}QDLibrary.c"

"{MWCIncludes}TextLibrary.c.o" Ä Makefile "{MWCIncludes}TextLibrary.c"

"{MWCIncludes}TransformLibrary.c.o" Ä Makefile "{MWCIncludes}TransformLibrary.c"

"{MWCIncludes}TransferModeLibrary.c.o" Ä Makefile "{MWCIncludes}TransferModeLibrary.c"

#
#   PowerPC Object Files:
#

2048.c.x Ä Makefile 2048.c 2048.h

2048-MCW.cp.x Ä Makefile 2048-MCW.cp 2048.h

"{MWCIncludes}ColorLibrary.c.x" Ä Makefile "{MWCIncludes}ColorLibrary.c"

"{MWCIncludes}FontLibrary.c.x" Ä Makefile "{MWCIncludes}FontLibrary.c"

"{MWCIncludes}OffscreenLibrary.c.x" Ä Makefile "{MWCIncludes}OffscreenLibrary.c"

"{MWCIncludes}QDLibrary.c.x" Ä Makefile "{MWCIncludes}QDLibrary.c"

"{MWCIncludes}TextLibrary.c.x" Ä Makefile "{MWCIncludes}TextLibrary.c"

"{MWCIncludes}TransformLibrary.c.x" Ä Makefile "{MWCIncludes}TransformLibrary.c"

"{MWCIncludes}TransferModeLibrary.c.x" Ä Makefile "{MWCIncludes}TransferModeLibrary.c"

#   MPW Shell Makefile for building FAT executable for Mac OS System 7-9 both M68K and PPC architectures.
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

OBJECTS           = 2048.c.o �
                    2048-MCW.cp.o �
                    "{MWCIncludes}ColorLibrary.c.o" �
                    "{MWCIncludes}FontLibrary.c.o" �
                    "{MWCIncludes}OffscreenLibrary.c.o" �
                    "{MWCIncludes}QDLibrary.c.o" �
                    "{MWCIncludes}TextLibrary.c.o" �
                    "{MWCIncludes}TransformLibrary.c.o" �
                    "{MWCIncludes}TransferModeLibrary.c.o"

OBJECTS_PPC       = 2048.c.x �
                    2048-MCW.cp.x �
                    "{MWCIncludes}ColorLibrary.c.x" �
                    "{MWCIncludes}FontLibrary.c.x" �
                    "{MWCIncludes}OffscreenLibrary.c.x" �
                    "{MWCIncludes}QDLibrary.c.x" �
                    "{MWCIncludes}TextLibrary.c.x" �
                    "{MWCIncludes}TransformLibrary.c.x" �
                    "{MWCIncludes}TransferModeLibrary.c.x"

{APPNAME} �� Makefile {OBJECTS}
	{Link} {LinkOptions} �
		{OBJECTS} �
		"{MW68KLibraries}MSL Runtime68K.Lib" �
		"{MW68KLibraries}MacOS.lib" �
		"{MW68KLibraries}MathLib68K (2i).Lib" �
		"{MW68KLibraries}MSL C.68K (2i).Lib" �
		"{MW68KLibraries}MSL C++.68K (2i).Lib" �
		"{MW68KLibraries}MSL SIOUX.68K.Lib" �
		-o {APPNAME}

{APPNAME} �� Makefile {OBJECTS_PPC}
	{PPCLink} {PPCLinkOptions} �
		{OBJECTS_PPC} �
		"{MWPPCLibraries}MSL RuntimePPC.Lib" �
		"{MWPPCLibraries}InterfaceLib" �
		"{MWPPCLibraries}MathLib" �
		"{MWPPCLibraries}MSL C.PPC.Lib" �
		"{MWPPCLibraries}MSL C++.PPC.Lib" �
		"{MWPPCLibraries}MSL SIOUX.PPC.Lib" �
		"{MWPPCLibraries}QuickDrawGXLib" �
		-weakLib "QuickDrawGXLib" �
		-t APPL �
		-c {SIGNATURE} �
		-o {APPNAME}

{APPNAME} �� Makefile 2048-MCW.r 2048-MCW.rsrc
	Rez -append -o {APPNAME} 2048-MCW.r
	SetFile {APPNAME} -t APPL -c {SIGNATURE} -a B

#
#   Motorola 68000 Object Files:
#

2048.c.o � Makefile 2048.c 2048.h

2048-MCW.cp.o � Makefile 2048-MCW.cp 2048.h

"{MWCIncludes}ColorLibrary.c.o" � Makefile "{MWCIncludes}ColorLibrary.c"

"{MWCIncludes}FontLibrary.c.o" � Makefile "{MWCIncludes}FontLibrary.c"

"{MWCIncludes}OffscreenLibrary.c.o" � Makefile "{MWCIncludes}OffscreenLibrary.c"

"{MWCIncludes}QDLibrary.c.o" � Makefile "{MWCIncludes}QDLibrary.c"

"{MWCIncludes}TextLibrary.c.o" � Makefile "{MWCIncludes}TextLibrary.c"

"{MWCIncludes}TransformLibrary.c.o" � Makefile "{MWCIncludes}TransformLibrary.c"

"{MWCIncludes}TransferModeLibrary.c.o" � Makefile "{MWCIncludes}TransferModeLibrary.c"

#
#   PowerPC Object Files:
#

2048.c.x � Makefile 2048.c 2048.h

2048-MCW.cp.x � Makefile 2048-MCW.cp 2048.h

"{MWCIncludes}ColorLibrary.c.x" � Makefile "{MWCIncludes}ColorLibrary.c"

"{MWCIncludes}FontLibrary.c.x" � Makefile "{MWCIncludes}FontLibrary.c"

"{MWCIncludes}OffscreenLibrary.c.x" � Makefile "{MWCIncludes}OffscreenLibrary.c"

"{MWCIncludes}QDLibrary.c.x" � Makefile "{MWCIncludes}QDLibrary.c"

"{MWCIncludes}TextLibrary.c.x" � Makefile "{MWCIncludes}TextLibrary.c"

"{MWCIncludes}TransformLibrary.c.x" � Makefile "{MWCIncludes}TransformLibrary.c"

"{MWCIncludes}TransferModeLibrary.c.x" � Makefile "{MWCIncludes}TransferModeLibrary.c"

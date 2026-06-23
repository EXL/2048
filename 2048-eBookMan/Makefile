#  (c)2000 Franklin Electronic Publishers, Inc. Burlington, NJ.
#  All rights reserved. */
#
#
#	File: game2048/Makefile
#

APPNAME = game2048

# Define the list of source files
SRCS_CPP = game2048.cpp
SRCS_C = 2048.c
SRCS_S =

# Program parameters (ebo_locate needs 12K of stack)
HEAPSPACE       = 98304
MAINSTACKSPACE  = 16384
TIMERSTACKSPACE = 4096

# Environment: Use "yes" or "no"
GUI_LOCAL_COPY  = no
OS_LOCAL_COPY   = no
LANG_LOCAL_COPY = no
GUI_LANGUAGE    = GUI_Amr.pkg

#To prevent warnings from stopping the compilation, change the following line
#to "ERROR=" or start the make using "make ERROR=".
ERROR = -Werror

# Include the standard Makefile targets
ifeq (x$(EBSDK_LIBS)x,xx)
	# Normal: binary release version
	include ${EBOOKMAN_SDK}/ebsdk.uses
	include ${ESDK_TARGET_INC}/Makefile.GUI
else
	# Special: building the SDK
	include ${EBSDK_LIBS}/ebookman_libs.uses
	include ../source/Makefile.GUI
endif

install_to_sync: ${SYNC_OUT_DIR} ${APPNAME}.icn ${APPNAME}.fxe
	cp -p ${APPNAME}.fxe ${SYNC_OUT_DIR}
	cp -p ${APPNAME}.icn ${SYNC_OUT_DIR}
	cp -p initial.mom.${APPNAME} ${SYNC_OUT_DIR}

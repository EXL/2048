# This is an automatically generated record.
# The area between QNX Internal Start and QNX Internal End is controlled by
# the QNX IDE properties.


ifndef QCONFIG
QCONFIG=qconfig.mk
endif
include $(QCONFIG)

#===== USEFILE - the file containing the usage message for the application. 
USEFILE=


include $(MKFILES_ROOT)/qphabtarg.mk


#QNX internal start
ifeq ($(filter g, $(VARIANT_LIST)),g)
DEBUG_SUFFIX=_g
LIB_SUFFIX=_g
else
DEBUG_SUFFIX=_r
endif

LIBS_D = $(LIBS_$(CPUDIR)$(DEBUG_SUFFIX)) $(LIBS$(DEBUG_SUFFIX))

EXTRA_LIBVPATH := $(EXTRA_LIBVPATH_$(CPUDIR)$(DEBUG_SUFFIX)) $(EXTRA_LIBVPATH$(DEBUG_SUFFIX)) \
                 $(EXTRA_LIBVPATH_$(CPUDIR)) $(EXTRA_LIBVPATH)

EXTRA_INCVPATH := $(EXTRA_INCVPATH_$(CPUDIR)$(DEBUG_SUFFIX)) $(EXTRA_INCVPATH$(DEBUG_SUFFIX)) \
                 $(EXTRA_INCVPATH_$(CPUDIR)) $(EXTRA_INCVPATH)

EXTRA_SRCVPATH := $(EXTRA_SRCVPATH_$(CPUDIR)$(DEBUG_SUFFIX)) $(EXTRA_SRCVPATH$(DEBUG_SUFFIX)) \
				  $(EXTRA_SRCVPATH_$(CPUDIR)) $(EXTRA_SRCVPATH)

CCFLAGS_D = $(CCFLAGS$(DEBUG_SUFFIX)) $(CCFLAGS_$(CPUDIR)$(DEBUG_SUFFIX)) \
			$(CCFLAGS_$(basename $@)$(DEBUG_SUFFIX)) 					  \
			$(CCFLAGS_$(CPUDIR)_$(basename $@)$(DEBUG_SUFFIX)) 
LDFLAGS_D = $(LDFLAGS$(DEBUG_SUFFIX)) $(LDFLAGS_$(CPUDIR)$(DEBUG_SUFFIX))

CCFLAGS += $(CCFLAGS_$(CPUDIR))  $(CCFLAGS_$(basename $@)) 				  \
		   $(CCFLAGS_$(CPUDIR)_$(basename $@))  $(CCFLAGS_D)

LDFLAGS += $(LDFLAGS_$(CPUDIR)) $(LDFLAGS_D)

LIBS := $(foreach token, $(LIBS_D) $(LIBS_$(CPUDIR)) $(LIBS), $(if $(findstring ^, $(token)), $(subst ^,,$(token))$(LIB_SUFFIX), $(token)))

libnames:= $(subst lib-Bdynamic.a, ,$(subst lib-Bstatic.a, , $(libnames)))
libopts := $(subst -l-B,-B, $(libopts))
#QNX internal end

OPTIMIZE_TYPE_g=none
OPTIMIZE_TYPE=$(OPTIMIZE_TYPE_$(filter g, $(VARIANTS)))

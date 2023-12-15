#-------------------------------------------------------------------------------
.SUFFIXES:
#-------------------------------------------------------------------------------

ifeq ($(strip $(DEVKITPRO)),)
$(error "Please set DEVKITPRO in your environment. export DEVKITPRO=<path to>/devkitpro")
endif

TOPDIR ?= $(CURDIR)
include $(DEVKITPRO)/wut/share/wut_rules

PKGCONF          :=  /opt/devkitpro/portlibs/ppc/bin/powerpc-eabi-pkg-config
PKGCONF_WIIU     :=  /opt/devkitpro/portlibs/wiiu/bin/powerpc-eabi-pkg-config

#-------------------------------------------------------------------------------
# TARGET is the name of the output
# BUILD is the directory where object files & intermediate files will be placed
# SOURCES is a list of directories containing source code
# INCLUDES is a list of directories containing header files
#-------------------------------------------------------------------------------
TARGET		     :=	 gng
BUILD		     :=	 build
SOURCES		     :=	 src
INCLUDES	     :=	 

# WUHB

WHUB_TOOL        :=  /opt/devkitpro/tools/bin/wuhbtool

WHUB_NAME        :=  Grab\'n\'Go!
WHUB_SHORT_NAME  :=  $(WHUB_NAME)
WUHB_ICON        :=  ../assets/logo.png

# metagen-u
NODE_PACKAGE_MANAGER_X  :=  pnpx

#-------------------------------------------------------------------------------
# options for code generation
#-------------------------------------------------------------------------------
CFLAGS		:=	-g -Wall -O2 -Wno-format-truncation -ffunction-sections \
			-ffast-math \
			$(MACHDEP)

CFLAGS		+=	$(INCLUDE) -D__WIIU__ -D__WUT__
CFLAGS      +=  `$(PKGCONF_WIIU) --cflags SDL2_image SDL2_ttf sdl2`

CXXFLAGS	:=	$(CFLAGS) -std=gnu++14

ASFLAGS		:=	-g $(MACHDEP)
LDFLAGS		:=	-g $(MACHDEP) $(RPXSPECS) -Wl,-Map,$(notdir $*.map)

LIBS        :=  `$(PKGCONF_WIIU) --libs SDL2_image SDL2_ttf sdl2` \
					`$(PKGCONF) --libs zlib libpng`
LIBS        +=  -lharfbuzz -lfreetype
#-------------------------------------------------------------------------------
# list of directories containing libraries, this must be the top level
# containing include and lib
#-------------------------------------------------------------------------------
LIBDIRS		:=	$(PORTLIBS) $(WUT_ROOT)


#-------------------------------------------------------------------------------
# no real need to edit anything past this point unless you need to add additional
# rules for different file extensions
#-------------------------------------------------------------------------------
ifneq ($(BUILD),$(notdir $(CURDIR)))
#-------------------------------------------------------------------------------

export OUTPUT	:=	$(CURDIR)/$(TARGET)
export TOPDIR	:=	$(CURDIR)

export VPATH	:=	$(foreach dir,$(SOURCES),$(CURDIR)/$(dir))
export DEPSDIR	:=	$(CURDIR)/$(BUILD)

CFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
CPPFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))
SFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.s)))

#-------------------------------------------------------------------------------
# use CXX for linking C++ projects, CC for standard C
#-------------------------------------------------------------------------------
ifeq ($(strip $(CPPFILES)),)
#-------------------------------------------------------------------------------
	export LD	:=	$(CC)
#-------------------------------------------------------------------------------
else
#-------------------------------------------------------------------------------
	export LD	:=	$(CXX)
#-------------------------------------------------------------------------------
endif
#-------------------------------------------------------------------------------

export SRCFILES		:=	$(CPPFILES) $(CFILES) $(SFILES)
export OFILES		:=	$(CPPFILES:.cpp=.o) $(CFILES:.c=.o) $(SFILES:.s=.o)
export INCLUDE		:=	$(foreach dir,$(INCLUDES),-I$(CURDIR)/$(dir)) \
				$(foreach dir,$(LIBDIRS),-I$(dir)/include) \
				-I$(CURDIR)/$(BUILD)

export LIBPATHS		:=	$(foreach dir,$(LIBDIRS),-L$(dir)/lib)

.PHONY: $(BUILD) clean all

#-------------------------------------------------------------------------------

all: assets $(BUILD) wuhb metagen package

include ../assets.mk

dev: all test

$(BUILD): $(SRCFILES)
	@[ -d $@ ] || mkdir -p $@
	@$(MAKE) --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile

wuhb:
	@$(WHUB_TOOL) $(TARGET).rpx $(TARGET).wuhb --name=$(WHUB_NAME) --short-name=$(WHUB_SHORT_NAME) --icon=$(WUHB_ICON)

metagen:
	$(NODE_PACKAGE_MANAGER_X) metagen-u $(TOPDIR)

package:
	cp $(TARGET).rpx $(TARGET).wuhb meta/* bin/gng-wiiu/
	zip -r bin/gng-wiiu.zip bin/gng-wiiu/

test:
	Cemu -g $(TARGET).rpx

#-------------------------------------------------------------------------------
clean: clean-assets
	@echo clean ...
	@rm -rf $(BUILD) $(TARGET).rpx $(TARGET).elf $(TARGET).wuhb bin/gng-wiiu/* bin/gng-wiiu.zip

#-------------------------------------------------------------------------------
else
.PHONY:	all

DEPENDS		:=	$(OFILES:.o=.d)

#-------------------------------------------------------------------------------
# main targets
#-------------------------------------------------------------------------------
all		:	$(OUTPUT).rpx

$(OUTPUT).rpx	:	$(OUTPUT).elf

$(OUTPUT).elf	:	$(OFILES)

-include $(DEPENDS)

#-------------------------------------------------------------------------------
endif
#------------------------------------------------------------------------------- 
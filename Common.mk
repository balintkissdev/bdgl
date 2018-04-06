!ifdef __UNIX__
COPY_CMD = cp -rf
SEP = /
SCRIPT_EXTENSION =sh    # Mind the lack of space
!else
COPY_CMD = COPY /Y
SEP = \                 # Unlike GNU Make, one backslash should be used instead
                        # of two for WMake
SCRIPT_EXTENSION =bat   # Mind the lack of space
!endif

####### Compiler, flags and options

SYSTEM_DOS16 = DOS
SYSTEM_DOS32 = DOS4G

CC_DOS16 = wcl -cc
CC_DOS32 = wcl386 -cc

CPPFLAGS = -I$(INCLUDE_DIR) -DWATCOM

CFLAGS = -we -w4 -zq -ml

CFLAGS_OPTIMIZE_BASIC = -oneatx -oh -ei -zp8

# TODO: These specialized optimization flags can be set by a configure script
CFLAGS_OPTIMIZE_DOS16 = $(CFLAGS_OPTIMIZE_BASIC) -fpi87
CFLAGS_OPTIMIZE_DOS16_8086 = $(CFLAGS_OPTIMIZE_DOS16) -0
CFLAGS_OPTIMIZE_DOS16_186 = $(CFLAGS_OPTIMIZE_DOS16) -1
CFLAGS_OPTIMIZE_DOS16_286 = $(CFLAGS_OPTIMIZE_DOS16) -2 -fp2
CFLAGS_OPTIMIZE_DOS16_386 = $(CFLAGS_OPTIMIZE_DOS16) -3 -fp3
CFLAGS_OPTIMIZE_DOS16_486 = $(CFLAGS_OPTIMIZE_DOS16) -4 -fp3
CFLAGS_OPTIMIZE_DOS16_PENTIUM = $(CFLAGS_OPTIMIZE_DOS16) -5 -fp5
CFLAGS_OPTIMIZE_DOS16_PENTIUM_PRO = $(CFLAGS_OPTIMIZE_DOS16) -6 -fp6

CFLAGS_OPTIMIZE_DOS32_386 = $(CFLAGS_OPTIMIZE_BASIC) -3 -fp3
CFLAGS_OPTIMIZE_DOS32_486 = $(CFLAGS_OPTIMIZE_BASIC) -4 -fp3
CFLAGS_OPTIMIZE_DOS32_PENTIUM = $(CFLAGS_OPTIMIZE_BASIC) -5 -fp5
CFLAGS_OPTIMIZE_DOS32_PENTIUM_PRO = $(CFLAGS_OPTIMIZE_BASIC) -6 -fp6

CFLAGS_DOS16 = $(CFLAGS) -l=$(SYSTEM_DOS16) $(CFLAGS_OPTIMIZE_DOS16_8086)
CFLAGS_DOS32 = $(CFLAGS) -l=$(SYSTEM_DOS32) $(CFLAGS_OPTIMIZE_DOS32_386)

LIBUTIL = wlib

# Target library directory
LIB_DIR = lib

LIB_DOS16_DIR = $(LIB_DIR)$(SEP)dos16
LIB_DOS32_DIR = $(LIB_DIR)$(SEP)dos32

LIB_DOS16_TARGET = $(LIB_DOS16_DIR)$(SEP)BDGL.lib
LIB_DOS32_TARGET = $(LIB_DOS32_DIR)$(SEP)BDGL.lib

# Platform-independent file operation commands
# TODO: Can you make it that Makefile prints the commands of the scripts
#       instead of the filenames of them?
MKDIR_CMD=scripts$(SEP)internal$(SEP)mkdir_cmd.$(SCRIPT_EXTENSION)
RM_CMD=scripts$(SEP)internal$(SEP)rm_cmd.$(SCRIPT_EXTENSION)

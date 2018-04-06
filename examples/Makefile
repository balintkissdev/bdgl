!include ../Common.mk

RM_CMD=..$(SEP)$(RM_CMD)
MKDIR_CMD=..$(SEP)$(MKDIR_CMD)

INCLUDE_DIR = ..$(SEP)include

LIB_DOS16 = ..$(SEP)$(LIB_DOS16_TARGET)
LIB_DOS32 = ..$(SEP)$(LIB_DOS32_TARGET)

PROGRAM_DIR = bin
OBJ_DIR = build

PROGRAM_DOS16_DIR = $(PROGRAM_DIR)$(SEP)dos16
PROGRAM_DOS32_DIR = $(PROGRAM_DIR)$(SEP)dos32

PROGRAMS_DOS16 = &
  $(PROGRAM_DOS16_DIR)$(SEP)bmp.exe &
  $(PROGRAM_DOS16_DIR)$(SEP)hello.exe &
  $(PROGRAM_DOS16_DIR)$(SEP)keys.exe &
  $(PROGRAM_DOS16_DIR)$(SEP)mouse.exe &
  $(PROGRAM_DOS16_DIR)$(SEP)stars.exe

PROGRAMS_DOS32 = &
  $(PROGRAM_DOS32_DIR)$(SEP)bmp.exe &
  $(PROGRAM_DOS32_DIR)$(SEP)hello.exe &
  $(PROGRAM_DOS32_DIR)$(SEP)keys.exe &
  $(PROGRAM_DOS32_DIR)$(SEP)mouse.exe &
  $(PROGRAM_DOS32_DIR)$(SEP)stars.exe

OBJ_DOS16_DIR = $(OBJ_DIR)$(SEP)dos16
OBJ_DOS32_DIR = $(OBJ_DIR)$(SEP)dos32

all : $(PROGRAMS_DOS16) $(PROGRAMS_DOS32)

examples_dos16 : $(PROGRAMS_DOS16)

examples_dos32 : $(PROGRAMS_DOS32)

!include bmp/bmp.mk
!include hello/hello.mk
!include keys/keys.mk
!include mouse/mouse.mk
!include stars/stars.mk

clean : .SYMBOLIC
	$(RM_CMD) $(PROGRAM_DIR)
	$(RM_CMD) $(OBJ_DIR)

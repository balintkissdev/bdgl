!include ../Common.mk

INCLUDE_DIR = ../include

LIB_DOS16 = ../$(LIB_DOS16_TARGET)
LIB_DOS32 = ../$(LIB_DOS32_TARGET)

PROGRAM_DIR = bin
OBJ_DIR = build

PROGRAM_DOS16_DIR = $(PROGRAM_DIR)/dos16
PROGRAM_DOS32_DIR = $(PROGRAM_DIR)/dos32

PROGRAMS_DOS16 = &
  $(PROGRAM_DOS16_DIR)/bmp.exe &
  $(PROGRAM_DOS16_DIR)/hello.exe &
  $(PROGRAM_DOS16_DIR)/keys.exe &
  $(PROGRAM_DOS16_DIR)/mouse.exe &
  $(PROGRAM_DOS16_DIR)/stars.exe

PROGRAMS_DOS32 = &
  $(PROGRAM_DOS32_DIR)/bmp.exe &
  $(PROGRAM_DOS32_DIR)/hello.exe &
  $(PROGRAM_DOS32_DIR)/keys.exe &
  $(PROGRAM_DOS32_DIR)/mouse.exe &
  $(PROGRAM_DOS32_DIR)/stars.exe

OBJ_DOS16_DIR = $(OBJ_DIR)/dos16
OBJ_DOS32_DIR = $(OBJ_DIR)/dos32

all : $(PROGRAMS_DOS16) $(PROGRAMS_DOS32)

examples_dos16 : $(PROGRAMS_DOS16)

examples_dos32 : $(PROGRAMS_DOS32)

!include bmp/bmp.mk
!include hello/hello.mk
!include keys/keys.mk
!include mouse/mouse.mk
!include stars/stars.mk

clean : .SYMBOLIC
	$(RM_DIR) $(PROGRAM_DIR) $(OBJ_DIR)

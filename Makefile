!include Common.mk

SRC_DIR = src           # Sources directory
INCLUDE_DIR = include   # Public header directory
OBJ_DIR = build         # Intermediate build directory

# TODO: Write build configuration script

####### Sources

OBJ_DOS16_DIR = $(OBJ_DIR)/dos16
OBJ_DOS32_DIR = $(OBJ_DIR)/dos32

# TODO: Move to .mk files
OBJ_DOS16 = &
	$(OBJ_DOS16_DIR)/screen.obj &
	$(OBJ_DOS16_DIR)/shapes.obj &
	$(OBJ_DOS16_DIR)/keyboard.obj &
	$(OBJ_DOS16_DIR)/mouse.obj &
	$(OBJ_DOS16_DIR)/image.obj

OBJ_DOS32 = &
	$(OBJ_DOS32_DIR)/screen.obj &
	$(OBJ_DOS32_DIR)/shapes.obj &
	$(OBJ_DOS32_DIR)/keyboard.obj &
	$(OBJ_DOS32_DIR)/mouse.obj &
	$(OBJ_DOS32_DIR)/image.obj

####### Build rules

all : $(LIB_DOS16_TARGET) $(LIB_DOS32_TARGET) examples

lib_dos16 : $(LIB_DOS16_TARGET)

lib_dos32 : $(LIB_DOS32_TARGET)

examples : $(LIB_DOS16_TARGET) $(LIB_DOS32_TARGET)
	cd examples
	wmake all
	cd ..

# 16-bit target

$(LIB_DOS16_TARGET) : .AUTODEPEND $(OBJ_DOS16)
	$(MKDIR) $(LIB_DOS16_DIR)
	$(LIBUTIL) -n $@ $(OBJ_DOS16)

# 32-bit target
# FIXME: 32-bit library still needs to be ported

$(LIB_DOS32_TARGET) : .AUTODEPEND $(OBJ_DOS32)
	$(MKDIR) $(LIB_DOS32_DIR)
	$(LIBUTIL) -n $@ $(OBJ_DOS32)

!include src/src.mk

# TODO: dist:

# TODO: check: (Requires tests)

doc : .SYMBOLIC
	doxygen

clean : .SYMBOLIC
	$(RM_DIR) -rf $(LIB_DIR) $(OBJ_DIR)
	cd examples
	wmake clean
	cd ..

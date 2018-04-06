!include Common.mk

SRC_DIR = src           # Sources directory
INCLUDE_DIR = include   # Public header directory
OBJ_DIR = build         # Intermediate build directory

# TODO: Write build configuration script
# TODO: Use implicit build rules

####### Sources

OBJ_DOS16_DIR = $(OBJ_DIR)$(SEP)dos16
OBJ_DOS32_DIR = $(OBJ_DIR)$(SEP)dos32

# TODO: Move to .mk files
OBJ_DOS16 = &
	$(OBJ_DOS16_DIR)$(SEP)screen.obj &
	$(OBJ_DOS16_DIR)$(SEP)shapes.obj &
	$(OBJ_DOS16_DIR)$(SEP)keyboard.obj &
	$(OBJ_DOS16_DIR)$(SEP)mouse.obj &
	$(OBJ_DOS16_DIR)$(SEP)image.obj

OBJ_DOS32 = &
	$(OBJ_DOS32_DIR)$(SEP)screen.obj &
	$(OBJ_DOS32_DIR)$(SEP)shapes.obj &
	$(OBJ_DOS32_DIR)$(SEP)keyboard.obj &
	$(OBJ_DOS32_DIR)$(SEP)mouse.obj &
	$(OBJ_DOS32_DIR)$(SEP)image.obj

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
	@$(MKDIR_CMD) $(LIB_DOS16_DIR)
	$(LIBUTIL) -n $@ $(OBJ_DOS16)

# 32-bit target
# FIXME: 32-bit library still needs to be ported

$(LIB_DOS32_TARGET) : .AUTODEPEND $(OBJ_DOS32)
	@$(MKDIR_CMD) $(LIB_DOS32_DIR)
	$(LIBUTIL) -n $@ $(OBJ_DOS32)

!include $(SRC_DIR)/src.mk

# TODO: dist:

# TODO: check: (Requires tests)

doc : .SYMBOLIC
	doxygen

clean : .SYMBOLIC
	$(RM_CMD) $(LIB_DIR)
	$(RM_CMD) $(OBJ_DIR)
	cd examples
	wmake clean
	cd ..

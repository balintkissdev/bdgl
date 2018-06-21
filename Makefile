!include Common.mk

SRC_DIR = src           	# Sources directory
EXAMPLES_SRC_DIR = examples	# Example sources directory
INCLUDE_DIR = include   	# Public header directory

# TODO: Ordering of the targets and !include directives matters. Figure out
#       why.
all : $(LIB_DOS16_TARGET) $(LIB_DOS32_TARGET) examples

lib_dos16 : $(LIB_DOS16_TARGET)

lib_dos32 : $(LIB_DOS32_TARGET)

!include $(SRC_DIR)/src.mk
!include $(EXAMPLES_SRC_DIR)/examples.mk

$(LIB_DOS16_TARGET) : $(OBJ_DOS16)
	@$(MKDIR_CMD) $(LIB_DOS16_DIR)
	$(LINK_LIB_CMD)

# FIXME: 32-bit library still needs to be ported
$(LIB_DOS32_TARGET) : $(OBJ_DOS32)
	@$(MKDIR_CMD) $(LIB_DOS32_DIR)
	$(LINK_LIB_CMD)

examples : $(EXAMPLES_DOS16) $(EXAMPLES_DOS32)
	@%null		# Needed, otherwise returns with error

examples_dos16 : $(EXAMPLES_DOS16)

examples_dos32 : $(EXAMPLES_DOS32)

# TODO: dist:

# TODO: check: (Requires tests)

doc : .SYMBOLIC
	doxygen

clean : .SYMBOLIC
	$(RM_CMD) $(BIN_DIR)
	$(RM_CMD) $(LIB_DIR)
	$(RM_CMD) $(OBJ_DIR)

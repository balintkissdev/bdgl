OBJ_DOS16 = &
	$(OBJ_DOS16) &
	$(OBJ_DOS16_DIR)$(SEP)core.obj

OBJ_DOS32 = &
	$(OBJ_DOS32) &
	$(OBJ_DOS32_DIR)$(SEP)core.obj

$(OBJ_DOS16_DIR)/core.obj : $(SRC_DIR)/core/core.c
	@$(MKDIR_CMD) $(OBJ_DOS16_DIR)
	$(C_TO_OBJ16)

$(OBJ_DOS32_DIR)/core.obj : $(SRC_DIR)/core/core.c
	@$(MKDIR_CMD) $(OBJ_DOS32_DIR)
	$(C_TO_OBJ32)


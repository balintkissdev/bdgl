OBJ_DOS16 = &
	$(OBJ_DOS16) &
	$(OBJ_DOS16_DIR)$(SEP)keyboard.obj &
	$(OBJ_DOS16_DIR)$(SEP)mouse.obj &

OBJ_DOS32 = &
	$(OBJ_DOS32) &
	$(OBJ_DOS32_DIR)$(SEP)keyboard.obj &
	$(OBJ_DOS32_DIR)$(SEP)mouse.obj &

$(OBJ_DOS16_DIR)/keyboard.obj : $(SRC_DIR)/event/keyboard.c
	@$(MKDIR_CMD) $(OBJ_DOS16_DIR)
	$(C_TO_OBJ16)

$(OBJ_DOS16_DIR)/mouse.obj : $(SRC_DIR)/event/mouse.c
	@$(MKDIR_CMD) $(OBJ_DOS16_DIR)
	$(C_TO_OBJ16)

$(OBJ_DOS32_DIR)/keyboard.obj : $(SRC_DIR)/event/keyboard.c
	@$(MKDIR_CMD) $(OBJ_DOS32_DIR)
	$(C_TO_OBJ32)

$(OBJ_DOS32_DIR)/mouse.obj : $(SRC_DIR)/event/mouse.c
	@$(MKDIR_CMD) $(OBJ_DOS32_DIR)
	$(C_TO_OBJ32)


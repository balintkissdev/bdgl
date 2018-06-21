OBJ_DOS16 = &
	$(OBJ_DOS16) &
	$(OBJ_DOS16_DIR)$(SEP)screen.obj &
	$(OBJ_DOS16_DIR)$(SEP)shapes.obj &
	$(OBJ_DOS16_DIR)$(SEP)image.obj

OBJ_DOS32 = &
	$(OBJ_DOS32) &
	$(OBJ_DOS32_DIR)$(SEP)screen.obj &
	$(OBJ_DOS32_DIR)$(SEP)shapes.obj &
	$(OBJ_DOS32_DIR)$(SEP)image.obj

$(OBJ_DOS16_DIR)/screen.obj : $(SRC_DIR)/video/screen.c
	@$(MKDIR_CMD) $(OBJ_DOS16_DIR)
	$(C_TO_OBJ16)

$(OBJ_DOS16_DIR)/shapes.obj : $(SRC_DIR)/video/shapes.c
	@$(MKDIR_CMD) $(OBJ_DOS16_DIR)
	$(C_TO_OBJ16)

$(OBJ_DOS16_DIR)/image.obj : $(SRC_DIR)/video/image.c
	@$(MKDIR_CMD) $(OBJ_DOS16_DIR)
	$(C_TO_OBJ16)

$(OBJ_DOS32_DIR)/screen.obj : $(SRC_DIR)/video/screen.c
	@$(MKDIR_CMD) $(OBJ_DOS32_DIR)
	$(C_TO_OBJ32)

$(OBJ_DOS32_DIR)/shapes.obj : $(SRC_DIR)/video/shapes.c
	@$(MKDIR_CMD) $(OBJ_DOS32_DIR)
	$(C_TO_OBJ32)

$(OBJ_DOS32_DIR)/image.obj : $(SRC_DIR)/video/image.c
	@$(MKDIR_CMD) $(OBJ_DOS32_DIR)
	$(C_TO_OBJ32)


$(OBJ_DOS16_DIR)/screen.obj : .AUTODEPEND $(SRC_DIR)/video/screen.c
	@$(MKDIR_CMD) $(OBJ_DOS16_DIR)
	$(CC_DOS16) -c $(CPPFLAGS) $(CFLAGS_DOS16) $[* -fo=$@ -fr=$*.err

$(OBJ_DOS16_DIR)/shapes.obj : .AUTODEPEND $(SRC_DIR)/video/shapes.c
	@$(MKDIR_CMD) $(OBJ_DOS16_DIR)
	$(CC_DOS16) -c $(CPPFLAGS) $(CFLAGS_DOS16) $[* -fo=$@ -fr=$*.err

$(OBJ_DOS16_DIR)/image.obj : .AUTODEPEND $(SRC_DIR)/video/image.c
	@$(MKDIR_CMD) $(OBJ_DOS16_DIR)
	$(CC_DOS16) -c $(CPPFLAGS) $(CFLAGS_DOS16) $[* -fo=$@ -fr=$*.err

$(OBJ_DOS32_DIR)/screen.obj : .AUTODEPEND $(SRC_DIR)/video/screen.c
	@$(MKDIR_CMD) $(OBJ_DOS32_DIR)
	$(CC_DOS32) -c $(CPPFLAGS) $(CFLAGS_DOS32) $[* -fo=$@ -fr=$*.err

$(OBJ_DOS32_DIR)/shapes.obj : .AUTODEPEND $(SRC_DIR)/video/shapes.c
	@$(MKDIR_CMD) $(OBJ_DOS32_DIR)
	$(CC_DOS32) -c $(CPPFLAGS) $(CFLAGS_DOS32) $[* -fo=$@ -fr=$*.err

$(OBJ_DOS32_DIR)/image.obj : .AUTODEPEND $(SRC_DIR)/video/image.c
	@$(MKDIR_CMD) $(OBJ_DOS32_DIR)
	$(CC_DOS32) -c $(CPPFLAGS) $(CFLAGS_DOS32) $[* -fo=$@ -fr=$*.err


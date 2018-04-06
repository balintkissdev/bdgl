$(PROGRAM_DOS16_DIR)/hello.exe : hello/hello.c $(LIB_DOS16)
	$(MKDIR_CMD) $(PROGRAM_DOS16_DIR)
	$(MKDIR_CMD) $(OBJ_DOS16_DIR)
	$(CC_DOS16) $(CPPFLAGS) $(CFLAGS_DOS16) $< -fe=$@ -fo=$(OBJ_DOS16_DIR)$(SEP)$^&.obj -fr=$(OBJ_DOS16_DIR)$(SEP)$^&.err

$(PROGRAM_DOS32_DIR)/hello.exe : hello/hello.c $(LIB_DOS32) 
	$(MKDIR_CMD) $(PROGRAM_DOS32_DIR)
	$(MKDIR_CMD) $(OBJ_DOS32_DIR)
	$(CC_DOS32) $(CPPFLAGS) $(CFLAGS_DOS32) $< -fe=$@ -fo=$(OBJ_DOS32_DIR)$(SEP)$^&.obj -fr=$(OBJ_DOS32_DIR)$(SEP)$^&.err


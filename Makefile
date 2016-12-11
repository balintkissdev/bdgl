# TODO: This currently does 16-bit DOS compiling
# TODO: Only used with Open Watcom

####### Compiler, flags and options

SOURCE_DIR = src
INCLUDE_DIR = include
OBJ_DIR = build
LIB_DIR = lib

SYSTEM = dos
# SYSTEM = dos4g

CC = wcl
# CC = wcl386
CFLAGS = -cc -w4 -zq -l=$(SYSTEM) -ml
INCLUDE = -I$(INCLUDE_DIR)

# Needed for Watcom-specific "aux" pragma used for inline assembly
ifeq CC wcl
CFLAGS += -DWATCOM		
endif

LIBUTIL = wlib

####### Sources

VPATH = $(SOURCE_DIR)
SOURCES = BDGL_Video.c BDGL_Shapes.c BDGL_Keyboard.c BDGL_Mouse.c

OBJECTS = BDGL_Video.obj BDGL_Shapes.obj BDGL_Keyboard.obj BDGL_Mouse.obj

####### Build rules

all: BDGL.lib

BDGL.lib: .SYMBOLIC $(OBJECTS)
	@if not exist $(LIB_DIR) md $(LIB_DIR)
	$(LIBUTIL) -n -o=$(LIB_DIR)\$@ $@ +$<

# TODO: Place .obj files in separate "build" directory
# TODO: use wildcards
BDGL_Video.obj: .SYMBOLIC $(SOURCE_DIR)/graphics/BDGL_Video.c			
	$(CC) $(CFLAGS) $(INCLUDE) -c $<

BDGL_Shapes.obj: .SYMBOLIC $(SOURCE_DIR)/graphics/BDGL_Shapes.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $<

BDGL_Keyboard.obj: .SYMBOLIC $(SOURCE_DIR)/event/BDGL_Keyboard.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $<

BDGL_Mouse.obj: .SYMBOLIC $(SOURCE_DIR)/event/BDGL_Mouse.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $<

#BDGL_Image.obj: $(SOURCE_DIR)/graphics/BDGL_Image.c
#	$(CC) $(CFLAGS) $(INCLUDE) -c $<

# TODO: dist:

# TODO: check:

clean: .SYMBOLIC
	del /F *.exe *.lib *.err *.obj
	rd /S /Q $(LIB_DIR)

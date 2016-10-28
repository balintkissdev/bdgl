# TODO: This currently does 16-bit DOS compiling
# TODO: Only used with Open Watcom
# TODO: Place .obj files in separate "build" directory

####### Compiler, flags and options

SOURCE_DIR = src
INCLUDE_DIR = include
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

SOURCES = BDGL_Video.c BDGL_Shapes.c

OBJECTS = BDGL_Video.obj BDGL_Shapes.obj

####### Build rules

all: BDGL.lib

BDGL.lib: .SYMBOLIC $(OBJECTS)
	@if not exist $(LIB_DIR) md $(LIB_DIR)
	$(LIBUTIL) -n -o=$(LIB_DIR)\$@ $@ +$<

BDGL_Video.obj: $(SOURCE_DIR)/graphics/BDGL_Video.c			
	$(CC) $(CFLAGS) $(INCLUDE) -c $<

BDGL_Shapes.obj: $(SOURCE_DIR)/graphics/BDGL_Shapes.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $<

# TODO: dist:

# TODO: check:

clean: .SYMBOLIC
	del /F *.exe *.lib *.err *.obj
	rd /S /Q $(LIB_DIR)

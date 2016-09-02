# TODO: This currently does 16-bit DOS compiling
# TODO: Only used with Open Watcom

SRC_DIR = src
INCLUDE_DIR = include
LIB_DIR = lib

OBJS = BDGL_Video.obj

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

all: BDGL.lib

BDGL.lib: .SYMBOLIC BDGL_Video.obj
	@if not exist $(LIB_DIR) md $(LIB_DIR)
	$(LIBUTIL) -n -o=$(LIB_DIR)\$@ $@ +$<

BDGL_Video.obj: $(SRC_DIR)/BDGL_Video.c			# TODO: place .obj files in separate "build" directory
	$(CC) $(CFLAGS) $(INCLUDE) -c $<

clean: .SYMBOLIC
	del /F *.exe *.lib *.err *.obj
	rd /S /Q $(LIB_DIR)

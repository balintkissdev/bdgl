INCLUDE_DIR = ..\..\include
LIB = ..\..\lib\BDGL.lib

SYSTEM = dos
# SYSTEM = dos4g

CC = wcl -cc
# CC = wcl386 -cc
CFLAGS = -w4 -zq -l=$(SYSTEM) -ml
INCLUDE = -I$(INCLUDE_DIR)

ifeq CC wcl
CFLAGS += -DWATCOM		
endif

all: Keyboard.exe

Keyboard.exe: Keyboard.c $(LIB)
	$(CC) $(CFLAGS) $(INCLUDE) $<

clean: .SYMBOLIC
	del /F *.exe *.obj *.err

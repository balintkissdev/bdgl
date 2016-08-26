INCLUDE_DIR = ..\..\include
LIB = ..\..\lib\BDGL.lib

SYSTEM = dos
# SYSTEM = dos4g

CC = wcl
# CC = wcl386
CFLAGS = -w4 -zq -l=$(SYSTEM) -ml
INCLUDE = -I$(INCLUDE_DIR)

all: HelloWorld.exe

HelloWorld.exe: HelloWorld.c $(LIB)
	$(CC) $(CFLAGS) $(INCLUDE) $<

clean: .SYMBOLIC
	del /F *.exe *.obj *.err

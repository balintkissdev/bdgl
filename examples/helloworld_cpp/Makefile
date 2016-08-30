INCLUDE_DIR = ..\..\include
LIB = ..\..\lib\BDGL.lib

SYSTEM = dos
# SYSTEM = dos4g

CCX = wcl -cc++
# CCX = wcl386 -cc++
CFLAGS = -w4 -zq -l=$(SYSTEM) -ml
INCLUDE = -I$(INCLUDE_DIR)

all: HelloWorld.exe

HelloWorld.exe: HelloWorld.cpp $(LIB)
	$(CCX) $(CFLAGS) $(INCLUDE) $<

clean: .SYMBOLIC
	del /F *.exe *.obj *.err

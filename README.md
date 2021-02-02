# BDGL DOS Game Library

![Build](https://github.com/balintkissdev/bdgl/workflows/Build/badge.svg)

**NOTICE:**
This library is in **pre-release** state. The API is being experimented on and
is subject to constant changes during this phase that could break the code
compatibility of client applications using the library.

## Introduction

A work-in-progress C library for DOS game programming, currently containing DOS
graphics-related functions and has an API reminiscent of SDL. 16-bit programs
compiled with a Open Watcom and linked with this library work under DOSBox.
The currently supported DOS compiler is Open Watcom 1.9 and
Open Watcom V2 on Windows and Linux.

## Features

### Current features

- [x] 256 color 320x240 VGA mode with optional VSync and Double Buffering
- [x] Drawing of primitives, like points, lines and rectangles
- [x] BMP image support
- [x] Palette manipulation
- [x] Keyboard input handling
- [x] Mouse input handling

### Planned features

- [ ] Buffered keyboard input
- [ ] Joystick handling
- [ ] Other video modes like CGA, TGA, EGA and SVGA
- [ ] Circle drawing
- [ ] PCX image support
- [ ] 2D sprite framework
- [ ] State management framework
- [ ] PC speaker sound
- [ ] Sound Blaster 16 sound
- [ ] 3D math library and rendering

## Building

The recommended compiler to use is the recent Open Watcom V2 compiler, although
Open Watcom 1.9 is also supported. You can download the binary release
from https://github.com/open-watcom/open-watcom-v2/releases/download/Current-build/ow-snapshot.tar.gz
and extract it somewhere, but better yet, you can use the bundled
`install_deps.py` script under the `scripts` folder to download and extract
inside a `deps` folder in the project.

1. Clone this repository with Git and enter the project folder.

   ```bash
   git clone https://github.com/balintkiss501/bdgl
   cd bdgl
   ```

2. Execute `scripts/install_deps.py` script with Python 3 to download the
   Open Watcom V2 compiler suite and other dependencies.

   ```bash
   python3 scripts/install_deps.py
   ```

3. Set the Watcom environment using `scripts/set_watcom.sh` if you are under
   Linux/Unix/MSYS/Cygwin or `set_watcom.bat` if you are under Windows.

   ```bash
   # If under Linux/Unix/MSYS/Cygwin
   source scripts/set_watcom.sh
   ```

   ```bash
   # If under Windows command line
   scripts/set_watcom.bat
   ```

4. Build the library using `wmake`. This will build the linkable static
   libraries for 16- and 32-bit architectures under the `lib` folder and the
   examples in `examples/bin` folder.

   ```
   wmake
   ```

You are done and ready to use the library.

## Usage

Until there's avaible documentation here, see the examples in the `examples`
directory for usage of the API. To compile your program with the library
using Watcom, issue the command

```
wcl -ml -I<directory of BDGL header files> yourprogram.c BDGL.lib
```

Then you'll be able to run your executable in DOSBox.

```
dosbox yourprogram.exe
```

**Note about 32-bit DOS builds:** Running 32-bit DOS programs requires the use of
a DOS Extender. One such as DOS/32A can be downloaded from
http://dos32a.narechk.net. However, executing programs compiled with 32-bit
BDGL is currently not supported.

## References:

* ftp://ftp.openwatcom.org/pub/manuals/current/cguide.pdf
* ftp://ftp.openwatcom.org/manuals/current/tools.pdf
* http://www.brackeen.com/vga/
* http://www.wagemakers.be/english/doc/vga
* http://www.columbia.edu/~em36/wpdos/videomodes.txt
* http://tuttlem.github.io/2015/10/04/building-libraries-using-open-watcom.html
* http://tuttlem.github.io/2015/10/04/inline-assembly-with-watcom.html
* http://flipcode.com/demomaking

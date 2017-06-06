# BDGL DOS Game Library
A work-in-progress C library for DOS game programming, currently containing DOS
graphics-related functions and has an API reminiscent of SDL. 16-bit programs
compiled with a Open Watcom and linked with this library work under DOSBox.
Currently supported DOS compiler is Open Watcom 1.9 and
Open Watcom V2 on Windows and Linux.

## Current features

* 256 color 320x240 VGA mode with optional VSync and Double Buffering
* Drawing of primitives, like points, lines and rectangles
* BMP image loading
* Palette manipulation
* Keyboard input handling
* Mouse input handling

## Building

1. The recommended compiler to use is the recent Open Watcom V2
   compiler, although Open Watcom 1.9 is also supported.
   Download the binary release from
   [](https://github.com/open-watcom/travis-ci-ow-builds/archive/master.zip).
   Uncompress the files to somewhere.
2. Clone this repository with Git using
   `git clone https://github.com/balintkiss501/BDGL`
3. Modify the `WATCOM` variable in `scripts/setwatcom.sh` file if you are
   under Linux or in `scripts/setwatcom.bat` if you are under Windows to
   point to your uncompressed Watcom folder.
4. Load the Watcom environment using `. scripts/setwatcom.sh` if you are under
   Linux or `setwatcom.bat` if you are under Windows.
3. Build the library using `wmake`. This will build the linkable static
   libraries for 16- and 32-bit architectures under the `lib` folder and the
   examples in `examples/bin` folder.

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
[](http://dos32a.narechk.net). However, executing programs compiled with 32-bit
BDGL is currently not supported.

## References:

* <ftp://ftp.openwatcom.org/pub/manuals/current/cguide.pdf>
* <ftp://ftp.openwatcom.org/manuals/current/tools.pdf>
* <http://www.brackeen.com/vga/>
* <http://www.wagemakers.be/english/doc/vga>
* <http://www.columbia.edu/~em36/wpdos/videomodes.txt>
* <http://tuttlem.github.io/2015/10/04/building-libraries-using-open-watcom.html>
* <http://tuttlem.github.io/2015/10/04/inline-assembly-with-watcom.html>
* <http://flipcode.com/demomaking>

# BDGL DOS Game Library
A work-in-progress C library for DOS game programming, currently containing DOS graphics-related functions and has an API reminiscent of SDL. 16-bit programs compiled with a Open Watcom and linked with this library work under DOSBox. Currently supported DOS compiler is Open Watcom 1.9 on Windows platform, others (Open Watcom 2.0, DJGPP, Borland C, Turbo C) were not yet tested.

## How to build the library:

1. Download and install [Open Watcom 1.9](ftp://ftp.openwatcom.org/pub/open-watcom-c-win32-1.9.exe) under Windows.
2. `git clone https://github.com/balintkiss501/BDGL`
3. Build the library using `wmake all`. This will create the linkable static library `BDGL.lib` under the `lib` folder.

## How to use the library:

See "examples/HelloWorld.c" for usage of the API. To compile your program with the library, issue

```
wcl -ml -I<directory of BDGL header files> yourprogram.c BDGL.lib
```

Then you'll be able to run your executable in DOSBox.

## References:

* <ftp://ftp.openwatcom.org/pub/manuals/current/cguide.pdf>
* <http://www.brackeen.com/vga/>
* <http://www.wagemakers.be/english/doc/vga>
* <http://www.columbia.edu/~em36/wpdos/videomodes.txt>
* <http://tuttlem.github.io/2015/10/04/building-libraries-using-open-watcom.html>
* <http://tuttlem.github.io/2015/10/04/inline-assembly-with-watcom.html>
* <http://flipcode.com/demomaking>

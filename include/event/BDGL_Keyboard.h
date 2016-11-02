/*
  Copyright (c) 2016 Bálint Kiss <balint.kiss.501@gmail.com>

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/
#ifndef BDGL_KEYBOARD_H_
#define BDGL_KEYBOARD_H_

#include "../core/BDGL_Types.h"

// TODO: Finish keycodes
/* Special keys */
#define BDGL_K_SHIFT_RIGHT  (0x0001)
#define BDGL_K_SHIFT_LEFT   (0x0002)
#define BDGL_K_CTRL         (0x0003)

/* Scancodes */
#define BDGL_SCAN_ESC       (1)
#define BDGL_SCAN_1         (2)
#define BDGL_SCAN_Q         (16)

#define BDGL_SCAN_UP        (72)
#define BDGL_SCAN_LEFT      (75)
#define BDGL_SCAN_RIGHT     (77)
#define BDGL_SCAN_DOWN      (80)

// TODO: Library users shouldn't require -DWATCOM compiler flag
// FIXME: Keyboard recognition is not continous enough, need to implement
//        buffered input
BDGL_BYTE BDGL_GetScancode();
#ifdef WATCOM
#pragma aux BDGL_GetScancode =                                  \
  "mov AH, 01h"     /* Function 1: Check if key is ready */     \
  "int 16h"         /* BIOS interrupt */                        \
  "jz empty"        /* No key was pressed, exit */              \
  "mov AH, 00h"     /* Function 0: Acquire scancode */          \
  "int 16h"         /* BIOS interrupt */                        \
  "mov AL, AH"      /* Get result from AH to AL */              \
                                                                \
  "xor AH, AH"      /* Null out AH */                           \
  "jmp done"        /* Exit */                                  \
                                                                \
  "empty:"                                                      \
  " xor AX, AX"     /* Null out AX */                           \
                                                                \
  "done:"                             
#endif

#endif // BDGL_KEYBOARD_H_

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
#include <event/BDGL_Keyboard.h>

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 */
/*BDGL_BYTE BDGL_GetScancode();
#ifdef WATCOM
#pragma aux BDGL_GetScancode =        \
  "mov AH, 01h"                       \
  "int 16h"                           \
  "jz empty"                          \
  "mov AH, 00h"                       \
  "int 16h"                           \
  "mov AL, AH"                        \
                                      \
  "xor AH, AH"                        \
  "jmp done"                          \
                                      \
  "empty:"                            \
  " xor AX, AX"                       \
                                      \
  "done:"                             \
  value [AX]
#else
{
  // TODO
}
#endif*/

#ifdef __cplusplus
}
#endif

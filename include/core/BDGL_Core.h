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

/**
 * @file BDGL_Core.h
 */
#ifndef BDGL_CORE_H_
#define BDGL_CORE_H_

#include "BDGL_Types.h"

#include <dos.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Memory addresses */
/** 18.2 Hz system clock */
#define BDGL_CLOCK_ADDRESS      (0x046C)
/** VGA array            */
#define BDGL_VGA_ADDRESS        (0xA000)    

/**
 * Get the sign of a number.
 *
 * @param x         positive or negative number
 * @return          1 for positive, -1 for negative number and 0 for 0
 */
#define BDGL_GetMathSign(x)     ((0 < x) - (x < 0))

/**
 * Helper macro to get the number of elements in an array.
 *
 * BE CAREFUL! It doesn't work with pointers, and arrays passed as function parameters 
 * are decayed as such.
 *
 * @param array     array with a constant size
 * @return          number of elements in array
 */
#define BDGL_GetArrayLength(array)         (sizeof((array)) / sizeof((array)[0]))

BDGL_WORD *BDGL_SystemClock = (BDGL_WORD *)MK_FP(0,BDGL_CLOCK_ADDRESS);  // FIXME: encapsulate

// TODO
inline float BDGL_GetCurrentTicks()
{
    return (*BDGL_SystemClock) / 18.2;
}

#ifdef __cplusplus
}
#endif

#endif  // BDGL_CORE_H_

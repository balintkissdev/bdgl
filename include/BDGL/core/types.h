/*
 * Copyright (c) 2016-2017 Bálint Kiss <balint.kiss.501@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */
#ifndef _BDGL_TYPES_H_
#define _BDGL_TYPES_H_

/** 
 * Primitive byte.
 *
 * 1 byte size, values ranging from 0 to 255.
 */
typedef unsigned char BDGL_Uint8;

/**
 * Primitive word.
 *
 * 2 byte size, values ranging from 0 to 65,535.
 */
typedef unsigned short BDGL_Uint16;

/**
 * Primitive double word.
 *
 * 1 byte size, values ranging from 0 to 4,294,967,295.
 */
typedef unsigned long int BDGL_Uint32;

typedef unsigned long long int BDGL_Uint64;

typedef char BDGL_Int8;

typedef short BDGL_Int16;

typedef long int BDGL_Int32;

typedef long long int BDGL_Int64;

/**
 * Primitive boolean type.
 */
typedef enum
{
  BDGL_FALSE,
  BDGL_TRUE
} BDGL_Bool;

typedef BDGL_Uint8 BDGL_KeyScancode;

typedef BDGL_Uint8 BDGL_MouseButton;

#endif  /* _BDGL_TYPES_H_ */

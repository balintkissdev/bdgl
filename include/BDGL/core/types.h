/*
 * Copyright (c) 2016 Bálint Kiss <balintkissdev@gmail.com>
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
 * Typedef for unsigned char.
 *
 * Also known as byte. 1 byte sized, values range from 0 to 255. This
 * is the equivalent of uint8_t from C99's stdint.h.
 */
typedef unsigned char BDGL_Uint8;

/**
 * Typedef for unsigned short.
 *
 * Also known as word. 2 byte sized, values range from 0 to 65,535. This is
 * the equivalent of uint16_t from C99's stdint.h.
 */
typedef unsigned short BDGL_Uint16;

/**
 * Typedef for unsigned long int.
 *
 * Also known as double word. 4 byte sized, values range from 0 to
 * 4,294,967,295. This is the equivalent of uint32_t from C99's stdint.h.
 */
typedef unsigned long int BDGL_Uint32;

/**
 * Typedef for unsigned long long int.
 *
 * 8 byte sized, values range from 0 to 18,446,744,073,709,551,615. This is
 * the equivalent of uint64_t from C99's stdint.h.
 */
typedef unsigned long long int BDGL_Uint64;

/**
 * Typedef for signed char.
 *
 * 1 byte sized, values range from −127 to 127. This is the equivalent of
 * int8_t from C99's stdint.h.
 */
typedef signed char BDGL_Int8;

/**
 * Typedef for signed short.
 *
 * 2 byte sized, values range from −32,767 to 32,767. This is the equivalent
 * of int16_t from C99's stdint.h.
 */
typedef signed short BDGL_Int16;

/**
 * Typedef for signed long int.
 *
 * 4 byte sized, values range from -2,147,483,648 to 2,147,483,647. This is
 * the equivalent of int32_t from C99's stdint.h.
 */
typedef signed long int BDGL_Int32;

/**
 * Typedef for signed long long int.
 *
 * 8 byte sized, values range from -9,223,372,036,854,775,808 to
 * 9,223,372,036,854,775,807. This is the equivalent of int64_t from C99's
 * stdint.h.
 */
typedef signed long long int BDGL_Int64;

/**
 * Primitive boolean type.
 */
typedef enum
{
  BDGL_FALSE = 0,
  BDGL_TRUE = 1
} BDGL_Bool;

#endif  /* _BDGL_TYPES_H_ */

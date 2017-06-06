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
#ifndef _BDGL_MACROS_H_
#define _BDGL_MACROS_H_

/**
 * Helper macro to get the number of elements in an array.
 *
 * BE CAREFUL! It doesn't work with pointers, and arrays passed as function
 * parameters are decayed as such.
 *
 * @param array     array with a constant size
 * @return          number of elements in array
 */
#define BDGL_ARRAY_LENGTH(array)         (sizeof((array)) / sizeof((array)[0]))

#define BDGL_MATH_SIGN(number)           ((0 < number) - (number < 0))

/* TODO */
#define BDGL_EXPECTS(predicate, message)  \
do                                        \
{                                         \
  if (predicate)                          \
  {                                       \
    fprintf(stderr, "%s\n", message);     \
  }                                       \
} while(0)                                \

/* TODO */
#define BDGL_ENSURES(predicate, message)

#endif  /* _BDGL_MACROS_H_ */

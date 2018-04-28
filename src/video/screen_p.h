/*
 * Copyright (c) 2016-2018 Balint Kiss <balint.kiss.501@gmail.com>
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
#ifndef _BDGL_SCREEN_P_H_
#define _BDGL_SCREEN_P_H_

#include <BDGL/core/core.h>

typedef struct BDGL_Screen
{
  BDGL_Uint8 mode;                  /**< Video mode */
  BDGL_Uint16 width;                /**< Width of screen resoulution */
  BDGL_Uint16 height;               /**< Height of screen resolution */
  BDGL_Uint16 color_number;         /**< Number of available colors */
  BDGL_Uint8 current_draw_color;    /**< Current drawing color */
  BDGL_Uint8 *vga_memory;           /**< Address of VGA memory */
  BDGL_Uint8 *buffer;               /**< Buffer address */
  BDGL_Uint8 flags;                 /**< Option flags */
} BDGL_Screen;

#endif

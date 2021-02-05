/*
 * Copyright (c) 2016 Balint Kiss <balintkissdev@gmail.com>
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
#include <BDGL/video/shapes.h>

#include <BDGL/video/screen.h>

#include "screen_p.h"

#include <dos.h>
#include <mem.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Check if x and y are within screen boundaries
 *
 * @param screen
 * @param x
 * @param y
 */
#define WITHIN_SCREEN_BOUNDS(screen, x, y) \
    ((-1 < (x)) && ((x) < (screen)->width) && (-1 < (y)) && ((screen)->height))

void BDGL_DrawPoint2D(
  BDGL_Screen *const screen,
  const int x,
  const int y)
{
  /* Makes sure doesn't wrap around screen */
  if (WITHIN_SCREEN_BOUNDS(screen, x, y))    
  {
    /* 320*y = 256*y + 64*y = (y << 8) + (y << 6) */
    screen->buffer[(y << 8) + (y << 6) + x] = screen->current_draw_color;

  }
}

void BDGL_DrawLine(
  BDGL_Screen *const screen, 
  const int x_start, 
  const int y_start,  
  const int x_end, 
  const int y_end)
{
  int delta_x = x_end - x_start;

  int delta_y = y_end - y_start;
  int delta_x_abs = abs(delta_x);
  int delta_y_abs = abs(delta_y);
  int delta_x_sign = BDGL_MATH_SIGN(delta_x);
  int delta_y_sign = BDGL_MATH_SIGN(delta_y);

  int x = delta_x_abs >> 1;
  int y = delta_y_abs >> 1;
  int pixel_x = x_start;
  int pixel_y = y_start;

  int i;

  BDGL_DrawPoint2D(screen, x_start, y_start);
  if (delta_x_abs >= delta_y_abs)
  {
    for (i = 0; i < delta_x_abs; ++i)
    {
      y += delta_y_abs;
      if (y >= delta_x_abs)
      {
        y -= delta_x_abs;
        pixel_y += delta_y_sign;
      }
      pixel_x += delta_x_sign;
      BDGL_DrawPoint2D(screen, pixel_x, pixel_y);
    }
  }
  else
  {
    for (i = 0; i < delta_y_abs; ++i)
    {
      x += delta_x_abs;
      if (x >= delta_y_abs)
      {
        x -= delta_y_abs;
        pixel_x += delta_x_sign;
      }
      pixel_y += delta_y_sign;
      BDGL_DrawPoint2D(screen, pixel_x, pixel_y);
    }
  }
}

/* FIXME: drawing outside of screen wraps around */
void BDGL_DrawRectangle(
  BDGL_Screen *const screen,
  const BDGL_Rectangle *const rectangle)
{
  BDGL_Uint16 top_offset;
  BDGL_Uint16 bottom_offset;

  int top = rectangle->y;
  int bottom = top + rectangle->height;
  int left = rectangle->x;
  int right = left + rectangle->width;

  int i;

  int tmp;
  if (top > bottom)
  {
    tmp = top;
    top = bottom;
    bottom = tmp;
  }
  if (left > right)
  {
    tmp = left;
    left = right;
    right = tmp;
  }

  top_offset = (top << 8) + (top << 6);
  bottom_offset = (bottom << 8) + (bottom << 6);

  for (i = left; i <= right; i++)
  {
    screen->buffer[top_offset + i] = screen->current_draw_color;
    screen->buffer[bottom_offset + i] = screen->current_draw_color;
  }

  for (i = top_offset; i <= bottom_offset; i += screen->width)
  {
    screen->buffer[left + i] = screen->current_draw_color;
    screen->buffer[right + i] = screen->current_draw_color;
  }
}

/*
 * FIXME: crashes
 * FIXME: drawing outside of screen wraps around
 */
void BDGL_DrawFilledRectangle(
  BDGL_Screen *const screen,
  const BDGL_Rectangle *const rectangle)
{
  BDGL_Uint16 top_offset;
  BDGL_Uint16 bottom_offset;

  int top = rectangle->y;
  int bottom = top + rectangle->height;
  int left = rectangle->x;
  int right = left + rectangle->width;

  BDGL_Uint16 tmp, width, i;

  if (top > bottom)
  {
    tmp = top;
    top = bottom;
    bottom = tmp;
  }
  if (left > right)
  {
    tmp = left;
    left = right;
    right = tmp;
  }

  top_offset = (top << 8) + (top << 6) + left;
  bottom_offset = (bottom << 8) + (bottom << 6) + left;

  width = right - left + 1;
  for (i = top_offset; i <= bottom_offset; i += screen->width)
  {
    memset(&screen->vga_memory[i], screen->current_draw_color, width);
  }
}

void BDGL_DrawPolygon2D(
  BDGL_Screen *const screen, 
  BDGL_Vertex2D const* vertices,
  const int vertex_number)
{
  int i;
  for (i = 0; i < vertex_number - 1; ++i)
  {
    BDGL_DrawLine(
      screen,
      vertices[i].x,
      vertices[i].y,
      vertices[i + 1].x,
      vertices[i + 1].y);
  }

  BDGL_DrawLine(
    screen,
    vertices[i].x,
    vertices[i].y,
    vertices[0].x,
    vertices[0].y);
}


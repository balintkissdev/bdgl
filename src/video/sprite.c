/*
 * Copyright (c) 2016 Balint Kiss <balint.kiss.501@gmail.com>
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
#include <BDGL/video/sprite.h>

#include <stdlib.h>

#define SPRITE_WIDTH    (24)
#define SPRITE_HEIGHT   (24)

void BDGL_GrabPCXBitmap(
    BDGL_PCXImage *const image,
    BDGL_Sprite *const sprite,
    const int sprite_frame,
    const int grab_x,
    const int grab_y)
{
  int x_offset, y_offset;
  int x, y;
  char *sprite_data = NULL;

  sprite->frames[sprite_frame] = (char*)malloc(SPRITE_WIDTH * SPRITE_HEIGHT);

  sprite_data = sprite->frames[sprite_frame];

  x_offset = 25*grab_x + 1;
  y_offset = 25*grab_y + 1;

  y_offset = y_offset*320;

  for (y = 0; y < SPRITE_HEIGHT; ++y)
  {
    for (x = 0; x < SPRITE_HEIGHT; ++x)
    {
      sprite_data[y*24 + x] = image->buffer[y_offset + x_offset + x];
    }

    y_offset += 320;
  }

  ++sprite->frame_number;
}

void BDGL_DrawSprite(BDGL_Screen *const screen, BDGL_Sprite *const sprite)
{
  char *work_sprite = NULL;
  int work_offset, offset;
  int x, y;
  BDGL_BYTE data;

  work_sprite = sprite->frames[sprite->current_frame];

  offset = (sprite->y << 8) + (sprite->y << 6) + sprite->x;

  for (y = 0; y < SPRITE_HEIGHT; ++y)
  {
    for (x = 0; x < SPRITE_WIDTH; ++x)
    {
      if ((data = work_sprite[work_offset + x]))
      {
        screen->buffer[offset + x] = data;
      }
    }

    offset += screen->width;
    work_offset += screen->width;
  }
}


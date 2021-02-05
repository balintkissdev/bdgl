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
#include <BDGL/video/screen.h>

#include "screen_p.h"

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <dos.h>
#include <mem.h>

/* VGA registers */
#define VGA_CRT_INPUT_STATUS_1           (0x03da)
#define VGA_PALETTE_INDEX                (0x03c8)
#define VGA_PALETTE_DATA                 (0x03c9)

/* VGA status */
#define VGA_STATUS_VRETRACE              (0x08)

/**
 * Set video mode. This operation is encapsulated.
 *
 * @param video_mode    identifier of video mode
 */
/* TODO: only observed working with text and 256 VGA mode */
static void BDGL_SetVideoMode(const BDGL_Uint8 video_mode);
#ifdef WATCOM
#pragma aux BDGL_SetVideoMode =  \
  "mov ah, 0"                 \
  "int 0x10"                  \
  parm [al];
#endif

/* 
 * TODO: currently only supports 256 VGA mode
 * FIXME: needs a better way to parse parameters rather than using
 *        switch-case
 */
BDGL_Screen* BDGL_CreateScreen(const BDGL_Uint8 video_mode)
{
  BDGL_Screen *screen = NULL;
  screen = malloc(sizeof *screen);
  if (!screen)
  {
    fprintf(stderr,
            "Fatal error: Not enough memory for screen data allocation.\n");
    exit(EXIT_FAILURE);
  }

  screen->mode = video_mode;
  switch (video_mode)
  {
    case BDGL_MODE_VGA_320x200_256_COLOR:
      screen->width = 320;
      screen->height = 200;
      screen->color_number = 256;
      screen->current_draw_color = 0;
      screen->flags = 0x00;

      screen->vga_memory = (BDGL_Uint8 *)MK_FP(BDGL_ADDRESS_VGA,0);
      screen->buffer = screen->vga_memory;
      break;

    default:
      free(screen);
      fprintf(stderr,
              "Sorry, video mode 0x%08x is not supported.\n",
              video_mode);
      return NULL;
  }
  return screen;
}

void BDGL_DestroyScreen(BDGL_Screen *const screen)
{
  if (screen)
  {
    BDGL_SetVideoMode(BDGL_MODE_TEXT_640x200_16_COLOR);
    if (screen->flags & BDGL_SCREEN_DOUBLE_BUFFER)
    {
      free(screen->buffer);
    }
    free(screen);
  }
}

void BDGL_EnableScreenOption(BDGL_Screen *const screen, const BDGL_Uint8 flags)
{
  screen->flags |= flags;

  if (flags & BDGL_SCREEN_DOUBLE_BUFFER)
  {
    screen->buffer = NULL;
    screen->buffer = calloc(screen->width * screen->height, 1);
    if (!screen->buffer)
    {
      BDGL_DestroyScreen(screen);
      fprintf(stderr,
            "Fatal error: Not enough memory for double buffer allocation.\n");
      exit(EXIT_FAILURE);
    }
  }
}

void BDGL_DisableScreenOption(
  BDGL_Screen *const screen,
  const BDGL_Uint8 flags)
{
  screen->flags &= flags;

  if (flags & BDGL_SCREEN_DOUBLE_BUFFER)
  {
    free(screen->buffer);
    screen->buffer = screen->vga_memory;
  }
}

void BDGL_InitializeVideo(BDGL_Screen *const screen)
{
  BDGL_SetVideoMode(screen->mode);
}

void BDGL_ClearScreen(BDGL_Screen *const screen)
{
  memset(screen->buffer, 0, screen->width * screen->height);
}

void BDGL_UpdateScreen(BDGL_Screen *const screen)
{
  /* Wait for vertical retrace if enabled */
  if (screen->flags & BDGL_SCREEN_VSYNC)
  {
    while (inp(VGA_CRT_INPUT_STATUS_1) & VGA_STATUS_VRETRACE);
    while (!inp(VGA_CRT_INPUT_STATUS_1) & VGA_STATUS_VRETRACE);
  }

  /* Flip double buffer if enabled */
  if (screen->flags & BDGL_SCREEN_DOUBLE_BUFFER)
  {
    memcpy(screen->vga_memory, screen->buffer, screen->width * screen->height);
  }
}

void BDGL_SetDrawColor(BDGL_Screen *const screen, const BDGL_Uint8 color)
{
  screen->current_draw_color = color;
}

void BDGL_ModifyPaletteColor(const BDGL_Uint8 palette_index,
  const BDGL_Uint8 red63,
  const BDGL_Uint8 green63,
  const BDGL_Uint8 blue63)
{
  outp(VGA_PALETTE_INDEX, palette_index);
  outp(VGA_PALETTE_DATA, red63);
  outp(VGA_PALETTE_DATA, green63);
  outp(VGA_PALETTE_DATA, blue63);
}

BDGL_Uint16 BDGL_GetScreenWidth(const BDGL_Screen *const screen)
{
  return screen->width;
}

BDGL_Uint16 BDGL_GetScreenHeight(const BDGL_Screen *const screen)
{
  return screen->height;
}

BDGL_Uint16 BDGL_GetScreenColorNumber(const BDGL_Screen *const screen)
{
  return screen->color_number;
}

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
#ifndef _BDGL_SCREEN_H_
#define _BDGL_SCREEN_H_

#include <BDGL/core/core.h>

#ifdef __cplusplus
extern "C" {
#endif

/* TODO: implement CGA, TGA, EGA and SVGA modes */
/** 
 * @addtogroup DOS Video Modes
 * Options for DOS video modes
 * @{
 */

/* Text display modes */

/**
 * 320x200 black and white text mode.
 */
#define BDGL_MODE_TEXT_320x200_16_GREY      (0x00)

/**
 * 320x200 16 color text mode.
 */
#define BDGL_MODE_TEXT_320x200_16_COLOR     (0x01)

/**
 * 640x200 16 shades of grey text mode.
 */
#define BDGL_MODE_TEXT_640x200_16_GREY      (0x02)

/**
 * 640x200 16-bit color text mode.
 */
#define BDGL_MODE_TEXT_640x200_16_COLOR     (0x03)

/**
 * 720x350 monochrome text mode.
 */
#define BDGL_MODE_TEXT_720x350_MONO         (0x07)

/**
 * 1056x200 16 color text mode.
 */
#define BDGL_MODE_TEXT_1056x200_16_COLOR    (0x08)

/* CGA display modes */

/**
 * 320x200 4 color CGA mode.
 */
#define BDGL_MODE_CGA_320x200_4_COLOR       (0x04)

/**
 * 320x200 monochrome CGA mode.
 */
#define BDGL_MODE_CGA_320x200_MONO          (0x05)

/**
 * 640x200 monochrome CGA mode.
 */
#define BDGL_MODE_CGA_640x200_MONO          (0x06)

/* Tandy display modes */

/**
 * 320x200 16 color Tandy mode.
 */
#define BDGL_MODE_TGA_320x200_16_COLOR      (0x09)

/**
 * 640x200 4 color Tandy mode.
 */
#define BDGL_MODE_TGA_640x200_4_COLOR       (0x0A)

/* EGA display modes */

/**
 * 320x200 16 color EGA mode.
 */
#define BDGL_MODE_EGA_320x200_16_COLOR      (0x0D)

/**
 * 640x200 16 color EGA mode.
 */
#define BDGL_MODE_EGA_640x200_16_COLOR      (0x0E)

/**
 * 640x350 monochrome EGA mode.
 */
#define BDGL_MODE_EGA_640x350_MONO          (0x0F)

/**
 * 640x350 4 color EGA mode.
 */
#define BDGL_MODE_EGA_640x350_4_COLOR       (0x10)

/* VGA display modes */

/**
 * 640x480 monochrome VGA mode.
 */
#define BDGL_MODE_VGA_640x480_MONO          (0x11)

/**
 * 640x480 16 color VGA mode.
 */
#define BDGL_MODE_VGA_640x480_16_COLOR      (0x12)

/**
 * 640x480 256 color VGA mode.
 */
#define BDGL_MODE_VGA_320x200_256_COLOR     (0x13)

/* SVGA display modes */

/**
 * 640x400 256 color SVGA mode.
 */
#define BDGL_MODE_SVGA_640x400_256_COLOR    (0x100)

/**
 * 640x480 256 color SVGA mode.
 */
#define BDGL_MODE_SVGA_640x480_256_COLOR    (0x101)

/**
 * 640x480 16 color SVGA mode.
 */
#define BDGL_MODE_SVGA_800x600_16_COLOR     (0x102)

/**
 * 800x600 256 color SVGA mode.
 */
#define BDGL_MODE_SVGA_800x600_256_COLOR    (0x103)

/**
 * 1024x768 16 color SVGA mode.
 */
#define BDGL_MODE_SVGA_1024x768_16_COLOR    (0x104)

/**
 * 1024x768 256 color SVGA mode.
 */
#define BDGL_MODE_SVGA_1024x768_256_COLOR   (0x105)

/**
 * 1280x1024 16 color SVGA mode.
 */
#define BDGL_MODE_SVGA_1280x1024_16_COLOR   (0x106)

/**
 * 1280x1024 256 color SVGA mode.
 */
#define BDGL_MODE_SVGA_1280x1024_256_COLOR  (0x107)
/** @} */

/* First 16 colors */
#define BDGL_BLACK          (0x00)  /**< Black color. */
#define BDGL_BLUE           (0x01)  /**< Blue color. */
#define BDGL_GREEN          (0x02)  /**< Green color. */
#define BDGL_CYAN           (0x03)  /**< Cyan color. */
#define BDGL_RED            (0x04)  /**< Red color. */
#define BDGL_MAGENTA        (0x05)  /**< Magenta color. */
#define BDGL_BROWN          (0x06)  /**< Brown color. */
#define BDGL_LIGHT_GRAY     (0x07)  /**< Light gray color. */
#define BDGL_DARK_GRAY      (0x08)  /**< Dark gray color. */
#define BDGL_LIGHT_BLUE     (0x09)  /**< Light blue color. */
#define BDGL_LIGHT_GREEN    (0x0A)  /**< Light green color. */
#define BDGL_LIGHT_CYAN     (0x0B)  /**< Light cyan color. */
#define BDGL_LIGHT_RED      (0x0C)  /**< Light red color. */
#define BDGL_LIGHT_MAGENTA  (0x0D)  /**< Light magenta color. */
#define BDGL_YELLOW         (0x0E)  /**< Yellow color. */
#define BDGL_WHITE          (0x0F)  /**< White color. */

/* Screen option flags */

/**
 * Vertical retrace (VSync) option flag.
 */
#define BDGL_SCREEN_VSYNC            (0x01)

/**
 * Double buffering option flag.
 */
#define BDGL_SCREEN_DOUBLE_BUFFER    (0x02)

/* TODO */
#if 0
/**
 * Page flipping option flag.
 */
#define BDGL_SCREEN_PAGE_FLIPPING  (0x03)
#endif

/**
 * Data structure of the screen
 */
typedef struct BDGL_Screen BDGL_Screen;

/**
 * Create screen and allocate memory resource for it's properties, like
 * screen dimensions, number of color and the address of the VGA memory,
 * depending on the chosen video mode.
 *
 * Make sure you free the screen with "BDGL_DestroyScreen" at the end of
 * your program.
 *
 * @param video_mode        identifier for the video mode, for example 
 *                          "BDGL_MODE_VGA_320x200_256_COLOR" for 256 VGA mode.
 *
 * @return              pointer to allocated screen resources
 */
BDGL_Screen* BDGL_CreateScreen(const BDGL_Uint8 video_mode);

/**
 * Free screen resources. This also nullifies the pointer pointing to it
 * and switches back to text mode.
 *
 * @param screen            screen pointer to deallocate memory resource from
 */
void BDGL_DestroyScreen(BDGL_Screen *const screen);

/**
 * Enable display options, like vertical sync or double buffering.
 *
 * The following values can be set:
 *
 * BDGL_SCREEN_VSYNC:           Enable wait for vertical retrace (VSync)
 * BDGL_SCREEN_DOUBLE_BUFFER:   Enable double buffering
 *
 * These flags can be chained together, for example
 *
 * BDGL_SCREEN_VSYNC | BDGL_SCREEN_DOUBLE_BUFFER
 *
 * @param flags             bit flags to customize screen properties.
 */
void BDGL_EnableScreenOption(
  BDGL_Screen *const screen,
  const BDGL_Uint8 flags);

/**
 * Disable display options, like vertical sync or double buffering.
 *
 * The following values can be set:
 *
 * BDGL_SCREEN_VSYNC:           Disable wait for vertical retrace (VSync)
 * BDGL_SCREEN_DOUBLE_BUFFER:   Disable double buffering
 *
 * These flags can be chained together, for example
 *
 * BDGL_SCREEN_VSYNC | BDGL_SCREEN_DOUBLE_BUFFER
 *
 * @param flags             bit flags to customize screen properties.
 */
void BDGL_DisableScreenOption(
  BDGL_Screen *const screen,
  const BDGL_Uint8 flags);

/**
 * Switch to the specified video mode of the screen.
 *
 * @param screen            screen pointer to switch video modes to
 */
void BDGL_InitializeVideo(BDGL_Screen *const screen);

/**
 * Clear screen to draw again.
 *
 * @param screen            screen pointer to be cleared
 */
void BDGL_ClearScreen(BDGL_Screen *const screen);

/**
 * Update screen with double buffering.
 *
 * Until this call, every pixel is written into
 * a temporary buffer before displaying.
 * This also includes waiting for vertical retrace (VSync)
 *
 * @param                   screen to update
 */
void BDGL_UpdateScreen(BDGL_Screen *const screen);

/**
 * Set drawing color to draw primitives with.
 *
 * @param screen            screen to set color of
 * @param color             drawing color between 0 and 255
 */
void BDGL_SetDrawColor(BDGL_Screen *const screen, const BDGL_Uint8 color);

/**
 * Modify value of color found in VGA palette.
 *
 * Good if you want to implement screen filtering effects or
 * want to define custom colors for yourself, however, 
 * you overwrite the default 256 color palette with this.
 *
 * This only works AFTER the screen is already initialized and displayed.
 *
 * @param screen            screen to set palette of
 * @param palette_index     index of the color in the default palette to modify
 * @param red63             red component of RGB between 0 and 63
 * @param green63           green component of RGB between 0 and 63
 * @param blue63            blue component of RGB between 0 and 63
 */
void BDGL_ModifyPaletteColor(
  const BDGL_Uint8 palette_index,
  const BDGL_Uint8 red63,
  const BDGL_Uint8 green63,
  const BDGL_Uint8 blue63);

BDGL_Uint16 BDGL_GetScreenWidth(const BDGL_Screen *const screen);

BDGL_Uint16 BDGL_GetScreenHeight(const BDGL_Screen *const screen);

BDGL_Uint16 BDGL_GetScreenColorNumber(const BDGL_Screen *const screen);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  /* _BDGL_SCREEN_H_ */

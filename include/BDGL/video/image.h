/*
 * Copyright (c) 2016-2017 Bálint Kiss <balintkissdev@gmail.com>
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

/* 
 * TODO: color masking
 * TODO: generalize image drawing instead of having separate PCX and BMP
 *       images
 */
/**
 * @file image.h
 */
#ifndef _BDGL_IMAGE_H_
#define _BDGL_IMAGE_H_

#include <BDGL/core/core.h>
#include <BDGL/video/screen.h>

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Data structure representing image color in RGB format.
 */
typedef struct BDGL_RGBColor
{
  BDGL_Uint8 red;   /**< Red component of RGB */
  BDGL_Uint8 green; /**< Green component of RGB */
  BDGL_Uint8 blue;  /**< Blue component of RGB */
} BDGL_RGBColor;

#if 0
typedef struct BDGL_PCXHeader
{
  char manufacturer;
  char version;
  char encoding;
  char bits_per_pixel;
  int x, y;
  int width, height;
  int horizontal_resolution;
  int vertical_resolution;
  char ega_palette[48];
  char reserved;
  char color_plane_number;
  int bytes_per_line;
  int palette_type;
  char padding[58];
} BDGL_PCXHeader;

typedef struct BDGL_PCXImage
{
  BDGL_PCXHeader header;
  BDGL_RGBColor palette[256];
  char *buffer;
} BDGL_PCXImage;
#endif

/**
 * Data structure representing image in BMP format.
 */
typedef struct BDGL_BMPImage
{
  BDGL_Uint16 width;          /**< Width of image   */
  BDGL_Uint16 height;         /**< Height of image  */
  BDGL_Uint8 palette[256*3];  /**< Color palette     */
  BDGL_Uint8 *pixels;         /**< Array of pixels  */
} BDGL_BMPImage;

#if 0
/**
 * Create image from PCX file.
 *
 * @param filepath
 * @return
 */
BDGL_PCXImage* BDGL_LoadPCXNo prototype found for function(
  BDGL_Screen *const screen,
  const char *filepath,
  const int enable_palette);
#endif

/**
 * Create image from BMP file.
 *
 * @param screen              screen to destroy when BMP image loading fails         
 * @param filepath            file path of BMP file      
 * @return
 */
BDGL_BMPImage BDGL_LoadBMP(BDGL_Screen *const screen, const char *filepath);

/**
 * Draw BMP image.
 *
 * @param screen              screen to draw BMP image onto
 * @param image               BMP image to draw
 * @param x                   x coordinate to draw image
 * @param y                   y coordinate to draw image
 */
void BDGL_DrawBMPImage(
    BDGL_Screen *const screen,
    BDGL_BMPImage *const image,
    const int x,
    const int y);

#if 0
/**
 * Free PCX image resources.
 *
 * @param image
 */
void BDGL_DestroyPCXImage(BDGL_PCXImage *const image);
#endif

/**
 * Free BMP image resources.
 *
 * @param image               BMP image resource to free
 */
void BDGL_DestroyBMPImage(BDGL_BMPImage *const image);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  /* _BDGL_IMAGE_H_ */

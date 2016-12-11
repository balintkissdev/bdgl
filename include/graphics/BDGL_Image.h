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

/* TODO: color masking */
/* TODO: generalize image drawing instead of having separate PCX and BMP images */
/**
 * @file BDGL_Image.h
 */
#ifndef BDGL_IMAGE_H_
#define BDGL_IMAGE_H_

#include "../core/BDGL_Core.h"

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct BDGL_Screen BDGL_Screen;

#if 0
typedef struct BDGL_RGBColor
{
  BDGL_BYTE red, green, blue;
} BDGL_RGBColor;

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

typedef struct BDGL_BMPImage
{
  BDGL_WORD width;          /**< Width of image   */
  BDGL_WORD height;         /**< Height of image  */
  BDGL_BYTE palette[256*3]; /** Color palette     */
  BDGL_BYTE *pixels;        /**< Array of pixels  */
} BDGL_BMPImage;

#if 0
/**
 * Create image from PCX file.
 *
 * @param filepath
 * @return
 */
BDGL_PCXImage* BDGL_LoadPCX(BDGL_Screen *const screen, const char *filepath, const int enable_palette);
#endif

/**
 * Load BMP image
 *
 * @param screen
 * @param filepath
 * @return
 */
BDGL_BMPImage BDGL_LoadBMP(BDGL_Screen *const screen, const char *filepath);

/**
 * Draw BMP image
 *
 * @param screen
 * @param image
 * @param x
 * @param y
 */
void BDGL_DrawBMPImage(
    BDGL_Screen *const screen,
    BDGL_BMPImage *const image,
    const int x,
    const int y);

/* HACK */
void BDGL_BMPskip(FILE *fp, int byte_number);

/**
 * Free image resources.
 *
 * @param image
 */
//void BDGL_DestroyPCXImage(BDGL_PCXImage *const image);

/**
 * Free BMP image resources.
 *
 * @param image
 */
void BDGL_DestroyBMPImage(BDGL_BMPImage *const image);

#ifdef __cplusplus
}
#endif

#endif  // BDGL_IMAGE_H_

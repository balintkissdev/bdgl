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
#include <graphics/BDGL_Image.h>

#include <graphics/BDGL_Video.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dos.h>

#if 0
/* TODO: this was rushed, tidy code */
BDGL_PCXImage* BDGL_LoadPCX(BDGL_Screen *const screen, const char *filepath, const int enable_palette)
{
  FILE *fp = NULL;
  int byte_number, index;
  long count;
  BDGL_BYTE data;
  BDGL_PCXImage *image = NULL;
  char *tmp_buffer = NULL;

  fp = fopen(filepath, "rb");

  /* Load PCX header */
  tmp_buffer = (char*)image;
  for (index = 0; index < 128; ++index)
  {
    tmp_buffer[index] = getc(fp);
  }

  /* Load data and decompress RLE */
  count = 0;
  while (count <= screen->width * screen->height)
  {
    data = getc(fp);

    /* Is this an RLE? */
    if (data >= 192 && data <= 255)
    {
      byte_number = data - 192; /* How many bytes in the run? */
      data = getc(fp);          /* Get actual data for the run */

      while (byte_number > 0)
      {
        image->buffer[count++] = data;
      }
    }
    else
    {
      image->buffer[count++] = data;
    }
  }

  /* Palette */
  fseek(fp, -768, SEEK_END);
  for (index = 0; index < 256; ++index)
  {
    image->palette[index].red = (getc(fp) >> 2);
    image->palette[index].green = (getc(fp) >> 2);
    image->palette[index].blue = (getc(fp) >> 2);
  }

  fclose(fp);

  if (enable_palette)
  {
    for (index = 0; index < 256; +index)
    {
      BDGL_RGBColor color = image->palette[index];
      BDGL_ModifyPaletteColor(index, color.red, color.green, color.blue);
    }
  }

  return image;
}
#endif

/* TODO: remove this */
void BDGL_BMPskip(FILE *fp, int byte_number)
{
  int i;
  for (i = 0; i < byte_number; ++i)
  {
    fgetc(fp);
  }
}

BDGL_BMPImage BDGL_LoadBMP(BDGL_Screen *const screen, const char *filepath)
{
  FILE *fp;
  long i;
  BDGL_WORD color_number;
  int x;
  BDGL_BMPImage bmp;

  if (NULL == (fp = fopen(filepath, "rb")))
  {
    BDGL_DestroyScreen(screen);
    fprintf(stderr, "Error opening BMP file %s.\n", filepath);
    exit(1);
  }

  if (fgetc(fp) != 'B' || fgetc(fp) != 'M')
  {
    fclose(fp);
    BDGL_DestroyScreen(screen);
    fprintf(stderr, "File is not a BMP file.\n");
    exit(1);
  }

  BDGL_BMPskip(fp, 16);
  fread(&bmp.width, sizeof(BDGL_WORD), 1, fp);
  BDGL_BMPskip(fp, 2);
  fread(&bmp.height, sizeof(BDGL_WORD), 1, fp);
  BDGL_BMPskip(fp, 22);
  fread(&color_number, sizeof(BDGL_WORD), 1, fp);
  BDGL_BMPskip(fp, 6);

  if (color_number == 0)
  {
    color_number = 256;
  }

  /* Allocate memory */
  if (NULL == (bmp.pixels = malloc((BDGL_WORD)(bmp.width*bmp.height))))
  {
    fclose(fp);
    fprintf(stderr, "Error allocating memory for BMP image.\n");
    exit(1);
  }

#if 0
  /* Read palette information */
  for (i = 0; i < color_number; ++i)
  {
    bmp.palette[(int)(i*3 + 2)] = fgetc(fp) >> 2;
    bmp.palette[(int)(i*3 + 1)] = fgetc(fp) >> 2;
    bmp.palette[(int)(i*3 + 0)] = fgetc(fp) >> 2;
    x = fgetc(fp);
  }
#endif
  BDGL_BMPskip(fp, color_number*4);

  /* Read bitmap */
  for (i = (bmp.height - 1)*bmp.width; i >= 0; i -= bmp.width)
  {
    for (x = 0; x < bmp.width; ++x)
    {
      bmp.pixels[(BDGL_WORD)i + x] = (BDGL_BYTE)fgetc(fp);
    }
  }

  fclose(fp);

  /* FIXME: doesn't work */
  /* Set palette */
#if 0
  outp(0x03c8, 0);
  for (i = 0; i < 256*3; ++i)
  {
    outp(0x03c9, bmp.palette[i]);
  }
#endif

  return bmp;
}

/* FIXME: doesn't work on BMPs made on modern Windows */
void BDGL_DrawBMPImage(
    BDGL_Screen *const screen, 
    BDGL_BMPImage *const image,
    const int x,
    const int y)
{
  int j;
  BDGL_WORD screen_offset = (y << 8) + (y << 6) + x;
  BDGL_WORD bmp_offset = 0;

  for (j = 0; j < image->height; ++j)
  {
    memcpy(&screen->buffer[screen_offset], &image->pixels[bmp_offset], image->width);

    bmp_offset += image->width;
    screen_offset += screen->width;
  }
}

#if 0
void BDGL_DestroyPCXImage(BDGL_PCXImage *const image)
{
  if (image)
  {
    free(image->buffer);
    free(image);
  }
}
#endif

void BDGL_DestroyBMPImage(BDGL_BMPImage *const image)
{
  if (image)
  {
    free(image->pixels);
    /*free(image);*/
  }
}

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

/*
 * This examples is based on the tutorials by David Brackeen.
 *
 * http://www.brackeen.com/vga/
 */
#include <BDGL/BDGL.h>

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
  int x, y;                           /* Variables for points */
  int x1, y1, x2, y2;                 /* Variables for lines */
  BDGL_Uint16 i;                      /* Loop variable */

  BDGL_Rectangle rect;                /* Rectangle */

  BDGL_Vertex2D vertices[3] = {       /* Vertices */
    {0,0},
    {7,5},
    {0,5}
  };

  BDGL_Uint16 screen_width, screen_height, screen_color_number;

  /* Create screen */
  BDGL_Screen *screen = BDGL_CreateScreen(BDGL_MODE_VGA_320x200_256_COLOR);
  if (!screen)
  {
    fprintf(stderr, "There was an error when creating screen.\n");
    return 1;
  }

  /* Initialize and display screen */
  BDGL_InitializeVideo(screen);
  screen_width = BDGL_GetScreenWidth(screen);
  screen_height = BDGL_GetScreenHeight(screen);
  screen_color_number = BDGL_GetScreenColorNumber(screen);

  /* Draw single pixels */
  BDGL_SetDrawColor(screen, BDGL_CYAN);
  BDGL_DrawPoint2D(screen, 0, 0);
  BDGL_SetDrawColor(screen, BDGL_WHITE);
  BDGL_DrawPoint2D(screen, 0, 1);
  BDGL_SetDrawColor(screen, BDGL_CYAN);
  BDGL_DrawPoint2D(screen, 0, 2);
  BDGL_DrawPoint2D(screen, 0, 3);
  BDGL_DrawPoint2D(screen, 0, 4);
  BDGL_DrawPoint2D(screen, 0, 0);
  BDGL_DrawPoint2D(screen, 7, 5);
  BDGL_DrawPoint2D(screen, 0, 5);
  BDGL_SetDrawColor(screen, BDGL_RED);
  BDGL_DrawPoint2D(screen, -20, -10);    /* Test for drawing outside screen  */
  BDGL_UpdateScreen(screen);
  delay(4000);
  BDGL_ClearScreen(screen);

  /* Draw points */
  for(i = 0; i < 50000L; ++i)
  {
    x = rand() % screen_width;
    y = rand() % screen_height;
    BDGL_SetDrawColor(screen, rand() % screen_color_number);
    BDGL_DrawPoint2D(screen, x, y);
    BDGL_UpdateScreen(screen);
  }
  BDGL_ClearScreen(screen);

  /* Draw lines */
  for (i = 0; i < 5000; ++i)
  {
    x1 = rand() % screen_width;
    y1 = rand() % screen_height;
    x2 = rand() % screen_width;
    y2 = rand() % screen_height;

    BDGL_SetDrawColor(screen, rand() % screen_color_number);
    BDGL_DrawLine(screen, x1, y1, x2, y2);
    BDGL_UpdateScreen(screen);
  }
  BDGL_ClearScreen(screen);

  /* Draw rectangles */
  for (i = 0; i < 5000; ++i)
  {
    rect.x = rand() % screen_width;
    rect.y = rand() % screen_height;
    rect.width = rand() % screen_width;
    rect.height = rand() % screen_height;

    BDGL_SetDrawColor(screen, rand() % screen_color_number);
    BDGL_DrawRectangle(screen, &rect);
    BDGL_UpdateScreen(screen);
  }
  BDGL_ClearScreen(screen);

  /* FIXME: crashes */
#if 0
  /* Draw filled rectangles */
  for (i = 0; i < 5000; i++)
  {
    rect.x = rand() % screen->width;
    rect.y = rand() % screen->height;
    rect.width = rand() % screen->width;
    rect.height = rand() % screen->height;
    color = rand() % screen->color_number;

    BDGL_DrawFilledRectangle(screen, &rect, color);
  }
  BDGL_ClearScreen(screen);
#endif

  /* Draw polygon */
  BDGL_SetDrawColor(screen, BDGL_LIGHT_BLUE);
  BDGL_DrawPolygon2D(screen, vertices, BDGL_ARRAY_LENGTH(vertices));
  BDGL_UpdateScreen(screen);
  delay(4000);

  /* Free screen resources */
  BDGL_DestroyScreen(screen);

  printf("Done\n");
  return 0;
}

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
#include <BDGL/BDGL.h>

#include <stdio.h>

/*
 * FIXME: Originally wanted a small paint program, but performance was really
 *        slow. Needs profiling and code fixing in mouse functions.
 */
int main(int argc, char *argv[])
{
  BDGL_Bool running = BDGL_TRUE;
  BDGL_KeyEvent event;
  int mouse_x = 0;
  int mouse_y = 0;
  BDGL_Uint8 cursor_color = BDGL_WHITE;
  BDGL_Screen *screen = NULL;

  BDGL_InitializeSystem();

  screen = BDGL_CreateScreen(BDGL_MODE_VGA_320x200_256_COLOR);
  if (!screen)
  {
    fprintf(stderr, "There was an error when creating screen.\n");
    return 1;
  }
  BDGL_EnableScreenOption(screen, BDGL_SCREEN_VSYNC | BDGL_SCREEN_DOUBLE_BUFFER);
  BDGL_InitializeVideo(screen);
  BDGL_InitializeMouse();

  /* Loop until ESC key on keyboard is pressed */
  while (running)
  {
    /* Event handling */
    if (BDGL_PollKeyboard(&event))
    {
      running = BDGL_FALSE;
      break;
    }

    BDGL_GetMouseAbsPos(&mouse_x, &mouse_y);

    /* Logic update */
    if (BDGL_MOUSE_LEFT == BDGL_GetMouseButton())
    {
      cursor_color = BDGL_CYAN;
    }
    else if (BDGL_MOUSE_RIGHT == BDGL_GetMouseButton())
    {
      cursor_color = BDGL_WHITE;
    }

    /* Rendering */
    BDGL_ClearScreen(screen);

    BDGL_SetDrawColor(screen, cursor_color);
    BDGL_DrawPoint2D(screen, mouse_x, mouse_y);

    BDGL_UpdateScreen(screen);
  }

  /* Free screen resources */
  BDGL_DestroyScreen(screen);
  BDGL_CleanupSystem();

  printf("Done\n");
  return 0;
}

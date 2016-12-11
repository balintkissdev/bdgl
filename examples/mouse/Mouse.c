#include <BDGL.h>

#include <stdio.h>

/*  FIXME: Originally wanted a small paint program, but performance was really slow.
 *         Needs profiling and code fixing in mouse functions.
 */

int main(int argc, char *argv[])
{
  int mouse_x = 0;
  int mouse_y = 0;
  BDGL_BYTE key = 0;
  BDGL_BYTE cursor_color = BDGL_WHITE;
  BDGL_Screen *screen = NULL;

  /* Initialize screen   */
  screen = BDGL_CreateScreen(BDGL_MODE_VGA_320x200_256_COLOR);
  if (!screen)
  {
    fprintf(stderr, "There was an error when creating screen.\n");
    return 1;
  }
  BDGL_EnableScreenOption(screen, BDGL_SCREEN_VSYNC | BDGL_SCREEN_DOUBLE_BUFFER);
  BDGL_InitializeVideo(screen);

  /* Initialize mouse */
  BDGL_InitializeMouse();

  /* Loop until ESC key on keyboard is pressed  */
  while (key != BDGL_SCAN_ESC)
  {
    /* Event handling */
    key = BDGL_GetScancode();
    BDGL_MouseAbsPos(&mouse_x, &mouse_y);

    /* Logic update */
    if (BDGL_MOUSE_LEFT == BDGL_MouseButton())
    {
      cursor_color = BDGL_CYAN;
    }
    else if (BDGL_MOUSE_RIGHT == BDGL_MouseButton())
    {
      cursor_color = BDGL_WHITE;
    }

    /* Rendering */
    BDGL_ClearScreen(screen);

    BDGL_SetDrawColor(screen, cursor_color);
    BDGL_DrawPoint(screen, mouse_x, mouse_y);
    
    BDGL_UpdateScreen(screen);
  }

  /* Free screen resources    */
  BDGL_DestroyScreen(screen);

  printf("Done\n");
  return 0;
}

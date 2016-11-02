/**
 * Origin of example is from
 * http://www.flipcode.com/archives/The_Art_of_Demomaking-Issue_02_Introduction_To_Computer_Graphics.shtml
 */
// TODO: Tidy code
#include <BDGL.H>

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define STAR_NUMBER         (256)     /* Number of stars */
#define STAR_BASE_SPEED     (0.7f)    /* Base star speed */
#define SHIP_SPEED          (2.0f)    /* Ship speed      */

/* Star */
typedef struct Star
{
  float x, y;         /* Star position                                */
  BDGL_BYTE plane;    /* Number of planes, which define star speed    */
} Star;

/* Spaceship */
typedef struct Spaceship
{
  float x, y;
} Spaceship;

/* Globals on heap memory */
Star stars[STAR_NUMBER];
Spaceship player;

int main(int argc, char *argv[])
{
  /* Variable declaration. Putting local variables here is 
   * how it only compiles under DOS.                          */
  int i;
  BDGL_BYTE key = 0;

  BDGL_Rectangle player_rect;

  /* Create screen, enable VSync and double buffering   */
  BDGL_Screen *screen = BDGL_CreateScreen(BDGL_MODE_VGA_320x200_256_COLOR);
  if (!screen)
  {
    fprintf(stderr, "There was an error when creating screen.\n");
    return 1;
  }
  BDGL_EnableScreenOption(screen, BDGL_SCREEN_VSYNC | BDGL_SCREEN_DOUBLE_BUFFER);
  
  player.x = 100;
  player.y = 100;
  player_rect.x = player.x;
  player_rect.y = player.y;
  player_rect.width = 10;
  player_rect.height = 5;

  /* Initialize starfield             */
  for (i = 0; i < STAR_NUMBER; ++i)
  {
    stars[i].x = rand() % screen->width;
    stars[i].y = rand() % screen->height;
    stars[i].plane = rand() % 3;
  }

  /* Initialize and display screen            */
  BDGL_InitializeVideo(screen);

  /* Set the colors of stars by modifying the palette */
  BDGL_ModifyPaletteColor(1, 24, 24, 24);     /* dark grey  */
  BDGL_ModifyPaletteColor(2, 48, 48, 48);     /* light grey */
  BDGL_ModifyPaletteColor(3, 63, 63, 63);     /* white      */

  /* Loop until a key on keyboard is pressed  */
  while (key != BDGL_SCAN_ESC)
  {
    key = BDGL_GetScancode();
    if (key == BDGL_SCAN_UP)
    {
      player.y -= SHIP_SPEED;
    }
    else if (key == BDGL_SCAN_DOWN)
    {
      player.y += SHIP_SPEED;
    }
    if (key == BDGL_SCAN_LEFT)
    {
      player.x -= SHIP_SPEED;
    }
    else if (key == BDGL_SCAN_RIGHT)
    {
      player.x += SHIP_SPEED;
    }

    /* Clear screen to blank    */
    BDGL_ClearScreen(screen);

    /* For each star...         */
    for (i = 0; i < STAR_NUMBER; ++i)
    {
      /* Move current star forward from left to right */
      stars[i].x -= (1 + (float)stars[i].plane) * STAR_BASE_SPEED;

      /* Reset current star if it left the screen     */
      if (stars[i].x < 0)
      {
          stars[i].x = screen->width;
          stars[i].y = rand() % screen->height;
      }

      /* Draw current star    */
      BDGL_SetDrawColor(screen, stars[i].plane + 1);      /* Now custom color is used from the palette */
      BDGL_DrawPoint(screen, stars[i].x, stars[i].y);
    }

    /* Draw space ship */
    BDGL_SetDrawColor(screen, BDGL_RED);
    player_rect.x = player.x;
    player_rect.y = player.y;
    BDGL_DrawRectangle(screen, &player_rect);

    /* Refresh screen   */
    BDGL_UpdateScreen(screen);
  }

  /* Free screen resources    */
  BDGL_DestroyScreen(screen);

  printf("Done\n");
  return 0;
}

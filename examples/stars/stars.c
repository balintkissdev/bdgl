/*
 * Copyright (c) 2016-2017 Bálint Kiss <balint.kiss.501@gmail.com>
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
 * Origin of example is from
 * http://www.flipcode.com/archives/
 * The_Art_of_Demomaking-Issue_02_Introduction_To_Computer_Graphics.shtml
 */
#include <BDGL/BDGL.h>

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

/* Types */

/* Star */
typedef struct Star
{
  float x, y;         /* Star position */
  BDGL_Uint8 plane;   /* Number of planes, which define star speed */
} Star;

/* Spaceship */
typedef struct Spaceship
{
  BDGL_Rectangle rect;
} Spaceship;

/* Global constants */
#define STAR_NUMBER         (256)     /* Number of stars */
#define STAR_BASE_SPEED     (0.7f)    /* Base star speed */
#define SHIP_SPEED          (2.0f)    /* Ship speed */

/* Globals variables */
int screen_width, screen_height;

BDGL_Bool running;

BDGL_Screen *screen = NULL;

Star stars[STAR_NUMBER];
Spaceship player;

/* Function prototypes */
void initialize();
void update();
void display();
void cleanup();

int main(int argc, char *argv[])
{
  initialize();

  /* Loop until a key on keyboard is pressed */
  running = BDGL_TRUE;
  while (running)
  {
    update();
    display();
  }

  cleanup();
  return 0;
}

void initialize()
{
  int i;

  /* Create screen, enable VSync and double buffering */
  screen = BDGL_CreateScreen(BDGL_MODE_VGA_320x200_256_COLOR);
  if (!screen)
  {
    fprintf(stderr, "There was an error when creating screen.\n");
    exit(1);
  }
  BDGL_EnableScreenOption(screen, BDGL_SCREEN_VSYNC | BDGL_SCREEN_DOUBLE_BUFFER);
  
  screen_width = BDGL_GetScreenWidth(screen);
  screen_height = BDGL_GetScreenHeight(screen);

  player.rect.x = 100;
  player.rect.y = 100;
  player.rect.width = 10;
  player.rect.height = 5;

  /* Initialize starfield */
  for (i = 0; i < STAR_NUMBER; ++i)
  {
    stars[i].x = rand() % screen_width;
    stars[i].y = rand() % screen_height;
    stars[i].plane = rand() % 3;
  }

  /* Initialize and display screen */
  BDGL_InitializeVideo(screen);

  /* Set the colors of stars by modifying the palette */
  BDGL_ModifyPaletteColor(1, 24, 24, 24);     /* dark grey */
  BDGL_ModifyPaletteColor(2, 48, 48, 48);     /* light grey */
  BDGL_ModifyPaletteColor(3, 63, 63, 63);     /* white */
}

void update()
{
  int i;

  BDGL_KeyScancode key = BDGL_GetScancode();
  if (key == BDGL_SCAN_ESC)
  {
    running = BDGL_FALSE;
    return;
  }
  if (key == BDGL_SCAN_UP || key == BDGL_SCAN_W)
  {
    player.rect.y -= SHIP_SPEED;
  }
  else if (key == BDGL_SCAN_DOWN || key == BDGL_SCAN_S)
  {
    player.rect.y += SHIP_SPEED;
  }
  if (key == BDGL_SCAN_LEFT || key == BDGL_SCAN_A)
  {
    player.rect.x -= SHIP_SPEED;
  }
  else if (key == BDGL_SCAN_RIGHT || key == BDGL_SCAN_D)
  {
    player.rect.x += SHIP_SPEED;
  }

  /* For each star... */
  for (i = 0; i < STAR_NUMBER; ++i)
  {
    /* Move current star forward from left to right */
    stars[i].x -= (1 + (float)stars[i].plane) * STAR_BASE_SPEED;

    /* Reset current star if it left the screen */
    if (stars[i].x < 0)
    {
      stars[i].x = screen_width;
      stars[i].y = rand() % screen_height;
    }
  }
}

void display()
{
  int i;

  /* Clear screen to blank */
  BDGL_ClearScreen(screen);

  /* For each star... */
  for (i = 0; i < STAR_NUMBER; ++i)
  {
    /* Draw current star */
    /* Now custom color is used from the palette */
    BDGL_SetDrawColor(screen, stars[i].plane + 1);      
    BDGL_DrawPoint2D(screen, stars[i].x, stars[i].y);
  }

  /* Draw space ship */
  BDGL_SetDrawColor(screen, BDGL_RED);
  BDGL_DrawRectangle(screen, &player.rect);

  /* Refresh screen */
  BDGL_UpdateScreen(screen);
}

void cleanup()
{
  /* Free screen resources */
  BDGL_DestroyScreen(screen);

  printf("Done\n");
}

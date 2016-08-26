/**
 * Origin of example is from
 * http://www.flipcode.com/archives/The_Art_of_Demomaking-Issue_02_Introduction_To_Computer_Graphics.shtml
 */

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include <BDGL.H>

#define STAR_NUMBER         256
#define STAR_BASE_SPEED     0.7f

// Star data type
typedef struct Star
{
    float x, y;         // Star positions
    BDGL_BYTE plane;    // Plane, which defines star speed
} Star;

Star stars[STAR_NUMBER];

// FIXME: needs implementation of VSync and Double buffer to be impressive
int main(int argc, char *argv[])
{
    // Create screen
    BDGL_Screen *screen = BDGL_CreateScreen(BDGL_MODE_VGA_320x200_256_COLOR,
            BDGL_SCREEN_ENABLE_VSYNC | BDGL_SCREEN_ENABLE_DOUBLE_BUFFER);

    // Initialize starfield
    int i;
    for (i = 0; i < STAR_NUMBER; ++i)
    {
        stars[i].x = rand() % screen->width;
        stars[i].y = rand() % screen->height;
        stars[i].plane = rand() % 3;
    }

    if (screen)
    {
        // Initialize screen to be displayed
        BDGL_InitializeVideo(screen);

        // Set the color of stars to white
        BDGL_SetDrawColor(screen, BDGL_WHITE);

        // Loop until key on keyboard is pressed
        while (!kbhit())
        {
            // Clear screen to blank
            BDGL_ClearScreen(screen);

            // For each star
            for (i = 0; i < STAR_NUMBER; ++i)
            {
                // Move current star forward from left to right
                stars[i].x += (1 + (float)stars[i].plane) * STAR_BASE_SPEED;

                // Reset current star if it left the screen
                if (stars[i].x > screen->width)
                {
                    stars[i].x = 0;
                    stars[i].y = rand() % screen->height;
                }

                // Draw current star
                BDGL_DrawPoint(screen, stars[i].x, stars[i].y);
            }

            // Refresh screen
            BDGL_UpdateScreen(screen);
        }

        // Free screen resources
        BDGL_DestroyScreen(screen);
        printf("Done\n");
    }
    return 0;
}

#include <stdio.h>
#include <stdlib.h>

#include <BDGL.H>

int main(int argc, char *argv[])
{
    int x, y, color;
    int x1, y1, x2, y2;
    BDGL_WORD i;

    BDGL_Rectangle rect;

	BDGL_Vertex vertices[3] = {
        {0,0},
        {7,5},
        {0,5}
	};

    BDGL_Screen *screen = BDGL_CreateScreen(BDGL_MODE_VGA_320x200_256_COLOR);
    if (screen)
    {
        BDGL_InitializeVideo(screen);

        // Draw single pixels
        BDGL_SetDrawColor(screen, BDGL_CYAN);
        BDGL_DrawPoint(screen, 0, 0);
        BDGL_SetDrawColor(screen, BDGL_WHITE);
        BDGL_DrawPoint(screen, 0, 1);
        BDGL_SetDrawColor(screen, BDGL_CYAN);
        BDGL_DrawPoint(screen, 0, 2);
        BDGL_DrawPoint(screen, 0, 3);
        BDGL_DrawPoint(screen, 0, 4);
        BDGL_DrawPoint(screen, 0, 0);
        BDGL_DrawPoint(screen, 7, 5);
        BDGL_DrawPoint(screen, 0, 5);
        BDGL_SetDrawColor(screen, BDGL_RED);
        BDGL_DrawPoint(screen, -20, -10);     // Check for drawing outside screen
        delay(4000);
        BDGL_ClearScreen(screen);

        // Draw points
        for(i = 0; i < 50000L; ++i)
        {
            x = rand() % screen->width;
            y = rand() % screen->height;
            BDGL_SetDrawColor(screen, rand() % screen->color_number);
            BDGL_DrawPoint(screen, x, y);
        }
        BDGL_ClearScreen(screen);

        // Draw lines
        for (i = 0; i < 5000; i++)
        {
            x1 = rand() % screen->width;
            y1 = rand() % screen->height;
            x2 = rand() % screen->width;
            y2 = rand() % screen->height;

            BDGL_SetDrawColor(screen, rand() % screen->color_number);
            BDGL_DrawLine(screen, x1, y1, x2, y2);
        }
        BDGL_ClearScreen(screen);

        // Draw rectangles
        for (i = 0; i < 5000; i++)
        {
            rect.x = rand() % screen->width;
            rect.y = rand() % screen->height;
            rect.width = rand() % screen->width;
            rect.height = rand() % screen->height;

            BDGL_SetDrawColor(screen, rand() % screen->color_number);
            BDGL_DrawRectangle(screen, &rect);
        }
        BDGL_ClearScreen(screen);

        // FIXME: crashes
        // Draw filled rectangles
        /*for (i = 0; i < 5000; i++)
        {
            rect.x = rand() % screen->width;
            rect.y = rand() % screen->height;
            rect.width = rand() % screen->width;
            rect.height = rand() % screen->height;
            color = rand() % screen->color_number;

    		BDGL_DrawFilledRectangle(screen, &rect, color);
        }
        BDGL_ClearScreen(screen);*/

        // Draw polygons
        BDGL_SetDrawColor(screen, BDGL_LIGHT_BLUE);
        BDGL_DrawPolygon(screen, BDGL_GetArrayLength(vertices), vertices);
        delay(4000);

        // The end
        BDGL_DestroyScreen(screen);
        printf("Done\n");
    }
    return 0;
}

/**
 * Origin of example is from
 * http://www.brackeen.com/vga/
 */

#include <stdio.h>
#include <stdlib.h>

#include <BDGL.H>

int main(int argc, char *argv[])
{
    /* Variable declarations. Putting local variables here is 
     * how it only compiles under DOS.                          */
    int x, y;                           /* Variables for points */
    int x1, y1, x2, y2;                 /* Variables for lines  */
    BDGL_WORD i;                        /* Loop variable        */

    BDGL_Rectangle rect;                /* Rectangle            */

	BDGL_Vertex vertices[3] = {         /* Vertices             */
        {0,0},
        {7,5},
        {0,5}
	};

    /* Create screen    */
    BDGL_Screen *screen = BDGL_CreateScreen(BDGL_MODE_VGA_320x200_256_COLOR);
    if (!screen)
    {
        fprintf(stderr, "There was an error when creating screen.\n");
        return 1;
    }

    /* Initialize and display screen    */
    BDGL_InitializeVideo(screen);

    /* Draw single pixels               */
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
    BDGL_DrawPoint(screen, -20, -10);     /* Test for drawing outside screen    */
    BDGL_UpdateScreen(screen);
    delay(4000);
    BDGL_ClearScreen(screen);

    /* Draw points                      */
    for(i = 0; i < 50000L; ++i)
    {
        x = rand() % screen->width;
        y = rand() % screen->height;
        BDGL_SetDrawColor(screen, rand() % screen->color_number);
        BDGL_DrawPoint(screen, x, y);
        BDGL_UpdateScreen(screen);
    }
    BDGL_ClearScreen(screen);

    /* Draw lines                       */
    for (i = 0; i < 5000; i++)
    {
        x1 = rand() % screen->width;
        y1 = rand() % screen->height;
        x2 = rand() % screen->width;
        y2 = rand() % screen->height;

        BDGL_SetDrawColor(screen, rand() % screen->color_number);
        BDGL_DrawLine(screen, x1, y1, x2, y2);
        BDGL_UpdateScreen(screen);
    }
    BDGL_ClearScreen(screen);

    /* Draw rectangles                  */
    for (i = 0; i < 5000; i++)
    {
        rect.x = rand() % screen->width;
        rect.y = rand() % screen->height;
        rect.width = rand() % screen->width;
        rect.height = rand() % screen->height;

        BDGL_SetDrawColor(screen, rand() % screen->color_number);
        BDGL_DrawRectangle(screen, &rect);
        BDGL_UpdateScreen(screen);
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

    /* Draw polygon                     */
    BDGL_SetDrawColor(screen, BDGL_LIGHT_BLUE);
    BDGL_DrawPolygon(screen, BDGL_GetArrayLength(vertices), vertices);
    BDGL_UpdateScreen(screen);
    delay(4000);

    /* Free screen resources            */
    BDGL_DestroyScreen(screen);

    printf("Done\n");
    return 0;
}

#ifndef BDGL_VIDEO_H_
#define BDGL_VIDEO_H_

#include "BDGL_Core.h"

#ifdef __cplusplus
extern "C" {
#endif

/* VGA display modes */
enum BDGL_VideoModes
{
    BDGL_MODE_TEXT_320x200_16_GREY = 0x00,
    BDGL_MODE_TEXT_320x200_16_COLOR,
    BDGL_MODE_TEXT_640x200_16_GREY,
    BDGL_MODE_TEXT_640x200_16_COLOR,
    BDGL_MODE_CGA_320x200_COLOR,
    BDGL_MODE_CGA_320x200_MONO,
    BDGL_MODE_CGA_640x200_MONO,
    BDGL_MODE_TEXT_720x350_MONO,
    BDGL_MODE_TEXT_1056x200_16_COLOR,
    BDGL_MODE_TGA_320x200_16_COLOR,
    BDGL_MODE_TGA_640x200_4_COLOR,
    BDGL_MODE_0BH_EGA_BIOS_RESERVED,
    BDGL_MODE_0CH_EGA_BIOS_RESERVED,
    BDGL_MODE_EGA_320x200_16_COLOR,
    BDGL_MODE_EGA_640x200_16_COLOR,
    BDGL_MODE_EGA_640x350_MONO,
    BDGL_MODE_EGA_640x350_4_COLOR,
    BDGL_MODE_VGA_640x480_MONO,
    BDGL_MODE_VGA_640x480_16_COLOR,
    BDGL_MODE_VGA_320x200_256_COLOR,
    BDGL_MODE_XGA_16_COLOR   // FIXME: I don't know what this mode is
    // TODO: Remaining modes and VESA modes
};

/* First 16 colors */
enum BDGL_Colors
{
    BDGL_BLACK = 0x00,
    BDGL_BLUE,
    BDGL_GREEN,
    BDGL_CYAN,
    BDGL_RED,
    BDGL_MAGENTA,
    BDGL_BROWN,
    BDGL_LIGHT_GRAY,
    BDGL_DARK_GRAY,
    BDGL_LIGHT_BLUE,
    BDGL_LIGHT_GREEN,
    BDGL_LIGHT_CYAN,
    BDGL_LIGHT_RED,
    BDGL_LIGHT_MAGENTA,
    BDGL_YELLOW,
    BDGL_WHITE
};

/* Data structure of the screen, holding dimensions and address of the VGA memory */
typedef struct BDGL_Screen
{
    BDGL_BYTE mode;
    BDGL_WORD width, height;
    BDGL_WORD color_number;
    BDGL_BYTE *vga_memory;
} BDGL_Screen;

/* Rectagular shape */
typedef struct BDGL_Rectangle
{
    int x, y;
    int width, height;
} BDGL_Rectangle;

/* 2D vertex for drawing polygons */
typedef struct BDGL_Vertex
{
    int x, y;
} BDGL_Vertex;


/**
 * Create screen and allocate memory resource for it's properties, like
 * screen dimensions, number of color and the address of the VGA memory,
 * depending on the chosen video mode.
 * Make sure you free the screen with "BDGL_DestroyScreen" at the end of
 * your program.
 *
 * @param video_mode    identifier for the video mode, for example 
 *                      "BDGL_MODE_VGA_320x200_256_COLOR" for 256 VGA mode.
 * @return              pointer to allocated screen resources
 */
BDGL_Screen* BDGL_CreateScreen(const BDGL_BYTE video_mode);

/**
 * Free screen resources. This also nullifies the pointer pointing to it
 * and switches back to text mode.
 *
 * @param screen        screen pointer to deallocate memory resource from
 */
void BDGL_DestroyScreen(BDGL_Screen *screen);

/**
 * Switch to the specified video mode of the screen.
 *
 * @param screen        screen pointer to switch video modes to
 */
void BDGL_InitializeVideo(BDGL_Screen *screen);

/**
 * Clear screen to draw again.
 *
 * @param screen        screen pointer to be cleared
 */
void BDGL_ClearScreen(BDGL_Screen *screen);

/**
 * Draw a single point as a pixel on the screen. On negative coordinates, the 
 * point doesn't wrap around the screen.
 *
 * @param screen        screen pointer to draw point on
 * @param x             horizontal x coordinate
 * @param y             vertical y coordinate
 * @param color         color of point between 0 and 255
 */
void BDGL_DrawPoint(BDGL_Screen *screen, int x, int y, const BDGL_BYTE color);

/**
 * Draw a straight line using Bresenham's algorithm.
 *
 * @param screen        screen pointer to draw line on
 * @param x_start       horizontal x coordinate of line starting point
 * @param y_start       vertical y coordinate of line starting point
 * @param x_end         horizontal x coordinate of line ending point
 * @param y_end         vertical y coordinate of line ending point
 * @param color         color of line between 0 and 255
 */
void BDGL_DrawLine(BDGL_Screen *screen, int x_start, int y_start, int x_end, int y_end, 
        const BDGL_BYTE color);

/**
 * Draw outlines of a rectangle.
 *
 * @param screen        screen pointer to draw rectangle on
 * @param rectangle     rectangle to draw
 * @param color         color of rectangle between 0 and 255
 */
void BDGL_DrawRectangle(BDGL_Screen *screen, BDGL_Rectangle *rectangle, const BDGL_BYTE color);

/**
 * Draw a filled rectangle.
 *
 * @param screen        screen pointer to draw filled rectangle on
 * @param rectangle     rectangle to draw
 * @param color         color of filled rectangle between 0 and 255
 */
void BDGL_DrawFilledRectangle(BDGL_Screen *screen, BDGL_Rectangle *rectangle, const BDGL_BYTE color);

/**
 * Draw polygonal shape specified by series of vertexes.
 *
 * @param screen            screen pointer to draw polygon on
 * @param vertex_number     number of vertices to draw. Due to C decaying array parameters to pointers,
 *                          the function can't determine array size internally and needs to be specified
 *                          outside.
 * @param vertices          series of vertexes to draw
 * @param color             color of polygon between 0 and 255
 */
void BDGL_DrawPolygon(BDGL_Screen *screen, const int vertex_number, BDGL_Vertex vertices[], 
        const BDGL_BYTE color);

// TODO
/**
 * Draw filled polygonal shape specified by series of vertexes.
 */
//void BDGL_DrawFilledPolygon(BDGL_Screen *screen, const int vertex_number, BDGL_Vertex vertices[],
//                      const BDGL_BYTE color);

// TODO
/**
 * Draw bitmap image
 */
//void BDGL_DrawBMP(BDGL_ImageBMP *image, int x, int y)

#ifdef __cplusplus
}
#endif

#endif  // BDGL_VIDEO_H_

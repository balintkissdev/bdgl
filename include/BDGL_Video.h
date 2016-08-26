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

enum BDGL_ScreenFlags
{
    BDGL_SCREEN_DEFAULT                    = 0x00,
    BDGL_SCREEN_ENABLE_VSYNC,
    BDGL_SCREEN_ENABLE_DOUBLE_BUFFER
};


/* Data structure of the screen */
typedef struct BDGL_Screen
{
    BDGL_BYTE mode;                 // Video mode
    BDGL_WORD width, height;        // Screen dimensions
    BDGL_WORD color_number;         // Number of available colors
    BDGL_BYTE current_draw_color;   // Current drawing color
    BDGL_BYTE *vga_memory;          // Address of VGA memory
    BDGL_BYTE *buffer;              // Double buffer
    BDGL_BYTE flags;                // Bit flags
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
 * @param flags         bit flags to customize screen properties. The following values can be set:
 *
 *                      BDGL_SCREEN_DEFAULT:                Nothing. This means disabling
 *                                                          VSync and double buffering
 *                      BDGL_SCREEN_ENABLE_VSYNC:           Enable wait for vertical retrace (VSync)
 *                      BDGL_SCREEN_ENABLE_DOUBLE_BUFFER:   Enable double buffering
 *
 *                      These flags can be chained together, for example
 *
 *                      BDGL_SCREEN_ENABLE_VSYNC | BDGL_SCREEN_ENABLE_DOUBLE_BUFFER
 *
 * @return              pointer to allocated screen resources
 */
BDGL_Screen* BDGL_CreateScreen(const BDGL_BYTE video_mode, const BDGL_BYTE flags);

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
 * Update screen with double buffering. Until this call, every pixel is written into
 * a temporary buffer before displaying.
 * This also includes waiting for vertical retrace (VSync)
 *
 * @param               screen to update
 */
void BDGL_UpdateScreen(BDGL_Screen *screen);

/**
 * Set drawing color to draw primitives with.
 *
 * @param screen        screen to set color of
 * @param color         drawing color between 0 and 255
 */
void BDGL_SetDrawColor(BDGL_Screen *screen, const BDGL_BYTE color);

/**
 * Draw a single point as a pixel on the screen. On negative coordinates, the 
 * point doesn't wrap around the screen.
 *
 * @param screen        screen pointer to draw point on
 * @param x             horizontal x coordinate
 * @param y             vertical y coordinate
 */
void BDGL_DrawPoint(BDGL_Screen *screen, int x, int y);

/**
 * Draw a straight line using Bresenham's algorithm.
 *
 * @param screen        screen pointer to draw line on
 * @param x_start       horizontal x coordinate of line starting point
 * @param y_start       vertical y coordinate of line starting point
 * @param x_end         horizontal x coordinate of line ending point
 * @param y_end         vertical y coordinate of line ending point
 */
void BDGL_DrawLine(BDGL_Screen *screen, int x_start, int y_start, int x_end, int y_end);

/**
 * Draw outlines of a rectangle.
 *
 * @param screen        screen pointer to draw rectangle on
 * @param rectangle     rectangle to draw
 */
void BDGL_DrawRectangle(BDGL_Screen *screen, BDGL_Rectangle *rectangle);

/**
 * Draw a filled rectangle.
 *
 * @param screen        screen pointer to draw filled rectangle on
 * @param rectangle     rectangle to draw
 */
void BDGL_DrawFilledRectangle(BDGL_Screen *screen, BDGL_Rectangle *rectangle);

/**
 * Draw polygonal shape specified by series of vertexes.
 *
 * @param screen            screen pointer to draw polygon on
 * @param vertex_number     number of vertices to draw. Due to C decaying array parameters to pointers,
 *                          the function can't determine array size internally and needs to be specified
 *                          outside.
 * @param vertices          series of vertexes to draw
 */
void BDGL_DrawPolygon(BDGL_Screen *screen, const int vertex_number, BDGL_Vertex vertices[]);

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

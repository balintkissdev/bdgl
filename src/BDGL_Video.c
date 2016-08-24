#include <BDGL_Video.h>

#include <stdio.h>
#include <stdlib.h>

/* BIOS video interrupts */
#define BDGL_BIOS_VIDEO_INTERRUPT        (0x10)
#define BDGL_BIOS_VIDEO_SET_MODE         (0x00)

/* Check if x and y are within screen boundaries */
#define WITHIN_SCREEN_BOUNDARIES(screen, x, y) \
    ((-1 < (x)) && ((x) < (screen)->width) && (-1 < (y)) && ((screen)->height))

/**
 * Set video mode. This operation is encapsulated.
 *
 * @param video_mode    identifier of video mode
 */
// TODO: only observed working with Watcom compiler
// TODO: only observed working with text and 256 VGA mode
static void BDGL_SetVideoMode(const BDGL_BYTE video_mode);
#ifdef WATCOM       // Only Watcom compilers have the aux pragma
#pragma aux BDGL_SetVideoMode =  \
    "mov ah, 0"                 \
    "int 0x10"                  \
    parm [al];
#else
static void BDGL_SetVideoMode(const BDGL_BYTE video_mode)
{
    union REGS registers;
    registers.h.ah = BDGL_BIOS_VIDEO_SET_MODE;
    registers.h.al = video_mode;
    int86(BDGL_BIOS_VIDEO_INTERRUPT, &registers, &registers);
}
#endif

// TODO: currently only supports 256 VGA mode
// FIXME: needs a better way to parse parameters rather than using switch-case
BDGL_Screen* BDGL_CreateScreen(const BDGL_BYTE video_mode)
{
    BDGL_Screen *screen = malloc(sizeof BDGL_Screen);
    screen->mode = video_mode;
    switch (video_mode)
    {
        case BDGL_MODE_VGA_320x200_256_COLOR:
            screen->width = 320;
            screen->height = 200;
            screen->color_number = 256;
            screen->vga_memory = (BDGL_BYTE *)MK_FP(BDGL_VGA_ADDRESS,0);
            break;

        default:
            free(screen);
            fprintf(stderr, "Sorry, video mode 0x%08x is not yet supported.\n", video_mode);
            return NULL;
    }
    return screen;
}

void BDGL_DestroyScreen(BDGL_Screen *screen)
{
    if (screen)
    {
        BDGL_SetVideoMode(BDGL_MODE_TEXT_640x200_16_COLOR);
        free(screen);
        screen = NULL;
    }
}

void BDGL_InitializeVideo(BDGL_Screen *screen)
{
    BDGL_SetVideoMode(screen->mode);
}

void BDGL_ClearScreen(BDGL_Screen *screen)
{
    BDGL_SetVideoMode(screen->mode);
}

void BDGL_DrawPoint(BDGL_Screen *screen, int x, int y, const BDGL_BYTE color)
{
    if (WITHIN_SCREEN_BOUNDARIES(screen, x, y))    // Makes sure doesn't wrap around screen
        screen->vga_memory[(y << 8) + (y << 6) + x] = color;
}

void BDGL_DrawLine(BDGL_Screen *screen, int x_start, int y_start,  int x_end, int y_end, const BDGL_BYTE color)
{
    int delta_x = x_end - x_start;

    int delta_y = y_end - y_start;
    int delta_x_abs = abs(delta_x);
    int delta_y_abs = abs(delta_y);
    int delta_x_sign = BDGL_GetMathSign(delta_x);
    int delta_y_sign = BDGL_GetMathSign(delta_y);

    int x = delta_x_abs >> 1;
    int y = delta_y_abs >> 1;
    int pixel_x = x_start;
    int pixel_y = y_start;

    int i;

    BDGL_DrawPoint(screen, x_start, y_start, color);
    if (delta_x_abs >= delta_y_abs)
    {
        for (i = 0; i < delta_x_abs; ++i)
        {
            y += delta_y_abs;
            if (y >= delta_x_abs)
            {
                y -= delta_x_abs;
                pixel_y += delta_y_sign;
            }
            pixel_x += delta_x_sign;
            BDGL_DrawPoint(screen, pixel_x, pixel_y, color);
        }
    }
    else
    {
        for (i = 0; i < delta_y_abs; ++i)
        {
            x += delta_x_abs;
            if (x >= delta_y_abs)
            {
                x -= delta_y_abs;
                pixel_x += delta_x_sign;
            }
            pixel_y += delta_y_sign;
            BDGL_DrawPoint(screen, pixel_x, pixel_y, color);
        }
    }
}

// FIXME: drawing outside of screen wraps around
void BDGL_DrawRectangle(BDGL_Screen *screen, BDGL_Rectangle *rectangle, const BDGL_BYTE color)
{
    BDGL_WORD top_offset;
    BDGL_WORD bottom_offset;

    int top = rectangle->y;
    int bottom = top + rectangle->height;
    int left = rectangle->x;
    int right = left + rectangle->width;

    int i;

    int tmp;
    if (top > bottom)
    {
        tmp = top;
        top = bottom;
        bottom = tmp;
    }
    if (left > right)
    {
        tmp = left;
        left = right;
        right = tmp;
    }

    top_offset = (top << 8) + (top << 6);
    bottom_offset = (bottom << 8) + (bottom << 6);

    for (i = left; i <= right; i++)
    {
        screen->vga_memory[top_offset + i] = color;
        screen->vga_memory[bottom_offset + i] = color;
    }

    for (i = top_offset; i <= bottom_offset; i += screen->width)
    {
        screen->vga_memory[left + i] = color;
        screen->vga_memory[right + i] = color;
    }
}

// FIXME: crashes
// FIXME: drawing outside of screen wraps around
void BDGL_DrawFilledRectangle(BDGL_Screen *screen, BDGL_Rectangle *rectangle, const BDGL_BYTE color)
{
    BDGL_WORD top_offset;
    BDGL_WORD bottom_offset;

    int top = rectangle->y;
    int bottom = top + rectangle->height;
    int left = rectangle->x;
    int right = left + rectangle->width;

    BDGL_WORD tmp, width, i;

    if (top > bottom)
    {
        tmp = top;
        top = bottom;
        bottom = tmp;
    }
    if (left > right)
    {
        tmp = left;
        left = right;
        right = tmp;
    }

    top_offset = (top << 8) + (top << 6) + left;
    bottom_offset = (bottom << 8) + (bottom << 6) + left;

    width = right - left + 1;
    for (i = top_offset; i <= bottom_offset; i += screen->width)
    {
        memset(&screen->vga_memory[i], color, width);
    }
}

void BDGL_DrawPolygon(BDGL_Screen *screen, const int vertex_number, BDGL_Vertex vertices[], const BDGL_BYTE color)
{
	int i;
    for (i = 0; i < vertex_number - 1; ++i)
	{
        BDGL_DrawLine(screen,
		    vertices[i].x,
			vertices[i].y,
			vertices[i + 1].x,
			vertices[i + 1].y,
			color
        );
	}

	BDGL_DrawLine(screen,
        vertices[i].x,
        vertices[i].y,
        vertices[0].x,
		vertices[0].y,
		color
    );
}

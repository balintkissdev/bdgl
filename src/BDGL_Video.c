#include <BDGL_Video.h>

#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <mem.h>

/* BIOS video interrupts */
#define BDGL_BIOS_VIDEO_INTERRUPT        (0x10)
#define BDGL_BIOS_VIDEO_SET_MODE         (0x00)
#define BDGL_BIOS_VIDEO_SET_VESA_MODE    (0x4F2)

/* VGA registers */
#define VGA_CRT_INPUT_STATUS_1           (0x03da)
#define VGA_PALETTE_INDEX                (0x03c8)
#define VGA_PALETTE_DATA                 (0x03c9)

/* VGA status */
#define VGA_STATUS_VRETRACE              (0x08)

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
#ifdef WATCOM       // Only Watcom compilers have the aux pragma
static void BDGL_SetVideoMode(const BDGL_BYTE video_mode);
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

// TODO
#ifdef WATCOM
static void BDGL_SetVESAVideoMode(const BDGL_WORD video_mode);
#pragma aux BDGL_SetVESAVideoMode = \
    "mov ax, 0x4F02"                \
    "int 0x10"                      \
    parm [bx];
#else
static void BDGL_SetVESAVideoMode(const BDGL_WORD video_mode)
{
    union REGS registers;
    registers.x.ax = BDGL_BIOS_VIDEO_SET_VESA_MODE;
    registers.x.bx = video_mode;
    int86(BDGL_BIOS_VIDEO_INTERRUPT, &registers, &registers);
}
#endif

// TODO: currently only supports 256 VGA mode
// FIXME: needs a better way to parse parameters rather than using switch-case
BDGL_Screen* BDGL_CreateScreen(const BDGL_BYTE video_mode)
{
    BDGL_Screen *screen = malloc(sizeof(BDGL_Screen));
    screen->mode = video_mode;
    switch (video_mode)
    {
        case BDGL_MODE_VGA_320x200_256_COLOR:
            screen->width = 320;
            screen->height = 200;
            screen->color_number = 256;
            screen->current_draw_color = 0;
            screen->flags = 0x00;

            screen->vga_memory = (BDGL_BYTE *)MK_FP(BDGL_VGA_ADDRESS,0);
            screen->buffer = screen->vga_memory;
            break;

        default:
            free(screen);
            fprintf(stderr, "Sorry, video mode 0x%08x is not supported.\n", video_mode);
            return NULL;
    }
    return screen;
}

void BDGL_DestroyScreen(BDGL_Screen *screen)
{
    if (screen)
    {
        BDGL_SetVideoMode(BDGL_MODE_TEXT_640x200_16_COLOR);
        if (screen->flags & BDGL_SCREEN_DOUBLE_BUFFER)
        {
            free(screen->buffer);
        }
        free(screen);
    }
}

void BDGL_EnableScreenOption(BDGL_Screen *screen, const BDGL_BYTE flags)
{
    screen->flags |= flags;

    if (flags & BDGL_SCREEN_DOUBLE_BUFFER)
    {
        screen->buffer = calloc(screen->width * screen->height, 1);
    }
}

void BDGL_DisableScreenOption(BDGL_Screen *screen, const BDGL_BYTE flags)
{
    screen->flags &= flags;

    if (flags & BDGL_SCREEN_DOUBLE_BUFFER)
    {
        free(screen->buffer);
        screen->buffer = screen->vga_memory;
    }
}

void BDGL_InitializeVideo(BDGL_Screen *screen)
{
    BDGL_SetVideoMode(screen->mode);
}

void BDGL_ClearScreen(BDGL_Screen *screen)
{
    memset(screen->buffer, 0, screen->width * screen->height);
}

void BDGL_UpdateScreen(BDGL_Screen *screen)
{
    /* Wait for vertical retrace    */
    if (screen->flags & BDGL_SCREEN_VSYNC)
    {
        while (inp(VGA_CRT_INPUT_STATUS_1) & VGA_STATUS_VRETRACE);
        while (!inp(VGA_CRT_INPUT_STATUS_1) & VGA_STATUS_VRETRACE);
    }

    /* Flip double buffer   */
    if (screen->flags & BDGL_SCREEN_DOUBLE_BUFFER)
    {
        memcpy(screen->vga_memory, screen->buffer, screen->width * screen->height);
    }
}

void BDGL_SetDrawColor(BDGL_Screen *screen, const BDGL_BYTE color)
{
    screen->current_draw_color = color;
}

void BDGL_ModifyPaletteColor(const BDGL_BYTE palette_index, 
        const BDGL_BYTE red63, const BDGL_BYTE green63, const BDGL_BYTE blue63)
{
     outp(VGA_PALETTE_INDEX, palette_index);
     outp(VGA_PALETTE_DATA, red63);
     outp(VGA_PALETTE_DATA, green63);
     outp(VGA_PALETTE_DATA, blue63);
}

void BDGL_DrawPoint(BDGL_Screen *screen, int x, int y)
{
    if (WITHIN_SCREEN_BOUNDARIES(screen, x, y))    /* Makes sure doesn't wrap around screen */
        screen->buffer[(y << 8) + (y << 6) + x] = screen->current_draw_color;
}

void BDGL_DrawLine(BDGL_Screen *screen, int x_start, int y_start,  int x_end, int y_end)
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

    BDGL_DrawPoint(screen, x_start, y_start);
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
            BDGL_DrawPoint(screen, pixel_x, pixel_y);
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
            BDGL_DrawPoint(screen, pixel_x, pixel_y);
        }
    }
}

// FIXME: drawing outside of screen wraps around
void BDGL_DrawRectangle(BDGL_Screen *screen, BDGL_Rectangle *rectangle)
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
        screen->buffer[top_offset + i] = screen->current_draw_color;
        screen->buffer[bottom_offset + i] = screen->current_draw_color;
    }

    for (i = top_offset; i <= bottom_offset; i += screen->width)
    {
        screen->buffer[left + i] = screen->current_draw_color;
        screen->buffer[right + i] = screen->current_draw_color;
    }
}

// FIXME: crashes
// FIXME: drawing outside of screen wraps around
void BDGL_DrawFilledRectangle(BDGL_Screen *screen, BDGL_Rectangle *rectangle)
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
        memset(&screen->vga_memory[i], screen->current_draw_color, width);
    }
}

void BDGL_DrawPolygon(BDGL_Screen *screen, const int vertex_number, BDGL_Vertex vertices[])
{
	int i;
    for (i = 0; i < vertex_number - 1; ++i)
	{
        BDGL_DrawLine(screen,
		    vertices[i].x,
			vertices[i].y,
			vertices[i + 1].x,
			vertices[i + 1].y
        );
	}

	BDGL_DrawLine(screen,
        vertices[i].x,
        vertices[i].y,
        vertices[0].x,
		vertices[0].y
    );
}

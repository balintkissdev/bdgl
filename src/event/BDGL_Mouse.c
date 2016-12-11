/*
  Copyright (c) 2016 Bálint Kiss <balint.kiss.501@gmail.com>

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/
#include <event/BDGL_Mouse.h>

#ifdef __cplusplus
extern "C" {
#endif

/* BIOS interrupt */
#define MOUSE_INTERRUPT                 (0x33)

/* Mouse BIOS functions */
#define MOUSE_FUNCTION_RESET            (0x00)
#define MOUSE_FUNCTION_SHOW             (0x01)
#define MOUSE_FUNCTION_HIDE             (0x02)
#define MOUSE_FUNCTION_STATUS           (0x03)
#define MOUSE_FUNCTION_RELATIVE_MOTION  (0x0B)
#define MOUSE_FUNCTION_SET_SENSITIVITY  (0x1A)

/* TODO: write assembly code? */
void BDGL_InitializeMouse()
{
  union REGS regs;
  regs.x.ax = MOUSE_FUNCTION_RESET;
  int86(MOUSE_INTERRUPT, &regs, &regs);
}

void BDGL_ShowMouseCursor()
{
  union REGS regs;
  regs.x.ax = MOUSE_FUNCTION_SHOW;
  int86(MOUSE_INTERRUPT, &regs, &regs);
}

void BDGL_HideMouseCursor()
{
  union REGS regs;
  regs.x.ax = MOUSE_FUNCTION_HIDE;
  int86(MOUSE_INTERRUPT, &regs, &regs);
}

void BDGL_MouseAbsPos(int *const x_position, int *const y_position)
{
  union REGS regs;
  regs.x.ax = MOUSE_FUNCTION_STATUS;
  int86(MOUSE_INTERRUPT, &regs, &regs);

  *x_position = regs.x.cx / 2;   /* HACK: somehow in DosBox, gives double value for horizontal position.
                                    Needs test on different resolutions. */
  *y_position = regs.x.dx;
}

BDGL_BYTE BDGL_MouseButton()
{
  union REGS regs;
  regs.x.ax = MOUSE_FUNCTION_STATUS;
  int86(MOUSE_INTERRUPT, &regs, &regs);

  return regs.x.bx;
}

void BDGL_MouseRelPos(int *const x_delta, int *const y_delta)
{
  union REGS regs;
  regs.x.ax = MOUSE_FUNCTION_RELATIVE_MOTION;
  int86(MOUSE_INTERRUPT, &regs, &regs);

  *x_delta = regs.x.cx;
  *y_delta = regs.x.dx;
}

/* TODO: look after "doublespeed" register parameter */
void BDGL_SetMouseSensitivity(const BDGL_BYTE horizontal, const BDGL_BYTE vertical)
{
  union REGS regs;
  regs.x.ax = MOUSE_FUNCTION_SET_SENSITIVITY;
  regs.x.bx = horizontal;
  regs.x.cx = vertical;
  int86(MOUSE_INTERRUPT, &regs, &regs);
}

#ifdef __cplusplus
}
#endif

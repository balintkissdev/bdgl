/*
 * Copyright (c) 2016 Balint Kiss <balint.kiss.501@gmail.com>
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
#include <BDGL/event/mouse.h>

#include <dos.h>

/* Mouse BIOS functions */
#define MOUSE_FUNCTION_RESET            (0x00)
#define MOUSE_FUNCTION_SHOW             (0x01)
#define MOUSE_FUNCTION_HIDE             (0x02)
#define MOUSE_FUNCTION_STATUS           (0x03)
#define MOUSE_FUNCTION_RELATIVE_MOTION  (0x0B)
#define MOUSE_FUNCTION_SET_SENSITIVITY  (0x1A)

/* TODO: Rename and move to public API */
#if !defined(_M_I86)
  #define INTERRUPT(a,b,c)   int386(a,b,c)

  #define REGISTER_A  eax
  #define REGISTER_B  ebx
  #define REGISTER_C  ecx
  #define REGISTER_D  edx
#else
  #define INTERRUPT(a,b,c)   int86(a,b,c)

  #define REGISTER_A  ax
  #define REGISTER_B  bx
  #define REGISTER_C  cx
  #define REGISTER_D  dx
#endif

/* TODO: write assembly code */
void BDGL_InitializeMouse()
{
  union REGS regs;
  regs.x.REGISTER_A = MOUSE_FUNCTION_RESET;
  INTERRUPT(BDGL_INTERRUPT_MOUSE, &regs, &regs);
}

void BDGL_ShowMouseCursor()
{
  union REGS regs;
  regs.x.REGISTER_A = MOUSE_FUNCTION_SHOW;
  INTERRUPT(BDGL_INTERRUPT_MOUSE, &regs, &regs);
}

void BDGL_HideMouseCursor()
{
  union REGS regs;
  regs.x.REGISTER_A = MOUSE_FUNCTION_HIDE;
  INTERRUPT(BDGL_INTERRUPT_MOUSE, &regs, &regs);
}

void BDGL_GetMouseAbsPos(int *const x_position, int *const y_position)
{
  union REGS regs;
  regs.x.REGISTER_A = MOUSE_FUNCTION_STATUS;
  INTERRUPT(BDGL_INTERRUPT_MOUSE, &regs, &regs);

  /*
   * HACK: Somehow in DosBox, gives double value for horizontal position.
   *        Needs testing on different resolutions.
   */
  *x_position = regs.x.REGISTER_C / 2;
  *y_position = regs.x.REGISTER_D;
}

BDGL_MouseButton BDGL_GetMouseButton()
{
  union REGS regs;
  regs.x.REGISTER_A = MOUSE_FUNCTION_STATUS;
  INTERRUPT(BDGL_INTERRUPT_MOUSE, &regs, &regs);

  return regs.x.REGISTER_B;
}

void BDGL_GetMouseRelPos(int *const x_delta, int *const y_delta)
{
  union REGS regs;
  regs.x.REGISTER_A = MOUSE_FUNCTION_RELATIVE_MOTION;
  INTERRUPT(BDGL_INTERRUPT_MOUSE, &regs, &regs);

  *x_delta = regs.x.REGISTER_C;
  *y_delta = regs.x.REGISTER_D;
}

/* TODO: look after "doublespeed" register parameter */
void BDGL_SetMouseSensitivity(
  const BDGL_Uint8 horizontal,
  const BDGL_Uint8 vertical)
{
  union REGS regs;
  regs.x.REGISTER_A = MOUSE_FUNCTION_SET_SENSITIVITY;
  regs.x.REGISTER_B = horizontal;
  regs.x.REGISTER_C = vertical;
  INTERRUPT(BDGL_INTERRUPT_MOUSE, &regs, &regs);
}


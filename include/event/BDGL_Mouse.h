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
#ifndef BDGL_MOUSE_H_
#define BDGL_MOUSE_H_

#include "../core/BDGL_Core.h"

#define BDGL_MOUSE_NOTHING  (0x00)
#define BDGL_MOUSE_LEFT     (0x01)
#define BDGL_MOUSE_RIGHT    (0x02)
#define BDGL_MOUSE_MIDDLE   (0x04)

/**
 * Initialize mouse. This needs to be called before you want to use the mouse.
 * You can also use this to reset the mouse cursor to the center of the screen.
 */
void BDGL_InitializeMouse();

/**
 * Shows the actual system cursor. You might want to keep it
 * hidden and use own cursor icon.
 */
void BDGL_ShowMouseCursor();

/**
 * Hide system cursor.
 */
void BDGL_HideMouseCursor();

/**
 * Get the absolute position of the mouse.
 *
 * @param x_position  Output to the horizontal position of the mouse
 * @param y_position  Output to the vertical position of the mouse
 */
void BDGL_MouseAbsPos(int *const x_position, int *const y_position);

/**
 * Get the relative position of the mouse.
 *
 * @param x_delta   Output to the horizontal movement difference of the mouse
 * @param y_delta   Output to the vertical movement difference of the mouse
 */
void BDGL_MouseRelPos(int *const x_delta, int *const y_delta);

/**
 * Get button currently pressed on the mouse.
 *
 * @return  The following constants can be returned:
 *          BDGL_MOUSE_NOTHING - if no button was pressed
 *          BDGL_MOUSE_LEFT    - if the left mouse button was pressed
 *          BDGL_MOUSE_RIGHT   - if the right mouse button was pressed
 *          BDGL_MOUSE_MIDDLE  - if the middle mouse button was pressed
 */
BDGL_BYTE BDGL_MouseButton();

/**
 * Set the horizontal and vertical sensitivity with values between 0 and 100.
 *
 * @param horizontal  Horizontal sensitivity with values ranging from 0 to 100
 * @param vertical    Vertical sensitivity with values ranging from 0 to 100
 */
void BDGL_SetMouseSensitivity(const BDGL_BYTE horizontal, const BDGL_BYTE vertical);

#endif // BDGL_MOUSE_H_

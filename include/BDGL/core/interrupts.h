/*
 * Copyright (c) 2016 Balint Kiss <balintkissdev@gmail.com>
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
#ifndef _BDGL_INTERRUPTS_H_
#define _BDGL_INTERRUPTS_H_

#define BDGL_INTERRUPT_IRQ_KEYBOARD           (0x0009)

#define BDGL_INTERRUPT_MOUSE                  (0x0033)
#define BDGL_INTERRUPT_VIDEO                  (0x0010)
#define BDGL_INTERRUPT_VIDEO_SET_MODE         (0x0000)
#define BDGL_INTERRUPT_VIDEO_SET_VESA_MODE    (0x04F2)

/* TODO: More BIOS interrupts */

#endif  /* _BDGL_INTERRUPTS_H_ */

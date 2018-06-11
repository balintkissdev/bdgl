/*
 * Copyright (c) 2018 Balint Kiss <balint.kiss.501@gmail.com>
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
#ifndef _BDGL_PORTS_H_
#define _BDGL_PORTS_H_

/* TODO: More ports */

/**
 * Port of the Programmable Interrupt Controller (PIC).
 */
#define BDGL_PORT_PIC                   (0x0020)

/**
 * Input port containing data of the pressed key on the keyboard.
 */
#define BDGL_PORT_KEYBOARD_DATA         (0x0060)

/**
 * Input port containing the status bits of the keyboard.
 */
#define BDGL_PORT_KEYBOARD_STATUS       (0x0061)


#endif  /* _BDGL_PORTS_H_ */

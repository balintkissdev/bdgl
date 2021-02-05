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
#ifndef _BDGL_KEYBOARD_H_
#define _BDGL_KEYBOARD_H_

#include <BDGL/core/core.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup Special modifier key states
 * @{
 */

#define BDGL_KEY_MODIFIER_SHIFT_RIGHT         (0x0001)
#define BDGL_KEY_MODIFIER_SHIFT_LEFT          (0x0002)
#define BDGL_KEY_MODIFIER_CTRL                (0x0004)
#define BDGL_KEY_MODIFIER_ALT                 (0x0008)
#define BDGL_KEY_MODIFIER_SCROLL_LOCK_ON      (0x0010)
#define BDGL_KEY_MODIFIER_NUM_LOCK_ON         (0x0020)
#define BDGL_KEY_MODIFIER_CAPS_LOCK_ON        (0x0040)
#define BDGL_KEY_MODIFIER_INSERT_MODE         (0x0080)
#define BDGL_KEY_MODIFIER_CTRL_LEFT           (0x0100)
#define BDGL_KEY_MODIFIER_ALT_LEFT            (0x0200)
#define BDGL_KEY_MODIFIER_CTRL_RIGHT          (0x0400)
#define BDGL_KEY_MODIFIER_ALT_RIGHT           (0x0800)
#define BDGL_KEY_MODIFIER_SCROLL_LOCK_DOWN    (0x1000)
#define BDGL_KEY_MODIFIER_NUM_LOCK_DOWN       (0x2000)
#define BDGL_KEY_MODIFIER_CAPS_LOCK_DOWN      (0x4000)
#define BDGL_KEY_MODIFIER_SYS_REQ_DOWN        (0x8000)

/** @} */

/**
 * @addtogroup Keyboard scancodes
 * @{
 */

#define BDGL_KEY_SCAN_NONE          (0)
#define BDGL_KEY_SCAN_ESCAPE        (1)
#define BDGL_KEY_SCAN_1             (2)
#define BDGL_KEY_SCAN_2             (3)
#define BDGL_KEY_SCAN_3             (4)
#define BDGL_KEY_SCAN_4             (5)
#define BDGL_KEY_SCAN_5             (6)
#define BDGL_KEY_SCAN_6             (7)
#define BDGL_KEY_SCAN_7             (8)
#define BDGL_KEY_SCAN_8             (9)
#define BDGL_KEY_SCAN_9             (10)
#define BDGL_KEY_SCAN_0             (11)
#define BDGL_KEY_SCAN_DASH          (12)
#define BDGL_KEY_SCAN_EQUALS        (13)
#define BDGL_KEY_SCAN_BACKSPACE     (14)
#define BDGL_KEY_SCAN_TAB           (15)
#define BDGL_KEY_SCAN_Q             (16)
#define BDGL_KEY_SCAN_W             (17)
#define BDGL_KEY_SCAN_E             (18)
#define BDGL_KEY_SCAN_R             (19)
#define BDGL_KEY_SCAN_T             (20)
#define BDGL_KEY_SCAN_Y             (21)
#define BDGL_KEY_SCAN_U             (22)
#define BDGL_KEY_SCAN_I             (23)
#define BDGL_KEY_SCAN_O             (24)
#define BDGL_KEY_SCAN_P             (25)
#define BDGL_KEY_SCAN_LEFT_BRACKET  (26)
#define BDGL_KEY_SCAN_RIGHT_BRACKET (27)
#define BDGL_KEY_SCAN_ENTER         (28)
#define BDGL_KEY_SCAN_CTRL          (29)
#define BDGL_KEY_SCAN_A             (30)
#define BDGL_KEY_SCAN_S             (31)
#define BDGL_KEY_SCAN_D             (32)
#define BDGL_KEY_SCAN_F             (33)
#define BDGL_KEY_SCAN_G             (34)
#define BDGL_KEY_SCAN_H             (35)
#define BDGL_KEY_SCAN_J             (36)
#define BDGL_KEY_SCAN_K             (37)
#define BDGL_KEY_SCAN_L             (38)
#define BDGL_KEY_SCAN_SEMICOLON     (39)
#define BDGL_KEY_SCAN_APOSTROPHE    (40)
#define BDGL_KEY_SCAN_SHIFT_LEFT    (42)
#define BDGL_KEY_SCAN_BACKSLASH     (43)
#define BDGL_KEY_SCAN_Z             (44)
#define BDGL_KEY_SCAN_X             (45)
#define BDGL_KEY_SCAN_C             (46)
#define BDGL_KEY_SCAN_V             (47)
#define BDGL_KEY_SCAN_B             (48)
#define BDGL_KEY_SCAN_N             (49)
#define BDGL_KEY_SCAN_M             (50)
#define BDGL_KEY_SCAN_COMMA         (51)
#define BDGL_KEY_SCAN_PERIOD        (52)
#define BDGL_KEY_SCAN_FORWARD_SLASH (53)
#define BDGL_KEY_SCAN_SHIFT_RIGHT   (54)
#define BDGL_KEY_SCAN_PRINT_SCREEN  (55)
#define BDGL_KEY_SCAN_ALT           (56)
#define BDGL_KEY_SCAN_SPACE         (57)
#define BDGL_KEY_SCAN_CAPS_LOCK     (58)
#define BDGL_KEY_SCAN_F1            (59)
#define BDGL_KEY_SCAN_F2            (60)
#define BDGL_KEY_SCAN_F3            (61)
#define BDGL_KEY_SCAN_F4            (62)
#define BDGL_KEY_SCAN_F5            (63)
#define BDGL_KEY_SCAN_F6            (64)
#define BDGL_KEY_SCAN_F7            (65)
#define BDGL_KEY_SCAN_F8            (66)
#define BDGL_KEY_SCAN_F9            (67)
#define BDGL_KEY_SCAN_F10           (68)
#define BDGL_KEY_SCAN_F11           (133)
#define BDGL_KEY_SCAN_F12           (134)
#define BDGL_KEY_SCAN_NUM_LOCK      (69)
#define BDGL_KEY_SCAN_SCROLL_LOCK   (70)
#define BDGL_KEY_SCAN_HOME          (71)
#define BDGL_KEY_SCAN_UP            (72)
#define BDGL_KEY_SCAN_PAGE_UP       (73)
#define BDGL_KEY_SCAN_MINUS         (74)
#define BDGL_KEY_SCAN_LEFT          (75)
#define BDGL_KEY_SCAN_CENTER        (76)
#define BDGL_KEY_SCAN_RIGHT         (77)
#define BDGL_KEY_SCAN_PLUS          (78)
#define BDGL_KEY_SCAN_END           (79)
#define BDGL_KEY_SCAN_DOWN          (80)
#define BDGL_KEY_SCAN_PAGE_DOWN     (81)
#define BDGL_KEY_SCAN_INSERT        (82)
#define BDGL_KEY_SCAN_DEL           (83)

/** @} */


/**
 * Typedef for the keyboard scancode.
 */
typedef BDGL_Uint8 BDGL_KeyScancode;

typedef enum
{
  BDGL_KEY_RELEASED,
  BDGL_KEY_PRESSED
} BDGL_KeyStatus;

/* TODO: Handle modifier keys */
typedef struct BDGL_KeyEvent
{
  BDGL_KeyScancode key;
  BDGL_KeyStatus status;
} BDGL_KeyEvent;

extern BDGL_KeyStatus BDGL_KeyboardMap[];

void BDGL_InitializeKeyboard();

void BDGL_CleanupKeyboard();

BDGL_Bool BDGL_PollKeyboard(BDGL_KeyEvent *key_event);

const char* BDGL_GetKeyName(BDGL_KeyEvent *key_event);


#endif /* _BDGL_KEYBOARD_H_ */

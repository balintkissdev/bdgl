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
#include <BDGL/event/keyboard.h>

#include <BDGL/core/interrupts.h>
#include <BDGL/core/macros.h>
#include <BDGL/core/ports.h>
#include <BDGL/core/types.h>

#include <conio.h>
#include <dos.h>
#include <stdio.h>

#define KEYBOARD_UP_MASK              (0x80)
#define KEYBOARD_HIGH_BIT_CLEAR_MASK  (0x7f)

typedef BDGL_Uint8 RawScancode;
static RawScancode current_raw_scancode;

#define KEYBOARD_MAP_MAX_SIZE (128)
BDGL_KeyStatus BDGL_KeyboardMap[KEYBOARD_MAP_MAX_SIZE];

#define KEYBOARD_BUFFER_MAX_SIZE (256)
typedef struct RingBuffer
{
  BDGL_Uint8 data[KEYBOARD_BUFFER_MAX_SIZE];
  BDGL_Uint8 head;
  BDGL_Uint8 tail;
} RingBuffer;

static RingBuffer key_buffer;

/* Old BIOS keyboard Interrupt Service Routine (ISR) */
static void _interrupt (*BIOSKeyboardHandler)();

/**
 * Our buffered keyboard Interrupt Service Routine (ISR).
 *
 * Called by the hardware keyboard interrupt. Reads raw keyboard scan codes
 * into the keyboard buffer.
 */
static void _interrupt BufferedKeyboardHandler();

void BDGL_InitializeKeyboard()
{
  BDGL_Uint8 i;

  for (i = 0; i < KEYBOARD_MAP_MAX_SIZE; ++i)
  {
    BDGL_KeyboardMap[i] = BDGL_KEY_RELEASED;
  }

  /* Save the original BIOS keyboard handler to be able to restore later. */
  BIOSKeyboardHandler = _dos_getvect(BDGL_INTERRUPT_IRQ_KEYBOARD);

  key_buffer.head = 0;
  key_buffer.tail = 0;

  /* Install buffered keyboard interrupt handler */
  _dos_setvect(BDGL_INTERRUPT_IRQ_KEYBOARD, BufferedKeyboardHandler);
}

void BDGL_CleanupKeyboard()
{
  /* Restore BIOS keyboard interrupt handler */
  _dos_setvect(BDGL_INTERRUPT_IRQ_KEYBOARD, BIOSKeyboardHandler);
}

BDGL_Bool BDGL_PollKeyboard(BDGL_KeyEvent *event)
{
  RawScancode scancode;
  BDGL_Bool has_event = BDGL_FALSE;

  if (key_buffer.head != key_buffer.tail)
  {
    scancode = key_buffer.data[key_buffer.head];

    if (scancode == 0xe0)
    {
      ++key_buffer.head;
      return has_event;
    }

    ++key_buffer.head;

    event->key = scancode & KEYBOARD_HIGH_BIT_CLEAR_MASK;
    if (scancode & KEYBOARD_UP_MASK)
    {
      event->status = BDGL_KEY_RELEASED;
    }
    else
    {
      event->status = BDGL_KEY_PRESSED;
    }

    has_event = BDGL_TRUE;
  }

  return has_event;
}

const char* BDGL_GetKeyName(BDGL_KeyEvent *key_event)
{
  switch (key_event->key)
  {
    case BDGL_KEY_SCAN_NONE:          return "NONE";
    case BDGL_KEY_SCAN_ESCAPE:        return "ESC";
    case BDGL_KEY_SCAN_1:             return "1";
    case BDGL_KEY_SCAN_2:             return "2";
    case BDGL_KEY_SCAN_3:             return "3";
    case BDGL_KEY_SCAN_4:             return "4";
    case BDGL_KEY_SCAN_5:             return "5";
    case BDGL_KEY_SCAN_6:             return "6";
    case BDGL_KEY_SCAN_7:             return "7";
    case BDGL_KEY_SCAN_8:             return "8";
    case BDGL_KEY_SCAN_9:             return "9";
    case BDGL_KEY_SCAN_0:             return "0";
    case BDGL_KEY_SCAN_DASH:          return "-";
    case BDGL_KEY_SCAN_EQUALS:        return "=";
    case BDGL_KEY_SCAN_BACKSPACE:     return "BACKSPACE";
    case BDGL_KEY_SCAN_TAB:           return "TAB";
    case BDGL_KEY_SCAN_Q:             return "q";
    case BDGL_KEY_SCAN_W:             return "w";
    case BDGL_KEY_SCAN_E:             return "e";
    case BDGL_KEY_SCAN_R:             return "r";
    case BDGL_KEY_SCAN_T:             return "t";
    case BDGL_KEY_SCAN_Y:             return "y";
    case BDGL_KEY_SCAN_U:             return "u";
    case BDGL_KEY_SCAN_I:             return "i";
    case BDGL_KEY_SCAN_O:             return "o";
    case BDGL_KEY_SCAN_P:             return "p";
    case BDGL_KEY_SCAN_LEFT_BRACKET:  return "[";
    case BDGL_KEY_SCAN_RIGHT_BRACKET: return "]";
    case BDGL_KEY_SCAN_ENTER:         return "ENTER";
    case BDGL_KEY_SCAN_CTRL:          return "CTRL";
    case BDGL_KEY_SCAN_A:             return "a";
    case BDGL_KEY_SCAN_S:             return "s";
    case BDGL_KEY_SCAN_D:             return "d";
    case BDGL_KEY_SCAN_F:             return "f";
    case BDGL_KEY_SCAN_G:             return "g";
    case BDGL_KEY_SCAN_H:             return "h";
    case BDGL_KEY_SCAN_J:             return "j";
    case BDGL_KEY_SCAN_K:             return "k";
    case BDGL_KEY_SCAN_L:             return "l";
    case BDGL_KEY_SCAN_SEMICOLON:     return ";";
    case BDGL_KEY_SCAN_APOSTROPHE:    return "'";
    case BDGL_KEY_SCAN_SHIFT_LEFT:    return "LEFT SHIFT";
    case BDGL_KEY_SCAN_BACKSLASH:     return "\\";
    case BDGL_KEY_SCAN_Z:             return "z";
    case BDGL_KEY_SCAN_X:             return "x";
    case BDGL_KEY_SCAN_C:             return "c";
    case BDGL_KEY_SCAN_V:             return "v";
    case BDGL_KEY_SCAN_B:             return "b";
    case BDGL_KEY_SCAN_N:             return "n";
    case BDGL_KEY_SCAN_M:             return "m";
    case BDGL_KEY_SCAN_COMMA:         return ",";
    case BDGL_KEY_SCAN_PERIOD:        return ".";
    case BDGL_KEY_SCAN_FORWARD_SLASH: return "/";
    case BDGL_KEY_SCAN_SHIFT_RIGHT:   return "RIGHT SHIFT";
    case BDGL_KEY_SCAN_PRINT_SCREEN:  return "PRT SCR";
    case BDGL_KEY_SCAN_ALT:           return "ALT";
    case BDGL_KEY_SCAN_SPACE:         return " ";
    case BDGL_KEY_SCAN_CAPS_LOCK:     return "CAPS LOCK";
    case BDGL_KEY_SCAN_F1:            return "F1";
    case BDGL_KEY_SCAN_F2:            return "F2";
    case BDGL_KEY_SCAN_F3:            return "F3";
    case BDGL_KEY_SCAN_F4:            return "F4";
    case BDGL_KEY_SCAN_F5:            return "F5";
    case BDGL_KEY_SCAN_F6:            return "F6";
    case BDGL_KEY_SCAN_F7:            return "F7";
    case BDGL_KEY_SCAN_F8:            return "F8";
    case BDGL_KEY_SCAN_F9:            return "F9";
    case BDGL_KEY_SCAN_F10:           return "F10";
    case BDGL_KEY_SCAN_F11:           return "F11";
    case BDGL_KEY_SCAN_F12:           return "F12";
    case BDGL_KEY_SCAN_NUM_LOCK:      return "NUM LOCK";
    case BDGL_KEY_SCAN_SCROLL_LOCK:   return "SCROLL LOCK";
    case BDGL_KEY_SCAN_HOME:          return "HOME";
    case BDGL_KEY_SCAN_UP:            return "UP";
    case BDGL_KEY_SCAN_PAGE_UP:       return "PAGE UP";
    case BDGL_KEY_SCAN_MINUS:         return "-";
    case BDGL_KEY_SCAN_LEFT:          return "LEFT";
    case BDGL_KEY_SCAN_CENTER:        return "CENTER";
    case BDGL_KEY_SCAN_RIGHT:         return "RIGHT";
    case BDGL_KEY_SCAN_PLUS:          return "+";
    case BDGL_KEY_SCAN_END:           return "END";
    case BDGL_KEY_SCAN_DOWN:          return "DOWN";
    case BDGL_KEY_SCAN_PAGE_DOWN:     return "PAGE DOWN";
    case BDGL_KEY_SCAN_INSERT:        return "INSERT";
    case BDGL_KEY_SCAN_DEL:           return "DEL";
    default:                          return "UNKNOWN";
  }
}

static void _interrupt BufferedKeyboardHandler()
{
  static BDGL_Uint8 tmp;

  current_raw_scancode = inp(BDGL_PORT_KEYBOARD_DATA);
  outp(BDGL_PORT_KEYBOARD_STATUS, (tmp = inp(BDGL_PORT_KEYBOARD_STATUS)) | KEYBOARD_UP_MASK);
  outp(BDGL_PORT_KEYBOARD_STATUS, tmp);
  outp(0x20, 0x20);

  if (current_raw_scancode & KEYBOARD_UP_MASK)
  {
    BDGL_KeyboardMap[current_raw_scancode & KEYBOARD_HIGH_BIT_CLEAR_MASK] = BDGL_KEY_RELEASED;
  }
  else
  {
    BDGL_KeyboardMap[current_raw_scancode & KEYBOARD_HIGH_BIT_CLEAR_MASK] = BDGL_KEY_PRESSED;
  }

  *(key_buffer.data + key_buffer.tail) = current_raw_scancode;
  ++key_buffer.tail;
}

#ifndef BDGL_CORE_H_
#define BDGL_CORE_H_

#include <dos.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Primitive types */
typedef unsigned char           BDGL_BYTE;  /* 1 byte, 0-255            */
typedef unsigned short          BDGL_WORD;  /* 2 byte, 0-65,535         */
typedef unsigned long           BDGL_DWORD; /* 4 byte, 0-4,294,967,295  */

/* Memory addresses */
#define BDGL_CLOCK_ADDRESS      (0x046C)    /* 18.2 Hz system clock */
#define BDGL_VGA_ADDRESS        (0xA000)    /* VGA array            */

/**
 * Get the sign of a number.
 *
 * @param x         positive or negative number
 * @return          1 for positive, -1 for negative number and 0 for 0
 */
#define BDGL_GetMathSign(x)     ((0 < x) - (x < 0))

/**
 * Helper macro to get the number of elements in an array.
 *
 * BE CAREFUL! It doesn't work with pointers, and arrays passed as function parameters 
 * are decayed as pointers.
 *
 * @param array     array with a constant size
 * @return          number of elements in array
 */
#define BDGL_GetArrayLength(array)         (sizeof((array)) / sizeof((array)[0]))

BDGL_WORD *BDGL_SystemClock = (BDGL_WORD *)MK_FP(0,BDGL_CLOCK_ADDRESS);  // FIXME: encapsulate

/* TODO */
inline float BDGL_GetCurrentTicks()
{
    return (*BDGL_SystemClock) / 18.2;
}

#ifdef __cplusplus
}
#endif

#endif  // BDGL_CORE_H_

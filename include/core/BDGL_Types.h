#ifndef BDGL_TYPES_H_
#define BDGL_TYPES_H_

/** Primitive byte. 1 byte size, values ranging from 0 to 255. */
typedef unsigned char           BDGL_BYTE;

/** Primitive word. 2 byte size, values ranging from 0 to 65,535. */
typedef unsigned short          BDGL_WORD;

/** Primitive double word. 1 byte size, values ranging from 0 to 4,294,967,295. */
typedef unsigned long           BDGL_DWORD;

/** Primitive boolean type. */
typedef enum
{
  BDGL_FALSE,
  BDGL_TRUE
} BDGL_BOOL;

#endif

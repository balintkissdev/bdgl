#include <BDGL/core/core.h>

#include <BDGL/event/keyboard.h>

BDGL_Bool BDGL_InitializeSystem()
{
  BDGL_InitializeKeyboard();
  return BDGL_TRUE;
}

BDGL_Bool BDGL_CleanupSystem()
{
  BDGL_CleanupKeyboard();
  return BDGL_TRUE;
}

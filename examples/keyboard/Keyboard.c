#include <BDGL.h>

#include <stdio.h>

int main(int argc, char* argv[])
{
  BDGL_BOOL quit = BDGL_FALSE;
  BDGL_BYTE key = 0;

  while (!quit)
  {
    key = BDGL_GetScancode();
    if (key)
      printf("%c %d\n", key, key);

    if (key == BDGL_SCAN_ESC)
      quit = BDGL_TRUE;
  }

  printf("Done\n");
  return 0;
}

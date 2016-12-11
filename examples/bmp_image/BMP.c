#include <BDGL.h>

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
  BDGL_BMPImage image;

  /* Create screen */
  BDGL_Screen *screen = BDGL_CreateScreen(BDGL_MODE_VGA_320x200_256_COLOR);
  if (!screen)
  {
    fprintf(stderr, "There was an error when creating screen.\n");
    return 1;
  }

  /* Load image from file */
  image = BDGL_LoadBMP(screen, "IMAGE.BMP");

  /* Initialize and display screen */
  BDGL_InitializeVideo(screen);

  /* Display image */
  BDGL_DrawBMPImage(screen, &image, 10, 10);
  delay(4000);

  /* Free resources */
  BDGL_DestroyBMPImage(&image);
  BDGL_DestroyScreen(screen);

  printf("Done\n");
  return 0;
}

/**
 * Origin of example is from
 * http://www.brackeen.com/vga/
 */
#include <BDGL.hpp>

#include <iostream>
#include <stdlib.h>     // Watcom doesn't recognize <cstdlib>

int main(int argc, char* argv[])
{
  // Variable declarations. Putting local variables here is 
  // how it only compiles under DOS.
  int x1, y1, x2, y2;                 // Variables for lines
  BDGL_WORD i;                        // Loop variable

  BDGL_Rectangle rect;                // Rectangle

  BDGL_Vertex vertices[3] = {         // Vertices
      {0,0},
      {7,5},
      {0,5}
  };

  // Create screen
  bdgl::graphics::Screen screen(BDGL_MODE_VGA_320x200_256_COLOR);

  // Initialize and display screen
  screen.initialize();

  // Draw single pixels
  screen.setDrawColor(BDGL_CYAN);
  screen.drawPoint(0, 0);
  screen.setDrawColor(BDGL_WHITE);
  screen.drawPoint(0, 1);
  screen.setDrawColor(BDGL_CYAN);
  screen.drawPoint(0, 2);
  screen.drawPoint(0, 3);
  screen.drawPoint(0, 4);
  screen.drawPoint(0, 0);
  screen.drawPoint(7, 5);
  screen.drawPoint(0, 5);
  screen.setDrawColor(BDGL_RED);
  screen.drawPoint(-20, -10);         // Test for drawing outside screen
  screen.update();
  delay(4000);
  screen.clear();

  // Draw points
  for(i = 0; i < 50000L; ++i)
  {
    screen.setDrawColor(rand() % screen.colorNumber());
    screen.drawPoint(rand() % screen.width(), rand() % screen.width());
    screen.update();
  }
  screen.clear();

  // Draw lines
  for (i = 0; i < 5000; ++i)
  {
    x1 = rand() % screen.width();
    y1 = rand() % screen.height();
    x2 = rand() % screen.width();
    y2 = rand() % screen.height();

    screen.setDrawColor(rand() % screen.colorNumber());
    screen.drawLine(x1, y1, x2, y2);
    screen.update();
  }
  screen.clear();

  // Draw rectangles
  for (i = 0; i < 5000; ++i)
  {
    rect.x = rand() % screen.width();
    rect.y = rand() % screen.height();
    rect.width = rand() % screen.width();
    rect.height = rand() % screen.height();

    screen.setDrawColor(rand() % screen.colorNumber());
    screen.drawRectangle(rect);
    screen.update();
  }
  screen.clear();

  // Draw polygon
  screen.setDrawColor(BDGL_LIGHT_BLUE);
  screen.drawPolygon(BDGL_GetArrayLength(vertices), vertices);
  screen.update();
  delay(4000);

  // No need to separately free screen resources, 
  // the class destructor takes care of it automatically.

  std::cout << "Done." << std::endl;
  return 0;
}

/*
  Copyright (c) 2016 Bálint Kiss <balint.kiss.501@gmail.com>

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

/**
 * @file BDGL_Video.hpp
 */
#ifndef BDGL_VIDEO_HPP_
#define BDGL_VIDEO_HPP_

#include "BDGL_Video.h"
#include "BDGL_Shapes.h"

#include <iostream>
#include <stdlib.h>     // Watcom doesn't recognize <cstdlib>

namespace bdgl
{
namespace graphics
{

// TODO: member functions for VSync and double buffer option setting
/**
 * C++ wrapper header for DOS screen
 */
class Screen
{
  public:
    Screen()
      : screen_(0)
      {}

    /**
     * Create screen object with the chosen video mode.
     *
     * @param video_mode
     */
    Screen(const BDGL_BYTE video_mode)
    {
      screen_ = BDGL_CreateScreen(video_mode);
      if (!screen_)
      {
        std::cerr << "There was an error when creating screen." << std::endl;
        exit(1);
      }
    }

    /**
     * Free screen resources.
     */
    ~Screen()
    {
      BDGL_DestroyScreen(screen_);
    }

    /**
     * Switch to the specified video mode of the screen.
     */
    void initialize();

    /**
     * Clear screen to draw again.
     */
    void clear();

    /**
     * Update screen with double buffering. Until this call, every pixel is written into
     * a temporary buffer before displaying.
     * This also includes waiting for vertical retrace (VSync)
     */
    void update();

    /**
     * Set drawing color to draw primitives with.
     *
     * @param color         drawing color between 0 and 255
     */
    void setDrawColor(const BDGL_BYTE color);

    /**
     * Draw a single point as a pixel on the screen. On negative coordinates, the 
     * point doesn't wrap around the screen.
     *
     * @param x             horizontal x coordinate
     * @param y             vertical y coordinate
     */
    void drawPoint(const int x, const int y);

    /**
     * Draw a straight line using Bresenham's algorithm.
     *
     * @param x_start       horizontal x coordinate of line starting point
     * @param y_start       vertical y coordinate of line starting point
     * @param x_end         horizontal x coordinate of line ending point
     * @param y_end         vertical y coordinate of line ending point
     */
    void drawLine(
      const int x_start,
      const int y_start,
      const int x_end,
      const int y_end);

    /**
     * Draw outlines of a rectangle.
     *
     * @param rectangle     rectangle to draw
     */
    void drawRectangle(const BDGL_Rectangle& rectangle);

    /**
     * Draw polygonal shape specified by series of vertexes.
     *
     * @param vertex_number     number of vertices to draw. Due to C decaying array
     *                          parameters to pointers, the function can't 
     *                          determine array size internally and needs to be 
     *                          specified outside.
     * @param vertices          series of vertexes to draw
     */
    void drawPolygon(const int vertex_number, BDGL_Vertex const* vertices);

    /**
     * Accessor for screen width
     *
     * @return  width of the screen
     */
    BDGL_WORD width() const;

    /**
     * Accessor for screen height.
     *
     * @return  height of the screen
     */
    BDGL_WORD height() const;

    /**
     * Accessor for color number.
     *
     * @return  number of colors, which can be
     *          4, 16 or 256
     */
    BDGL_WORD colorNumber() const;

  private:
    BDGL_Screen* screen_;
};

inline void Screen::initialize()
{
  BDGL_InitializeVideo(screen_); 
}

inline void Screen::clear()
{
  BDGL_ClearScreen(screen_);
}

inline void Screen::update()
{
  BDGL_UpdateScreen(screen_);
}

inline void Screen::setDrawColor(const BDGL_BYTE color)
{
  BDGL_SetDrawColor(screen_, color);
}

inline void Screen::drawPoint(const int x, const int y)
{
  BDGL_DrawPoint(screen_, x, y);
}

inline void Screen::drawLine(
  const int x_start,
  const int y_start,
  const int x_end,
  const int y_end)
{
  BDGL_DrawLine(screen_, x_start, y_start, x_end, y_end);
}

inline void Screen::drawRectangle(const BDGL_Rectangle& rectangle)
{
  BDGL_DrawRectangle(screen_, &rectangle);
}

inline void Screen::drawPolygon(const int vertex_number, BDGL_Vertex const* vertices)
{
  BDGL_DrawPolygon(screen_, vertex_number, vertices);
}

inline BDGL_WORD Screen::width() const
{
  return screen_->width;
}

inline BDGL_WORD Screen::height() const
{
  return screen_->height;
}

inline BDGL_WORD Screen::colorNumber() const
{
  return screen_->color_number;
}

} // namespace graphics
} // namespace bdgl
#endif  // BDGL_VIDEO_HPP_

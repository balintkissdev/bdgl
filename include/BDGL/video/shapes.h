/*
 * Copyright (c) 2016 Bálint Kiss <balintkissdev@gmail.com>
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
#ifndef _BDGL_SHAPES_H_
#define _BDGL_SHAPES_H_

#include <BDGL/core/core.h>
#include <BDGL/video/screen.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 2D vertex for drawing polygons
 */
typedef struct BDGL_Vertex2D
{
  int x;                          /**< Horizontal x position of vertex */
  int y;                          /**< Vertical y position of vertex */
} BDGL_Vertex2D;

/**
 * Rectagular shape
 */
typedef struct BDGL_Rectangle
{
  int x;                          /**< X coordinate of top left corner */
  int y;                          /**< Y coordinate of top left corner */
  int width;                      /**< Width of rectangle */
  int height;                     /**< Height of rectangle */
} BDGL_Rectangle;

/**
 * Draw a single point as a pixel on the screen.
 *
 * On negative coordinates, the 
 * point doesn't wrap around the screen.
 *
 * @param screen            screen pointer to draw point on
 * @param x                 horizontal x coordinate
 * @param y                 vertical y coordinate
 */
void BDGL_DrawPoint2D(
  BDGL_Screen *const screen,
  const int x,
  const int y);

/**
 * Draw a straight line using Bresenham's algorithm.
 *
 * @param screen            screen pointer to draw line on
 * @param x_start           horizontal x coordinate of line starting point
 * @param y_start           vertical y coordinate of line starting point
 * @param x_end             horizontal x coordinate of line ending point
 * @param y_end             vertical y coordinate of line ending point
 */
void BDGL_DrawLine(
  BDGL_Screen *const screen,
  const int x_start,
  const int y_start,
  const int x_end,
  const int y_end);

/**
 * Draw outlines of a rectangle.
 *
 * @param screen            screen pointer to draw rectangle on
 * @param rectangle         rectangle to draw
 */
void BDGL_DrawRectangle(
  BDGL_Screen *const screen,
  const BDGL_Rectangle *const rectangle);

/**
 * Draw a filled rectangle.
 *
 * @param screen            screen pointer to draw filled rectangle on
 * @param rectangle         rectangle to draw
 */
void BDGL_DrawFilledRectangle(
  BDGL_Screen *const screen,
  const BDGL_Rectangle *const rectangle);

/**
 * Draw polygonal shape specified by series of vertexes.
 *
 * @param screen            screen pointer to draw polygon on
 * @param vertex_number     number of vertices to draw. Due to C decaying array
 *                          parameters to pointers, the function can't 
 *                          determine array size internally and needs to be 
 *                          specified outside.
 * @param vertices          series of vertexes to draw
 */
void BDGL_DrawPolygon2D(
  BDGL_Screen *const screen, 
  BDGL_Vertex2D const* vertices,
  const int vertex_number);

/* TODO */
#if 0
/**
 * Draw filled polygonal shape specified by series of vertexes.
 */
void BDGL_DrawFilledPolygon(
  BDGL_Screen *screen,
  const int vertex_number,
  BDGL_Vertex vertices[],
  const BDGL_Uint8 color);
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  /* _BDGL_SHAPES_H_ */

#ifndef BDGL_VIDEO_HPP_
#define BDGL_VIDEO_HPP_

#include <iostream>
#include <stdlib.h>     // Watcom doesn't recognize <cstdlib>

#include "BDGL_Video.h"

namespace bdgl
{
    // TODO: write doc comments
    class Screen
    {
        public:
            Screen(const BDGL_BYTE video_mode)
            {
                screen_ = BDGL_CreateScreen(video_mode);
                if (!screen_)
                {
                    std::cerr << "There was an error when creating screen." << std::endl;
                    exit(1);
                }
            }

            ~Screen()
            {
                BDGL_DestroyScreen(screen_);
            }

            void initialize();
            void clear();
            void update();

            // TODO: member functions for VSync and double buffer option setting

            void setDrawColor(const BDGL_BYTE color);
            void drawPoint(const int x, const int y);
            void drawLine(const int x_start, const int y_start, const int x_end, const int y_end);
            void drawRectangle(const BDGL_Rectangle& rectangle);
            void drawPolygon(const int vertex_number, BDGL_Vertex const* vertices);

            BDGL_WORD width() const;
            BDGL_WORD height() const;
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

    inline void Screen::drawLine(const int x_start, const int y_start, const int x_end, const int y_end)
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
}   // namespace bdgl

#endif  // BDGL_VIDEO_HPP_

#pragma once
#include <cstdint>
#include <raylib.h>

namespace options {

void init() noexcept;

extern int screen_width;
extern int screen_height;
extern int window_fps;
extern Color background_color;
extern Color text_color;

}


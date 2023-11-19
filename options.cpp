#include <raylib.h>
#include <raygui.h>

#include "options.h"

namespace options {
//namespace options
int screen_width;
int screen_height;
int window_fps;
Color background_color;
Color text_color;

void init() noexcept{
  screen_width = 1200;
  screen_height = 800;
  window_fps = 160;
  background_color = {0,0,0,0};
  text_color = WHITE;
}


}//namespace options


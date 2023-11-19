#include <raylib.h>
#include <raygui.h>

#include "options.h"
#include "screen.h"

/* TODOS
 *
 * Do somwthing ith opacity;
 * SetWindowOpacity(float);
 *
 * Scan clipboard for fens;
 * GetClipboardText(void);
 * 
 * Set clipboard text to copied fen or opther foemat;
 * SetClipboardText(const char *text);
 */




int main () {
  options::init();
  screen::init();
  GuiLoadStyle("src/style.rgs");
  GuiEnable();
 
  while (1) {
    BeginDrawing();
    screen::close_button();
    // screen::move_implem();

    switch (screen::screen_state) {
      case 'M':
        screen::main_menu();break;
      case 'P':
        screen::main_board();break;
      case 'S':
        screen::main_settings();break;
    }

    EndDrawing();
  }

  return 0;
}


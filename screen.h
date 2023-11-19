#pragma onc
#include "options.h"

namespace screen {
extern char screen_state;

void init() noexcept;
void move_implem() noexcept;
void main_menu() noexcept;
void main_board() noexcept;
bool close_button();
void main_settings() noexcept;

}

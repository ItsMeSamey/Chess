#include <thread>
#include <chess.hpp>
#include <cstdint>
#include <iostream>
#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

#include "screen.h"
#include "options.h"


namespace screen{
//namespace screen


uint8_t move,move_2;
char mouse_down_on, screen_state, myside;
uint16_t timeout;
Rectangle rect_close, rect_move, cell_rect;
float scale_factor, close_button_size, cell_width;
Vector2 v, window_pos,mouse_pos{};
Texture2D txr[13];
chess::Board board;
chess::Movelist move_list;
chess::Move chess_move;


void init_main_menu() noexcept{
  scale_factor = GetMonitorHeight(GetCurrentMonitor())/((float)1000);
  close_button_size = scale_factor * 36;
  rect_close = {options::screen_width - 27*scale_factor, 0, 27*scale_factor, 26*scale_factor};
  rect_move = {0, 0, rect_close.x, rect_close.height};
}

void init_cell_grid() noexcept{
  int min = std::min(options::screen_width,options::screen_height);
  cell_rect = {0,min*0.049f,min*0.95f,min*0.95f};
  cell_width = (min*0.95)/8;
  window_pos = {-1,-1};
  mouse_pos = {-1,-1};
  screen_state = 'M';
}

void init_txr() noexcept{
  myside = 'w';
  move = 0;
  txr[(int)chess::Piece::NONE] = LoadTexture("src/100.png");
  txr[(int)chess::Piece::NONE].height = cell_rect.height;
  txr[(int)chess::Piece::NONE].width = cell_rect.width;
  txr[(int)chess::Piece::WHITEKING] = LoadTexture("src/K.png");
  txr[(int)chess::Piece::WHITEKING].height = cell_width;
  txr[(int)chess::Piece::WHITEKING].width = cell_width;
  txr[(int)chess::Piece::BLACKKING] = LoadTexture("src/k.png");
  txr[(int)chess::Piece::BLACKKING].height = cell_width;
  txr[(int)chess::Piece::BLACKKING].width = cell_width;
  txr[(int)chess::Piece::WHITEQUEEN] = LoadTexture("src/Q.png");
  txr[(int)chess::Piece::WHITEQUEEN].height = cell_width;
  txr[(int)chess::Piece::WHITEQUEEN].width = cell_width;
  txr[(int)chess::Piece::BLACKQUEEN] = LoadTexture("src/q.png");
  txr[(int)chess::Piece::BLACKQUEEN].height = cell_width;
  txr[(int)chess::Piece::BLACKQUEEN].width = cell_width;
  txr[(int)chess::Piece::WHITEROOK] = LoadTexture("src/R.png");
  txr[(int)chess::Piece::WHITEROOK].height = cell_width;
  txr[(int)chess::Piece::WHITEROOK].width = cell_width;
  txr[(int)chess::Piece::BLACKROOK] = LoadTexture("src/r.png");
  txr[(int)chess::Piece::BLACKROOK].height = cell_width;
  txr[(int)chess::Piece::BLACKROOK].width = cell_width;
  txr[(int)chess::Piece::WHITEBISHOP] = LoadTexture("src/B.png");
  txr[(int)chess::Piece::WHITEBISHOP].height = cell_width;
  txr[(int)chess::Piece::WHITEBISHOP].width = cell_width;
  txr[(int)chess::Piece::BLACKBISHOP] = LoadTexture("src/b.png");
  txr[(int)chess::Piece::BLACKBISHOP].height = cell_width;
  txr[(int)chess::Piece::BLACKBISHOP].width = cell_width;
  txr[(int)chess::Piece::WHITEKNIGHT] = LoadTexture("src/N.png");
  txr[(int)chess::Piece::WHITEKNIGHT].height = cell_width;
  txr[(int)chess::Piece::WHITEKNIGHT].width = cell_width;
  txr[(int)chess::Piece::BLACKKNIGHT] = LoadTexture("src/n.png");
  txr[(int)chess::Piece::BLACKKNIGHT].height = cell_width;
  txr[(int)chess::Piece::BLACKKNIGHT].width = cell_width;
  txr[(int)chess::Piece::WHITEPAWN] = LoadTexture("src/P.png");
  txr[(int)chess::Piece::WHITEPAWN].height = cell_width;
  txr[(int)chess::Piece::WHITEPAWN].width = cell_width;
  txr[(int)chess::Piece::BLACKPAWN] = LoadTexture("src/p.png");
  txr[(int)chess::Piece::BLACKPAWN].height = cell_width;
  txr[(int)chess::Piece::BLACKPAWN].width = cell_width;
  for (uint8_t i{}; i < 12; i++){
    SetTextureFilter(txr[i], TEXTURE_FILTER_BILINEAR);
  }
}

void init_window() noexcept{
  SetConfigFlags(FLAG_MSAA_4X_HINT);
  InitWindow(options::screen_width, options::screen_height, "Whatever");
  SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));
  SetWindowState(FLAG_WINDOW_UNDECORATED);
}

void init() noexcept{
  std::thread t3(&init_cell_grid);
  init_window();
  init_main_menu();
  init_txr();
  t3.join();
  return;
}

bool close_button(){
  if (CheckCollisionPointRec(GetMousePosition(), rect_close)){
    DrawPoly({(float)options::screen_width, 0}, 5, close_button_size, -45, {222,20,20, 255});
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
      mouse_down_on |= 1;
    }
    if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
      if (mouse_down_on){
        CloseWindow();
        std::exit(0);
      }
    }
    return true;
  }
  else{
    DrawPoly({(float)options::screen_width, 0}, 5, close_button_size, -45, {222,21,30,150});
    mouse_down_on = 0;
    return false;
  }
}

void move_implem() noexcept{
  if (CheckCollisionPointRec(GetMousePosition(), rect_move)){
    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
      if (window_pos.x > 0 && mouse_pos.x > 0){
        SetWindowPosition(window_pos.x + GetMousePosition().x - mouse_pos.x, window_pos.y + GetMousePosition().y - mouse_pos.y);
      }
      window_pos = GetWindowPosition();
      mouse_pos = GetMousePosition();
    }
    else {
    window_pos.x = -1;
    }
  }
  else {
    window_pos.x = -1;
  }
}

void main_menu() noexcept{
  ClearBackground(options::background_color);
  if (GuiButton({(float)options::screen_width/2 -70, 120, 140, 60}, "PLAY !!")){
    screen_state = 'P';
  }
  else if (GuiButton({(float)options::screen_width/2 -70, 120 + 80, 140, 60}, "Settings")) {
    screen_state = 'S';
  }
}

[[nodiscard]] inline chess::Square cell_num(uint8_t i){if (myside == 'b'){return (chess::Square)i;}return (chess::Square)(63-i);}

void draw_board() noexcept{
  ClearBackground(options::background_color);
  DrawTexture(txr[12], cell_rect.x, cell_rect.y, WHITE);
  GuiGrid(cell_rect, "", cell_width, 1, &v);

  for (uint8_t i = 0; i < 64;i++){
    uint8_t at = (uint8_t)board.at(cell_num(i));
    if (at != 12){
      DrawTexture(txr[at], cell_rect.x + cell_width*(i&7), cell_rect.y + cell_width*(i>>3), {255,255,255,255});
    }
  }
}

void gen_moves(){
  chess::movegen::legalmoves(move_list, board);
}


void make_moves(){
  if (v.x != -1){
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
      std::cout << ((int)v.x) << '-';
      std::cout << ((int)v.y) << '=';
      std::cout << ((((int)(v.y)) << 3) | ((int)v.x)) << '\n';

      if (move == 0){
        uint8_t at = (uint8_t)board.at(cell_num(cell_num(move)));
        if( at != 12){
          std::cout << "!" << (int)at << "!";
          move = cell_num( (((uint16_t)(v.y)) << 3) | ((uint16_t)v.x) );
          timeout = options::window_fps/8;
        }
      }
      else {
        move_2 = cell_num( (((uint16_t)(v.y)) << 3) | ((uint16_t)v.x) );
        chess_move = chess::Move::make((chess::Square)move, (chess::Square)move_2);
        if (move_list.find(chess_move) != -1){
          board.makeMove(chess_move);
        }
        move = move_2 = 0;
      }
    }
    else if (move != 0 && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
      move_2 = cell_num((((uint16_t)(v.y)) << 3) | ((uint16_t)v.x));
      if (move != move_2){
        chess_move = chess::Move::make((chess::Square)move, (chess::Square)move_2);
        if (move_list.find(chess_move) != -1){
          board.makeMove(chess_move);
        }
        move = move_2 = 0;
      }
    }
  }
  if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
    if (timeout != 0){
      timeout--;
      return;
    }
    else {
      if (move != 0){
        uint8_t at = (uint8_t)board.at(cell_num(cell_num(move)));
        if( at != 12){
          DrawTexture(txr[at], GetMouseX() - cell_width/2, GetMouseY() - cell_width/2, {255,255,255,155});
        }
      }
    }
  }

}

void main_board() noexcept{
  std::thread t1(&gen_moves);
  draw_board();
  t1.join();
}

// void main_board() noexcept{}

void main_settings() noexcept{
  ClearBackground(options::background_color);
}




}//namespace screen


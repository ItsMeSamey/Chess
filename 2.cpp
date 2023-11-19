#include <chess.hpp>
#include <iostream>


int main () {
  chess::Board board;
  chess::movegen();
  std::cout << (int)chess::Piece::NONE <<'\n';
}

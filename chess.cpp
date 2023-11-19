#include <cstdint>
#include <asm/bitops.h>

#include "chess.h"

namespace chess {

class Board {
public:
  uint64_t hash;
  uint64_t[12*2];


  Board();
  Board(Board &&) = default;
  Board(const Board &) = default;
  Board &operator=(Board &&) = default;
  Board &operator=(const Board &) = default;
  ~Board();

private:
  
};



}//namespace chess

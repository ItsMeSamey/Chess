#!/bin/bash

sudo su -c "curl https://raw.githubusercontent.com/Disservin/chess-library/master/include/chess.hpp > /usr/include/chess.hpp &&
  curl https://raw.githubusercontent.com/raysan5/raygui/master/src/raygui.h > /usr/include/raygui.h"

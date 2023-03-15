
#include "bs_game.h"

int main() {
  BsGame game;

  game.init();
  game.mainLoop();
  game.finish();

  return 0;
}

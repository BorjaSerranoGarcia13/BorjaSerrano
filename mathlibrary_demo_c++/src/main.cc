
#include "bs_game.h"
#include "bs_path.h"

int main() {
  BsGame game;

  game.init();
  game.mainLoop();
  game.finish();

  return 0;
}
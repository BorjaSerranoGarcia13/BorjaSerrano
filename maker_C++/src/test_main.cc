
/**
 * Author: Borja Serrano <serranoga@esat-alumni.com>
 * Filename: bs_backgorund.cc
 *
 * Implementation: background class
 */

#include "bs_game.cc"

int esat::main(int argc, char **argv) {

  bsGame game;
  bsDataBase *b_ = new bsDataBase();

  game.init(b_);
  game.mainLoop(b_);
  game.finish();

  return 0;
}

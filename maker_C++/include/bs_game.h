/**
 * Author: Borja Serrano <serranoga@esat-alumni.com>
 * Filename: bs_backgorund.cc
 *
 * Implementation: background class
 */

 #ifndef __BS_GAME_H__
 #define __BS_GAME_H__ 1

 #include "bs_window.cc"
 #include "bs_rect.cc"
 #include "bs_label.cc"
 #include "bs_sprite.cc"
 #include "bs_scene.cc"
 #include "bs_game_manager.h"
  #include "bs_database.cc"

/**
/* Class game
/* manage the main of the program
*/
class bsGame {
 public:
  bsGame(); /**<  Constructor used to initilizate the class  */

  /* init the game
    /*
    \*param database to do the loads
*/
  void init(bsDataBase *b_);

   /* the loop of the game
    /*
    \*param database to do the loads
*/
  void mainLoop(bsDataBase *b_);
  void finish(); /**<   void to finish the program*/

  bsScene scene_; /**<   object scene created to be managed in the game*/
  bsWindow window_;  /**<   object window created to be managed*/

 };

 #endif // __BS_GAME_H__

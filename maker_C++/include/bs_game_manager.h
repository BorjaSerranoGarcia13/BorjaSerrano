
/**
 * Author: Borja Serrano <serranoga@esat-alumni.com>
 * Filename: bs_backgorund.cc
 *
 * Implementation: background class
 */

#ifndef __BS_GAMEMANAGER_H__
#define __BS_GAMEMANAGER_H__ 1

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

 #include "esat/draw.h"
#include "esat/math.h"

/**
/* Class gameManager
/* Singleton to manage all the gameobjects and var
*/
class bsGameManager {

 public:
 //* the instance from the singleton
    /*
    \*param returns the instance of the static object
*/
  static bsGameManager *getInstance()
  {
    if (instance == NULL) {
      instance = new bsGameManager();
      return 0;
    }
    else {
      return instance;
    }
  }

  bool edition_; /**<   var to manage the edition mode*/
  int sizeEdition; /**<   var to manage the size of the game*/
  bsRect *player_; /**<   object to manage the player*/
  bsSprite *background_; /**<   object to manage the background*/
  bsLabel *label_; /**<   object to manage the label*/
  bsRect *cubes[900]; /**<   object to manage all cubes can be created and used*/
  bool puzzle_mode_; /**<   var to manage the puzzle mode*/
  bsEntity** all_elements_; /**<   pointer to pointer of all elements can be used*/
  bsEntity** all_elements_tag_; /**<   pointer to pointer of all elements can be used, ordered by tag*/
  bool save_; /**<   var to know when to save to database*/

 //* set if its time to save
    /*
    \*param receive the var to set
*/
  void set_save(bool save){
    save_ = save;
  }

//* get the var to save
    /*
    \*param return the var
*/
  bool save() {
    return save_;
  }

 //* set if its edition active
    /*
    \*param receive the var to set
*/
  void set_edition(bool edition) {
    edition_ = edition;
  }

//* set the size od game
    /*
    \*param receive the var to set
*/
  void set_size_edition(int edition) {
    sizeEdition = edition;
  }

//* get the var to size
    /*
    \*param return the var
*/
  int size_edition()
  {
    return sizeEdition;
  }

//* get the var to edit
    /*
    \*param return the var
*/
  bool edition() {
    return edition_;
  }

//* get the var to puzzle mode
    /*
    \*param return the var
*/
  bool puzzle_mode() {
    return puzzle_mode_;
  }

//* set if its puzzle mode active
    /*
    \*param receive the var to set
*/
  void set_puzzle_mode(bool edition) {
    puzzle_mode_ = edition;
  }

 protected:

  bsGameManager() {
    player_ = new bsRect();
    background_ = new bsSprite();
    label_ = new bsLabel();
    label_->tag_ = 4;
    for (int i = 0; i < 900; i++)
    {
      cubes[i] = new bsRect();
    }
    player_->init({400.0f, 300.0f}, (float)800/sizeEdition * 0.5f, (float)600/sizeEdition * 0.5f, 0, {1,1},
                    255, 0, 0, 255,
                    100, 0, 0, 255,
                    15);
    player_->enabled_ = 1;
    player_->tag_ = 0;
    all_elements_ = (bsEntity**)malloc(903 * sizeof(bsEntity));
    all_elements_tag_ = (bsEntity**)malloc(903 * sizeof(bsEntity));
    edition_ = true;
    sizeEdition = 10;

    puzzle_mode_ = false;


  } /**<  Constructor used to initilizate the class and all objects */

  virtual ~bsGameManager() {
    
  } /**<  destroy and free all objects used */

  bsGameManager(bsGameManager const&);

 private:
  static bsGameManager *instance; /**<  the static instance of clss */

};

bsGameManager* bsGameManager::instance=NULL;

#endif // __BS_GAMEMANAGER_H__

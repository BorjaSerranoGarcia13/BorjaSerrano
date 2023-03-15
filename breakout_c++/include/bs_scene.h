
#ifndef __BS_SCENE_H__
#define __BS_SCENE_H__ 1

#include <SFML/Window/Mouse.hpp>

#include "bs_label.h"

/**
/* Class scene
/* manage evrything from the scene, gameplay
*/
class BsScene {
 public:

  enum TypeScene {
    kTypeScene_LoginSign = 0,
    kTypeScene_Start = 1,
    kTypeScene_Board = 2,
    kTypeScene_GameOver = 3    
  };

  /**
  * @brief constructor of class
  */
  BsScene();

  /**
  * @brief Destructor used to initilizate the class
  */
  ~BsScene();

  virtual void init() = 0; /**<   virtual init to heredate the variables */

  virtual void update() = 0; /**<   virtual init to heredate the variables */

  virtual void draw(sf::RenderWindow& window) = 0; /**<   virtaul void to draw entity*/

  uint8_t enabled_;
  int tag_;

  BsLabel* label_ = nullptr;
  uint8_t size_label_;

 };

#endif // __BS_SCENE_H__

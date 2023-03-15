
#ifndef __BS_IMGUI__
#define __BS_IMGUI__ 1

//#include "bs_game_manager.h"

#include "../deps/imgui-sfml-master/imgui-SFML.h"
#include "../deps/imgui-sfml-master/imgui.h"

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include <stdint.h>
#include <iostream>

class BsImgui {
 public:

   enum TypeScene {
     kTypeScene_LoginSign = 0,
     kTypeScene_Start = 1,
     kTypeScene_Board = 2,
     kTypeScene_GameOver = 3,
   };

   /**
  * @brief constructor of class
  */
  BsImgui();

  /**
  * @brief destructor of class
  */
  virtual ~BsImgui();

  BsImgui(const BsImgui& o) =delete;

  /**
  * @brief inti the enemy
  */
  void init(sf::RenderWindow& window);

  void scene_enabled(uint8_t scene_manager);
  void scene_manager();

  void update(sf::RenderWindow& window, sf::Clock clock);


  // ATTRIBUTES
  uint8_t scene_manager_;
  uint8_t enabled_;
};


#endif // __BS_IMGUI__

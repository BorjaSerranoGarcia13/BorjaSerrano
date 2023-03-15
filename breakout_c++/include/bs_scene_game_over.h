
#ifndef __BS_SCENE_GAME_OVER_H__
#define __BS_SCENE_GAME_OVER_H__ 1

#include "bs_scene.h"

/**
/* Class scene
/* manage evrything from the scene, gameplay
*/
class BsSceneGameOver : public BsScene {
 public:

  /**
  * @brief constructor of class
  */
  BsSceneGameOver();

  BsSceneGameOver(const BsSceneGameOver& copy) = delete;
  BsSceneGameOver& operator=(const BsSceneGameOver&) = delete;

   /**
  * @brief Destructor used to initilizate the class
  */
  virtual ~BsSceneGameOver();

  void init() override;

  void update() override;

  void draw(sf::RenderWindow& window) override;

};

#endif // __BS_SCENE_GAME_OVER_H__

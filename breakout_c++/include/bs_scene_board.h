
#ifndef __BS_SCENE_BOARD_H__
#define __BS_SCENE_BOARD_H__ 1

#include "bs_scene.h"

/**
/* Class scene
/* manage evrything from the scene, gameplay
*/
class BsSceneBoard : public BsScene {
 public:

  /**
  * @brief constructor of class
  */
  BsSceneBoard();

  BsSceneBoard(const BsSceneBoard& copy) = delete;
  BsSceneBoard& operator=(const BsSceneBoard&) = delete;

   /**
  * @brief Destructor used to initilizate the class
  */
  virtual ~BsSceneBoard();

  void init() override;

  void update() override;

  void draw(sf::RenderWindow& window) override;
 protected:

 private:


 };

#endif // __BS_SCENE_BOARD_H__

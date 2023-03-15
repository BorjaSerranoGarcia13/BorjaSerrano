
#ifndef __BS_SCENE_START_H__
#define __BS_SCENE_START_H__ 1

#include "bs_scene.h"

/**
/* Class scene
/* manage evrything from the scene, gameplay
*/
class BsSceneStart : public BsScene {
 public:

  /**
  * @brief constructor of class
  */
  BsSceneStart();

  BsSceneStart(const BsSceneStart& copy) = delete;
  BsSceneStart& operator=(const BsSceneStart&) = delete;

   /**
  * @brief Destructor used to initilizate the class
  */
  virtual ~BsSceneStart();

  void init() override;

  void update() override;

  void draw(sf::RenderWindow& window) override;



 };

#endif // __BS_SCENE_START_H__

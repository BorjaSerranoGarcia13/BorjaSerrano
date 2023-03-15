
#ifndef __BS_SCENE_LOGIN_SIGN_H__
#define __BS_SCENE_LOGIN_SIGN_H__ 1

#include "bs_scene.h"

/**
/* Class scene
/* manage evrything from the scene, gameplay
*/
class BsSceneLoginSign : public BsScene {
 public:

  /**
  * @brief constructor of class
  */
  BsSceneLoginSign();

  BsSceneLoginSign(const BsSceneLoginSign& copy) = delete;
  BsSceneLoginSign& operator=(const BsSceneLoginSign&) = delete;

   /**
  * @brief Destructor used to initilizate the class
  */
  virtual ~BsSceneLoginSign();

  void init() override;

  void update() override;

  void draw(sf::RenderWindow& window) override;
 protected:

 private:


 };

#endif // __BS_SCENE_LOGIN_SIGN_H__

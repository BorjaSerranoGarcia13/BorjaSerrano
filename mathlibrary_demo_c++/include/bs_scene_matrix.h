
#ifndef __BS_SCENE_GAME_OVER_H__
#define __BS_SCENE_GAME_OVER_H__ 1

#include "bs_scene.h"
#include "bs_path.h"
#include "bs_rect.h"
#include "bs_game_manager.h"

#define MPI 3.14159265358979323846

const int kMaxRect = 15;

/**
/* Class scene
/* manage evrything from the scene, gameplay
*/
class BsSceneMatrix : public BsScene {
 public:

  /**
  * @brief constructor of class
  */
  BsSceneMatrix();

  BsSceneMatrix(const BsSceneMatrix& copy) = delete;
  BsSceneMatrix& operator=(const BsSceneMatrix&) = delete;

   /**
  * @brief Destructor used to initilizate the class
  */
  virtual ~BsSceneMatrix();

  /**
   * @brief init scene
   */
  void init() override;

  /**
   * @brief update scene
   */
  void update() override;

  /**
   * @brief draw scene
   */
  void draw(sf::RenderWindow& window) override;

  /**
   * @brief create shape from mouse input
   */
  void createShape();
  

  BsPath* path_ = nullptr;

  BsGameManager& GM_ = BsGameManager::getInstance();
  std::string font_;
};

#endif // __BS_SCENE_GAME_OVER_H__

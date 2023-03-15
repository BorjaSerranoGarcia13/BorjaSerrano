
#ifndef __BS_SCENE_START_H__
#define __BS_SCENE_START_H__ 1

#include "bs_scene.h"
#include "bs_path.h"
#include "bs_rect.h"
#include "bs_game_manager.h"

#define MPI 3.14159265358979323846

const int kMaxRects = 15;
const int kRectRotate = 6;

/**
/* Class scene
/* manage evrything from the scene, gameplay
*/
class BsSceneVector : public BsScene {
 public:

  /**
  * @brief constructor of class
  */
	 BsSceneVector();

	 BsSceneVector(const BsSceneVector& copy) = delete;
	 BsSceneVector& operator=(const BsSceneVector&) = delete;

   /**
  * @brief Destructor used to initilizate the class
  */
  virtual ~BsSceneVector();

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
   * @brief vector methods used in the demo
   */
  void vectorMethods();

  /**
   * @brief move shapes from mouse input
   */
  void moveShapes();

  /**
   * @brief shapes follow another shape, some vector methods used 
   */
  void followShapes();
  /**
   * @brief scale vector2
   */
  void scaleVector2();
  /**
   * @brief scale vector3
   */
  void scaleVector3();

  /**
   * @brief rotate vector2
   */
  void rotateVector2();
  /**
   * @brief rotate vector3
   */
  void rotateVector3();

  /**
   * @brief reflection a vector2
   */
  void reflectionVector3();

  /**
   * @brief get inverse from matrix3
   */
  void inverseMatrix3x3();
  /**
   * @brief get inverse from matrix4
   */
  void inverseMatrix4x4();

  BsGameManager& GM_ = BsGameManager::getInstance();

  BsRect* rect_ = nullptr;
  std::string font_;

  uint8_t do_scale_;
  uint8_t do_distance_normalize_;
  uint8_t do_lerp_;
  uint8_t do_lerp_unclamped;
  uint8_t do_dot_product;

  uint8_t direction_;
  Vector2 rect_center_;

  Vector2 distanceA_;
  Vector2 distanceB_;
  Vector2 vector_direction_;
  float distance_;

  int index_shape_;
  bool rect_collision_;
  bool ball_collision_;

  sf::CircleShape circle_;

  uint8_t scale_vector2_;
  uint8_t scale_vector3_;

  Vector2 mouse_vector_;
 };

#endif // __BS_SCENE_START_H__

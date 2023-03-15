
#ifndef __BS_BALL__
#define __BS_BALL__ 1

#include "bs_character.h"

class BsBall : public BsCharacter {
 public:

   const float kMinY = 5.0f;
   const float kMaxY = 780.0f;
   const float kMinX = 5.0f;
   const float kMaxX = 980.0f;
  const float kCollisionX = 3.0f;
  const float kCollisionY = 5.0f;

  const float kSpaceCollisionBlock = 450.0f;
  const float kSpaceCollisionPlayer = 600.0f;


   /**
  * @brief constructor of class
  */
  BsBall();

  /**
  * @brief destructor of class
  */
  virtual ~BsBall();

  BsBall(const BsBall& o) = delete;
  BsBall& operator=(const BsBall& o) = delete;

  /**
  * @brief inti the enemy
  */
  void init();

  void update() override;

  bool collision(sf::Vector2f rect2, sf::Vector2f size);

  const sf::Vector2f direction();
  void set_direction(sf::Vector2f direction);

  const float velocity();
  void set_velocity(float velocity);

  // ATTRIBUTES
  bool start_;
  bool enabled_collision_;

  sf::Vector2f direction_;
  float velocity_;

  bool life_lost_;
};


#endif // __BS_BALL__

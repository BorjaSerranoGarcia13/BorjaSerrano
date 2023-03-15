
#ifndef __BS_PLAYER__
#define __BS_PLAYER__ 1

#include "bs_character.h"

class BsPlayer : public BsCharacter {
 public:
  enum PlayerDirection {
    kPlayerDirection_None = 0,
    kPlayerDirection_Left = 1,
    kPlayerDirection_Right = 2
  };

  /**
  * @brief constructor of class
  */
  BsPlayer();

  BsPlayer(const BsPlayer& copy) = delete;
  BsPlayer& operator=(const BsPlayer&) = delete;
  /**
  * @brief constructor of class
  */
  virtual ~BsPlayer();

  /**
  * @brief inti the player
  */
  void init();

  void init(sf::Vector2f new_size);

  void init(sf::Vector2f pos, sf::Vector2f size, float rotation, sf::Vector2f scale, uint8_t border_r, uint8_t border_g, uint8_t border_b, uint8_t border_a, uint8_t interior_r, uint8_t interior_g, uint8_t interior_b, uint8_t interior_a, uint8_t hollow);

  void update() override;

  void set_new_size();
  sf::Vector2f new_size();
  float collision_points_[11];

 private:
  // ATTRIBUTES
  uint8_t direction_;
  sf::Vector2f new_size_;
};


#endif // __BS_PLAYER__

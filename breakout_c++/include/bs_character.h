
#ifndef __BS_CHARACTER__
#define __BS_CHARACTER__ 1

#include "bs_rect.h"
#include "bs_game_manager.h"

class BsCharacter : public BsRect {

 public:

  enum TypeCharacter {
    kTypeCharacter_None = 0,
    kTypeCharacter_Player = 1,
    kTypeCharacter_Block = 2
  };

  // CONSTRUCTOR AND DESTRUCTOR

  /**
  * @brief constructor of class
  */
   BsCharacter();

  /**
  * @brief Destructor used to initilizate the class
  */
   virtual ~BsCharacter();

   BsCharacter(const BsCharacter& o) = delete;
   BsCharacter& operator=(const BsCharacter& o) = delete;

   // METHODS

  /**
  * @brief default init
  */
   void init();

   virtual void update() = 0;

  /**
  * @brief constructor with the init done
  * @param pos the pos to set
  * @param scale the scale to set
  * @param rotation the rotation to set
  */
  void init(sf::Vector2f pos, sf::Vector2f size, float rotation,
    sf::Vector2f scale, uint8_t border_r, uint8_t border_g, uint8_t border_b,
    uint8_t border_a, uint8_t interior_r, uint8_t interior_g,
    uint8_t interior_b, uint8_t interior_a, uint8_t hollow);

  const uint8_t type_character();

  void set_type_character(uint8_t type_character);

  const uint8_t health_points();

  void set_health_points(uint8_t health_points);

  const bool enabled();

  void set_enabled(uint8_t enabled);

  void draw(sf::RenderWindow& window);

  // ATTRIBUTES
  uint8_t type_character_;
  uint8_t health_points_;

};

#endif // __BS_CHARACTER__

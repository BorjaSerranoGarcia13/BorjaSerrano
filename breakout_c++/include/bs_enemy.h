
#ifndef __BS_ENEMY__
#define __BS_ENEMY__ 1

#include "bs_character.h"

class BsEnemy : public BsCharacter {
 public:

   /**
  * @brief constructor of class
  */
  BsEnemy();

  /**
  * @brief destructor of class
  */
  virtual ~BsEnemy();

  BsEnemy(const BsEnemy& o) ;

  /**
  * @brief inti the enemy
  */
  void init();

  void update() override;


  // ATTRIBUTES




};


#endif // __BS_ENEMY__

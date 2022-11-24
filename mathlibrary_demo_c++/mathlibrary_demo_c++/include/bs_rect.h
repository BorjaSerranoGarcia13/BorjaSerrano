
/**
 * Author: Borja Serrano <serranoga@esat-alumni.com>
 * Filename: Bs_backgorund.cc
 *
 * Implementation: rect class
 */

#ifndef __BS_RECT__
#define __BS_RECT__ 1

#include "bs_path.h"

/**
/* Class rect, heredates from entity
/* manage rects to creat and use
*/
class BsRect : public BsPath {

 public:
  /// METHODS

  /**
 * @brief constructor of class
 */
  BsRect();

  /**
 * @brief   Constructer not by default
 * @param  pos set the pos
 * @param  width set the width
 * @param  height set the height
 * @param  rotation set the rotation
 * @param  scale set the scale
 * @param  border_r set the border_r
 * @param  border_g set the border_g
 * @param  border_b set the border_b
 * @param  border_a set the border_a
 * @param  interior_r set the interior_r
 * @param  interior_g set the interior_g
 * @param  interior_b set the interior_b
 * @param  interior_a set the hollow
 */
  BsRect::BsRect(sf::Vector2f pos, sf::Vector2f size, float rotation, sf::Vector2f scale, uint8_t border_r, uint8_t border_g, uint8_t border_b, uint8_t border_a, uint8_t interior_r, uint8_t interior_g, uint8_t interior_b, uint8_t interior_a, uint8_t hollow);

  /**
  * @brief vistual destroyer
  */
  virtual ~BsRect();  /**<   Destructor used to initilizate the class */

  /**
  * @brief init defatault cube
  */
  void init();

  /**
 * @brief   Constructer not by default
 * @param  pos set the pos
 * @param  width set the width
 * @param  height set the height
 * @param  rotation set the rotation
 * @param  scale set the scale
 * @param  border_r set the border_r
 * @param  border_g set the border_g
 * @param  border_b set the border_b
 * @param  border_a set the border_a
 * @param  interior_r set the interior_r
 * @param  interior_g set the interior_g
 * @param  interior_b set the interior_b
 * @param  interior_a set the hollow
 */
  void init(sf::Vector2f pos, float rotation,
  sf::Vector2f scale, uint8_t border_r, uint8_t border_g, uint8_t border_b,
  uint8_t border_a, uint8_t interior_r, uint8_t interior_g,
  uint8_t interior_b, uint8_t interior_a, uint8_t hollow); /**<   init cube setting everything*/

  /**
 * @brief set the rect
 */
  void set_rect();

  /**
 * @brief set the color
 * @param  border_r set the border_r
 * @param  border_g set the border_g
 * @param  border_b set the border_b
 * @param  border_a set the border_a
 * @param  interior_r set the interior_r
 * @param  interior_g set the interior_g
 * @param  interior_b set the interior_b
 */
  void set_color(uint8_t border_r, uint8_t border_g, uint8_t border_b,
  uint8_t border_a, uint8_t interior_r, uint8_t interior_g,
  uint8_t interior_b, uint8_t interior_a); /**<   set the scale*/


  static bool collision(sf::Vector2f rect1, sf::Vector2f size1, sf::Vector2f rect2, sf::Vector2f size2);

  // Border color
  uint8_t border_r_; /**<   save the color border R*/
  uint8_t border_g_;  /**<   save the color border G*/
  uint8_t border_b_; /**<   save the color border B*/
  uint8_t border_a_; /**<   save the color border A*/
  // Interior color
  uint8_t interior_r_; /**<   save the color inside R*/
  uint8_t interior_g_; /**<   save the color inside G*/
  uint8_t interior_b_; /**<   save the color inside B*/
  uint8_t interior_a_;  /**<   save the color inside A*/

  // Hollow flag
  uint8_t hollow_;

 protected:
  sf::Vector2f pos_; /**<   save the position*/
  float rotation_; /**<   save the rotation*/
  sf::Vector2f scale_; /**<   save the scale*/
  // Counter for the factory
  static uint32_t s_total_rects_; /**<   static counter of all cubes*/

 private:
  BsRect(const BsRect& o); /**<   Constructer copy */


};

#endif // __BS_RECT__


/**
 * Author: Borja Serrano <serranoga@esat-alumni.com>
 * Filename: bs_backgorund.cc
 *
 * Implementation: background class
 */

#ifndef __BS_RECT__
#define __BS_RECT__ 1

#include "bs_entity.h"

#include "esat/math.h"

const uint32_t kMaxRects = 900;

/**
/* Class sprite, heredates from entity 
/* manage rects to creat and use
*/
class bsRect : public bsEntity {

 public:
  /// METHODS
  bsRect(); /**<  Constructor used to initilizate the class  */
  bsRect::bsRect(esat::Vec2 pos, float width, float height, float rotation,
    esat::Vec2 scale, uint8_t border_r, uint8_t border_g, uint8_t border_b,
    uint8_t border_a, uint8_t interior_r, uint8_t interior_g,
    uint8_t interior_b, uint8_t interior_a, uint8_t hollow); /**<   Constructer not by default */
  virtual ~bsRect();  /**<   Destructor used to initilizate the class */

  void init() override;  /**<   init defatault cube*/
  void init(esat::Vec2 pos, float width, float height, float rotation,
    esat::Vec2 scale, uint8_t border_r, uint8_t border_g, uint8_t border_b,
    uint8_t border_a, uint8_t interior_r, uint8_t interior_g,
    uint8_t interior_b, uint8_t interior_a, uint8_t hollow); /**<   init cube setting everything*/

  void draw() override; /**<   idraw the cube*/

  void set_position(esat::Vec2 pos) override; /**<   set the position*/
  void set_rotation(float rot) override; /**<   set the rotation*/
  void set_scale(esat::Vec2 scale) override; /**<   set the scale*/

  esat::Vec2 position() override; /**<   get the position*/
  float rotation() override; /**<   get the rotation*/
  esat::Vec2 scale() override; /**<   get the scale*/

  /// ATTRIBUTES
  float width_; /**<   save the witdh*/
  float height_; /**<   save the height*/

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

  // Factory
  static bsRect* CreateRect(); /**<   factory of cubes*/

 //protected:
  esat::Vec2 pos_; /**<   save the position*/
  float rotation_; /**<   save the rotation*/
  esat::Vec2 scale_; /**<   save the scale*/
  // Counter for the factory
  static uint32_t total_rects_; /**<   static counter of all cubes*/

 private:
  bsRect(const bsRect& o); /**<   Constructer copy */

};

#endif // __BS_RECT__


/**
 * Author: Borja Serrano <serranoga@esat-alumni.com>
 * Filename: bs_backgorund.cc
 *
 * Implementation: background class
 */

#ifndef __BS_ENTITY_H__
#define __BS_ENTITY_H__ 1

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

 #include "esat/draw.h"
#include "esat/math.h"

/**
/* Class Entity 
/* Virtual class for all the childs, heredate to other objects
*/
class bsEntity {

 public:
  /// METHODS
  bsEntity(); /**<  Constructor used to initilizate the class  */
  bsEntity(const bsEntity& o); /**<   Constructer copy */
  ~bsEntity(); /**<   Destructor used to initilizate the class */


  uint32_t id(); /**<   get the id from the object */

  virtual void init(); /**<   virtual init to heredate the variables */

  virtual void set_position(esat::Vec2 pos) = 0; /**<   virtual void to set position*/
  virtual void set_rotation(float rot) = 0;/**<   virtual void  to set rotation*/
  virtual void set_scale(esat::Vec2 scale) = 0; /**<   virtual void to set scale*/

  virtual esat::Vec2 position()  = 0; /**<   virtual var save the position*/
  virtual float rotation()  = 0; /**<   virtual var save the rotation*/
  virtual esat::Vec2 scale()  = 0; /**<   virtual var save the scale*/

  virtual void draw() = 0; /**<   virtaul void to draw entity*/

  /// ATTRIBUTES
    /// -1 not tagged
  int tag_;   /**<   var tag to know what type of object is*/
  uint8_t enabled_; /**<   determinate if its enabled to draw*/

 private:
  uint32_t id_; /**<   id for every single object created*/
  static uint32_t entity_counter_; /**<   counter of total entity, static just 1 var can be used*/

};

#endif // __BS_ENTITY_H__

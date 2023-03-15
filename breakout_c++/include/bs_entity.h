#ifndef __BS_ENTITY_H__
#define __BS_ENTITY_H__ 1

#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

/**
/* Class Entity
/* Virtual class for all the childs, heredate to other objects
*/
class BsEntity {

 public:
  /// METHODS
  BsEntity(); /**<  Constructor used to initilizate the class  */
  BsEntity(const BsEntity& o); /**<   Constructer copy */
  ~BsEntity(); /**<   Destructor used to initilizate the class */

  uint32_t id(); /**<   get the id from the object */

  virtual void init(); /**<   virtual init to heredate the variables */

  virtual void set_position(sf::Vector2f pos) = 0; /**<   virtual void to set position*/
  virtual void set_rotation(float rot) = 0;/**<   virtual void  to set rotation*/
  virtual void set_scale(sf::Vector2f scale) = 0; /**<   virtual void to set scale*/

  virtual sf::Vector2f position() = 0; /**<   virtual var save the position*/
  virtual float rotation() = 0; /**<   virtual var save the rotation*/
  virtual sf::Vector2f scale()  = 0; /**<   virtual var save the scale*/

  virtual void draw(sf::RenderWindow& window) = 0; /**<   virtaul void to draw entity*/

  /// ATTRIBUTES
    /// -1 not tagged
  int tag_;   /**<   var tag to know what type of object is*/
  uint8_t enabled_; /**<   determinate if its enabled to draw*/

 private:
  uint32_t id_; /**<   id for every single object created*/
  static uint32_t s_entity_counter_; /**<   counter of total entity, static just 1 var can be used*/

};

#endif // __BS_ENTITY_H__


// Author: Borja Serrano <serranoga@esat-alumni.com>

#ifndef __BS_SPRITE_H__
#define __BS_SPRITE_H__ 1

#include "bs_entity.h"

#include "esat/sprite.h"
#include "esat/math.h"

/** An enum type. 
     *  determinate from where comes the sprite
     */
enum SpriteOrigin {

  kSpriteOrigin_None, /**< null origin */
  kSpriteOrigin_File, /**< from file */
  kSpriteOrigin_Memory, /**< from memory */
  kSpriteOrigin_Copy /**< copy of 1 charged */

};

/**
/* Class sprite, heredates from entity 
/* manage evrything from sprites
*/
class bsSprite : public bsEntity {

 public:
  bsSprite(); /**<  Constructor used to initilizate the class  */
  bsSprite(const bsSprite& o); /**<   Constructer copy */
  virtual ~bsSprite(); /**<   Destructor used to initilizate the class */

  void init() override; /**<   init fro sprite from entity */
  void init(const char* file_name); /**<   init from path to charge  */
  void init(int width, int height, unsigned char* data); /**<   init charged sprite */
  void init(esat::SpriteHandle handle); /**<   get the handle to init the sprite */

  void set_position(esat::Vec2 pos) override; /**<   void to set position*/
  void set_rotation(float rot) override; /**<   void to set rotation*/
  void set_scale(esat::Vec2 scale) override; /**<   void to set scale*/

  esat::Vec2 position() override; /**<   var to save the position*/
  float rotation() override; /**<   var to save the rotation*/
  esat::Vec2 scale() override; /**<   var to save the scale*/
 
  int width(); /**<   var to save the withd*/
  int height(); /**<   var to save the height*/

//* Get pixel from sprite
    /*
    \*param ints to determinate the size od sprite
    \*param the color of sprite
*/
  void getPixel(int x, int y, unsigned char rgba[4]); 

  void draw(); /**<   function to draw the sprite*/
 
 private:
  void release(); /**<   function to release the sprite*/

  esat::SpriteTransform transform_; /**<   var to save the transform*/
  int origin_;
  esat::SpriteHandle handle_; /**<   var to save the spritesheet*/

};

#endif // __BS_SPRITE_H__

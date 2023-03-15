
/*
 * Author: Borja Serrano <serranoga@esat-alumni.com>
 * Filename: bs_backgorund.cc
 *
 * Implementation: background class
 */

#ifndef __BS_LABEL_H__
#define __BS_LABEL_H__ 1

#include "bs_entity.h"
#include "esat/math.h"

#include <string.h>

/**
/* Class sprite, heredates from entity 
/* manage evrything from labels
*/
class bsLabel : public bsEntity {

 public:
  bsLabel(); /**<  Constructor used to initilizate the class  */
  bsLabel(const bsLabel& o); /**<   Constructer copy */
  virtual ~bsLabel(); /**<   Destructor used to initilizate the class */

  //* init the label
    /*
    \*param char the text to print
    \*param the font 
    \*param the size of label
*/
  void init(const char* text, const char* font, float size);
  // setters
  void set_text(const char* text); /**<   set text*/
  void set_font(const char* font); /**<   set font*/
  void set_size(float size); /**<   set size*/
  void set_fill_color(unsigned char r, unsigned char g,
                      unsigned char b, unsigned char a); /**<   set color inside*/

  void set_stroke_color(unsigned char r, unsigned char g, /**<   set border color*/
                        unsigned char b, unsigned char a);

  void set_blur_radius(float radius); /**<   set radius*/

  void set_position(esat::Vec2 pos) override; /**<   set position label*/
  void set_rotation(float rot) override; /**<   set rotation label*/
  void set_scale(esat::Vec2 scale) override; /**<   set scale label*/

  // getters
  const char* text(); /**<   get the text of label*/
  const char* font(); /**<   get the font of label*/
  const float size(); /**<   get the size of label*/

  esat::Vec2 position() override; /**<   get the position of label*/
  float rotation() override; /**<   get the rotation of label*/
  esat::Vec2 scale() override; /**<   get the scale of label*/

  void draw() override; /**<   draw the label label*/

 private:
  char* text_; /**<   save the text*/
  char* font_; /**<   save the font*/

  float size_; /**<   save the size*/
  float radius_; /**<   save the radius*/

  esat::Vec2 position_; /**<   save the position*/

  unsigned char fill_r_; /**<   save the color inside R*/
  unsigned char fill_g_; /**<   save the color inside G*/
  unsigned char fill_b_; /**<   save the color inside B*/
  unsigned char fill_a_; /**<   save the color inside A*/

  unsigned char stroke_r_; /**<   save the color border R*/
  unsigned char stroke_g_; /**<   save the color border G*/
  unsigned char stroke_b_; /**<   save the color border B*/
  unsigned char stroke_a_; /**<   save the color border A*/

};

#endif // __BS_LABEL_H__

// Author: Borja Serrano <serranoga@esat-alumni.com>

#ifndef __BS_TEXTURE_H__
#define __BS_TEXTURE_H__ 1

#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

/**
/* Class texture
/* manage evrything from texture
*/
class BsTexture {

public:

  /**
 * @brief constructor of class
 */
  BsTexture();

  /**
 * @brief constructor with init
 * @param *file_name pointer to file name
 * @param pos the position to set
 * @param scale the scale to set
 */
  BsTexture::BsTexture(const char* file_name, sf::Vector2f pos, sf::Vector2f scale);
  /**
 * @brief Constructer copy
 */
  BsTexture(const BsTexture& o);

  /**
 * @brief vistual destroyer
 */
  virtual ~BsTexture();

  /**
 * @brief init for the object
 */
  void init();

  /**
 * @brief init for the file_name
 * @param *file_name pointer to file name
 */
  void init(const char* file_name);

  /**
 * @brief constructor with manual init
 * @param *file_name pointer to file name
 * @param pos the position to set
 * @param scale the scale to set
 */
  void init(const char* file_name, sf::Vector2f pos, sf::Vector2f scale);

  /**
 * @brief set the area
 */
  void set_texture_rect(sf::IntRect rect);

  /**
 * @brief set the pos
 * @param pos value to set
 */
  void set_position(sf::Vector2f pos);

  /**
 * @brief set the rot
 * @param rot value to set
 */
  void set_rotation(float rot);

  /**
 * @brief set the scale
 * @param scale value to set
 */
  void set_scale(sf::Vector2f scale);

  void set_color(sf::Color color);

  /**
  * @brief get the position
  * @return the position
  */
  sf::Vector2f position();

  /**
  * @brief get the   float rotation() override;

  * @return the   float rotation() override;

  */
  float rotation();

  /**
  * @brief get the scale
  * @return the scale
  */
  sf::Vector2f scale();

  void draw(sf::RenderWindow& window);

  sf::Texture text_;
  sf::Vector2f pos_; /**<   save the position*/
  float rotation_; /**<   save the rotation*/
  sf::Vector2f scale_; /**<   save the scale*/

  sf::Sprite sprite_;

};

#endif // __BsTexture_H__

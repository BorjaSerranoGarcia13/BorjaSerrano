/**
 * Author: Borja Serrano <serranoga@esat-alumni.com>
 * Filename: Bs_label.h
 *
 * Implementation: label class
 */

#ifndef __BS_LABEL__
#define __BS_LABEL__ 1

#include "bs_entity.h"

class BsLabel : public BsEntity {
  public:
  /// METHODS

  /**
 * @brief constructor of class
 */
    BsLabel();
    /**
   * @brief vistual destroyer
   */
    virtual ~BsLabel();

    BsLabel(const BsLabel& copy);

	/**
    * @brief innits the object
    */
    void init() override; /**<   virtual init to heredate the variables */

	  /**
	   * @brief  init manually
	   * @param  char* data pointer to data
	   * @param char* font_src pointer to font_src
	   * @param size the size to set
	  */
    void init(const char* data,const char* font_src, uint32_t size);

	  void init(const char* data,const char* font_src, uint32_t size, sf::Vector2f position, float rotation, sf::Vector2f scale, uint8_t border_color[4], uint8_t fill_color[4]);

    /**
   * @brief set the rot
   * @param rot value to set
   */
   void set_rotation(float rot) override; /**<   set the rotation*/

    /**
    * @brief get the position
    * @return the position
    */
    sf::Vector2f position() override; /**<   get the position*/

    /**
    * @brief set the pos
    * @param pos value to set
    */
    void set_position(sf::Vector2f pos) override;

    /**
    * @brief get the rotation
    * @return the rotation
    */
    float rotation() override; /**<   get the rotation*/

    /**
   * @brief set border color
   * @param  color_r set color_r
   * @param  color_g set color_g
   * @param  color_b set color_b
   * @param  color_a set the visibility
   */
    void set_border_color(uint8_t color_r,uint8_t color_g,uint8_t color_b,
                          uint8_t color_a);

    /**
    * @brief set fill color
      * @param  color_r set color_r
     * @param  color_g set color_g
     * @param  color_b set color_b
     * @param  color_a set the visibility
     */
    void set_fill_color(uint8_t color_r,uint8_t color_g,uint8_t color_b,
                          uint8_t color_a);

    /**
   * @brief set the pos
   * @param pos value to set
   */
    sf::Vector2f scale() override;

    /**
   * @brief set the scale
   * @param scale value to set
   */
    void set_scale(sf::Vector2f scale) override;

    /**
    * @brief get the text
    * @return the text
    */
    const sf::String text() ;

    /**
   * @brief set the pos
   * @param pos value to set
   */
    void set_text(const std::string &data);

    /**
    * @brief get the font
    * @return the font
    */
    const sf::Font* font();

    /**
   * @brief set the font_src
   * @param font_src value to set
   */
    void set_font(const char* font_src);

    /**
    * @brief draws the label character election
    */
    void draw(sf::RenderWindow& window) override;

  protected:
    sf::Font font_;
    sf::Text text_;
    float rotation_;
};

#endif // __BS_LABEL__

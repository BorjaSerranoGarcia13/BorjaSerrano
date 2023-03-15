
 #ifndef __BS_WINDOW_H__
 #define __BS_WINDOW_H__ 1

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

/**
/* Class window
/* manage evrything to draw and start the window
*/
class BsWindow {

 public:

/**
* @brief Init the window
* @param width for the width od window
* @param height for the height od window
* @param title tfor the name of window
*/
  void init(const unsigned int width, const unsigned int height, const std::string &title);
  /**
 * @brief Constructor used to initilizate the class
 */
  void frame();

  /**
 * @brief  Destroy the window
 */
  void destroy();

  /**
 * @brief check if window is isOpened
 * @preturn true if is opened
 * @preturn false if is not opened
 */
  bool isOpened(); /**<  return if window is opened  */

  /**
 * @brief clear the window
 */
  void clear();

  /**
  * @brief set the mouse visibility
 * @param visible set the mouse visibility
 */
  void setMouseVisibility(bool visible);

  /**
  * @brief get the height
  * @return height
  */
  const unsigned int height();

  /**
  * @brief get the width
  * @return width
  */
  const unsigned int width();

  /**
  * @brief set the limit framerate
 * @param limit to set the limit framerate
 */
  void setFramerateLimit(const unsigned int limit);

  sf::RenderWindow window_;
  sf::Clock delta_clock_;

};

#endif // __BS_WINDOW_H__

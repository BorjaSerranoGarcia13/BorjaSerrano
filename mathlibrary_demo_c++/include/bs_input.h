
#ifndef __BS_INPUT_H__
#define __BS_INPUT_H__ 1

#include "stdint.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>

enum KeyboardKey {
    kKeyboardKey_None = 0,
    kKeyboardKey_Left = 1,
    kKeyboardKey_Right = 2,
    kKeyboardKey_Up = 3,
    kKeyboardKey_Down = 4,
    kKeyboardKey_Space = 5,
    kKeyboardKey_Enter = 6,
    kKeyboardKey_Escape = 7,
    kKeyboardKey_Z = 8,
    kKeyboardKey_X = 9,
    kKeyboardKey_C = 10,
    kKeyboardKey_F1 = 11,
    kKeyboardKey_F2 = 12,
};

enum MouseButton {
    kMouseButton_None = 0,
    kMouseButton_Left = 1,
    kMouseButton_Right = 2
};

/**
/* Class scene
/* manage evrything from the scene, gameplay
*/
class BsInput {
 public:

  /**
  * @brief constructor of class
  */
  BsInput();

  /**
  * @brief Destructor used to initilizate the class
  */
  ~BsInput();

  BsInput(const BsInput& copy) = delete;
  BsInput& operator=(const BsInput&) = delete;

  /**
  * @brief get the control_mouse
  * @return the control_mouse
  */
   void mouseButton();

   /**
   * @brief get the control_mouse
   * @return the control_mouse
   */
    const uint8_t mouse_button();

   /**
  * @brief set the control_mouse
  * @param control_mouse value to set
  */
   void set_mouse_button(uint8_t control_mouse);

   /**
  * @brief get the mouse_position
  * @return the mouse_position
  */
   sf::Vector2i mouse_position(sf::RenderWindow& window);

   /**
  * @brief set the mouse_position
  * @param mouse_position value to set
  */
   void set_mouse_position(sf::Vector2i mouse_position);

   /**
  * @brief detects controls in keypad
  */
   void keyboardKey();

   /**
  * @brief detects controls in keypad
  */
   const uint8_t keyboard_key();

   /**
  * @brief detects controls in keypad
  */
   void set_keyboard_key(uint8_t keyboard_key);

   void input(sf::RenderWindow& window);

   void clearInput();

   bool enabled_keyboard_; /*!< mouse_pressed_ */
   bool enabled_mouse_; /*!< mouse_pressed_ */

  private:

   sf::Vector2i mouse_position_; /*!< mouse_position_ */
   uint8_t keyboard_key_; /*!< control_pad_ */
   uint8_t last_keyboard_key_; /*!< control_pad_ */
   uint8_t mouse_button_; /*!< control_mouse_ */
   uint8_t last_mouse_button_; /*!< control_mouse_ */
 };

#endif // __BS_INPUT_H__

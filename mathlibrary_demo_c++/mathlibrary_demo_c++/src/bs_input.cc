
#include "../include/bs_input.h"

BsInput::BsInput() {
  enabled_keyboard_ = true;
  enabled_mouse_ = true;

  mouse_position_ = sf::Vector2i(0, 0);

  keyboard_key_ = kKeyboardKey_None;
  last_keyboard_key_ = kKeyboardKey_None;
  mouse_button_ = kMouseButton_None;
  last_mouse_button_ = kMouseButton_None;
}

BsInput::~BsInput() {

}

void BsInput::mouseButton() {
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    set_mouse_button(kMouseButton_Left);
  } else  if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
    set_mouse_button(kMouseButton_Right);
  } else {
    set_mouse_button(kMouseButton_None);
  }
}

const uint8_t BsInput::mouse_button() {
  return mouse_button_;
}

void BsInput::set_mouse_button(uint8_t mouse_button) {
  mouse_button_ = mouse_button;
}

sf::Vector2i BsInput::mouse_position(sf::RenderWindow& window) {
  set_mouse_position(sf::Mouse::getPosition(window));
  return mouse_position_;
}
void BsInput::set_mouse_position(sf::Vector2i mouse_position) {
  mouse_position_ = mouse_position;
}

void BsInput::keyboardKey() {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    set_keyboard_key(kKeyboardKey_Left);
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    set_keyboard_key(kKeyboardKey_Right);
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
    set_keyboard_key(kKeyboardKey_Up);
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
    set_keyboard_key(kKeyboardKey_Down);
  }  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
    set_keyboard_key(kKeyboardKey_Space);
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
    set_keyboard_key(kKeyboardKey_Enter);
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
    set_keyboard_key(kKeyboardKey_Z);
  }
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
      set_keyboard_key(kKeyboardKey_X);
  }
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
      set_keyboard_key(kKeyboardKey_C);
  }
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1)) {
      set_keyboard_key(kKeyboardKey_F1);
  }
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2)) {
      set_keyboard_key(kKeyboardKey_F2);
  }
  else {
    set_keyboard_key(kKeyboardKey_None);
  }
}

const uint8_t BsInput::keyboard_key() {
  return keyboard_key_;
}

void BsInput::set_keyboard_key(uint8_t keyboard_key) {
    keyboard_key_ = keyboard_key;
}

void BsInput::input(sf::RenderWindow& window) {
  mouseButton();
  mouse_position(window);
  keyboardKey();

  if (last_keyboard_key_ == keyboard_key_ && keyboard_key_ != kKeyboardKey_None) {
    enabled_keyboard_ = false;
  } else {
    enabled_keyboard_ = true;
  }
  if (last_mouse_button_ == mouse_button_ && mouse_button_ != kMouseButton_None) {
    enabled_mouse_ = false;
  } else {
    enabled_mouse_ = true;
  }
}

void BsInput::clearInput() {
  last_keyboard_key_ = keyboard_key_;
  last_mouse_button_ = mouse_button_;
  keyboard_key_ = kKeyboardKey_None;
  mouse_button_ = kMouseButton_None;
}

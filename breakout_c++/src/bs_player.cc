
#include "../include/bs_player.h"

BsPlayer::BsPlayer() {
  direction_ = kPlayerDirection_None;
  type_character_ = kTypeCharacter_Player;
  set_health_points(1);
  new_size_.x = 0.0f;
  new_size_.y = 0.0f;
}

BsPlayer::~BsPlayer() {

}

void BsPlayer::init() {
  BsCharacter::init(sf::Vector2f(500.0f, 700.0f), sf::Vector2f(120.0f, 10.0f), 0.0f, sf::Vector2f(1.0f, 1.0f), 150, 150, 150, 255, 100, 100, 100, 255, 0);
  set_new_size();
}

void BsPlayer::init(sf::Vector2f pos, sf::Vector2f size, float rotation, sf::Vector2f scale, uint8_t border_r, uint8_t border_g, uint8_t border_b, uint8_t border_a, uint8_t interior_r, uint8_t interior_g, uint8_t interior_b, uint8_t interior_a, uint8_t hollow) {
  BsCharacter::init(pos, size, rotation, scale, border_r, border_g, border_b, border_a, interior_r, interior_g, interior_b, interior_a, hollow);
  set_new_size();

}

void BsPlayer::init(sf::Vector2f new_size) {
  BsCharacter::init(sf::Vector2f(500.0f, 700.0f), sf::Vector2f(120.0f, 10.0f), 0.0f, new_size, 150, 150, 150, 255, 100, 100, 100, 255, 0);
  set_origin(size().x * 0.5f, 0);
  set_new_size();

}

void BsPlayer::set_new_size() {
  set_origin(size().x * 0.5f, 0);
  new_size_.x = (size().x * 0.5f) * scale().x;
  new_size_.y = size().y * scale().y;
  float points =  0.0f;
  for (int i = 0; i < sizeof(collision_points_) / sizeof(collision_points_[0]); i++) {
    collision_points_[i] = (size().x * scale().x) * points - new_size_.x;
    points += 0.1f;
  }
}

sf::Vector2f BsPlayer::new_size() {
  return new_size_;
}

void BsPlayer::update() {
  if (enabled_ == 1) {
    if (BsGameManager::getInstance().input_.keyboard_key() == BsGameManager::getInstance().input_.kKeyboardKey_Left &&
    position().x - new_size().x >= 3.0f) {
      set_position(position() + sf::Vector2f(-7.0f, 0.0f));
    } else if (BsGameManager::getInstance().input_.keyboard_key() == BsGameManager::getInstance().input_.kKeyboardKey_Right &&
    position().x + new_size().x <= 997.0f) {
      set_position(position() + sf::Vector2f(7.0f, 0.0f));
    }
    if (position().x - new_size().x < 3.0f) {set_position(sf::Vector2f(3.0f + new_size().x, position().y));}
    if (position().x + new_size().x > 997.0f) {set_position(sf::Vector2f(997.0f - new_size().x, position().y));}

    if (health_points_ <= 0) {
      set_enabled(0);
    }
  }
}

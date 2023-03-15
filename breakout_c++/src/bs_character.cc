
#include "../include/bs_character.h"

BsCharacter::BsCharacter() {
  init();
  type_character_ = 0;
  health_points_ = 0;
}

BsCharacter::~BsCharacter() {

}

void BsCharacter::init() {
  BsRect::init();
}

void BsCharacter::init(sf::Vector2f pos, sf::Vector2f size, float rotation, sf::Vector2f scale, uint8_t border_r, uint8_t border_g, uint8_t border_b, uint8_t border_a, uint8_t interior_r, uint8_t interior_g, uint8_t interior_b, uint8_t interior_a, uint8_t hollow) {
  BsRect::init(pos, size, rotation,
    scale, border_r, border_g, border_b,
    border_a, interior_r, interior_g,
    interior_b, interior_a, hollow);
}

const uint8_t BsCharacter::type_character() {
  return type_character_;
}

void BsCharacter::set_type_character(uint8_t type_character) {
  type_character_ = type_character;
}

const uint8_t BsCharacter::health_points() {
  return health_points_;

}
void BsCharacter::set_health_points(uint8_t health_points) {
  health_points_ = health_points;
}

const bool BsCharacter::enabled() {
  return enabled_;
}
void BsCharacter::set_enabled(uint8_t enabled) {
  enabled_ = enabled;
}

void BsCharacter::draw(sf::RenderWindow& window) {
  BsRect::draw(window);
}

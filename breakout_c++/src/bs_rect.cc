
#include "../include/bs_rect.h"

BsRect::BsRect() {
  pos_ = {0.0f, 0.0f};
  size_ = {0.0f, 0.0f};
  rotation_ = 0.0f;

  border_r_ = 0xFF;
  border_g_ = 0x80;
  border_b_ = 0xFF;
  border_a_ = 0xFF;

  interior_r_ = 0xFF;
  interior_g_ = 0x80;
  interior_b_ = 0xFF;
  interior_a_ = 0xFF;

  hollow_ = 0;

  enabled_ = 1;

  BsRect::s_total_rects_;

  tag_ = 4;
}

BsRect::BsRect(sf::Vector2f pos, sf::Vector2f size, float rotation, sf::Vector2f scale, uint8_t border_r, uint8_t border_g, uint8_t border_b, uint8_t border_a, uint8_t interior_r, uint8_t interior_g, uint8_t interior_b, uint8_t interior_a, uint8_t hollow) {
  init(pos, size, rotation, scale, border_r, border_g, border_b, border_a, interior_r, interior_g, interior_b, interior_a, hollow);
}

BsRect::~BsRect() {

}

BsRect::BsRect(const BsRect& copy) {
  init(copy.pos_, copy.size_, copy.rotation_, copy.scale_, copy.border_r_, copy.border_g_, copy.border_b_, copy.border_a_, copy.interior_r_, copy.interior_g_, copy.interior_b_, copy.interior_a_, copy.hollow_);
}

void BsRect::init() {
  pos_ = {0.0f, 0.0f};
  size_ = {20.0f, 20.0f};
  rotation_ = 0.0f;
  scale_ = {1.0f, 1.0f};

  border_r_ = 0xFF;
  border_g_ = 0x80;
  border_b_ = 0xFF;
  border_a_ = 0xFF;

  interior_r_ = 0xFF;
  interior_g_ = 0x80;
  interior_b_ = 0xFF;
  interior_a_ = 0xFF;

  hollow_ = 0;

  set_rect();
}

void BsRect::init(sf::Vector2f pos, sf::Vector2f size, float rotation,
  sf::Vector2f scale, uint8_t border_r, uint8_t border_g, uint8_t border_b,
  uint8_t border_a, uint8_t interior_r, uint8_t interior_g,
  uint8_t interior_b, uint8_t interior_a, uint8_t hollow) {

  pos_ = pos;
  size_ = size;
  rotation_ = rotation;
  scale_ = scale;

  border_r_ = border_r;
  border_g_ = border_g;
  border_b_ = border_b;
  border_a_ = border_a;

  interior_r_ = interior_r;
  interior_g_ = interior_g;
  interior_b_ = interior_b;
  interior_a_ = interior_a;

  hollow_ = hollow;

  set_rect();
}

void BsRect::set_position(sf::Vector2f pos) {
  pos_ = pos;
  shape_.setPosition(pos_);
}

void BsRect::set_rotation(float rot) {
  rotation_ = rot;
}

void BsRect::set_scale(sf::Vector2f scale) {
  scale_ = scale;
  shape_.setScale(scale_);
}

void BsRect::set_size(sf::Vector2f size) {
  size_ = size;
  shape_.setSize(size_);
}

sf::Vector2f BsRect::position() {return pos_;}

float BsRect::rotation() {return rotation_;}

sf::Vector2f BsRect::scale() {return scale_;}

sf::Vector2f BsRect::size() const {return size_;}


void BsRect::set_rect() {
  // Set attributes
  shape_.setPosition(pos_);
  shape_.setSize(size_);
  shape_.setScale(scale_);
  // Set Color
  shape_.setOutlineColor(sf::Color(border_r_, border_g_, border_b_, border_a_));
  shape_.setFillColor(sf::Color(interior_r_, interior_g_, interior_b_, interior_a_));
  shape_.setOutlineThickness(3.0f);
}

void BsRect::set_origin(float x, float y) {
  shape_.setOrigin(x, y);
}

void BsRect::draw(sf::RenderWindow& window) {
  if (enabled_) {
    window.draw(shape_);
  }
}

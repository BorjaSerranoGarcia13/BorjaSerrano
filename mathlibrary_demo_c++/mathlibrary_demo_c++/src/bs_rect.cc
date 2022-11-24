
#include "bs_rect.h"

uint32_t BsRect::s_total_rects_;

BsRect::BsRect() {
  pos_ = {0.0f, 0.0f};
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

  s_total_rects_ = 0;

}

BsRect::BsRect(sf::Vector2f pos, sf::Vector2f size, float rotation, sf::Vector2f scale, uint8_t border_r, uint8_t border_g, uint8_t border_b, uint8_t border_a, uint8_t interior_r, uint8_t interior_g, uint8_t interior_b, uint8_t interior_a, uint8_t hollow) {
  init(pos, rotation, scale, border_r, border_g, border_b, border_a, interior_r, interior_g, interior_b, interior_a, hollow);
}

BsRect::~BsRect() {

}

BsRect::BsRect(const BsRect& copy) {
  init(copy.pos_, copy.rotation_, copy.scale_, copy.border_r_, copy.border_g_, copy.border_b_, copy.border_a_, copy.interior_r_, copy.interior_g_, copy.interior_b_, copy.interior_a_, copy.hollow_);
}

void BsRect::init() {
  pos_ = {0.0f, 0.0f};
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

void BsRect::init(sf::Vector2f pos, float rotation,
  sf::Vector2f scale, uint8_t border_r, uint8_t border_g, uint8_t border_b,
  uint8_t border_a, uint8_t interior_r, uint8_t interior_g,
  uint8_t interior_b, uint8_t interior_a, uint8_t hollow) {

  pos_ = pos;
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

void BsRect::set_color(uint8_t border_r, uint8_t border_g, uint8_t border_b, uint8_t border_a, uint8_t interior_r, uint8_t interior_g, uint8_t interior_b, uint8_t interior_a)
{
    border_r_ = border_r;
    border_g_ = border_g;
    border_b_ = border_b;
    border_a_ = border_a;

    interior_r_ = interior_r;
    interior_g_ = interior_g;
    interior_b_ = interior_b;
    interior_a_ = interior_a;

    convex_.setOutlineColor(sf::Color(border_r_, border_g_, border_b_, border_a_));
    convex_.setFillColor(sf::Color(interior_r_, interior_g_, interior_b_, interior_a_));
}


bool BsRect::collision(sf::Vector2f rect1, sf::Vector2f size1, sf::Vector2f rect2, sf::Vector2f size2)
{
    if (rect1.x - size1.x < rect2.x + size2.x * 0.5f &&
        rect1.x + size1.x * 0.5f  > rect2.x - size2.x &&
        rect1.y - size1.y < rect2.y + size2.y * 0.5f &&
        rect1.y - size1.y > rect2.y - size2.y) {

        return true;
    }
    return false;
}

void BsRect::set_rect() {
    Vector2 pos[5];
    pos[0] = { -0.1f, -0.1f };
    pos[1] = { 0.1f, -0.1f };
    pos[2] = { 0.1f, 0.1f };
    pos[3] = { -0.1f, 0.1f };

    for (int i = 0; i < 4; ++i) {
        addVertex(&pos[i]);
    }
    
  // Set attributes
  set_position(pos_);
  set_scale(scale_);
  set_rotation(rotation_);

  // Set Color
  convex_.setOutlineColor(sf::Color(border_r_, border_g_, border_b_, border_a_));
  convex_.setFillColor(sf::Color(interior_r_, interior_g_, interior_b_, interior_a_));
  convex_.setOutlineThickness(3.0f);
}



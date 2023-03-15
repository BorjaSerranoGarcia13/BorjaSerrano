
/**
 * Author: Borja Serrano <serranoga@esat-alumni.com>
 * Filename: bs_backgorund.cc
 *
 * Implementation: background class
 */
#include "bs_entity.cc"
#include "bs_rect.h"


bsRect::bsRect() {

  pos_ = {0.0f, 0.0f};
  width_ = 1.0f;
  height_ = 1.0f;
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

  bsRect::total_rects_;

}

bsRect::bsRect(esat::Vec2 pos, float width, float height, float rotation,
  esat::Vec2 scale, uint8_t border_r, uint8_t border_g, uint8_t border_b,
  uint8_t border_a, uint8_t interior_r, uint8_t interior_g,
  uint8_t interior_b, uint8_t interior_a, uint8_t hollow) {

    pos_ = pos;
    width_ = width;
    height_ = height;
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

  }

bsRect::bsRect(const bsRect& copy) {

  pos_ = copy.pos_;
  width_ = copy.width_;
  height_ = copy.height_;
  rotation_ = copy.rotation_;
  scale_ = copy.scale_;

  border_r_ = copy.border_r_;
  border_g_ = copy.border_g_;
  border_b_ = copy.border_b_;
  border_a_ = copy.border_a_;

  interior_r_ = copy.interior_r_;
  interior_g_ = copy.interior_g_;
  interior_b_ = copy.interior_b_;
  interior_a_ = copy.interior_a_;

  hollow_ = copy.hollow_;

}

void bsRect::init() {

  pos_ = {0.0f, 0.0f};
  width_ = 1.0f;
  height_ = 1.0f;
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

}

void bsRect::init(esat::Vec2 pos, float width, float height, float rotation,
  esat::Vec2 scale, uint8_t border_r, uint8_t border_g, uint8_t border_b,
  uint8_t border_a, uint8_t interior_r, uint8_t interior_g,
  uint8_t interior_b, uint8_t interior_a, uint8_t hollow) {

    pos_ = pos;
    width_ = width;
    height_ = height;
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
  }

void bsRect::draw() {

  if (enabled_) {
    esat::DrawSetStrokeColor(border_r_, border_g_, border_b_, border_a_);
    esat::DrawSetFillColor(interior_r_, interior_g_, interior_b_, interior_a_);

    float quad[10] = {pos_.x, pos_.y,
                      pos_.x + (width_ * scale_.x), pos_.y,
                      pos_.x + (width_ * scale_.x), pos_.y + (height_ * scale_.y),
                      pos_.x, pos_.y + (height_ * scale_.y),
                      pos_.x, pos_.y};
    esat::DrawSolidPath(quad, 5);
  }

}

void bsRect::set_position(esat::Vec2 pos) {pos_ = pos;}

void bsRect::set_rotation(float rot) {}

void bsRect::set_scale(esat::Vec2 scale) {scale_ = scale;}

esat::Vec2 bsRect::position() {return pos_;}

float bsRect::rotation() {return rotation_;}

esat::Vec2 bsRect::scale() {return scale_;}
/*
bsRect* bsRect::CreateRect() {
  if (bsRect::total_rects_ < kMaxRects) {
    bsRect* rect = new bsRect();
    rect->init();
    return rect;
  } else {
    return nullptr;
  }
}
*/
bsRect::~bsRect() {
  //--bsRect::total_rects_;
}

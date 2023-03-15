
// Author: Borja Serrano <serranoga@esat-alumni.com>

#include "bs_sprite.h"

bsSprite::bsSprite() {

  esat::SpriteTransformInit(&transform_);
  origin_ = kSpriteOrigin_None;
  handle_ = nullptr;

}

bsSprite::bsSprite(const bsSprite& o) {

  transform_ = o.transform_;
  origin_ = kSpriteOrigin_Copy;
  handle_ = o.handle_;

}

bsSprite::~bsSprite() {release();}

void bsSprite::release() {

  if ((origin_ != 0) && (origin_ != 3)) {
    /// WARNIGN: Avoid releasing handles used by other sprites
    esat::SpriteRelease(handle_);

  }

}

void bsSprite::init() {

  if (handle_ != nullptr) {release();}
  handle_ = nullptr;
  origin_ = kSpriteOrigin_None;
  esat::SpriteTransformInit(&transform_);

}

void bsSprite::init(const char* file_name) {

  if (file_name != NULL) {
    // Release the prior sprite if its is there
    release();
    // Try to load a new sprite from file
    handle_ = esat::SpriteFromFile(file_name);

    if (handle_ == nullptr) {
       fprintf(stderr, "WARNING Could not load file %s\n%", file_name);
    } else {
      // The sprite was sucessfully loaded
      origin_ = kSpriteOrigin_File;
      SpriteTransformInit(&transform_);
    }
  }

}

void bsSprite::init(int width, int height, unsigned char* data) {

  if ((width > 0) && (height > 0) && (data != nullptr)) {

    release();
    handle_ = esat::SpriteFromMemory(width, height, data);
    origin_ = kSpriteOrigin_Memory;

  }

}

void bsSprite::init(esat::SpriteHandle handle) {

  if (handle_ != nullptr) {

    release();
    handle_ = handle;
    origin_ = kSpriteOrigin_Copy;
  }

}

void bsSprite::set_position(esat::Vec2 pos) {

  transform_.x = pos.x;
  transform_.y = pos.y;

}

void bsSprite::set_rotation(float rot) {transform_.angle = rot;}

void bsSprite::set_scale(esat::Vec2 scale) {

  transform_.scale_x = scale.x;
  transform_.scale_y = scale.y;

}

esat::Vec2 bsSprite::position() {

  esat::Vec2 pos = {transform_.x, transform_.y};
  return pos;

}

float bsSprite::rotation() {return transform_.angle;}

esat::Vec2 bsSprite::scale() {

  esat::Vec2 scale = {transform_.scale_x, transform_.scale_y};
  return scale;

}

void bsSprite::draw() {

  esat::DrawSprite(handle_, transform_.x, transform_.y);

}

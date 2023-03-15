
/**
 * Author: Borja Serrano <serranoga@esat-alumni.com>
 * Filename: bs_backgorund.cc
 *
 * Implementation: background class
 */

 #include "bs_label.h"

bsLabel::bsLabel() {

  text_ = nullptr;
  font_ = nullptr;
  size_ = 0;
  fill_r_ = 255;
  fill_g_ = 255;
  fill_b_ = 255;
  fill_a_ = 255;
  stroke_r_ = 255;
  stroke_g_ = 255;
  stroke_b_ = 255;
  stroke_a_ = 255;
  radius_ = 0.0f;
  position_ = {0.0f, 0.0f};

}

bsLabel::bsLabel(const bsLabel& o) {

  if (o.text_ != nullptr) {
    text_ = (char*)calloc(strlen(o.text_), sizeof(char));
    if(text_ != nullptr) {
        strcpy(text_, o.text_);
    } else {
        //HELP no memory
    }
  }

  if (o.font_ != nullptr) {
    font_ = (char*)calloc(strlen(o.font_), sizeof(char));
    if(text_ != nullptr) {
        strcpy(font_, o.font_);
    } else {
        //HELP no memory
    }
  }

  size_ = o.size_;
  fill_r_ = o.fill_r_;
  fill_g_ = o.fill_g_;
  fill_b_ = o.fill_b_;
  fill_a_ = o.fill_a_;
  stroke_r_ = o.stroke_r_;
  stroke_g_ = o.stroke_b_;
  stroke_b_ = o.stroke_b_;
  stroke_a_ = o.stroke_a_;
  radius_ = o.radius_;
  position_ = o.position_;

}

bsLabel::~bsLabel() {

  if (text_ != nullptr) {
      free(text_);
  }
  if (font_ != nullptr) {
      free(font_);
  }

}

void bsLabel::init(const char* text, const char* font, float size) {

  bsEntity::init();

  set_text(text);

  set_font(font);

  set_size(size);
  esat::Vec2 s = {1.0f, 1.0f};
  set_position(s);

}

void bsLabel::set_text(const char* text) {

     if (text != nullptr) {
      if(text_ != nullptr) {
          free(text_);
      }
      text_ = (char*)calloc(strlen(text) + 1, sizeof(char));
      strcpy_s(text_, strlen(text) + 1,  text);
  }

}

void bsLabel::set_font(const char* font) {

  if (font != nullptr) {
      esat::DrawSetTextFont(font);
      font_ = (char*)calloc(strlen(font) + 1, sizeof(char));
      strcpy_s(font_, strlen(font) + 1,  font);
  }

}

void bsLabel::set_size (float size) {

    if (size > 0) size_ = size;
}

void bsLabel::set_fill_color(unsigned char r, unsigned char g,
                             unsigned char b, unsigned char a) {

  fill_r_ = r;
  fill_g_ = g;
  fill_b_ = b;
  fill_a_ = a;

}

void bsLabel::set_stroke_color(unsigned char r, unsigned char g,
                             unsigned char b, unsigned char a) {

  stroke_r_ = r;
  stroke_g_ = g;
  stroke_b_ = b;
  stroke_a_ = a;

}

void bsLabel::set_blur_radius(float radius) {if (radius > 0.0f) radius_ = radius;}

void bsLabel::set_position(esat::Vec2 pos) {position_ = pos;}

void bsLabel::set_scale(esat::Vec2 scale) {}

void bsLabel::set_rotation(float rot) {}

const char* bsLabel::text() {return text_;}

const char* bsLabel::font() {return font_;}

const float bsLabel::size() {return size_;}

esat::Vec2 bsLabel::position() {return position_;}

float bsLabel::rotation() {return 0.0f;}

esat::Vec2 bsLabel::scale() {
  esat::Vec2 size = {size_, size_};
  return size;
}

void bsLabel::draw() {

  if (enabled_ == 1) {
    esat::DrawSetTextFont(font_);
    esat::DrawSetTextSize(size_);
    esat::DrawSetTextBlur(radius_);
    esat::DrawSetStrokeColor(stroke_r_, stroke_g_, stroke_b_, stroke_a_);
    esat::DrawSetFillColor(fill_r_, fill_g_, fill_b_, fill_a_);
    esat::Vec2 pos = position();
    esat::DrawText(pos.x, pos.y, text_);
  }
}

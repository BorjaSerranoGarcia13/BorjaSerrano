
#include "bs_label.h"

BsLabel::BsLabel(){
  init();
}

BsLabel::BsLabel(const BsLabel& copy) {
  text_ = copy.text_;
  font_ = copy.font_;
  rotation_ = copy.rotation_;
}

BsLabel::~BsLabel(){
}

void BsLabel::init(){
  enabled_ = 1;
  tag_ = 1;
}

void BsLabel::init(const char* data, const char* font_src, int size){
  if (size == 0) {
	  std::cout <<"LABEL size 0" << std::endl;
    return;
  }

  if (NULL == data) {
	  std::cout <<"LABEL data NULL" << std::endl;
    return;
  }

  if (NULL == font_src) {
	  std::cout <<"LABEL font NULL" << std::endl;
    return;
  }

  if (!font_.loadFromFile(font_src)) {
	  std::cout <<"LABEL no font found" << std::endl;
    return;
  }

  text_.setFont(font_);
  text_.setCharacterSize(size);
  text_.setString(data);
}

void BsLabel::init(const char* data,const char* font_src, int size, sf::Vector2f position, float rotation, sf::Vector2f scale, uint8_t border_color[4], uint8_t fill_color[4]) {
  init(data, font_src, size);

	set_position(position);
	set_rotation(rotation);
	set_scale(scale);

	set_border_color(border_color[0], border_color[1], border_color[2], border_color[3]);
	set_fill_color(fill_color[0], fill_color[1], fill_color[2], fill_color[3]);
}

void BsLabel::set_border_color(uint8_t color_r,uint8_t color_g,uint8_t color_b,
                            uint8_t color_a){
  sf::Color border_color = {color_r,color_g,color_b,color_a};
  text_.setOutlineColor(border_color);
}

void BsLabel::set_fill_color(uint8_t color_r,uint8_t color_g,uint8_t color_b,
                            uint8_t color_a){
  sf::Color fill_color = {color_r,color_g,color_b,color_a};
  text_.setFillColor(fill_color);
}

void BsLabel::set_position(sf::Vector2f pos){
  text_.setPosition(pos.x,pos.y);
}

sf::Vector2f BsLabel::scale(){
  return text_.getScale();
}

void BsLabel::set_scale(sf::Vector2f scale){
  text_.setScale(scale);
}

const sf::String BsLabel::text() {
  return text_.getString();
}

void BsLabel::set_text(const std::string &data){
  text_.setString(data);
}

const sf::Font* BsLabel::font(){
  return text_.getFont();
}

void BsLabel::set_font(const char* font_src){
  font_.loadFromFile(font_src);
  text_.setFont(font_);
}

void BsLabel::draw(sf::RenderWindow& window){
  if(enabled_){
   window.draw(text_);
  }
}

void BsLabel::set_rotation(float rot) {rotation_ = rot;}
sf::Vector2f BsLabel::position() {return text_.getPosition();}
float BsLabel::rotation() {return 0;}

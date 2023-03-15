
#include "../include/bs_scene_start.h"

BsSceneStart::BsSceneStart() {
  tag_ = kTypeScene_Start;
  enabled_ = 0;

  size_label_ = 3;
}

BsSceneStart::~BsSceneStart() {

}

void BsSceneStart::init() {
  label_ = new BsLabel[size_label_];

  enabled_ = 1;

  uint8_t border_rgba[] = {255, 255, 255, 255};
  uint8_t fill_rgba[] = {255, 255, 255, 255};

  label_[0].init("BREAKOUT","../data/fonts/font1.ttf", 100, sf::Vector2f(330.0f, 50.0f), 0.0f, sf::Vector2f(1.0f, 1.0f), border_rgba, fill_rgba);

  label_[1].init("PRESS SPACE TO","../data/fonts/font1.ttf", 50, sf::Vector2f(360.0f, 450.0f), 0.0f, sf::Vector2f(1.0f, 1.0f), border_rgba, fill_rgba);
  label_[1].set_border_color(150, 0, 150, 255);
  label_[1].set_fill_color(150, 0, 150, 255);

  label_[2].init("START","../data/fonts/font1.ttf", 80, sf::Vector2f(400.0f, 520.0f), 0.0f, sf::Vector2f(1.0f, 1.0f), border_rgba, fill_rgba);
  label_[2].set_border_color(255, 0, 255, 255);
  label_[2].set_fill_color(255, 0, 255, 255);
}

void BsSceneStart::update() {

}

void BsSceneStart::draw(sf::RenderWindow& window) {
  if (enabled_ == 1) {
    for (int i = 0; i < size_label_; ++i) {
     label_[i].draw(window);
    }
  }
}


#include "../include/bs_scene_login_sign.h"

BsSceneLoginSign::BsSceneLoginSign() {
  tag_ = kTypeScene_LoginSign;
  enabled_ = 0;

  size_label_ = 4;
}

BsSceneLoginSign::~BsSceneLoginSign() {

}

void BsSceneLoginSign::init() {
  label_ = new BsLabel[size_label_];

  enabled_ = 0;

  uint8_t border_rgba[] = {255, 255, 255, 255};
  uint8_t fill_rgba[] = {255, 255, 255, 255};

  label_[0].init("BREAKOUT","../data/fonts/font1.ttf", 100, sf::Vector2f(330.0f, 50.0f), 0.0f, sf::Vector2f(1.0f, 1.0f), border_rgba, fill_rgba);
  label_[1].init("LOGIN","../data/fonts/font1.ttf", 70, sf::Vector2f(300.0f, 550.0f), 0.0f, sf::Vector2f(1.0f, 1.0f), border_rgba, fill_rgba);
  label_[2].init("SIGN","../data/fonts/font1.ttf", 70, sf::Vector2f(570.0f, 550.0f), 0.0f, sf::Vector2f(1.0f, 1.0f), border_rgba, fill_rgba);

}

void BsSceneLoginSign::update() {

}

void BsSceneLoginSign::draw(sf::RenderWindow& window) {
  if (enabled_ == 1) {
    for (int i = 0; i < size_label_; ++i) {
     label_[i].draw(window);
    }
  }
}


#include "../include/bs_scene_board.h"

BsSceneBoard::BsSceneBoard() {
  tag_ = kTypeScene_Board;
  enabled_ = 0;

  size_label_ = 4;
}

BsSceneBoard::~BsSceneBoard() {

}

void BsSceneBoard::init() {
  label_ = new BsLabel[size_label_];

  enabled_ = 0;

  uint8_t border_rgba[] = {255, 255, 255, 255};
  uint8_t fill_rgba[] = {255, 255, 255, 255};

  label_[0].init("SCORE","../data/fonts/font1.ttf", 50, sf::Vector2f(50.0f, 740.0f), 0.0f, sf::Vector2f(1.0f, 1.0f), border_rgba, fill_rgba);
  label_[1].init("0","../data/fonts/font1.ttf", 60, sf::Vector2f(170.0f, 730.0f), 0.0f, sf::Vector2f(1.0f, 1.0f), border_rgba, fill_rgba);
  label_[2].init("LIFES","../data/fonts/font1.ttf", 50, sf::Vector2f(820.0f, 740.0f), 0.0f, sf::Vector2f(1.0f, 1.0f), border_rgba, fill_rgba);
  label_[3].init("3","../data/fonts/font1.ttf", 60, sf::Vector2f(930.0f, 730.0f), 0.0f, sf::Vector2f(1.0f, 1.0f), border_rgba, fill_rgba);
}

void BsSceneBoard::update() {

}

void BsSceneBoard::draw(sf::RenderWindow& window) {
  if (enabled_ == 1) {
    for (int i = 0; i < size_label_; ++i) {
     label_[i].draw(window);
    }
  }
}

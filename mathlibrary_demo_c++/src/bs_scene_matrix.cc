
#include "bs_scene_matrix.h"

BsSceneMatrix::BsSceneMatrix() {
  tag_ = kTypeScene_GameOver;
  enabled_ = 1;

  size_label_ = 3;

  font_ = { "../../../data/fonts/font1.ttf" };

  path_ = new BsPath[kMaxShapes];
  BsPath::s_total_shapes_ = 0;
}

BsSceneMatrix::~BsSceneMatrix() {
    delete[] path_;
}

void BsSceneMatrix::init() {
  label_ = new BsLabel[size_label_];

  enabled_ = 1;
  uint8_t border_rgba[] = { 255, 255, 255, 255 };
  uint8_t fill_rgba[] = { 255, 255, 255, 255 };
  font_ = { "../../../data/fonts/font1.ttf" };
  label_[0].init("Z to start draw, X to finish", font_.c_str(), 100, sf::Vector2f(10.0f, 5.0f), 0.0f, sf::Vector2f(1.0f, 1.0f), border_rgba, fill_rgba);
  label_[1].init("F1     F2", font_.c_str(), 50, sf::Vector2f(850.0f, 5.0f), 0.0f, sf::Vector2f(1.0f, 1.0f), border_rgba, fill_rgba);
  label_[2].init("<    >", font_.c_str(), 80, sf::Vector2f(850.0f, 50.0f), 0.0f, sf::Vector2f(1.0f, 1.0f), border_rgba, fill_rgba);
}

void BsSceneMatrix::update() {
    if (GM_.input_.keyboard_key() == kKeyboardKey_Z && GM_.game_mode_ == kGameMode_None && BsPath::s_total_shapes_ < kCapacityVector) {
        GM_.game_mode_ = kGameMode_CreateShape;
    }
    if (GM_.input_.keyboard_key() == kKeyboardKey_X && GM_.game_mode_ == kGameMode_CreateShape) {
        BsPath::s_total_shapes_++;
        GM_.game_mode_ = kGameMode_None;
    }
    
    createShape();
}

void BsSceneMatrix::draw(sf::RenderWindow& window) {
  if (enabled_ == 1) {
    for (int i = 0; i < size_label_; ++i) {
     label_[i].draw(window);
    }

    // Draw Shapes
    for (int i = 0; i < kMaxShapes; ++i) {
        path_[i].draw(window);
    }
  }
}

void BsSceneMatrix::createShape()
{
    if (GM_.game_mode_ == kGameMode_CreateShape) {
        if (GM_.input_.mouse_button() == kMouseButton_Left && GM_.input_.enabled_mouse_) {
            Vector2 new_vector;
            new_vector.x = (float)GM_.input_.mouse_position(GM_.window_.window_).x;
            new_vector.y = (float)GM_.input_.mouse_position(GM_.window_.window_).y;

            path_[BsPath::s_total_shapes_].addVertex(&new_vector);
        }
    }
}


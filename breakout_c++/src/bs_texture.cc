
#include "bs_texture.h"


BsTexture::BsTexture() {
    init();
}

BsTexture::BsTexture(const char* file_name, sf::Vector2f pos, sf::Vector2f scale) {
    init(file_name, pos, scale);
}

BsTexture::BsTexture(const BsTexture& o)
{
}

BsTexture::~BsTexture() {}

void BsTexture::init() {
    pos_.x = 0.0f;
    pos_.y = 0.0f;
    scale_.x = 1.0f;
    scale_.y = 1.0f;
    rotation_ = 0.0f;
}

void BsTexture::init(const char* file_name) {
    if (!text_.loadFromFile(file_name))
    {
        std::cout << "Error init texture" << std::endl;
    }
    sprite_.setTexture(text_);
}

void BsTexture::init(const char* file_name, sf::Vector2f pos, sf::Vector2f scale) {
    if (!text_.loadFromFile(file_name, sf::IntRect((int)pos.x, (int)pos.y, (int)scale.x, (int)scale.y)))
    {
        std::cout << "Error init part of texture" << std::endl;
    }
    sprite_.setTexture(text_);
}

void BsTexture::set_texture_rect(sf::IntRect rect)
{
    sprite_.setTextureRect(rect);
}


void BsTexture::set_position(sf::Vector2f pos) {
    pos_ = pos;
    sprite_.setPosition(pos_);
}

void BsTexture::set_rotation(float rot) {
    rotation_ = rot;
    sprite_.setRotation(rotation_);
}

void BsTexture::set_scale(sf::Vector2f scale) {
    scale_ = scale;
    sprite_.setScale(scale_);
}

void BsTexture::set_color(sf::Color color)
{
    sprite_.setColor(color);
}


sf::Vector2f BsTexture::position() { return pos_; }

float BsTexture::rotation() { return rotation_; }

sf::Vector2f BsTexture::scale() { return scale_; }

void BsTexture::draw(sf::RenderWindow& window)
{
    window.draw(sprite_);
}

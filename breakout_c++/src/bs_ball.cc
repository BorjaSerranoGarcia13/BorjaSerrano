
#include "../include/bs_ball.h"

BsBall::BsBall() {
  start_ = false;
  set_direction(sf::Vector2f(1.0f, -4.0f));
  enabled_collision_ = false;
  set_velocity(1.0f);

  set_health_points(3);
  life_lost_ = false;
}

BsBall::~BsBall() {

}

void BsBall::init() {
  BsRect::init(sf::Vector2f(495.0f, 684.0f), sf::Vector2f(10.0f, 10.0f), 0.0f, sf::Vector2f(1.0f, 1.0f), 255, 255, 255, 255, 255, 255, 255, 255, 0);

  const uint8_t kMaxVelocity = 7;
  sf::Vector2f new_direction = {0.0f, 0.0f};
  new_direction.x = static_cast <float> (std::rand() % 3 + 1);
  new_direction.x = new_direction.x - static_cast <float> (std::rand() % (static_cast<int>(new_direction.x * 2.0f)));

  new_direction.y = abs(new_direction.x) - kMaxVelocity;

  set_direction(new_direction);
  life_lost_ = false;
  set_velocity(1.0f);
}

void BsBall::update() {
  if (enabled_ == 1) {
    if (start_ == false) {
      start_ = true;
    }
    if (start_) {
      set_position(position() + direction() * velocity());
    }
    if (position().y < kMinY) {
      direction_.y = -(direction_.y);
      pos_.y = kMinY;
    } else if (position().y > kMaxY) {
      life_lost_ = true;
      set_health_points(health_points() - 1);
      pos_.y = kMaxY;
    }
    if (position().x < kMinX) {
      direction_.x = -(direction_.x);
      pos_.x = kMinX;
    } else if (position().x > kMaxX) {
      direction_.x = -(direction_.x);
      pos_.x = kMaxX;
    }

    if (health_points_ <= 0) {
      set_enabled(0);
    }
  }
}

const sf::Vector2f BsBall::direction() {
  return direction_;
}

void BsBall::set_direction(sf::Vector2f direction) {
  direction_ = direction;
}

bool BsBall::collision(sf::Vector2f rect2, sf::Vector2f size) {
  if (enabled_ == 1) {
    if (pos_.x < rect2.x + size.x &&
     pos_.x + size_.x  > rect2.x &&
     pos_.y - (kCollisionY * velocity()) < rect2.y + size.y &&
     pos_.y > rect2.y) {
     // arriba
       if (enabled_collision_) {
        direction_.y = -(direction_.y);
        enabled_collision_ = false;
      }
      return true;
    } else if (pos_.x < rect2.x + size.x &&
      pos_.x + size_.x > rect2.x &&
      pos_.y + size_.y  < rect2.y + size.y &&
      pos_.y + size_.y + (kCollisionY * velocity()) > rect2.y) {
      // abajo
        if (enabled_collision_) {
          enabled_collision_ = false;
          direction_.y = -(direction_.y);
        }
      return true;
    } else if (pos_.x - (kCollisionX * velocity()) < rect2.x + size.x &&
      pos_.x > rect2.x &&
      pos_.y < rect2.y + size.y &&
      pos_.y + size_.y > rect2.y) {
      // izq
      if (enabled_collision_) {
        enabled_collision_ = false;
        direction_.x = abs(direction_.x);
      }

      return true;
    } else if (pos_.x + size_.x < rect2.x + size.x &&
      pos_.x + size_.x + (kCollisionX * velocity()) > rect2.x &&
      pos_.y < rect2.y + size.y &&
      pos_.y + size_.y > rect2.y) {
      // dcha
      if (enabled_collision_) {
        direction_.x = abs(direction_.x);
        enabled_collision_ = false;
        direction_.x = -(direction_.x);
      }
      return true;
    } else {
      enabled_collision_ = true;
    }
  }

  return false;
}

const float BsBall::velocity() {
  return velocity_;
}

void BsBall::set_velocity(float velocity) {
  velocity_ = velocity;
}

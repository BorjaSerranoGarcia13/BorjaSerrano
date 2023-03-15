
#include "../include/bs_enemy.h"

BsEnemy::BsEnemy() {
  set_health_points(1);
}

BsEnemy::~BsEnemy() {

}

BsEnemy::BsEnemy(const BsEnemy& o) {
  BsRect::init(o.pos_, o.size_, o.rotation_, o.scale_, o.border_r_, o.border_g_, o.border_b_, o.border_a_, o.interior_r_, o.interior_g_, o.interior_b_, o.interior_a_, o.hollow_);
}

void BsEnemy::init() {
  BsRect::init(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(78.0f, 38.0f), 0.0f, sf::Vector2f(1.0f, 1.0f), 255, 255, 255, 255, 255, 255, 255, 255, 0);
}

void BsEnemy::update() {
  if (enabled_ == 1) {
    if (health_points() <= 0) {
     set_enabled(0);
    }
  }
}

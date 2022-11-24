
#include "bs_scene_vector.h"

BsSceneVector::BsSceneVector() {
  tag_ = kTypeScene_Start;
  enabled_ = 1;

  size_label_ = 3;

  rect_ = new BsRect[kMaxRects];

  font_ = { "../../../data/fonts/font1.ttf" };

  do_scale_ = 1;
  do_distance_normalize_ = 1;
  do_lerp_ = 1;
  do_lerp_unclamped = 0;
  do_dot_product = 0;

  direction_ = 0;
  distance_ = 5.0f;

  index_shape_ = 0;
  rect_collision_ = false;
  ball_collision_ = false;

  circle_.setRadius(10.0f);
  circle_.setOrigin(circle_.getRadius(), circle_.getRadius());
  circle_.setPointCount(150);

  scale_vector2_ = 0;
  scale_vector3_ = 0;

}

BsSceneVector::~BsSceneVector() {
    delete[] rect_;
}

void BsSceneVector::init() {
  label_ = new BsLabel[size_label_];

  enabled_ = 1;

  uint8_t border_rgba[] = {255, 255, 255, 255};
  uint8_t fill_rgba[] = {255, 255, 255, 255};
  font_ = {"../../../data/fonts/font1.ttf"};
  label_[0].init("Demo", font_.c_str(), 100, sf::Vector2f(10.0f, 5.0f), 0.0f, sf::Vector2f(1.0f, 1.0f), border_rgba, fill_rgba);
  label_[1].init("F1     F2", font_.c_str(), 50, sf::Vector2f(850.0f, 5.0f), 0.0f, sf::Vector2f(1.0f, 1.0f), border_rgba, fill_rgba);
  label_[2].init("<    >", font_.c_str(), 80, sf::Vector2f(850.0f, 50.0f), 0.0f, sf::Vector2f(1.0f, 1.0f), border_rgba, fill_rgba);

  // scale Vector2
  rect_[0].init(sf::Vector2f(100.0f, 200.0f), float(0.0f), sf::Vector2f(100.0f, 100.0f),
      uint8_t(0), uint8_t(255), uint8_t(255), uint8_t(255),
      uint8_t(0), uint8_t(255), uint8_t(255), uint8_t(255),
      uint8_t(0));

  // distance, lerp, dot Vector2
  rect_[1].init(sf::Vector2f(500.0f, 300.0f),float(0.0f), sf::Vector2f(100.0f, 100.0f),
      uint8_t(0), uint8_t(0), uint8_t(255), uint8_t(255),
      uint8_t(0), uint8_t(0), uint8_t(255), uint8_t(255),
      uint8_t(0));

  rect_[2].init(sf::Vector2f(400.0f, 300.0f), float(0.0f), sf::Vector2f(150.f, 150.f),
      uint8_t(0), uint8_t(255), uint8_t(0), uint8_t(100),
      uint8_t(0), uint8_t(255), uint8_t(0), uint8_t(100),
      uint8_t(0));

  rect_[4].init(sf::Vector2f(600.0f, 300.0f), float(0.0f), sf::Vector2f(150.f, 150.f),
      uint8_t(200), uint8_t(150), uint8_t(200), uint8_t(100),
      uint8_t(200), uint8_t(150), uint8_t(200), uint8_t(100),
      uint8_t(0));

  rect_[3].init(sf::Vector2f(500.0f, 200.0f), float(0.0f), sf::Vector2f(150.f, 150.f),
      uint8_t(200), uint8_t(50), uint8_t(100), uint8_t(100),
      uint8_t(200), uint8_t(50), uint8_t(100), uint8_t(100),
      uint8_t(0));

  rect_[5].init(sf::Vector2f(500.0f, 400.0f),  float(0.0f), sf::Vector2f(150.f, 150.f),
      uint8_t(100), uint8_t(20), uint8_t(200), uint8_t(100),
      uint8_t(100), uint8_t(20), uint8_t(200), uint8_t(100),
      uint8_t(0));

  // rotate Vector2
  circle_.setPosition(800.0f, 400.0f);

  rect_[6].init(sf::Vector2f(800.0f, 500.0f), float(0.0f), sf::Vector2f(300.0f, 40.f),
      uint8_t(255), uint8_t(255), uint8_t(255), uint8_t(255),
      uint8_t(255), uint8_t(255), uint8_t(255), uint8_t(255),
      uint8_t(0));

  // scale Vector3
  rect_[7].init(sf::Vector2f(100.0f, 300.0f), float(0.0f), sf::Vector2f(200.0f, 200.0f),
      uint8_t(255), uint8_t(0), uint8_t(255), uint8_t(255),
      uint8_t(255), uint8_t(0), uint8_t(255), uint8_t(255),
      uint8_t(0));

  // crossP Vector3
  rect_[8].init(sf::Vector2f(400.0f, 600.0f), float(0.0f), sf::Vector2f(70.f, 10.f),
      uint8_t(100), uint8_t(100), uint8_t(100), uint8_t(255),
      uint8_t(100), uint8_t(100), uint8_t(100), uint8_t(255),
      uint8_t(0));
  // reflection Vector3
  rect_[9].init(sf::Vector2f(500.0f, 300.0f), float(0.0f), sf::Vector2f(70.f, 70.f),
      uint8_t(0), uint8_t(255), uint8_t(0), uint8_t(255),
      uint8_t(0), uint8_t(255), uint8_t(0), uint8_t(100),
      uint8_t(0));

  // Inverse Matrix3x3
  rect_[10].init(sf::Vector2f(500.0f, 700.0f), float(0.7f), sf::Vector2f(100.0f, 100.0f),
      uint8_t(0), uint8_t(255), uint8_t(255), uint8_t(255),
      uint8_t(0), uint8_t(255), uint8_t(255), uint8_t(255),
      uint8_t(0));

  // Inverse Matrix4x4
  rect_[11].init(sf::Vector2f(930.0f, 300.0f), float(0.7f), sf::Vector2f(100.0f, 100.0f),
      uint8_t(100), uint8_t(100), uint8_t(255), uint8_t(255),
      uint8_t(100), uint8_t(100), uint8_t(255), uint8_t(255),
      uint8_t(0));
  
  direction_ = 4;
  rect_center_ = { rect_[1].position().x, rect_[1].position().y };

  distanceA_ = { rect_[1].position().x, rect_[1].position().y };
  distanceB_ = { rect_[2].position().x, rect_[2].position().y };
  distance_ = distanceA_.Distance(distanceA_, distanceB_);
  vector_direction_ = { distanceB_.x - distanceA_.x, distanceB_.y - distanceA_.y };
  vector_direction_.Normalize();
}

void BsSceneVector::update() {
    
    if (GM_.input_.mouse_button() == kMouseButton_Left && GM_.game_mode_ == kGameMode_None) {
        mouse_vector_.x = (float)GM_.input_.mouse_position(GM_.window_.window_).x;
        mouse_vector_.y = (float)GM_.input_.mouse_position(GM_.window_.window_).y;
        rotateVector2();
        moveShapes();
    }
    else {
        rect_collision_ = false;
        ball_collision_ = false;
    }

    vectorMethods();
    inverseMatrix3x3();
    inverseMatrix4x4();
}

void BsSceneVector::draw(sf::RenderWindow& window) {
  if (enabled_ == 1) {
    // Draw Rects
    for (int i = 0; i < kMaxRects; ++i) {
        rect_[i].draw(window);
    }
    GM_.window_.window_.draw(circle_);
    // Draw Labels
    for (int i = 0; i < size_label_; ++i) {
        label_[i].draw(window);
    }
  }
}

void BsSceneVector::vectorMethods()
{
    scaleVector2();
    scaleVector3(); 
    followShapes();
    rotateVector3();
    reflectionVector3();

}

void BsSceneVector::moveShapes()
{
    Vector3 distanceA = { mouse_vector_.x, mouse_vector_.y, 1.0f };

    for (int i = 0; i < 10; ++i) {
        
        Vector3 distanceB = { rect_[i].position().x, rect_[i].position().y, 1.0f };

        distance_ = Vector3::Distance(distanceA, distanceB);
        if (distance_ <= rect_[i].scale().x/5 && distance_ <= rect_[i].scale().y/5 && !rect_collision_ && !ball_collision_)
        {
            rect_collision_ = true;
            index_shape_ = i;
        }
        if (BsRect::collision(sf::Vector2f(mouse_vector_.x, mouse_vector_.y), sf::Vector2f(1.f, 1.f),
            circle_.getPosition(), sf::Vector2f(circle_.getRadius(), circle_.getRadius())) &&
            !ball_collision_ && !rect_collision_)
        {
            ball_collision_ = true;
            index_shape_ = i;
        }
    }
    if (rect_collision_) {
        Vector2 rect_pos = { rect_[index_shape_].position().x, rect_[index_shape_].position().y };
        rect_pos = Vector2::Lerp(mouse_vector_, rect_pos, 0.9f);
        rect_[index_shape_].set_position(sf::Vector2f(rect_pos.x, rect_pos.y));
    }
    if (ball_collision_) {
        Vector3 circle_pos = { circle_.getPosition().x, circle_.getPosition().y, 1.0f };
        Vector3 mouse3 = {mouse_vector_.x, mouse_vector_.y, 1.0f};
        circle_pos = Vector3::Lerp(mouse3, circle_pos, 0.2f);
        circle_.setPosition(sf::Vector2f(circle_pos.x, circle_pos.y));
    }
}

void BsSceneVector::followShapes()
{
    distanceA_ = { rect_[1].position().x, rect_[1].position().y };
    switch (direction_) {
    case 0: distanceB_ = { rect_[2].position().x, rect_[2].position().y };
          break;
    case 1: distanceB_ = { rect_[3].position().x, rect_[3].position().y };
          break;
    case 2: distanceB_ = { rect_[4].position().x, rect_[4].position().y };
          break;
    case 3: distanceB_ = { rect_[5].position().x, rect_[5].position().y };
    }
    distance_ = Vector2::Distance(distanceA_, distanceB_);

    vector_direction_ = { distanceB_.x - distanceA_.x, distanceB_.y - distanceA_.y };
    vector_direction_.Normalize();
    rect_[1].set_position(sf::Vector2f(rect_[1].position().x + vector_direction_.x, rect_[1].position().y + vector_direction_.y));

    if (distance_ <= 2.0f) {
        Vector4 new_color = { (float)rect_[1].interior_r_,(float)rect_[1].interior_g_, (float)rect_[1].interior_b_, (float)rect_[1].interior_a_ };
        Vector4 rect_color = { (float)rect_[direction_ + 2].interior_r_,(float)rect_[direction_ + 2].interior_g_, (float)rect_[direction_ + 2].interior_b_, (float)rect_[direction_ + 2].interior_a_ };
        float dot_product = Vector4::DotProduct(new_color.Normalized(), rect_color.Normalized());
        new_color = Vector4::Lerp(new_color.Normalized(), rect_color.Normalized(), 0.5f);
        new_color.Scale(Vector4(255, 255, 255, 255));

        dot_product *= 255.0f;
         rect_[direction_ + 2].set_color(rect_[direction_ + 2].border_r_, rect_[direction_ + 2].border_g_, rect_[direction_ + 2].border_b_, rect_[direction_ + 2].border_a_,
             rect_[direction_ + 2].interior_r_, rect_[direction_ + 2].interior_g_, rect_[direction_ + 2].interior_b_, (uint8_t)dot_product);

        rect_[1].set_color((uint8_t)new_color.x, (uint8_t)new_color.y, (uint8_t)new_color.z, (uint8_t)new_color.w,
            (uint8_t)new_color.x, (uint8_t)new_color.y, (uint8_t)new_color.z, (uint8_t)new_color.w);
        direction_++;
        if (direction_ > 3) { direction_ = 0; }
    }

}

void BsSceneVector::scaleVector2()
{
    Vector2 scale = { 1.0f, 1.0f };
    if (scale_vector2_ == 0) {
        scale.Scale(Vector2(200.0f, 200.0f));
        if (rect_[0].scale().x < scale.x) {
            rect_[0].set_scale(sf::Vector2f(rect_[0].scale().x + 1.f, rect_[0].scale().y));
        }
        else if (rect_[0].scale().y < scale.y) {
            rect_[0].set_scale(sf::Vector2f(rect_[0].scale().x, rect_[0].scale().y + 1.f));
        }
        else if (scale_vector2_ == 0) {
            scale_vector2_ = 1;
        }
    }
    else if (scale_vector2_ == 1)
    {
        scale.Scale(Vector2(100.0f, 100.0f));
        if (rect_[0].scale().y > scale.y) {
            rect_[0].set_scale(sf::Vector2f(rect_[0].scale().x, rect_[0].scale().y - 1.f));
        }
        else if (rect_[0].scale().x > scale.x) {
            rect_[0].set_scale(sf::Vector2f(rect_[0].scale().x - 1.f, rect_[0].scale().y));
        }
        else if (scale_vector2_ == 1) {
            scale_vector2_ = 0;
        }
    }

}

void BsSceneVector::scaleVector3()
{
    Vector3 scale = { 1.0f, 1.0f, 0.0f };
    if (scale_vector3_ == 0) {
        scale.Scale(Vector3(200.0f, 200.0f, 0.0f));
        if (rect_[7].scale().x < scale.x) {
            rect_[7].set_scale(sf::Vector2f(rect_[7].scale().x + 1.f, rect_[7].scale().y));
        }
        else if (rect_[7].scale().y < scale.y) {
            rect_[7].set_scale(sf::Vector2f(rect_[7].scale().x, rect_[7].scale().y + 1.f));
        }
        else if (scale_vector3_ == 0) {
            scale_vector3_ = 1;

        }
    }
    else if (scale_vector3_ == 1)
    {
        scale.Scale(Vector3(100.0f, 100.0f, 0.0f));
        if (rect_[7].scale().y > scale.y) {
            rect_[7].set_scale(sf::Vector2f(rect_[7].scale().x, rect_[7].scale().y - 1.f));
        }
        else if (rect_[7].scale().x > scale.x) {
            rect_[7].set_scale(sf::Vector2f(rect_[7].scale().x - 1.f, rect_[7].scale().y));
        }
        else if (scale_vector3_ == 1) {
            scale_vector3_ = 0;
        }
    }
}

void BsSceneVector::rotateVector2()
{
    // sacar vector direccion primero
    Vector2 circle_pos = { (circle_.getPosition().x - rect_[kRectRotate].position().x), circle_.getPosition().y - rect_[kRectRotate].position().y };
    circle_pos.Normalize();
    Vector2 rect_rotation = { ((rect_[kRectRotate].position().x + rect_[kRectRotate].scale().x) - rect_[kRectRotate].position().x), (rect_[kRectRotate].position().y) - rect_[kRectRotate].position().y };
    rect_rotation.Normalize();
    
    
    float angle = asin(Vector2::DotProduct(rect_rotation, circle_pos)) ;
    if (circle_.getPosition().y > rect_[kRectRotate].position().y) {
        angle = -angle;
    }
    rect_[kRectRotate].set_rotation(angle);
}

void BsSceneVector::rotateVector3()
{
    Vector3 v = { ((circle_.getPosition().x ) - (rect_[6].position().x )), (circle_.getPosition().y ) - (rect_[6].position().y ), 0.0f };
    Vector3 k = { rect_[6].position().x + rect_[6].scale().x - rect_[6].position().x, (rect_[6].position().y) - rect_[6].position().y, 0.0f };
    
    Vector3 v2 = { ((circle_.getPosition().x) - (rect_[8].position().x)), (circle_.getPosition().y) - (rect_[8].position().y), 0.0f };
    Vector3 k2 = { rect_[8].position().x + rect_[8].scale().x - rect_[8].position().x, (rect_[8].position().y) - rect_[8].position().y, 0.0f };
    float angle = Vector3::Angle(v2, k2);
    if (angle >= 1.4f && angle <= 1.6f)
    {
        rect_[8].set_color(uint8_t(100), uint8_t(0), uint8_t(100), uint8_t(255),
            uint8_t(100), uint8_t(100), uint8_t(0), uint8_t(255));
    }
    else {
        rect_[8].set_color(uint8_t(100), uint8_t(100), uint8_t(100), uint8_t(255),
            uint8_t(100), uint8_t(100), uint8_t(100), uint8_t(255));
    }

    v.Normalize();
    k = k.Normalized();
    Vector3 perpendicular = Vector3::CrossProduct(v, k);

    
    if (perpendicular.Normalized() == Vector3::forward) {
        // do color
        Vector4 pos_rect = { rect_[6].position().x , rect_[6].position().y, 0.0f, 0.0f };
        Vector4 pos_circle = { circle_.getPosition().x , circle_.getPosition().y, 0.0f, 0.0f };
        float distance = Vector4::Distance(pos_rect, pos_circle);
        if (distance > 255.0f) distance = 255.0f;
        rect_[6].set_color((uint8_t)distance, (uint8_t)distance, (uint8_t)distance, (uint8_t)distance,
        (uint8_t)distance, (uint8_t)distance, (uint8_t)distance, (uint8_t)distance);
    }
    else {
        rect_[6].set_color(255, 255, 255, 255, 255, 255, 255, 255);
    }
}

void BsSceneVector::reflectionVector3()
{
    Vector3 dir = {vector_direction_.x, vector_direction_.y , 0.0f};
    dir.Normalize();
    Vector3 reflection = Vector3::Reflect(dir, Vector3::left);
    Vector3 pos = { rect_[9].position().x, rect_[9].position().y, 0.0f };
    rect_[9].set_position(sf::Vector2f(rect_[9].position().x + reflection.x, rect_[9].position().y + reflection.y));
}

void BsSceneVector::inverseMatrix3x3()
{
    Matrix3x3 matrix;
    matrix = matrix.Identity();
    Vector2 new_vector;
    new_vector.x = (float)GM_.input_.mouse_position(GM_.window_.window_).x;
    new_vector.y = (float)GM_.input_.mouse_position(GM_.window_.window_).y;
    matrix = matrix.Multiply(matrix.Translate(new_vector));

    matrix.Inverse();

    Vector3 line = matrix.GetLine(0);
    Vector3 column = matrix.GetColum(0);
    float inverseX = rect_[10].position().x * column.x + rect_[10].position().y * line.y + 1.0f * line.z;
    rect_[10].set_position(sf::Vector2f(rect_[10].position().x + inverseX * 0.01f, rect_[10].position().y));
    if (rect_[10].position().x < 100.0f) rect_[10].position_.x = 100.0f;
    if (rect_[10].position().x > 900.0f) rect_[10].position_.x = 900.0f;
}

void BsSceneVector::inverseMatrix4x4()
{
    Matrix4x4 matrix;
    matrix = matrix.Identity();
    Vector3 new_vector;
    new_vector.x = (float)GM_.input_.mouse_position(GM_.window_.window_).x;
    new_vector.y = (float)GM_.input_.mouse_position(GM_.window_.window_).y;
    new_vector.z = 1.0f;
    matrix = matrix.Multiply(matrix.Translate(new_vector));

    matrix.Inverse();

    Vector4 line = matrix.GetLine(1);
    Vector4 column = matrix.GetColum(0);
    float inverseY = rect_[11].position().x * column.y + rect_[11].position().y * line.y + 1.0f * line.z + 1.0f * line.w;
    rect_[11].set_position(sf::Vector2f(rect_[11].position().x , rect_[11].position().y + inverseY * 0.01f));
    if (rect_[11].position().y < 100.0f) rect_[11].position_.y = 100.0f;
    if (rect_[11].position().y > 700.0f) rect_[11].position_.y = 700.0f;
}

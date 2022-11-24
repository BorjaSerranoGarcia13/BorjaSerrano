
#include "bs_path.h"

uint32_t BsPath::s_total_shapes_;

BsPath::BsPath() {
  enabled_ = 1;
  position_ = {0.0f, 0.0f};
  scale_ = {1.0f, 1.0f};
  rotation_ = 0.0f;

  s_total_shapes_ = 0;
 
  stroke_color_.x = 0xFF;
  stroke_color_.y = 0xFF;
  stroke_color_.z = 0xFF;
  stroke_color_.w = 0xFF;

  fill_color_.x = 0xFF;
  fill_color_.y = 0xFF;
  fill_color_.z = 0xFF;
  fill_color_.w = 0xFF;
  
  solid_color_ = 0;

  buffer_vector_ = new BufferVector;
  buffer_vector_->capacity_ = kCapacityVector;
  buffer_vector_->head_ = 0;
  buffer_vector_->tail_ = 0;
}

BsPath::BsPath(const BsPath& o) {
  enabled_ = o.enabled_;
  tag_ = o.tag_;

  position_ = o.position_;
  scale_ = o.scale_;
  rotation_ = o.rotation_;
  
  stroke_color_.x = o.stroke_color_.x;
  stroke_color_.y = o.stroke_color_.y;
  stroke_color_.z = o.stroke_color_.w;
  stroke_color_.w = o.stroke_color_.z;

  fill_color_.x = o.fill_color_.x;
  fill_color_.y = o.fill_color_.y;
  fill_color_.z = o.fill_color_.w;
  fill_color_.w = o.fill_color_.z;

  solid_color_ = o.solid_color_;
}

BsPath::~BsPath() {
    delete buffer_vector_;
}

void BsPath::init() {
  position_ = {0.0f, 0.0f};
  scale_ = {1.0f, 1.0f};
  rotation_ = 0.0f;
  /*
  stroke_color_[0] = 0xFF;
  stroke_color_[1] = 0xFF;
  stroke_color_[2] = 0xFF;
  stroke_color_[3] = 0xFF;

  fill_color_[0] = 0xFF;
  fill_color_[1] = 0xFF;
  fill_color_[2] = 0xFF;
  fill_color_[3] = 0xFF;
  */
  solid_color_ = 0;
}

void BsPath::initBuffer() {
   
}


void BsPath::addVertex(const Vector2* vertex) {
  if (vertex == nullptr) return;
  if (buffer_vector_->tail_ < kCapacityVector && buffer_vector_->tail_ < kMaxShapes) {
      
      buffer_vector_->vector_[buffer_vector_->tail_].x = vertex->x;
      buffer_vector_->vector_[buffer_vector_->tail_].y = vertex->y;
      
      buffer_vector_->tail_++;
      convex_.setPointCount(buffer_vector_->tail_);
  }
}

sf::Vector2f BsPath::position()
{
    return position_;
}

float BsPath::rotation()
{
    return rotation_;
}

sf::Vector2f BsPath::scale()
{
    return scale_;
}

void BsPath::set_position(sf::Vector2f pos)
{
    position_.x = pos.x;
    position_.y = pos.y;
}

void BsPath::set_rotation(float rot)
{
    rotation_ = rot;
}

void BsPath::set_scale(sf::Vector2f scale)
{
    scale_.x = scale.x;
    scale_.y = scale.y;
}

void BsPath::draw(sf::RenderWindow& window) {
  if (enabled_) {
      Matrix4x4 matrix;
      matrix.Identity();
      matrix = matrix.GetTransform(position().x, position().y, 1.0f,
          scale().x, scale().y, 1.0f,
          0.0f, 0.0f, rotation());

      sf::Vector2f buffer;
      for (int i = 0; i < buffer_vector_->tail_; ++i)
      {
          buffer.x = buffer_vector_->vector_[i].x * matrix.m[0] + buffer_vector_->vector_[i].y * matrix.m[1] + 1.0f * matrix.m[2] + 1.0f * matrix.m[3];
          buffer.y = buffer_vector_->vector_[i].x * matrix.m[4] + buffer_vector_->vector_[i].y * matrix.m[5] + 1.0f * matrix.m[6] + 1.0f * matrix.m[7];
          convex_.setPoint(i, sf::Vector2f(buffer.x, buffer.y));
      }
      
      window.draw(convex_);    
  }
}

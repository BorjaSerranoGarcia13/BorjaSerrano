
#include "bs_entity.h"

uint32_t BsEntity::s_entity_counter_ = 0;

BsEntity::BsEntity() {
  tag_ = -1;
  enabled_ = 0;
  id_ = BsEntity::s_entity_counter_;
  ++BsEntity::s_entity_counter_;
}

BsEntity::BsEntity(const BsEntity& o) {
  tag_ = o.tag_;
  enabled_ = o.enabled_;
  id_ = BsEntity::s_entity_counter_;
  ++BsEntity::s_entity_counter_;
}

BsEntity::~BsEntity() {}

uint32_t BsEntity::id() {
    return id_;
}

void BsEntity::init() {
  tag_ = -1;
  enabled_ = 0;
}

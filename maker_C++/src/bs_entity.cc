
/**
 * Author: Borja Serrano <serranoga@esat-alumni.com>
 * Filename: bs_backgorund.cc
 *
 * Implementation: background class
 */

#include "bs_entity.h"

uint32_t bsEntity::entity_counter_ = 0;

bsEntity::bsEntity() {
  tag_ = -1;
  enabled_ = 0;
  id_ = bsEntity::entity_counter_;
  ++bsEntity::entity_counter_;
}

bsEntity::bsEntity(const bsEntity& o) {

  tag_ = o.tag_;
  enabled_ = o.enabled_;
  id_ = bsEntity::entity_counter_;
  ++bsEntity::entity_counter_;

}

void bsEntity::init() {

  tag_ = -1;
  enabled_ = 0;

}

void bsEntity::draw() {}

uint32_t bsEntity::id() {

  return id_;

}

bsEntity::~bsEntity() {}

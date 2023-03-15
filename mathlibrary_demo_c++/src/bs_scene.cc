
#include "bs_scene.h"

BsScene::BsScene() {
  tag_ = -1;
  enabled_ = 0;
  size_label_ = 0;
}

BsScene::~BsScene() {
  delete[] label_;
  label_ = nullptr;
}

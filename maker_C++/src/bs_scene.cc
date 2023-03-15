
#include "bs_scene.h"

bsScene::bsScene() {
  mouse_pos_x_ = 0.0f;
  mouse_pos_y_ = 0.0f;
  create_cube_ = false;

  delete_cube_ = false;


  player_fall_ = false;
  player_mov_right_ = false;
  player_mov_left_ = false;
  player_jump_ = false;
  player_jump_distance_ = 0.0f;

  color_draw_[0] = 255;
  color_draw_[1] = 255;
  color_draw_[2] = 0;
  color_draw_[3] = 255;

  order_by_tag_ = false;
}

// QUAD COLLISION
bool bsScene::CheckRectangleColision(float x, float y, float width, float height, float x2, float y2, float width2, float height2) {
    if (((x <= x2+width2 && x >= x2) || (x+width <= x2+width2 && x+width >= x2)) && ((y >= y2 && y <= y2+height2) || (y+height >= y2 && y+height <= y2+height2))) {
        return true;
    }
    return false;
}

void bsScene::playGame() {

  if (bsGameManager::getInstance()->edition()) {
    editionMode();
    bsGameManager::getInstance()->label_->set_text("EDITION ACTIVE");
    if (create_cube_) {
      addCube();
    }
    if (delete_cube_) {
      deleteCube();
    }
  } else {
    playMode();
    bsGameManager::getInstance()->label_->set_text("PLAY ACTIVE");
  }

  drawAllCubes();

  bsGameManager::getInstance()->label_->set_fill_color(255, 0, 255, 255);
  bsGameManager::getInstance()->label_->set_stroke_color(255, 0, 255, 255);
  bsGameManager::getInstance()->label_->draw();
  IMGUI();
}

void bsScene::controls() {
  if (esat::IsKeyDown('E')) {
    if (bsGameManager::getInstance()->edition()) {
      bsGameManager::getInstance()->set_edition(false);
    } else {
      bsGameManager::getInstance()->set_edition(true);
    }
  }

  if (esat::MouseButtonPressed(0)) {
    mouse_pos_x_ = esat::MousePositionX();
    mouse_pos_y_ = esat::MousePositionY();
    create_cube_ = true;
  } else {
    create_cube_ = false;
  }
  if (esat::MouseButtonPressed(1)) {
    mouse_pos_x_ = esat::MousePositionX();
    mouse_pos_y_ = esat::MousePositionY();
    delete_cube_ = true;
  } else {
    delete_cube_ = false;
  }

}

void bsScene::addCube() {
  esat::Vec2 playerPos = bsGameManager::getInstance()->player_->position();
  for (int i = 0; i < bsGameManager::getInstance()->size_edition() * bsGameManager::getInstance()->size_edition(); i++) {
    esat::Vec2 pos = bsGameManager::getInstance()->cubes[i]->position();
    if (mouse_pos_y_ > pos.y && mouse_pos_y_ < (pos.y + 600/bsGameManager::getInstance()->size_edition()) &&
        mouse_pos_x_ > pos.x && mouse_pos_x_ < (pos.x + 800/bsGameManager::getInstance()->size_edition()) &&
        !CheckRectangleColision(playerPos.x, playerPos.y,
                                bsGameManager::getInstance()->player_->width_ , bsGameManager::getInstance()->player_->height_,
                                pos.x, pos.y, bsGameManager::getInstance()->cubes[i]->width_,
                                bsGameManager::getInstance()->cubes[i]->height_) &&
                                bsGameManager::getInstance()->cubes[i]->tag_ == 2) {
          bsGameManager::getInstance()->cubes[i]->enabled_ = 1;
          bsGameManager::getInstance()->cubes[i]->interior_r_ = (uint8_t)color_draw_[0];
          bsGameManager::getInstance()->cubes[i]->interior_g_ = (uint8_t)color_draw_[1];
          bsGameManager::getInstance()->cubes[i]->interior_b_ = (uint8_t)color_draw_[2];
          bsGameManager::getInstance()->cubes[i]->interior_a_ = (uint8_t)color_draw_[3];
          break;
    }
  }
}

void bsScene::deleteCube() {
  for (int i = 0; i < bsGameManager::getInstance()->size_edition() * bsGameManager::getInstance()->size_edition(); i++) {
    esat::Vec2 pos = bsGameManager::getInstance()->cubes[i]->position();
    if (mouse_pos_y_ > pos.y && mouse_pos_y_ < (pos.y + 600/bsGameManager::getInstance()->size_edition()) &&
        mouse_pos_x_ > pos.x && mouse_pos_x_ < (pos.x + 800/bsGameManager::getInstance()->size_edition())) {
          bsGameManager::getInstance()->cubes[i]->enabled_ = 0;
         break;
    }
  }
  for (int i = 0; i < bsGameManager::getInstance()->size_edition(); i++) {
    for (int j = 0; j < bsGameManager::getInstance()->size_edition(); j++) {
      if (i == 0 || (i == bsGameManager::getInstance()->size_edition() - 1) || j == 0 || j == bsGameManager::getInstance()->edition() - 1)
      {
        bsGameManager::getInstance()->cubes[j + i * bsGameManager::getInstance()->size_edition()]->enabled_ = 1;
      }
    }
  }
}

void bsScene::drawAllCubes() {
  for (int i = 0; i < bsGameManager::getInstance()->size_edition() * bsGameManager::getInstance()->size_edition(); i++)
  {
    if (bsGameManager::getInstance()->cubes[i]->enabled_ == 1)
      bsGameManager::getInstance()->cubes[i]->draw();
  }

  if (bsGameManager::getInstance()->player_->enabled_)
  {
    bsGameManager::getInstance()->player_->draw();
  }
}

void bsScene::editionMode() {
  float x = 0;
  float y = 0;
  esat::DrawSetStrokeColor(255, 255, 255, 255);
  for (int i = 0; i < bsGameManager::getInstance()->size_edition(); i++) {
    esat::DrawLine(x, 0, x, 600);
    x += 800/bsGameManager::getInstance()->size_edition();
    esat::DrawLine(0, y, 800, y);
    y += 600/bsGameManager::getInstance()->size_edition();
  }
}

void bsScene::initEditionMode() {
  float x = 0;
  float y = 0;

  for (int i = 0; i < 30; i++) {
    for (int j = 0; j < 30; j++) {
      bsGameManager::getInstance()->cubes[j + i * bsGameManager::getInstance()->size_edition()]->init({x, y}, (float)800/bsGameManager::getInstance()->size_edition(), (float)600/bsGameManager::getInstance()->size_edition(), 0, {1,1},
      100, 100, 0, 255,
      200, 200, 0, 255,
      15);

      if (i == 0 || (i == bsGameManager::getInstance()->size_edition() - 1) || j == 0 || j == bsGameManager::getInstance()->size_edition() - 1)
      {
        bsGameManager::getInstance()->cubes[j + i * bsGameManager::getInstance()->size_edition()]->tag_ = 3;
        bsGameManager::getInstance()->cubes[j + i * bsGameManager::getInstance()->size_edition()]->enabled_ = 1;
        bsGameManager::getInstance()->cubes[j + i * bsGameManager::getInstance()->size_edition()]->interior_r_ = 0;
        bsGameManager::getInstance()->cubes[j + i * bsGameManager::getInstance()->size_edition()]->interior_g_ = 0;
        bsGameManager::getInstance()->cubes[j + i * bsGameManager::getInstance()->size_edition()]->interior_b_ = 0;
        bsGameManager::getInstance()->cubes[j + i * bsGameManager::getInstance()->size_edition()]->interior_a_ = 200;
      } else {
        bsGameManager::getInstance()->cubes[j + i * bsGameManager::getInstance()->size_edition()]->enabled_ = 0;
        bsGameManager::getInstance()->cubes[j + i * bsGameManager::getInstance()->size_edition()]->tag_ = 2;
        bsGameManager::getInstance()->cubes[j + i * bsGameManager::getInstance()->size_edition()]->border_r_ = 0;
        bsGameManager::getInstance()->cubes[j + i * bsGameManager::getInstance()->size_edition()]->border_g_ = 0;
        bsGameManager::getInstance()->cubes[j + i * bsGameManager::getInstance()->size_edition()]->border_b_ = 0;
        bsGameManager::getInstance()->cubes[j + i * bsGameManager::getInstance()->size_edition()]->border_a_ = 255;
      }
      x += 800/bsGameManager::getInstance()->size_edition();
    }
    x = 0;
    y  += 600/bsGameManager::getInstance()->size_edition();
  }
  bsGameManager::getInstance()->player_->init({400.0f, 300.0f}, (float)800/bsGameManager::getInstance()->size_edition() * 0.5f, (float)600/bsGameManager::getInstance()->size_edition() * 0.5f, 0, {1,1},
  255, 0, 0, 255,
  100, 0, 0, 255,
  15);
  bsGameManager::getInstance()->player_->enabled_ = 1;

  player_fall_ = false;
  player_mov_right_ = false;
  player_mov_left_ = false;
  player_jump_ = false;
  player_jump_distance_ = 0.0f;
}

void bsScene::playMode() {
  if (bsGameManager::getInstance()->player_->enabled_) {
    esat::Vec2 playerPos = bsGameManager::getInstance()->player_->position();

    for (int i = 0; i < bsGameManager::getInstance()->size_edition() * bsGameManager::getInstance()->size_edition(); i++) {
      if (bsGameManager::getInstance()->cubes[i]->enabled_ == 1) {
        esat::Vec2 cubePos = bsGameManager::getInstance()->cubes[i]->position();
        if (CheckRectangleColision(playerPos.x + 2, playerPos.y + 4, bsGameManager::getInstance()->player_->width_ - 4, bsGameManager::getInstance()->player_->height_ - 4, cubePos.x, cubePos.y, bsGameManager::getInstance()->cubes[i]->width_, bsGameManager::getInstance()->cubes[i]->height_)) {
          player_fall_ = true;
        }
        if (CheckRectangleColision(playerPos.x + 2, playerPos.y - 4, bsGameManager::getInstance()->player_->width_ - 4, bsGameManager::getInstance()->player_->height_ - 4, cubePos.x, cubePos.y, bsGameManager::getInstance()->cubes[i]->width_, bsGameManager::getInstance()->cubes[i]->height_)) {
          player_jump_ = false;
          player_jump_distance_ = 0.0f;
        }
        if (CheckRectangleColision(playerPos.x, playerPos.y, bsGameManager::getInstance()->player_->width_ * 0.3f, bsGameManager::getInstance()->player_->height_ - 2, cubePos.x, cubePos.y, bsGameManager::getInstance()->cubes[i]->width_, bsGameManager::getInstance()->cubes[i]->height_)) {
          player_mov_left_ = true;
        }
        if (CheckRectangleColision(playerPos.x + bsGameManager::getInstance()->player_->width_ - 2, playerPos.y, 2, bsGameManager::getInstance()->player_->height_ - 2, cubePos.x, cubePos.y, bsGameManager::getInstance()->cubes[i]->width_, bsGameManager::getInstance()->cubes[i]->height_)) {
          player_mov_right_ = true;
        }
      }
    }

    if (player_jump_) {
      if (bsGameManager::getInstance()->puzzle_mode()) {
        if (esat::IsKeyPressed('W')) {
          playerPos.y -= 2.0f;
        }
      } else {
        player_jump_distance_ += 3.0f;
        playerPos.y -= 8.0f;
        if (player_jump_distance_ > bsGameManager::getInstance()->cubes[0]->height_) {
          player_jump_distance_ = 0.0f;
          player_jump_ = false;
        }
      }
    }

    if (!player_fall_) {
      if (bsGameManager::getInstance()->puzzle_mode()) {
        if (esat::IsKeyPressed('S')) {
          playerPos.y += 2.0f;
        }
      } else {
        playerPos.y += 2.0f;
      }
    } else if (!bsGameManager::getInstance()->puzzle_mode()){
      if (esat::IsSpecialKeyDown(esat::kSpecialKey_Space)) {
        player_jump_ = true;
      }
    }

    if (!player_mov_left_) {
      if (esat::IsKeyPressed('A')) {
        playerPos.x -= 2.0f;
      }
    }
    if (!player_mov_right_) {
      if (esat::IsKeyPressed('D')) {
        playerPos.x += 2.0f;
      }
    }

    bsGameManager::getInstance()->player_->set_position(playerPos);
    player_mov_left_ = false;
    player_mov_right_ = false;
    player_fall_= false;
    if (bsGameManager::getInstance()->puzzle_mode())player_jump_ = true;
  }
}

void bsScene::addBackground() {
  bsGameManager::getInstance()-> bsGameManager::getInstance()->background_->init("../data/imagen/space.png");
  esat::Vec2 backgroundPos = {0, 0};
  bsGameManager::getInstance()-> bsGameManager::getInstance()->background_->set_position(backgroundPos);
  bsGameManager::getInstance()-> bsGameManager::getInstance()->background_->tag_ = 1;
   bsGameManager::getInstance()->background_->enabled_ = 1;


  bsGameManager::getInstance()->label_->init("hola", "../data/fonts/font1.ttf", 50);
  esat::Vec2 posLabel = {300, 50};
  bsGameManager::getInstance()->label_->set_position(posLabel);
  bsGameManager::getInstance()->label_->enabled_ = 1;
  bsGameManager::getInstance()->label_->tag_ = 4;
}

void bsScene::drawBackground() {
  if ( bsGameManager::getInstance()->background_->enabled_ == 1) {
     bsGameManager::getInstance()->background_->draw();
  }
}

void bsScene::allElements() {

  *(bsGameManager::getInstance()->all_elements_ + 0) = bsGameManager::getInstance()->player_;
  *(bsGameManager::getInstance()->all_elements_ + 1) = bsGameManager::getInstance()->background_;
  *(bsGameManager::getInstance()->all_elements_ + 2) = bsGameManager::getInstance()->label_;
  for (int i = 3; i < 903; i++)
  {
    *(bsGameManager::getInstance()->all_elements_ + i) = bsGameManager::getInstance()->cubes[i - 3];
  }

  int cc = 0;
  for (int i = 0; i < 903; i++)
  {
    if ((*(bsGameManager::getInstance()->all_elements_ + i))->tag_ == 0 )
    {
      *(bsGameManager::getInstance()->all_elements_tag_ + cc) = *(bsGameManager::getInstance()->all_elements_ + i);
      cc++;
    }
  }

  for (int i = 0; i < 903; i++)
  {
    if ((*(bsGameManager::getInstance()->all_elements_ + i))->tag_ == 1 )
    {
      *(bsGameManager::getInstance()->all_elements_tag_ + cc) = *(bsGameManager::getInstance()->all_elements_ + i);
      cc++;
    }
  }
  for (int i = 0; i < 903; i++)
  {
    if ((*(bsGameManager::getInstance()->all_elements_ + i))->tag_ == 2 )
    {
      *(bsGameManager::getInstance()->all_elements_tag_ + cc) = *(bsGameManager::getInstance()->all_elements_ + i);
      cc++;
    }
  }
  for (int i = 0; i < 903; i++)
  {
    if ((*(bsGameManager::getInstance()->all_elements_ + i))->tag_ == 3 )
    {
      *(bsGameManager::getInstance()->all_elements_tag_ + cc) = *(bsGameManager::getInstance()->all_elements_ + i);
      cc++;
    }
  }
  for (int i = 0; i < 903; i++)
  {
    if ((*(bsGameManager::getInstance()->all_elements_ + i))->tag_ == 4 )
    {
      *(bsGameManager::getInstance()->all_elements_tag_ + cc) = *(bsGameManager::getInstance()->all_elements_ + i);
      cc++;
    }
  }
  for (int i = 0; i < 903; i++)
  {
    if ((*(bsGameManager::getInstance()->all_elements_ + i))->tag_ == -1 )
    {
      *(bsGameManager::getInstance()->all_elements_tag_ + cc) = *(bsGameManager::getInstance()->all_elements_ + i);
      cc++;
    }
  }
}

void bsScene::IMGUI() {
    // values to change
    static char txt[1024] = "2";
    static float clear_col[4] = {1,2,3, 255};
    static float position[]{ 0.0f, 1.0f };
    bool open;
    //ImGui::SetNextWindowPos(ImVec2(0,0));
    ImGui::SetNextWindowSize(ImVec2(200, 280), ImGuiSetCond_Once);
    ImGui::Begin("MATRIX SIZE");
    ImGui::Text("SIZE %d x %d", bsGameManager::getInstance()->size_edition(), bsGameManager::getInstance()->size_edition());
    ImGui::Text("\n");
    ImGui::Text("CHANGE MATRIX SIZE");
    ImGui::Text("MIN 10 - 30 MAX");
    static int newSize = bsGameManager::getInstance()->size_edition();
    ImGui::InputInt("", &newSize);
    if (newSize < 10) {
      newSize = 10;
    }
    if (newSize > 30) {
      newSize = 30;
    }
    if (ImGui::Button("APPLY")) {
      bsGameManager::getInstance()->set_edition(true);
      bsGameManager::getInstance()->set_size_edition(newSize);
      initEditionMode();
      allElements();
    }
    ImGui::Text("\n");
    if (ImGui::Button("RESET")) {
      initEditionMode();
      bsGameManager::getInstance()->set_edition(true);
    }
    if (!bsGameManager::getInstance()->puzzle_mode())
    {
      char txt2[1024] = "CENITAL VIEW";
      strcpy(txt, txt2);
    } else {
      char txt2[1024] = "NORMAL VIEW";
      strcpy(txt, txt2);
    }
    if (ImGui::Button(txt)) {
      if (bsGameManager::getInstance()->puzzle_mode() == true) bsGameManager::getInstance()->set_puzzle_mode(false);
      else bsGameManager::getInstance()->set_puzzle_mode(true);
    }
    ImGui::Text("");
    ImGui::Text("Color Draw");
    ImGui::DragFloat4("", color_draw_);
    if (color_draw_[0] > 255) color_draw_[0] = 255;
    if (color_draw_[1] > 255) color_draw_[1] = 255;
    if (color_draw_[2] > 255) color_draw_[2] = 255;
    if (color_draw_[3] > 255) color_draw_[3] = 255;
    if (color_draw_[0] < 0) color_draw_[0] = 0;
    if (color_draw_[1] < 0) color_draw_[1] = 0;
    if (color_draw_[2] < 0) color_draw_[2] = 0;
    if (color_draw_[3] < 0) color_draw_[3] = 0;

    if (ImGui::Button("SAVE")) {
      bsGameManager::getInstance()->set_save(true);
    }

    ImGui::End();

    //ImGui::ShowTestWindow();
    ImGui::SetNextWindowSize(ImVec2(300, 400), ImGuiSetCond_Once);
    ImGui::Begin("ALL ELEMENTS");
    if (ImGui::Button("ID")) {
      order_by_tag_ = false;
    }
    ImGui::SameLine();
    if (ImGui::Button("TAG")) {
        order_by_tag_ = true;
    }
    if (!order_by_tag_)
    {
      for (int i = 0; i < 30 * 30 + 3; i++) {
        ImGui::Text("%d     %d   ", (*(bsGameManager::getInstance()->all_elements_ + i))->id(), (*(bsGameManager::getInstance()->all_elements_ + i))->tag_);
        ImGui::SameLine();
        if ((*(bsGameManager::getInstance()->all_elements_ + i))->enabled_ == 1) {
           char txt2[1024] = "ENABLED";
           char idid[1024];
           itoa (i,idid,10);
           strcat(txt2, idid);
           strcpy(txt, txt2);
         } else {
           char txt2[1024] = "DISABLED";
           char idid[1024];
           itoa (i,idid,10);
           strcat(txt2, idid);
           strcpy(txt, txt2);
         }
        if (ImGui::Button(txt, ImVec2(100, 20))) {
          if ((*(bsGameManager::getInstance()->all_elements_ + i))->enabled_ == 1) {
            (*(bsGameManager::getInstance()->all_elements_ + i))->enabled_ = 0;
          } else {
            (*(bsGameManager::getInstance()->all_elements_ + i))->enabled_ = 1;
          }
        }
        if ((*(bsGameManager::getInstance()->all_elements_ + i))->enabled_ == 1) {
          char txt2[1024] = "COLOR ";
          char idid[1024];
          itoa (i,idid,10);
          strcat(txt2, idid);
          strcpy(txt, txt2);
          if ((*(bsGameManager::getInstance()->all_elements_ + i))->tag_ == 0 )
            {
              float color[4] = {(float)bsGameManager::getInstance()->player_->interior_r_ , (float)bsGameManager::getInstance()->player_->interior_g_, (float)bsGameManager::getInstance()->player_->interior_b_, (float)bsGameManager::getInstance()->player_->interior_a_};
              ImGui::DragFloat4(txt, color);
              if (color[0] > 255) color[0] = 255;
              if (color[1] > 255) color[1] = 255;
              if (color[2] > 255) color[2] = 255;
              if (color[3] > 255) color[3] = 255;
              if (color[0] < 0) color[0] = 0;
              if (color[1] < 0) color[1] = 0;
              if (color[2] < 0) color[2] = 0;
              if (color[3] < 0) color[3] = 0;
              bsGameManager::getInstance()->player_->border_r_ = (uint8_t)color[0];
              bsGameManager::getInstance()->player_->border_g_ = (uint8_t)color[1];
              bsGameManager::getInstance()->player_->border_b_ = (uint8_t)color[2];
              bsGameManager::getInstance()->player_->border_a_ = (uint8_t)color[3];
              bsGameManager::getInstance()->player_->interior_r_ = (uint8_t)color[0];
              bsGameManager::getInstance()->player_->interior_g_ = (uint8_t)color[1];
              bsGameManager::getInstance()->player_->interior_b_ = (uint8_t)color[2];
              bsGameManager::getInstance()->player_->interior_a_ = (uint8_t)color[3];
            }
            else if ((*(bsGameManager::getInstance()->all_elements_ + i))->tag_ == 2)
            {
              float color[4] = {(float)bsGameManager::getInstance()->cubes[i - 3]->interior_r_ , (float)bsGameManager::getInstance()->cubes[i - 3]->interior_g_, (float)bsGameManager::getInstance()->cubes[i - 3]->interior_b_, (float)bsGameManager::getInstance()->cubes[i - 3]->interior_a_};
              ImGui::DragFloat4(txt, color);
              bsGameManager::getInstance()->cubes[i - 3]->interior_r_ = (uint8_t)color[0];
              bsGameManager::getInstance()->cubes[i - 3]->interior_g_ = (uint8_t)color[1];
              bsGameManager::getInstance()->cubes[i - 3]->interior_b_ = (uint8_t)color[2];
              bsGameManager::getInstance()->cubes[i - 3]->interior_a_ = (uint8_t)color[3];
            }
          }
        ImGui::Text("\n");
      }
    }
    else
    {
      for (int i = 0; i < 30 * 30 + 3; i++) {
        ImGui::Text("%d     %d   ", (*(bsGameManager::getInstance()->all_elements_tag_ + i))->id(), (*(bsGameManager::getInstance()->all_elements_tag_ + i))->tag_);
        ImGui::SameLine();
        if ((*(bsGameManager::getInstance()->all_elements_tag_ + i))->enabled_ == 1) {
           char txt2[1024] = "ENABLED";
           char idid[1024];
           itoa (i,idid,10);
           strcat(txt2, idid);
           strcpy(txt, txt2);
         } else {
           char txt2[1024] = "DISABLED";
           char idid[1024];
           itoa (i,idid,10);
           strcat(txt2, idid);
           strcpy(txt, txt2);
         }
        if (ImGui::Button(txt, ImVec2(100, 20))) {
          if ((*(bsGameManager::getInstance()->all_elements_tag_ + i))->enabled_ == 1) {
            (*(bsGameManager::getInstance()->all_elements_tag_ + i))->enabled_ = 0;
          } else {
            (*(bsGameManager::getInstance()->all_elements_tag_ + i))->enabled_ = 1;
          }
        }
        if ((*(bsGameManager::getInstance()->all_elements_tag_ + i))->enabled_ == 1) {
          char txt2[1024] = "COLOR ";
          char idid[1024];
          itoa (i,idid,10);
          strcat(txt2, idid);
          strcpy(txt, txt2);
          if ((*(bsGameManager::getInstance()->all_elements_tag_ + i))->tag_ == 0 )
            {
              float color[4] = {(float)bsGameManager::getInstance()->player_->interior_r_ , (float)bsGameManager::getInstance()->player_->interior_g_, (float)bsGameManager::getInstance()->player_->interior_b_, (float)bsGameManager::getInstance()->player_->interior_a_};
              ImGui::DragFloat4(txt, color);
              if (color[0] > 255) color[0] = 255;
              if (color[1] > 255) color[1] = 255;
              if (color[2] > 255) color[2] = 255;
              if (color[3] > 255) color[3] = 255;
              if (color[0] < 0) color[0] = 0;
              if (color[1] < 0) color[1] = 0;
              if (color[2] < 0) color[2] = 0;
              if (color[3] < 0) color[3] = 0;
              bsGameManager::getInstance()->player_->border_r_ = (uint8_t)color[0];
              bsGameManager::getInstance()->player_->border_g_ = (uint8_t)color[1];
              bsGameManager::getInstance()->player_->border_b_ = (uint8_t)color[2];
              bsGameManager::getInstance()->player_->border_a_ = (uint8_t)color[3];
              bsGameManager::getInstance()->player_->interior_r_ = (uint8_t)color[0];
              bsGameManager::getInstance()->player_->interior_g_ = (uint8_t)color[1];
              bsGameManager::getInstance()->player_->interior_b_ = (uint8_t)color[2];
              bsGameManager::getInstance()->player_->interior_a_ = (uint8_t)color[3];
            }
            else if ((*(bsGameManager::getInstance()->all_elements_tag_ + i))->tag_ == 2)
            {
              float color[4] = {(float)bsGameManager::getInstance()->cubes[i - 3]->interior_r_ , (float)bsGameManager::getInstance()->cubes[i - 3]->interior_g_, (float)bsGameManager::getInstance()->cubes[i - 3]->interior_b_, (float)bsGameManager::getInstance()->cubes[i - 3]->interior_a_};
              ImGui::DragFloat4(txt, color);
              bsGameManager::getInstance()->cubes[i - 3]->interior_r_ = (uint8_t)color[0];
              bsGameManager::getInstance()->cubes[i - 3]->interior_g_ = (uint8_t)color[1];
              bsGameManager::getInstance()->cubes[i - 3]->interior_b_ = (uint8_t)color[2];
              bsGameManager::getInstance()->cubes[i - 3]->interior_a_ = (uint8_t)color[3];
            }
          }
        ImGui::Text("\n");
      }
    }

    ImGui::End();

    ImGui::Render();
    //bsRect *s = new bsRect();
    //s->enabled_ = 0;

}

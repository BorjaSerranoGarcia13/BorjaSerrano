
#include "../include/bs_game.h"

BsGame::BsGame() {
  score_ = 0;
  total_blocks_ = 64;
}

BsGame::~BsGame() {
  delete[] block_;
  block_ = nullptr;

  delete player_;
  player_ = nullptr;

  delete ball_;
  ball_ = nullptr;
}

void BsGame::init() {
  window_.init(kWidthScreen, kHeightScreen, "BREAKOUT");
  window_.setMouseVisibility(true);

  window_.setFramerateLimit(60);
  std::srand((unsigned int)std::time(0));

  BsGameManager::getInstance().imgui_.init(window_.window_);

  initDatabase();
  initScenes();
  initCharacters();
  if (BsGameManager::getInstance().database_.exists_) {
    loadDatabase();
  } else {
    updateDatabase();
  }
}

void BsGame::initScenes() {
  BsGameManager::getInstance().scene_start_.init();
  BsGameManager::getInstance().scene_game_over_.init();
  BsGameManager::getInstance().scene_login_sign_.init();
  BsGameManager::getInstance().scene_board_.init();
}

void BsGame::initCharacters() {
  player_ = new BsPlayer();
  player_->init();

  ball_ = new BsBall();
  ball_->init();

  block_ = new BsEnemy[total_blocks_]();
  uint8_t rgba_border[] = {0, 0, 0, 255};
  uint8_t rgba_fill[] = {247, 0, 255, 255};
  sf::Vector2f pos = {100.0f, 3.0f};

  for (int i = 0; i < total_blocks_; ++i) {
    if (i == 8) {
      pos.x = 100.0f;
      pos.y += 53.0f;
      rgba_fill[0] = 255;
      rgba_fill[1] = 12;
      rgba_fill[2] = 0;
    } else if (i == 16) {
      pos.x = 100.0f;
      pos.y += 53.0f;
      rgba_fill[0] = 255;
      rgba_fill[1] = 143;
      rgba_fill[2] = 0;
    } else if (i == 24) {
      pos.x = 100.0f;
      pos.y += 53.0f;
      rgba_fill[0] = 243;
      rgba_fill[1] = 255;
      rgba_fill[2] = 0;
    } else if (i == 32) {
      pos.x = 100.0f;
      pos.y += 53.0f;
      rgba_fill[0] = 37;
      rgba_fill[1] = 191;
      rgba_fill[2] = 19;
    } else if (i == 40) {
      pos.x = 100.0f;
      pos.y += 53.0f;
      rgba_fill[0] = 19;
      rgba_fill[1] = 74;
      rgba_fill[2] = 191;
    } else if (i == 48) {
      pos.x = 100.0f;
      pos.y += 53.0f;
      rgba_fill[0] = 115;
      rgba_fill[1] = 19;
      rgba_fill[2] = 191;
    } else if (i == 56) {
      pos.x = 100.0f;
      pos.y += 53.0f;
      rgba_fill[0] = 13;
      rgba_fill[1] = 208;
      rgba_fill[2] = 228;
    }

    block_[i].BsCharacter::init(pos, sf::Vector2f(100.0f, 50.0f), 0.0f, sf::Vector2f(1.0f, 1.0f), rgba_border[0], rgba_border[1], rgba_border[2], rgba_border[3], rgba_fill[0], rgba_fill[1], rgba_fill[2], rgba_fill[3], 0);

    pos.x += 103.0f;
  }
}

void BsGame::initDatabase() {
  if (!BsGameManager::getInstance().database_.exists_) {
    BsGameManager::getInstance().database_.create();
  } else {
    BsGameManager::getInstance().database_.retrievingData("SELECT TotalBlocks FROM Scene_Info");
    total_blocks_ = (uint8_t)BsDataBase::s_result_;
    if (total_blocks_ < 1) total_blocks_ = 1;
    if (total_blocks_ > 64) total_blocks_ = 64;
  }
}

void BsGame::loadDatabase(){
  // Scene_Info
  BsGameManager::getInstance().database_.retrievingData("SELECT Login FROM Scene_Info");
  BsGameManager::getInstance().scene_login_sign_.enabled_ = (uint8_t)BsDataBase::s_result_;
  if (BsGameManager::getInstance().scene_login_sign_.enabled_ >= 1) {
    BsGameManager::getInstance().scene_login_sign_.enabled_ = 1;
  } else {
    BsGameManager::getInstance().database_.retrievingData("SELECT Start FROM Scene_Info");
    BsGameManager::getInstance().scene_start_.enabled_ = (uint8_t)BsDataBase::s_result_;
    if (BsGameManager::getInstance().scene_start_.enabled_ >= 1) {
      BsGameManager::getInstance().scene_start_.enabled_ = 1;
    } else {
      BsGameManager::getInstance().database_.retrievingData("SELECT Board FROM Scene_Info");
      BsGameManager::getInstance().scene_board_.enabled_ = (uint8_t)BsDataBase::s_result_;
      if (BsGameManager::getInstance().scene_board_.enabled_ >= 1) {
        BsGameManager::getInstance().scene_board_.enabled_ = 1;
      } else {
        BsGameManager::getInstance().database_.retrievingData("SELECT GameOver FROM Scene_Info");
        BsGameManager::getInstance().scene_game_over_.enabled_ = (uint8_t)BsDataBase::s_result_;
        if (BsGameManager::getInstance().scene_game_over_.enabled_ >= 1) {BsGameManager::getInstance().scene_game_over_.enabled_ = 1;}
      }
    }
  }

  // Ball_Info
  BsGameManager::getInstance().database_.retrievingData("SELECT Velocity FROM Ball_Info");
  ball_->set_velocity(BsDataBase::s_result_);
  if (BsDataBase::s_result_ < 1.0f) { ball_->set_velocity(1.0f); }
  else if (BsDataBase::s_result_ > 3.0f) { ball_->set_velocity(3.0f); }

  sf::Vector2f aux;
  BsGameManager::getInstance().database_.retrievingData("SELECT PosX FROM Ball_Info");
  aux.x = BsDataBase::s_result_;
  BsGameManager::getInstance().database_.retrievingData("SELECT PosY FROM Ball_Info");
  aux.y = BsDataBase::s_result_;
  ball_->set_position(aux);

  BsGameManager::getInstance().database_.retrievingData("SELECT DirectionX FROM Ball_Info");
  aux.x = BsDataBase::s_result_;
  BsGameManager::getInstance().database_.retrievingData("SELECT DirectionY FROM Ball_Info");
  aux.y = BsDataBase::s_result_;
  if (abs(aux.x) > 4.0f) { aux.x = 4.0f; }
  if (abs(aux.x) + abs(aux.y) > 7) aux.y = abs(aux.x) - 7;
  ball_->set_direction(aux);

  BsGameManager::getInstance().database_.retrievingData("SELECT Health FROM Ball_Info");
  ball_->set_health_points((uint8_t)BsDataBase::s_result_);

  // Player info
  BsGameManager::getInstance().database_.retrievingData("SELECT PosX FROM Player_Info");
  aux.x = BsDataBase::s_result_;
  BsGameManager::getInstance().database_.retrievingData("SELECT PosY FROM Player_Info");
  aux.y = BsDataBase::s_result_;
  if (aux.y < 700.0f) {aux.y = 700.0f;}
  if (aux.y > 780.0f) {aux.y = 780.0f;}
  player_->set_position(aux);
  BsGameManager::getInstance().database_.retrievingData("SELECT Health FROM Player_Info");
  player_->set_health_points((uint8_t)BsDataBase::s_result_);

  BsGameManager::getInstance().database_.retrievingData("SELECT ScaleX FROM Player_Info");
  aux.x = BsDataBase::s_result_;
  if (aux.x > 8) aux.x = 8.0f;
  aux.y = player_->scale().y;
  player_->set_scale(aux);
  player_->set_new_size();

  // BRICKS
  /*
  BsGameManager::getInstance().database_.retrievingData("SELECT TotalBlocks FROM Scene_Info");
  int var = (int)BsDataBase::s_result_;
  for (int i = 0; i < var; ++i) {
      BsGameManager::getInstance().database_.retrievingData("SELECT Health FROM Breaks_Info");
      block_[i].set_health_points((uint8_t)BsDataBase::s_result_);
      if (block_[i].health_points() < 1) {block_[i].enabled_ = 0;}
  }
  */
}

void BsGame::input() {
  BsGameManager::getInstance().input_.input(window_.window_);

}

void BsGame::clearInput() {
  BsGameManager::getInstance().input_.clearInput();
}

void BsGame::update() {
  updateScenes();
  if (BsGameManager::getInstance().input_.keyboard_key() == BsGameManager::getInstance().input_.kKeyboardKey_S) {
    updateDatabase();
  }
}

void BsGame::restart() {
  ball_->init();
  ball_->set_health_points(3);
  ball_->set_enabled(1);

  player_->init();

  for (int i = 0; i < total_blocks_; ++i) {
    block_[i].set_enabled(1);
    block_[i].set_health_points(1);
  }

  score_ = 0;
  BsGameManager::getInstance().scene_board_.label_[1].set_text(std::to_string(score_));

  BsGameManager::getInstance().scene_board_.label_[3].set_text(std::to_string(ball_->health_points()));
}

void BsGame::updateDatabase() {
  char buffer[200];

  std::string a = std::to_string(BsGameManager::getInstance().scene_login_sign_.enabled_);
  std::string b = std::to_string(BsGameManager::getInstance().scene_start_.enabled_);
  std::string c = std::to_string(BsGameManager::getInstance().scene_board_.enabled_);
  std::string d = std::to_string(BsGameManager::getInstance().scene_game_over_.enabled_);
  std::string e = std::to_string(total_blocks_);

  std::string database_update = "REPLACE INTO Scene_Info (Id, Login, Start, Board, GameOver, TotalBlocks) VALUES (1,'" + a + "','" + b + "','" + c + "','" + d + "','" + e + "');";

  strcpy_s(buffer, sizeof buffer, database_update.c_str());
  BsGameManager::getInstance().database_.insertData(buffer);

  buffer[0] = '\0';
  a = std::to_string(ball_->velocity());
  b = std::to_string(ball_->position().x);
  c = std::to_string(ball_->position().y);
  d = std::to_string(ball_->direction().x);
  e = std::to_string(ball_->direction().y);
  std::string f = std::to_string(ball_->health_points());

  database_update = "REPLACE INTO Ball_Info (Id, Velocity, PosX, PosY, DirectionX, DirectionY, Health) VALUES (1,'" + a + "','" + b + "','" + c + "','" + d + "','" + e + "','" + f + "');";
  strcpy_s(buffer, sizeof buffer, database_update.c_str());
  BsGameManager::getInstance().database_.insertData(buffer);

  buffer[0] = '\0';
  a = std::to_string(player_->position().x);
  b = std::to_string(player_->position().y);
  c = std::to_string(player_->health_points());
  d = std::to_string(player_->scale().x);

  database_update = "REPLACE INTO Player_Info (Id, PosX, PosY, Health, ScaleX) VALUES (1,'" + a + "','" + b + "','" + c + "','" + d + "');";
  strcpy_s(buffer, sizeof buffer, database_update.c_str());
  BsGameManager::getInstance().database_.insertData(buffer);


  for (int i = 0; i < total_blocks_; ++i) {
    buffer[0] = '\0';
    a = std::to_string(i);
    b = std::to_string(block_[i].position().x);
    c = std::to_string(block_[i].position().y);
    d = std::to_string(block_[i].health_points());

    database_update = "REPLACE INTO Breaks_Info (Id, PosX, PosY, Health) VALUES ('" + a + "','" + b + "','" + c + "','" + d +"');";

    strcpy_s(buffer, sizeof buffer, database_update.c_str());
    BsGameManager::getInstance().database_.insertData(buffer);
  }
}

void BsGame::updateScenes() {
  if (BsGameManager::getInstance().scene_login_sign_.enabled_) {
    if (BsGameManager::getInstance().input_.enabled_keyboard_ && BsGameManager::getInstance().input_.keyboard_key() == BsGameManager::getInstance().input_.kKeyboardKey_Space) {
      BsGameManager::getInstance().scene_start_.enabled_ = true;
      BsGameManager::getInstance().scene_login_sign_.enabled_ = false;

    }
  } else if (BsGameManager::getInstance().scene_start_.enabled_) {
    if (BsGameManager::getInstance().input_.enabled_keyboard_ && BsGameManager::getInstance().input_.keyboard_key() == BsGameManager::getInstance().input_.kKeyboardKey_Space) {
      BsGameManager::getInstance().scene_start_.enabled_ = false;
      BsGameManager::getInstance().scene_board_.enabled_ = true;

    }
  } else if (BsGameManager::getInstance().scene_board_.enabled_) {
    updateCharacters();
    if (ball_->health_points() <= 0) {
      BsGameManager::getInstance().scene_board_.enabled_ = false;
      BsGameManager::getInstance().scene_game_over_.enabled_ = true;
      if (ball_->enabled_ == 0) {
      }
    }
  } else if (BsGameManager::getInstance().scene_game_over_.enabled_) {
    if (BsGameManager::getInstance().input_.enabled_keyboard_ && BsGameManager::getInstance().input_.keyboard_key() == BsGameManager::getInstance().input_.kKeyboardKey_Space) {
      BsGameManager::getInstance().scene_game_over_.enabled_ = false;
      BsGameManager::getInstance().scene_board_.enabled_ = true;
      restart();
    }
  }

}

void BsGame::add_velocity(sf::Time time_out) {
  elapsed_time_ += clock_.getElapsedTime();
  clock_.restart();

  if (elapsed_time_ >= time_out) {
    elapsed_time_ = sf::Time::Zero;
    ball_->set_velocity(ball_->velocity() + 0.1f);
  }
}

void BsGame::updateCharacters() {
  player_->update();
  ball_->update();

  add_velocity(sf::seconds(15.0f));

  if (ball_->position().y < ball_->kSpaceCollisionBlock) {
    for (int i = 0; i < total_blocks_; ++i) {
      block_[i].update();
      if (block_[i].enabled_) {
        if (ball_->collision(block_[i].position(), block_[i].size())) {
          block_[i].set_health_points(block_[i].health_points() - 1);
          score_ += kScoreBlock;
          BsGameManager::getInstance().scene_board_.label_[1].set_text(std::to_string(score_));
        }
      }
    }
  } else if (ball_->position().y > ball_->kSpaceCollisionPlayer) {
    sf::Vector2f player_pos = {player_->position().x - player_->new_size().x, player_->position().y};
    sf::Vector2f player_size = {player_->size().x * player_->scale().x, player_->size().y * player_->scale().y};
    if (ball_->collision(player_pos, player_size)) {
      ball_->enabled_collision_ = false;
      float center = (ball_->position().x + ball_->size().x * 0.5f) - (player_->position().x);

      if (center >= player_->collision_points_[8] && center <= player_->collision_points_[10]) {
        ball_->set_direction(sf::Vector2f(4.0f, -3.0f));
      } else if (center < player_->collision_points_[8] && center >= player_->collision_points_[7]) {
        ball_->set_direction(sf::Vector2f(3.5f, -3.5f));

      } else if (center < player_->collision_points_[7] && center >= player_->collision_points_[6]) {
        ball_->set_direction(sf::Vector2f(3.0f, -4.0f));
      } else if (center < player_->collision_points_[6] && center >= player_->collision_points_[5]) {
        ball_->set_direction(sf::Vector2f(2.0f, -5.0f));
      } else if (center < player_->collision_points_[5] && center >= 0.0f) {
        ball_->set_direction(sf::Vector2f(1.0f, -6.0f));
      } else if (center >= player_->collision_points_[4] && center < 0.0f) {
        ball_->set_direction(sf::Vector2f(-1.0f, -6.0f));
      } else if (center < player_->collision_points_[4] && center >= player_->collision_points_[3]) {
        ball_->set_direction(sf::Vector2f(-2.0f, -5.0f));
      } else if (center < player_->collision_points_[3] && center >= player_->collision_points_[2]) {
        ball_->set_direction(sf::Vector2f(-3.0f, -4.0f));
      } else if (center < player_->collision_points_[2] && center >= player_->collision_points_[1]) {
        ball_->set_direction(sf::Vector2f(-3.5f, -3.5f));
      } else if (center < player_->collision_points_[1] && center >= player_->collision_points_[0]) {
        ball_->set_direction(sf::Vector2f(-4.0f, -3.f));
      }
    } else {
      ball_->enabled_collision_ = true;
    }
  }

  if (ball_->life_lost_) {
    ball_->init();
    player_->init(player_->scale());
  }
  BsGameManager::getInstance().scene_board_.label_[3].set_text(std::to_string(ball_->health_points()));
}

void BsGame::draw() {
  drawScenes();
}

void BsGame::drawScenes() {
  if (BsGameManager::getInstance().scene_login_sign_.enabled_) {
      BsGameManager::getInstance().scene_login_sign_.draw(window_.window_);
  }
  if (BsGameManager::getInstance().scene_start_.enabled_) {
    BsGameManager::getInstance().scene_start_.draw(window_.window_);
  }
  if (BsGameManager::getInstance().scene_game_over_.enabled_) {
    BsGameManager::getInstance().scene_game_over_.draw(window_.window_);
  }
  if (BsGameManager::getInstance().scene_board_.enabled_) {
      BsGameManager::getInstance().scene_board_.draw(window_.window_);
      drawCharacters();
  }
}

void BsGame::drawCharacters() {
  player_->draw(window_.window_);
  for (int i = 0; i < total_blocks_; ++i) {
    block_[i].draw(window_.window_);
  }
  ball_->draw(window_.window_);
}

void BsGame::exit() {
  finish();

}

// Free memory
void BsGame::finish() {

}

void BsGame::imgui() {
  BsGameManager::getInstance().imgui_.update(window_.window_, delta_clock_);
}

void BsGame::mainLoop() {
  while (window_.isOpened()) {
    sf::Event event;
    while (window_.window_.pollEvent(event))
    {
        if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
          window_.destroy();
    }

    window_.clear();

    // ------ Funciones del game loop ------
    input();
    update();
    draw();
    clearInput();

    //imgui();

    window_.frame();
  }

  window_.destroy();
}

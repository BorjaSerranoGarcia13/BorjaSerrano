
#include "../include/bs_imgui.h"

BsImgui::BsImgui() {
  enabled_ = 1;
  scene_manager_ = 0;
}

BsImgui::~BsImgui() {

}

void BsImgui::init(sf::RenderWindow& window) {
  ImGui::SFML::Init(window);
}

void BsImgui::scene_enabled(uint8_t scene_manager) {
  /*switch(scene_manager) {
    case 0: BsGameManager::getInstance().scene_login_sign_.enabled_ = true;
            BsGameManager::getInstance().scene_start_.enabled_ = false;
            BsGameManager::getInstance().scene_board_.enabled_ = false;
            BsGameManager::getInstance().scene_game_over_.enabled_ = false;
            break;
    case 1: BsGameManager::getInstance().scene_login_sign_.enabled_ = false;
            BsGameManager::getInstance().scene_start_.enabled_ = true;
            BsGameManager::getInstance().scene_board_.enabled_ = false;
            BsGameManager::getInstance().scene_game_over_.enabled_ = false;
            break;
    case 2: BsGameManager::getInstance().scene_login_sign_.enabled_ = false;
            BsGameManager::getInstance().scene_start_.enabled_ = false;
            BsGameManager::getInstance().scene_board_.enabled_ = true;
            BsGameManager::getInstance().scene_game_over_.enabled_ = false;
            break;
    case 3: BsGameManager::getInstance().scene_login_sign_.enabled_ = false;
            BsGameManager::getInstance().scene_start_.enabled_ = false;
            BsGameManager::getInstance().scene_board_.enabled_ = false;
            BsGameManager::getInstance().scene_game_over_.enabled_ = true;
            break;
  }*/
  scene_manager = 1;
}

void BsImgui::scene_manager() {
  ImGui::Text("Scene Manager");
  if (ImGui::Button("Login Sign")) {
    scene_enabled(kTypeScene_LoginSign);
    std::cout << "sdsd0" << std::endl;
  }
  if (ImGui::Button("Start")) {
    scene_enabled(kTypeScene_Start);

  }
  if (ImGui::Button("Board")) {
    scene_enabled(kTypeScene_Board);

  }
  if (ImGui::Button("Game Over")) {
    scene_enabled(kTypeScene_GameOver);
  }
}

void BsImgui::update(sf::RenderWindow& window, sf::Clock clock) {
  if (enabled_ == 1) {
    ImGui::SFML::Update(window, clock.restart());

    ImGui::SetNextWindowPos( ImVec2(0,0) );
    ImGui::SetNextWindowSize(ImVec2(100, 400));
    ImGui::Begin("Hello, world!");

    scene_manager();

    ImGui::End();
    ImGui::SFML::Render(window);
  } else {

  }

}

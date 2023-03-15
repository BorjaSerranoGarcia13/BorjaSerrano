
#include "bs_game.h"

BsGame::BsGame() {
    scene_manager_ = 0;
}

BsGame::~BsGame() {
  
}

void BsGame::init() {
  GM_.window_.init(kWidthScreen, kHeightScreen, "DataBase");
  GM_.window_.setMouseVisibility(true);

  GM_.window_.setFramerateLimit(60);
  std::srand((unsigned int)std::time(0));

  GM_.imgui_.init(GM_.window_.window_);

  initDatabase();
  initScenes();

}

void BsGame::initDatabase() {
  if (!GM_.database_.exists_) {
    GM_.database_.create();
  } else {
      GM_.database_.extractAllData();
  }
}

void BsGame::loadDatabase(){
}

void BsGame::input() {
  GM_.input_.input(GM_.window_.window_);
}

void BsGame::clearInput() {
  GM_.input_.clearInput();
}

void BsGame::update() {
    sceneManager();
    updateScenes();
}

void BsGame::restart() {

}

void BsGame::draw() {
    drawScenes();
}



void BsGame::updateDatabase() {
  
}

void BsGame::sceneManager()
{
    if (GM_.input_.keyboard_key() == kKeyboardKey_F1 && GM_.input_.enabled_keyboard_) {
        scene_manager_--;
        if (scene_manager_ >= kTotalScenes) { scene_manager_ = kTotalScenes - 1; }
    }
    if (GM_.input_.keyboard_key() == kKeyboardKey_F2 && GM_.input_.enabled_keyboard_) {
        scene_manager_++;
        if (scene_manager_ >= kTotalScenes) { scene_manager_ = 0; }
    }
}

void BsGame::initScenes() {
    scene_vector_.init();
    scene_matrix_.init();
}

void BsGame::updateScenes() {
    switch (scene_manager_) {
    case 0: scene_vector_.update();
        break;
    case 1: scene_matrix_.update();
        break;
    case 2: imgui();
        break;
    case 3:
        break;

    default: 
        break;
    }

}

void BsGame::drawScenes() {
    switch (scene_manager_) {
    case 0: scene_vector_.draw(GM_.window_.window_);
        break;
    case 1: scene_matrix_.draw(GM_.window_.window_);
        break;
    case 2: imgui();
        break;
    case 3:
        break;

    default:
        break;
    }  
}

void BsGame::exit() {
  finish();
}

// Free memory
void BsGame::finish() {

}

void BsGame::imgui() {
    GM_.imgui_.update(GM_.window_.window_, delta_clock_, GM_.database_);
    GM_.imgui_.end(GM_.window_.window_);
}

void BsGame::mainLoop() {
  GM_.imgui_.init(GM_.window_.window_);
  while (GM_.window_.isOpened()) {
    sf::Event event;
    while (GM_.window_.window_.pollEvent(event))
    {
        GM_.imgui_.event(event);
        if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
          GM_.window_.destroy();
    }

    GM_.window_.clear();

    // ------ Funciones del game loop ------
    input();
    update();
    draw();
    clearInput();

    

    GM_.window_.frame();
  }

  GM_.window_.destroy();
}

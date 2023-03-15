
#include "../include/bs_game.h"

BsGame::BsGame() {
    fps_input_ = -1.0f;
    fps_AI_ = 10.0f;
    fps_world_ = 14.0f;
    fps_draw_ = 0.0f;

    fps_input = sf::seconds(1.f / fps_input_);
    fps_AI = sf::seconds(1.f / fps_AI_);
    fps_world = sf::seconds(1.f / fps_world_);
    fps_draw = sf::seconds(1.f / fps_draw_);

    scene_manager_ = kTypeMap_Normal;
    random_mov_ = false;
    aStar_mov_ = true;

    float total_lines = (float)kTotalCol + (float)kTotalRow;
    lines_shape_ = new sf::RectangleShape[total_lines];
    for (int i = 0; i < kTotalRow; ++i) {
        lines_shape_[i].setPosition((i + 1) * kWidthGrid, 0);
        lines_shape_[i].setSize(sf::Vector2f(1.0f, 705));
        lines_shape_[i].setFillColor(sf::Color(0, 200, 0, 100));
    }
    for (int i = kTotalRow ; i < total_lines; ++i) {
        lines_shape_[i].setPosition(0, ((i + 1) - kTotalRow) * kHeightGrid);
        lines_shape_[i].setSize(sf::Vector2f(960, 1.0f));
        lines_shape_[i].setFillColor(sf::Color(0, 200, 0, 100));
    }
    
}

BsGame::~BsGame() {
    delete[] agent_;
    delete[] map_sprite_;
    delete[] lines_shape_;
}

void BsGame::init() {
  window_.init(kWindowWidth, kWindowHeight, "");
  window_.setMouseVisibility(true);

  window_.setFramerateLimit(kFrameRate);
  std::srand((unsigned int)std::time(0));

  initMaps();
  initCharacters();
}

void BsGame::initMaps() {
    scene_manager_ = kTypeMap_Normal;

    map_sprite_ = new BsTexture[kTotalSpriteMaps];
    (map_sprite_ + 0)->init("../../../data/gfx/maps/map_03_960x704_layout ABGS.png");
    (map_sprite_ + 1)->init("../../../data/gfx/maps/map_03_960x704_cost.png");

    BoardFromImage(GM_.board_, "../../../data/gfx/maps/map_03_120x88_cost.png");
}

void BsGame::initCharacters() {
    agent_ = new Agent[kTotalAgents];

    (agent_ + 0)->init(kAgentType_Player, 106, 34);
    mastermind_.addAgent((agent_ + 0));
    (agent_ + 1)->init(kAgentType_Medic, 40, 40);
    mastermind_.addAgent((agent_ + 1));
    (agent_ + 2)->init(kAgentType_Soldier, 80, 30);
    mastermind_.addAgent((agent_ + 2));
    (agent_ + 3)->init(kAgentType_Engineer, 60, 50);
    mastermind_.addAgent((agent_ + 3));
}

void BsGame::input() {
  GM_.input_.input(window_.window_);

}

void BsGame::clearInput() {
  GM_.input_.clearInput();
}

void BsGame::updateMaps() {
  

}

void BsGame::math_movementPlayer()
{
    if (GM_.input_.mouse_button() == GM_.input_.kMouseButton_right) {
        int goal_x = (int)GM_.input_.mouse_position().x / (int)kWidthGrid;
        int goal_y = (int)GM_.input_.mouse_position().y / (int)kHeightGrid;
        agent_[0].calculateAStarMovement(goal_x, goal_y, -1);
        //agent_[0].destiny_pos_.setPosition(GM_.input_.mouse_position().x, GM_.input_.mouse_position().y);
        agent_[0].destiny_pos_.setPosition((float)goal_x * (float)kWidthGrid, (float)goal_y * (float)kHeightGrid);

    
    }
    agent_[0].aStartMovement();
    

}

void BsGame::updateAgents() {
    for (int i = 0; i < kTotalAgents; ++i) {
        agent_[i].update();
    }    
}

void BsGame::updateMastermind()
{
    mastermind_.update();
}

void BsGame::drawMaps() {
  switch(scene_manager_) {
    case 0: map_sprite_[0].draw(window_.window_);
         break;
    case 1: map_sprite_[1].draw(window_.window_);
        float total_lines = kTotalCol + kTotalRow;

        for (int i = 0; i < total_lines; ++i) {
            window_.window_.draw(lines_shape_[i]);
        }
        break;
  }
}

void BsGame::drawAgents() {
    for (int i = 0; i < kTotalAgents; ++i) {
        agent_[i].draw(window_.window_);
        if (scene_manager_ == kTypeMap_Collision || agent_[i].agent_type_ == kAgentType_Player) {
            window_.window_.draw(agent_[i].goal_shape_);
            window_.window_.draw(agent_[i].destiny_pos_);
        }
    }
}

void BsGame::imgui()
{
    ImGui::Begin("IMGUI");
    
    for (int i = 0; i < kTotalAgents; ++i) {
        agentState(&agent_[i]);
    }   

    if (ImGui::Button("Coll Map")) {
        switch (scene_manager_) {
        case kTypeMap_Normal: scene_manager_ = kTypeMap_Collision;
            break;
        case kTypeMap_Collision: scene_manager_ = kTypeMap_Normal;
            break;
        }
    }

}

void BsGame::agentState(Agent* agent)
{
    if (agent->agent_type_ != kAgentType_Player) {
        switch (agent->agent_type_) {
        case kAgentType_Medic: ImGui::Text("M state:");
            break;
        case kAgentType_Soldier: ImGui::Text("S state:");
            break;
        case kAgentType_Engineer: ImGui::Text("I state:");
            break;
        }
        switch (agent->state_) {
            case AgentState_Normal: ImGui::SameLine();
                ImGui::Text(" Walking normal");
                break;
            case AgentState_PlayerSeen: ImGui::SameLine();
                ImGui::Text(" Player seen");
                break;
            case AgentState_PlayerEscaped: ImGui::SameLine();
                ImGui::Text(" Player Escaped");
                break;
        }
        ImGui::Text("  ");
    }
}

void BsGame::exit() {
  finish();

}

// Free memory
void BsGame::finish() {

}

void BsGame::mainLoop() {

    sf::Clock clock;
    
    sf::Time timeSinceLastUpdate_Input = sf::Time::Zero;
    sf::Time timeSinceLastUpdate_AI = sf::Time::Zero;
    sf::Time timeSinceLastUpdate_World = sf::Time::Zero;
    sf::Time timeSinceLastUpdate_Draw = sf::Time::Zero;
    
   

    GM_.imgui_.init(window_.window_);

  while (window_.isOpened()) {

    sf::Event event;
    while (window_.window_.pollEvent(event))
    {
        GM_.imgui_.event(event);
        if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
          window_.destroy();
    }

    window_.clear();

    // ------ Funciones del game loop ------
    simtime_ += clock.getElapsedTime();
    


    if (timeSinceLastUpdate_Draw > fps_draw) {
        
        // INPUT
        if (timeSinceLastUpdate_Input > fps_input) {
            input();
            
            t_input_ = timeSinceLastUpdate_Input;
            timeSinceLastUpdate_Input = sf::Time::Zero;
            //std::cout << "Input" << std::endl;
        }
        // AI
        if (timeSinceLastUpdate_AI > fps_AI) {
            updateAgents();
            updateMastermind();
            
            t_AI_ = timeSinceLastUpdate_AI;
            timeSinceLastUpdate_AI = sf::Time::Zero;
        }
        // WORLD
        if (timeSinceLastUpdate_World > fps_world) {
            
            math_movementPlayer();
            t_world_ = timeSinceLastUpdate_World;
            timeSinceLastUpdate_World = sf::Time::Zero;
        }
        // DRAW
        drawMaps();
        drawAgents();
        
        timeSinceLastUpdate_Draw = sf::Time::Zero;
    }

    timeSinceLastUpdate_Input += clock.getElapsedTime();
    timeSinceLastUpdate_AI += clock.getElapsedTime();
    timeSinceLastUpdate_World += clock.getElapsedTime();
    timeSinceLastUpdate_Draw += clock.getElapsedTime();
    uptime_ += clock.getElapsedTime();
    fps_ = clock.getElapsedTime();
    
    clock.restart();

    clearInput();
    
    GM_.imgui_.update(window_.window_, delta_clock_);
    imgui();
    GM_.imgui_.end(window_.window_);

    window_.frame();
    
  }
  window_.destroy();
}


#ifndef __BS_GAME_H__
#define __BS_GAME_H__ 1

#include "bs_window.h"
#include "bs_texture.h"
#include "bs_game_manager.h"

#include "loader.h"
#include "board.h"
#include "bs_mastermind.h"


const int kFrameRate = 60;
const int kWindowWidth = 1150;
const int kWindowHeight = 705;

/**
/* Class game
/* manage the main of the program
*/
class BsGame {
 public:

  const uint8_t kTotalSpriteMaps = 3;
  const uint8_t kTotalAgents = 4;

  enum TypeMap {
      kTypeMap_Normal = 0,
      kTypeMap_Collision = 1,
  };

  BsGame(); /**<  Constructor used to initilizate the class  */
  ~BsGame(); /**<  Destructor used to initilizate the class  */

  BsGame(const BsGame& copy) = delete;
  BsGame& operator=(const BsGame&) = delete;

   /**
  * @brief default init
  */
  void init();

  /**
  * @brief the loop of the game
  */
   void mainLoop();

   /**
   * @brief do all input
   */
   void input();

   /**
   * @brief do all input
   */
   void clearInput();

   /**
   * @brief close the game
   */
   void exit();

  /**
   * @brief to finish the program
   */
   void finish(); /**<   void to finish the program*/


  /**
   * @brief updates the scene character election
   */
  void initMaps();

  /**
   * @brief updates the scene character election
   */
  void initCharacters();

  /**
  * @brief updates the scene map, just in case
  */
  void updateMaps();
  /**
  * @brief updates the agents
  */
  void updateAgents();
  /**
  * @brief updates the mastermind
  */
  void updateMastermind();

  /**
   * @brief do Draws for maps
   */
  void drawMaps();
  /**
   * @brief do Draws for agents
   */
  void drawAgents();

  /**
   * @brief player movement management
   */
  void math_movementPlayer();
  /**
   * @brief manage imgui in program
   */
  void imgui();
  /**
   * @brief manage the agent state for ImGui
   */
  void agentState(Agent* agent);

 private:

  sf::Clock delta_clock_;
  sf::Time fps_;
  sf::Time t_input_;
  sf::Time t_AI_;
  sf::Time t_world_;
  sf::Time uptime_;
  sf::Time simtime_;

  sf::Time fps_input;
  sf::Time fps_AI;
  sf::Time fps_world;
  sf::Time fps_draw;

  float fps_input_;
  float fps_AI_;
  float fps_world_;
  float fps_draw_;

  BsWindow window_;  /**<   object window created to be managed*/
  BsTexture *map_sprite_ = nullptr;

  Agent* agent_ = nullptr;

  uint8_t scene_manager_;

  BsGameManager& GM_ = BsGameManager::getInstance();

  sf::RectangleShape* lines_shape_;

  BsMastermind mastermind_;

  bool random_mov_;
  bool aStar_mov_;

};

#endif // __BS_GAME_H__

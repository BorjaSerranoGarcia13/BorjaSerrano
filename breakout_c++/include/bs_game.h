
#ifndef __BS_GAME_H__
#define __BS_GAME_H__ 1

#include "bs_window.h"
#include "bs_player.h"
#include "bs_enemy.h"
#include "bs_ball.h"

#include <SFML/System/Clock.hpp>

/**
/* Class game
/* manage the main of the program
*/
class BsGame {
 public:

  const int kWidthScreen = 1000;
  const int kHeightScreen = 800;
  const int kScoreBlock = 100;

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
   * @brief do all input
   */
   void update();

    /**
   * @brief do all input
   */
   void draw();

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
  void initScenes();

  /**
   * @brief updates the scene character election
   */
  void initCharacters();

  void initDatabase();

  void loadDatabase();

  /**
  * @brief updates the scene character election
  */
  void updateScenes();

  void updateCharacters();

  void updateDatabase();

  void restart();

  void add_velocity(sf::Time time_out);

  /**
   * @brief updates the scene character election
   */
  void drawScenes();

  void drawCharacters();

  void imgui();

 private:
  //BsGameManager *gameManager_; /*!< starts the gamemanager */

  BsPlayer *player_ = nullptr;
  BsEnemy *block_ = nullptr;
  BsBall *ball_ = nullptr;

  sf::Clock delta_clock_;

  uint32_t score_;
  uint8_t total_blocks_;

  sf::Clock clock_;
  sf::Time elapsed_time_;
  sf::Time last_time_;

  BsWindow window_;  /**<   object window created to be managed*/
};

#endif // __BS_GAME_H__

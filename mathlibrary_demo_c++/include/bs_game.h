
#ifndef __BS_GAME_H__
#define __BS_GAME_H__ 1

#include "bs_scene_vector.h"
#include "bs_scene_matrix.h"

const int kWidthScreen = 1000;
const int kHeightScreen = 800;
const uint16_t kTotalScenes = 3;



/**
/* Class game
/* manage the main of the program
*/
class BsGame {
 public:


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
  * 
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

   void restart();

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

  // ----- Database Methods -----

  void initDatabase();

  void loadDatabase();
  
  // ----- Scene Methods -----
  void sceneManager();

  /**
   * @brief updates the scene character election
   */
  void initScenes();

  /**
  * @brief updates the scene character election
  */
  void updateScenes();

  void updateDatabase();

  /**
   * @brief updates the scene character election
   */
  void drawScenes();

  // ----- IMGUI Methods -----
  void imgui();

 private:
  sf::Clock delta_clock_;

  sf::Clock clock_;
  sf::Time elapsed_time_;
  sf::Time last_time_;

  uint16_t scene_manager_;
  
  BsGameManager& GM_ = BsGameManager::getInstance();

  BsSceneVector scene_vector_;
  BsSceneMatrix scene_matrix_;

};

#endif // __BS_GAME_H__

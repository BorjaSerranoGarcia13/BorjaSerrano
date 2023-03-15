

#ifndef __BS_GAMEMANAGER_H__
#define __BS_GAMEMANAGER_H__ 1

#include "bs_input.h"
#include "bs_imgui.h"
#include "bs_scene_game_over.h"
#include "bs_scene_start.h"
#include "bs_scene_board.h"
#include "bs_scene_login_sign.h"
#include "bs_database.h"

/**
/* Class scene
/* manage evrything from the BsGameManager
*/
class BsGameManager {

 public:
  static BsGameManager& getInstance() {
    static BsGameManager s_instance_;
    return s_instance_;
  }

  BsGameManager(BsGameManager const&) = delete;
  void operator=(BsGameManager const&)  = delete;

  BsInput input_;
  BsSceneLoginSign scene_login_sign_;
  BsSceneGameOver scene_game_over_; /**<   object scene created to be managed in the game*/
  BsSceneStart scene_start_; /**<   object scene created to be managed in the game*/
  BsSceneBoard scene_board_; /**<   object scene created to be managed in the game*/
  BsImgui imgui_;

  BsDataBase database_;

  uint8_t scene_manager_ = 0;

 private:
  BsGameManager() {}
};

#endif // __BS_GAMEMANAGER_H__

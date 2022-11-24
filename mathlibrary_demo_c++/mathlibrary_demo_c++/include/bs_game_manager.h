

#ifndef __BS_GAMEMANAGER_H__
#define __BS_GAMEMANAGER_H__ 1

#include "bs_input.h"
#include "bs_imgui.h"
#include "bs_database.h"
#include "bs_window.h"

enum GameMode {
    kGameMode_None = 0,
    kGameMode_CreateShape = 1,
    kGameMode_FinishShape = 2,
    kGameMode_EditShape = 3,
};

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

  BsWindow window_;  /**<   object window created to be managed*/
  BsInput input_;
  BsImgui imgui_;

  BsDataBase database_;

  uint16_t game_mode_ = 0;

 private:
  BsGameManager() {}
  BsGameManager(BsGameManager const&) = delete;
  void operator=(BsGameManager const&) = delete;
};

#endif // __BS_GAMEMANAGER_H__

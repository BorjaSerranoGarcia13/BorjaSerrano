

#ifndef __BS_GAMEMANAGER_H__
#define __BS_GAMEMANAGER_H__ 1

#include "bs_imgui.h"
#include "board.h"
#include "bs_input.h"

/**
/* Class scene
/* manage everything from the BsGameManager
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
  BsImgui imgui_;
  Board* board_ = new Board;

 private:
     BsGameManager() {}
     ~BsGameManager() { delete board_; }
};

#endif // __BS_GAMEMANAGER_H__

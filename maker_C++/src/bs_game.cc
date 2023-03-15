
#include "bs_game.h"

bsGame::bsGame () {}

void bsGame::init(bsDataBase* b_) {
  bsGameManager *s = bsGameManager::getInstance();

  b_->create();
  b_->retrievingData();

  window_.init(1200, 800);
  window_.setMouseVisibility(true);

  scene_.initEditionMode();
  bsGameManager::getInstance()->player_;

  scene_.addBackground();
  scene_.allElements();
  if (b_->all_enabled_[0] != NULL)
  {
    for (int i = 0; i < 903; i++)
    {
      (*(bsGameManager::getInstance()->all_elements_ + i))->enabled_ = b_->all_enabled_[i];
    }
  }

}

void saveSize(bsDataBase* b_)
{
  char id[200] = "INSERT INTO Size(SizeMatrix) VALUES(. );";
  char buffer[10];
  itoa(bsGameManager::getInstance()->size_edition(), buffer, 10);

  for (int i = 0; i < 200; i++) {
    if (id[i] == '.')
    {
      id[i] = buffer[0];
      id[i + 1] = buffer[0 + 1];
    }
  }
  b_->insertData(id);
}

void saveEdition(bsDataBase* b_)
{
  char id[200] = "INSERT INTO EditionMode(Edition) VALUES(. );";
  char buffer[10];
  itoa(bsGameManager::getInstance()->edition(), buffer, 10);
  for (int i = 0; i < 200; i++) {
    if (id[i] == '.')
    {
      id[i] = buffer[0];
    }
  }
  b_->insertData(id);
}

void savePuzzle(bsDataBase *b_)
{
  char id[200] = "INSERT INTO PuzzleMode(Puzzle) VALUES(.);";
  char buffer[10];
  itoa(bsGameManager::getInstance()->puzzle_mode_, buffer, 10);
  for (int i = 0; i < 200; i++) {
    if (id[i] == '.')
    {
      id[i] = buffer[0];
    }
  }
  b_->insertData(id);
}

void saveEntity(bsDataBase *b_)
{
  for (int i = 0; i < 30 * 30 + 3; i++)
  {
    char id[100] = "INSERT OR IGNORE INTO Entity(Id) VALUES(. );";
    if (i >= 10) {
      char id2[100] = "INSERT OR IGNORE INTO Entity(Id) VALUES(.  );";
      strcpy(id, id2);
    }
    if (i >= 100)
    {
      char id2[100] = "INSERT OR IGNORE INTO Entity(Id) VALUES(.   );";
      strcpy(id, id2);
    }
    char buffer[10];
    itoa((*(bsGameManager::getInstance()->all_elements_ + i))->id(), buffer, 10);
    for (int p = 0; p < 100; p++) {
      if (id[p] == '.')
      {
        id[p] = buffer[0];
        if (i >= 10) id[p +1] = buffer[0 +1];
        if (i >= 100) id[p +2] = buffer[0 +2];
      }
    }
    b_->insertData(id);

    char id3[100] = "INSERT OR REPLACE INTO EnabledEntitiy(Enabled) VALUES(. );";

    char buffer2[10];
    itoa((*(bsGameManager::getInstance()->all_elements_ + i))->enabled_, buffer2, 10);
    for (int p = 0; p < 100; p++) {
      if (id3[p] == '.')
      {
        id3[p] = buffer2[0];
      }
    }
    b_->insertData(id3);
  }
}

void bsGame::mainLoop(bsDataBase *b_) {
  unsigned char fps = 60;
  double current_time, last_time;

  //bsGameManager::getInstance()->edition()
  //bsGameManager::getInstance()->set_size_edition(size_edition_);


  while (window_.isOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {
    last_time = esat::Time();
    esat::DrawBegin();
    esat::DrawClear(0, 0, 0);

    scene_.drawBackground();
    scene_.controls();
    scene_.playGame();
    if (bsGameManager::getInstance()->save())
    {
      saveSize(b_);
      savePuzzle(b_);
      saveEntity(b_);
      saveEdition(b_);
      bsGameManager::getInstance()->set_save(false);
    }


    esat::DrawEnd();
    //Control fps
    do {
      current_time = esat::Time();
    } while ((current_time - last_time) <= 1000.0 / fps);
    window_.frame();
  }
}

void bsGame::finish() {
  free(bsGameManager::getInstance()->all_elements_);
  free(bsGameManager::getInstance()->all_elements_tag_);
  esat::WindowDestroy();
}

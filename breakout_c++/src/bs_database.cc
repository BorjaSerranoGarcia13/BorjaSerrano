
#include "../include/bs_database.h"

float BsDataBase::s_result_;

BsDataBase::BsDataBase() {
  std::string path = "../data/database.db";
  std::ifstream fin(path);
  if (fin.is_open()) {
    exists_ = true;
    fin.close();
  } else {
    exists_ = false;
  }

}

BsDataBase::~BsDataBase() {

}


int BsDataBase::create() {

    err_msg_ = 0;

    rc_ = sqlite3_open("../data/database.db", &db_);

    if (rc_ != SQLITE_OK) {

        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db_));
        sqlite3_close(db_);

        return 1;
    }

    sql_ =  "CREATE TABLE IF NOT EXISTS Player_Info(Id INTEGER UNIQUE, PosX REAL UNIQUE, PosY REAL UNIQUE, Health INTEGER, ScaleX REAL UNIQUE);"

    "CREATE TABLE IF NOT EXISTS Scene_Info(Id INTEGER UNIQUE, Login INTEGER UNIQUE, Start INTEGER UNIQUE, Board INTEGER UNIQUE, GameOver INTEGUER UNIQUE, TotalBlocks INTEGUER UNIQUE);"
    
    "CREATE TABLE IF NOT EXISTS Breaks_Info(Id INTEGER UNIQUE, PosX REAL, PosY REAL, Health INTEGER);"

    "CREATE TABLE IF NOT EXISTS Ball_Info(Id INTEGER UNIQUE, Health INTEGER UNIQUE, Velocity REAL, PosX REAL UNIQUE, PosY REAL UNIQUE, DirectionX REAL UNIQUE, DirectionY REAL UNIQUE );"
    ;

    rc_ = sqlite3_exec(db_, sql_, 0, 0, &err_msg_);

    if (rc_ != SQLITE_OK ) {

        fprintf(stderr, "SQL error: %s\n", err_msg_);
        sqlite3_free(err_msg_);

        return 1;
    }
    sqlite3_close(db_);

    return 0;

}

int BsDataBase::callback(void *notused, int argc, char **argv, char **azColName){
   notused  = 0;
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   BsDataBase::s_result_ = (float)atof(azColName[i]);
   printf("\n");
   return 0;
}

float BsDataBase::retrievingData(const char* sql) {

    rc_ = sqlite3_open("../data/database.db", &db_);

    if (rc_ != SQLITE_OK) {

        fprintf(stderr, "Cannot open database: %s\n",
                sqlite3_errmsg(db_));
        sqlite3_close(db_);

        return 1;
    }

    //sql_ = "SELECT TotalBlocks FROM Scene_Info";
    rc_ = sqlite3_exec(db_, sql, callback, 0, &err_msg_);

    if( rc_ != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", err_msg_);
      sqlite3_free(err_msg_);
    } else {
      //fprintf(stdout, "Table created successfully\n");
    }
    sqlite3_close(db_);

    return BsDataBase::s_result_;
}

int BsDataBase::insertData(char* sql) {
    err_msg_ = 0;

    rc_ = sqlite3_open("../data/database.db", &db_);

    if (rc_ != SQLITE_OK) {

        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db_));
        sqlite3_close(db_);

        return 1;
    }

    rc_ = sqlite3_exec(db_, sql, 0, 0, &err_msg_);

    if (rc_ != SQLITE_OK ) {

        fprintf(stderr, "SQL error: %s\n", err_msg_);
        sqlite3_free(err_msg_);

        return 1;
    }
    sqlite3_close(db_);

    return 0;

}

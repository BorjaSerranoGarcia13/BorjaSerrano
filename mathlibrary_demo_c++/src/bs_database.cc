
#include "bs_database.h"

std::string BsDataBase::s_result_[kTotalLogin];
uint16_t BsDataBase::s_total_col_;

BsDataBase::BsDataBase() {
  path = "../../../data/database.db";
  std::ifstream fin(path);
  if (fin.is_open()) {
    exists_ = true;
    fin.close();
  } else {
    exists_ = false;
  }
  s_total_col_ = 0;
}

BsDataBase::~BsDataBase() {

}


int BsDataBase::create() {

    err_msg_ = 0;

    rc_ = sqlite3_open(path.c_str(), &db_);

    if (rc_ != SQLITE_OK) {

        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db_));
        sqlite3_close(db_);

        return 1;
    }

    sql_ =   "CREATE TABLE IF NOT EXISTS Login(Username TEXT, Password TEXT);"
            "CREATE TABLE IF NOT EXISTS TestInt(int1 INTEGUER, int2 INTEGUER);"
            "CREATE TABLE IF NOT EXISTS TestFloat(float1 REAL, float2 REAL);"
            "CREATE TABLE IF NOT EXISTS TestBool(bool1 INTEGUER, bool2 INTEGUER);";

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
   uint16_t i;
   for(i = 0; i<argc; i++) {
       if (s_total_col_ < kTotalLogin) {
           BsDataBase::s_result_[s_total_col_] = argv[i];
       }
   }
   s_total_col_++;

   return 0;
}

void BsDataBase::retrievingData(const char* sql) {

    rc_ = sqlite3_open(path.c_str(), &db_);

    if (rc_ != SQLITE_OK) {

        fprintf(stderr, "Cannot open database: %s\n",
                sqlite3_errmsg(db_));
        sqlite3_close(db_);
        std::string a = { "error" };
        return;
    }

    //sql_ = "SELECT TotalBlocks FROM Scene_Info";
    s_total_col_ = 0;
    rc_ = sqlite3_exec(db_, sql, callback, 0, &err_msg_);

    if( rc_ != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", err_msg_);
      sqlite3_free(err_msg_);
    } else {
      //fprintf(stdout, "Table created successfully\n");
    }
    sqlite3_close(db_);
}

int BsDataBase::insertData(char* sql) {
    err_msg_ = 0;

    rc_ = sqlite3_open(path.c_str(), &db_);

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

void BsDataBase::extractAllData()
{
    
    // LOGIN
    for (int i = 0; i < kTotalLogin; ++i) {
        retrievingData("SELECT Username FROM Login");
        if (s_result_[i] != "\0") {
            username_login_[i] = s_result_[i];
        }
        retrievingData("SELECT Password FROM Login");
        if (s_result_[i] != "\0") {
            password_login_[i] = s_result_[i];
        }
    }
    clear_string();
    retrievingData("SELECT int1 FROM TestInt");
    int p = 0;
    for (int i = 0; i < kTotalInt; ++i) {
        if (i % 2 == 0) {
            if (s_result_[p] != "\0") {
                test_int[i] = s_result_[p];
                p++;
            }
        }
    }
    retrievingData("SELECT int2 FROM TestInt");
    p = 0;
    for (int i = 1; i < kTotalInt; ++i) {
        if (i % 2 != 0) {
            if (s_result_[p] != "\0") {
                test_int[i] = s_result_[p];
                p++;
            }
        }
    }
    clear_string();

    retrievingData("SELECT float1 FROM TestFloat");
    p = 0;
    for (int i = 0; i < kTotalFloat; ++i) {
        if (i % 2 == 0) {
            if (s_result_[p] != "\0") {
                test_float[i] = s_result_[p];
                p++;
            }
        }
    }
    retrievingData("SELECT float2 FROM TestFloat");
    p = 0;
    for (int i = 1; i < kTotalFloat; ++i) {
        if (i % 2 != 0) {
            if (s_result_[p] != "\0") {
                test_float[i] = s_result_[p];
                p++;
            }
        }
    }
    clear_string();

    retrievingData("SELECT bool1 FROM TestBool");
    p = 0;
    for (int i = 0; i < kTotalBool; ++i) {
        if (i % 2 == 0) {
            if (s_result_[p] != "\0") {
                test_bool[i] = s_result_[p];
                p++;
            }
        }         
    }
    retrievingData("SELECT bool2 FROM TestBool");
    p = 0;
    for (int i = 1; i < kTotalBool; ++i) {
        if (i % 2 != 0) {
            if (s_result_[p] != "\0") {
                test_bool[i] = s_result_[p];
                p++;
            }
        }
    }
    clear_string();
    
    retrievingData("SELECT name FROM sqlite_master WHERE type='table'");
    for (int i = 0; i < kTotalTables; ++i) {
        if (BsDataBase::s_result_[i] != "\0") {
            tables[i] = s_result_[i];
        }
    }clear_string();
    
    retrievingData("SELECT * FROM sqlite_master WHERE type='table'");
    table_login = s_result_[0];
    table_int = s_result_[1];
    table_float = s_result_[2];
    table_bool = s_result_[3];
    
    
}

void BsDataBase::clear_string()
{
    for (int i = 0; i < kTotalLogin; ++i) {
        s_result_[i].clear();
    }
}

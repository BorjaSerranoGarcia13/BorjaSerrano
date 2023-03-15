
/**
 * Author: Borja Serrano <serranoga@esat-alumni.com>
 * Filename: bs_backgorund.cc
 *
 * Implementation: background class
 */

#include "bs_database.h"
#include <stdio.h>

bsDataBase::bsDataBase() {
  all_enabled_[1] = 10;
}

bsDataBase::~bsDataBase() {

}

bsDataBase::bsDataBase(const bsDataBase& o)
{

}

int bsDataBase::create() {
  sqlite3 *db;
    char *err_msg = 0;

    int rc = sqlite3_open("../data/database.db", &db);

    if (rc != SQLITE_OK) {

        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);

        return 1;
    }

    char *sql = "CREATE TABLE IF NOT EXISTS Size(SizeMatrix INT PRIMARY KEY);"
                "INSERT OR IGNORE INTO Size(SizeMatrix) VALUES('0');"
                "CREATE TABLE IF NOT EXISTS Entity(Id INT PRIMARY KEY);"
                "CREATE TABLE IF NOT EXISTS EnabledEntitiy(Enabled INT);"
                "CREATE TABLE IF NOT EXISTS PuzzleMode(Puzzle INT PRIMARY KEY);"
                "CREATE TABLE IF NOT EXISTS EditionMode(Edition INT PRIMARY KEY);"
                ;

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK ) {

        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);

        return 1;
    }
    int last_id = sqlite3_last_insert_rowid(db);
    printf("The last Id of the inserted row is %d\n", last_id);

    sqlite3_close(db);

    return 0;
}

int size2[903];
int size_ = 0;
int index_ = 0;
static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
     size_ = atoi(azColName[i]);
     size2[index_] = atoi(azColName[i]);
     index_++;

   return 0;
}

int bsDataBase::retrievingData() {
  sqlite3 *db;
    char *err_msg = 0;

    int rc = sqlite3_open("../data/database.db", &db);

    if (rc != SQLITE_OK) {

        fprintf(stderr, "Cannot open database: %s\n",
                sqlite3_errmsg(db));
        sqlite3_close(db);

        return 1;
    }
    char *sql = "SELECT * FROM Size";
    rc = sqlite3_exec(db, sql, callback, 0, &err_msg);
    bsGameManager::getInstance()->set_size_edition(size_);

    if (bsGameManager::getInstance()->size_edition() > 30)
    {
      bsGameManager::getInstance()->set_size_edition(30);
    }
    if (bsGameManager::getInstance()->size_edition() < 10)
    {
      bsGameManager::getInstance()->set_size_edition(10);
    }

    char *sql2 = "SELECT * FROM Entity";
    rc = sqlite3_exec(db, sql2, callback, 0, &err_msg);

    char *sql3 = "SELECT * FROM PuzzleMode";
    rc = sqlite3_exec(db, sql3, callback, 0, &err_msg);
    bsGameManager::getInstance()->set_puzzle_mode(size_);

    char *sql4 = "SELECT * FROM EditionMode";
    rc = sqlite3_exec(db, sql4, callback, 0, &err_msg);
    bsGameManager::getInstance()->set_edition(size_);

    index_ = 0;
    char *sql5 = "SELECT * FROM EnabledEntitiy";
    rc = sqlite3_exec(db, sql5, callback, 0, &err_msg);
    for (int i = 0; i < 903; i++)
    {
      all_enabled_[i] = size2[i];
    }



    if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", err_msg);
      sqlite3_free(err_msg);
    } else {
      fprintf(stdout, "Table created successfully\n");
    }
    sqlite3_close(db);
    return 0;
}

int bsDataBase::insertData(char *sql)
{
  sqlite3 *db;
    char *err_msg = 0;

    int rc = sqlite3_open("../data/database.db", &db);

    if (rc != SQLITE_OK) {

        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);

        return 1;
    }

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK ) {

        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);

        return 1;
    }
    int last_id = sqlite3_last_insert_rowid(db);

    sqlite3_close(db);

    return 0;
}


#ifndef __BS_DATABASE_H__
#define __BS_DATABASE_H__ 1

#include "sqlite3.h"

#include <fstream>
#include <string>
#include <iostream>

const uint16_t kTotalLogin = 5;
const uint16_t kTotalInt = 4;
const uint16_t kTotalFloat = 4;
const uint16_t kTotalBool = 4;

const uint16_t kTotalTables = 4;

/**
/* Class database
/* Used to manage de database and charge and upload database
*/
class BsDataBase {

 public:
  /// METHODS

  /**
 * @brief constructor of class
 */
  BsDataBase();

  /**
 * @brief destructor of class
 */
  ~BsDataBase();

  /**
  * @brief creates the database if doesnt exist
  * @return 0 if the work is done
  * @return 1 if there is an error openeing database
  */
  int create();

  /**
  * @brief query to acces the database
  * @param void *data pointer to data
  * @param argc number of columns in the result set
  * @param **argv row's data
  * @param **acColName he column names
  * @return o when job is done
  */
  static int BsDataBase::callback(void *data, int argc, char **argv, char **azColName);

  /**
  * @brief access to the contetnt of databse
  * @return 0 if the work is done
  * @return 1 if there is an error openeing database
  */
  void retrievingData(const char* sql); /**<  Extract the info from the database to the program  */

  /**
  * @brief insert the data
  * @param *sql pointer to char to do the inserts
  * @return 0 if the work is done
  * @return 1 if there is an error openeing database
  */
  int insertData(char* sql);

  void extractAllData();

  void clear_string();

  sqlite3 *db_; /*!< database */
  int rc_; /*!< int to do the functions */
  char *err_msg_; /*!< the error message */
  char *sql_; /*!< text to use */

  static std::string s_result_[kTotalLogin];
  static uint16_t s_total_col_;

  std::string username_login_[kTotalLogin];
  std::string password_login_[kTotalLogin];

  std::string test_int[kTotalInt];
  std::string test_float[kTotalFloat];
  std::string test_bool[kTotalBool];

  std::string tables[kTotalTables];
  std::string table_login;
  std::string table_int;
  std::string table_float;
  std::string table_bool;

  std::string path;
  bool exists_;

 private:

};


#endif // __BS_DATABASE_H__

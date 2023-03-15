
/**
 * Author: Borja Serrano <serranoga@esat-alumni.com>
 * Filename: bs_backgorund.cc
 *
 * Implementation: background class
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <esat_extra/sqlite3.h>

/**
/* Class database 
/* Used to manage de database and charge and upload database
*/
class bsDataBase {

 public:
  /// METHODS
  bsDataBase::bsDataBase();  /**<  Constructor used to initilizate the class  */
  bsDataBase::~bsDataBase(); /**<   Destructor used to initilizate the class */
  bsDataBase::bsDataBase(const bsDataBase& o); /**<   Constructer copy */

  int all_enabled_[903]; /**<  Array of ints to save if objects are enabled before the program starts  */
  int bsDataBase::create(); /**<  Creates the database  */
  int bsDataBase::retrievingData(); /**<  Extract the info from the database to the program  */

  //* Save the info in the database from the program
    /*
    \*param a char argument to insert in database
    \*return The results
*/
  int bsDataBase::insertData(char *sql); 

 private:

};

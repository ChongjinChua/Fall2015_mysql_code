#include <mysql/mysql.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

class Database {
 private:
  MYSQL * connection_pointer = NULL;
  MYSQL_ROW row;
  MYSQL_RES *result;       //result set

  unsigned int num_fields; //number of columns in the result set
  unsigned int i;
  
  const char * server;
  const char * user;
  const char * password;
  const char * database;


 public:
  Database();
  ~Database();
  void Entry_count();
  void Select_from_tables();

};

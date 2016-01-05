#include <iostream>
#include <stdlib.h> //"exit(), EXIT_FAILURE"
#include "mysql.h"

Database::Database() {
  //Print current instance
  cout << endl << "Database::Database()" << endl;

  //Store default database parameters
  server = "";
  user = "";
  password = "";
  database = "";

  //Connect to MySQL database
  cout << "mysql_init" << endl;
  connection_pointer = mysql_init(NULL);

  if(!connection_pointer){
    cout << "MySQL Initialization failed";
    exit(EXIT_FAILURE);
  }

  connection_pointer = mysql_real_connect(connection_pointer, server, user, password, database, 0, NULL, 0);

  if(!connection_pointer){
    cout << "Error connecting to " << database << " database" << endl;
    cout << mysql_error(connection_pointer) << endl;
    exit(EXIT_FAILURE);
  }
  else{
    cout << "Connection to " << database << " database succeeded!" << endl;
  }
  
}

Database::~Database(){
  //Print current instance
  cout << endl << "Database::~Database()" << endl;

  //Close connection to MySQL database
  cout << "mysql_close" << endl;

  if(connection_pointer){
    mysql_close(connection_pointer);
    cout << "Connection to " << database << " database is closed!" << endl << endl;
  }
}

void Database::Select_from_tables(){
  int query_status = 1;
  int loop_var;
  const char *query_string[] = {"SELECT * FROM User;",
			       "SELECT * FROM Camera;",
			       "SELECT * FROM Timestamp;"};
  int query_count = sizeof(query_string) / sizeof(char *);

  //query_status is zero if query succeeded
  for(loop_var = 0; loop_var < query_count; loop_var++){
    query_status = mysql_query(connection_pointer, query_string[loop_var]);

    if(query_status){ //query failed
      cout << endl << "'SELECT *' query failed" << endl;
      cout << mysql_error(connection_pointer) << endl;
    }

    else{ //query succeeded
      unsigned long *lengths;
      result = mysql_store_result(connection_pointer);
      num_fields = mysql_num_fields(result);

      //print the executed mysql code
      cout << endl << query_string[loop_var];

      while((row = mysql_fetch_row(result))){
	lengths = mysql_fetch_lengths(result);
	cout << endl;
	for(i = 0; i < num_fields; i++){
	  cout.width(lengths[i]);
	  cout << (row[i] ? row[i] : "NULL") << '\t';
	}
      }
    
      cout << endl;
      mysql_free_result(result);
    }
  }
}

void Database::Entry_count(){
  int query_status = 1;
  int loop_var;
  const char *query_string[] = {"SELECT event_index, count FROM Timestamp WHERE DAY(time_stamp) = 13 && HOUR(time_stamp) >= 7 && HOUR(time_stamp) < 8 && MINUTE(time_stamp) = 58;", "SELECT COUNT(count) FROM Timestamp WHERE DAY(time_stamp) = 13 && HOUR(time_stamp) >= 7 && HOUR(time_stamp) < 8 && MINUTE(time_stamp) = 58;"};
  int query_count = sizeof(query_string) / sizeof(char *);

  //query_status is zero if query succeeded
  for(loop_var = 0; loop_var < query_count; loop_var++){
    query_status = mysql_query(connection_pointer, query_string[loop_var]);

    if(query_status){ //query failed
      cout << endl << "'SELECT *' query failed" << endl;
      cout << mysql_error(connection_pointer) << endl;
    }

    else{ //query succeeded
      unsigned long *lengths;
      result = mysql_store_result(connection_pointer);
      num_fields = mysql_num_fields(result);

      //print the executed mysql code
      cout << endl << query_string[loop_var];

      while((row = mysql_fetch_row(result))){
	lengths = mysql_fetch_lengths(result);
	cout << endl;
	for(i = 0; i < num_fields; i++){
	  cout.width(lengths[i]);
	  cout << (row[i] ? row[i] : "NULL") << '\t';
	}
      }
    
      cout << endl;
      mysql_free_result(result);
    }
  }
  
}

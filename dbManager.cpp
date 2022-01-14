#include"dbManager.h"

// PRIVATE METHODS
std::string DbManager::getDate(){

  std::string date;
  time_t tempo;
  time(&tempo);

  int dayOfMonth, month, year;
  struct tm *local = localtime(&tempo);
  dayOfMonth = local -> tm_mday;
  month = local -> tm_mon + 1;
  year = local -> tm_year + 1900;

  std::stringstream ss;
  std::string giornoDelMese;
  std::string mese;
  std::string anno;

  ss << dayOfMonth;
  ss >> giornoDelMese;
  ss.clear();

  ss << dayOfMonth;
  ss >> giornoDelMese;
  ss.clear();

  ss << year;
  ss >> anno;
  ss.clear();

  date = giornoDelMese + "-" + mese + "-" + anno;

  return date;

}

std::string DbManager::quoteSql(std::string s){

  return std::string("'") + s + std::string("'");

}

std::string DbManager::createSqlInsertStatement(){

  std::string sqlInsertStatement;
  std::string date;
  date = getDate();

  sqlInsertStatement = "INSERT INTO PASSWORDS VALUES("
  + quoteSql(date) + ","
  + quoteSql(webSiteOrAppName) + ','
  + quoteSql(password) + ")";

  return sqlInsertStatement;
}

std::string DbManager::createSqlQueryStatement(int nameOrDate, std::string parameters){

  std::string sqlQueryStatement;

  if(nameOrDate == 1){
    sqlQueryStatement = "SELECT * FROM PASSWORDS WHERE WEBSITEORAPPNAME = '" + std::string(parameters) + "'";
  }else{
    sqlQueryStatement = "SELECT * FROM PASSWORDS WHERE DATEOFRECORD = '" + std::string(parameters) + "'";
  }

  return sqlQueryStatement;
}

std::string DbManager::createSqlUpdateStatement(std::string name, std::string newPwd){

  std::string sqlStatement;

  sqlStatement = "UPDATE PASSWORDS SET PASSWORD = '" + std::string(newPwd) + "'" + " WHERE WEBSITEORAPP = '" + std::string(name) + "'";

  return sqlStatement;
}

int DbManager::callback(void *data, int argc, char** argv, char** azColName){

  int i;

  // fprintf(stderr, "%s: ", (const char*)data);
  printf("\n");
    for (i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;

}

void DbManager::deleteTable(){

  sqlite3 *database;
  sqlite3_stmt *stmt;

  int exit;
  char* errorMessage;
  // string sqlStatement = "DROP TABLE PASSWORD";
  /*
  exit = sqlite3_exec(database, sqlStatement.c_str(), NULL, 0, &errorMessage);
  if (exit != SQLITE_OK){
    cout << "table eliminata correttamente" << endl;
  }else{
    cout << "table non eliminata" << endl;
  }*/

}

// PUBLIC METHODS
void DbManager::setWebSiteOrAppName(std::string name){

  webSiteOrAppName = name;

}

void DbManager::setPassword(std::string givenPassword){

  password = givenPassword;

}

void DbManager::setDBName(std::string name){

  dbName = name;

}

bool DbManager::save(){

  sqlite3 *database;
  sqlite3_stmt *stmt;
  int exit = 0;

  std::string recordDate;
  std::string sqlStatement = createSqlInsertStatement();

  bool error;

  exit = sqlite3_open(dbName.c_str(), &database);
  if(exit != SQLITE_OK){
    std::cerr << "Error during database connection" << "\n";
  }

  recordDate = getDate();

  char *errorMessage;
  exit = sqlite3_exec(database, sqlStatement.c_str(), NULL, 0, &errorMessage);

  if(exit != SQLITE_OK){
    error = true;
  }else{
    error = false;
  }
  // Non dovrei chiudere la connessione con il database?
  return error;
}

bool DbManager::createTable(std::string sqlStmt){

  sqlite3 *database;
  sqlite3_stmt* statement;
  int exit = 0;

  bool error;

  exit = sqlite3_open(dbName.c_str(), &database);
  if(exit != SQLITE_OK){
    std::cerr << "Error during database connection" << "\n";
  }

  char *errorMessage;
  exit = sqlite3_exec(database, sqlStmt.c_str(), NULL, 0, &errorMessage);
  if(exit != SQLITE_OK){
    sqlite3_free(errorMessage);
    error = true;
  }else{
    error = false;
  }
  return error;
}

void DbManager::readDB(int nameOrDate, std::string parameters){

  sqlite3 *database;
  sqlite3_stmt *stmt;

  char *errorMessage;
  std::string sqlQueryStatement;

  int exit = 0;
  exit = sqlite3_open(dbName.c_str(), &database);
  if(exit != SQLITE_OK){
    std::cout << "Couldn't open db while trying to open it" << "\n";
    sqlite3_free(errorMessage);
  }
  
  sqlQueryStatement = createSqlQueryStatement(nameOrDate, parameters);

  exit = sqlite3_exec(database, sqlQueryStatement.c_str(), callback, NULL, &errorMessage);

  if(exit != SQLITE_OK){
    std::cout << "Something went wrong during db reading" << "\n";
    std::cout << errorMessage << "\n";
    sqlite3_free(errorMessage);
  }
}

bool DbManager::updatePassword(std::string name, std::string newPassword){

  sqlite3 *database;
  sqlite3_stmt *stmt;
  char *errorMessage;
  int exit;

  bool error;
  std::string sqlUpdateStatement = createSqlUpdateStatement(name, newPassword);

  exit = sqlite3_open(dbName.c_str(), &database);

  if(exit != SQLITE_OK){
    std::cerr << "Error occured while trying to open db to update it" << "\n";
    error = true;
  }else{
    error = false;
  }

  return error;
}

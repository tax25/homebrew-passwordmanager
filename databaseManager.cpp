#include<iostream>
#include"sqlite3/sqlite3.h"
#include<ctime>
#include<sstream>

using namespace std;

class DatabaseManager{

private:
  string webSiteOrAppName;
  string password;
  string dbName;

  string getDate(){
    string date;
    time_t tempo;
    time(&tempo);

    int dayOfMonth, month, year;
    struct tm *local = localtime(&tempo);
    dayOfMonth = local -> tm_mday;
    month = local -> tm_mon + 1;
    year = local -> tm_year + 1900;

    stringstream ss;
    string giornoDelMese;
    string mese;
    string anno;

    ss << dayOfMonth;
    ss >> giornoDelMese;
    ss.clear();
    ss << month;
    ss >> mese;
    ss.clear();
    ss << year;
    ss >> anno;
    ss.clear();

    date = giornoDelMese + "-" + mese + "-" + anno;

    return date;
  }

  string quoteSql(string s){
    return string("'") + s + string("'");
  }

  string createSqlInsertStatement(){
    string sqlInsertStatement;
    string date;
    date = getDate();

    sqlInsertStatement = "INSERT INTO PASSWORDS VALUES("
    + quoteSql(date) + ","
    + quoteSql(webSiteOrAppName) + ","
    + quoteSql(password) + ")";
    // cout << sqlInsertStatement << endl;
    return sqlInsertStatement;
  }

  string createSqlQueryStatement(int nameOrDate, string parameters){

    string sqlQueryStatement;

    if (nameOrDate == 1){
      sqlQueryStatement = "SELECT * FROM PASSWORDS WHERE WEBSITEORAPP = '" + string(parameters) + "'";
    }else{
      sqlQueryStatement = "SELECT * FROM PASSWORDS WHERE DATEOFRECORD = '" + string(parameters) + "'";
    }

    return sqlQueryStatement;
  }

  string createSqlUpdateStatement(string name, string newPwd){
    string sqlStatement;

    sqlStatement = "UPDATE PASSWORDS SET PASSWORD = '" + string(newPwd) + "'" + " WHERE WEBSITEORAPP = '" + string(name) + "'";

    return sqlStatement;
  }

  static int callback(void *data, int argc, char** argv, char** azColName){
    int i;

    // fprintf(stderr, "%s: ", (const char*)data);
    printf("\n");
      for (i = 0; i < argc; i++) {
          printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
      }
      printf("\n");
      return 0;
  }

  void deleteTable(){
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

public:

  void setWebSiteOrAppName(string name){
    webSiteOrAppName = name;
  }

  void setPassword(string givenPassword){
    password = givenPassword;
  }

  void setDBName(string name){
    dbName = name;
  }

  bool save(){
    // cout << webSiteOrAppName << "\t" << password << endl;
    // connecting to/creating db
    sqlite3 *database;
    sqlite3_stmt *stmt;
    int exit = 0;

    string recordDate;
    string sqlStatement = createSqlInsertStatement();

    bool error;

    exit = sqlite3_open(dbName.c_str(), &database);
    if(exit != SQLITE_OK){
      cerr << "Errore nell'apertura del db :(" << endl;
    }else{
      // cout << "DB aperto correttamente" << endl;
    }

    recordDate = getDate();
    // cout << recordDate << endl;
    // cout << sqlStatement << endl;
    // cout << secondSqlStatement << endl;
    // cout << "All saved!" << endl;

    char *errorMessage;
    exit = sqlite3_exec(database, sqlStatement.c_str(), NULL, 0, &errorMessage);

    if(exit != SQLITE_OK){
      error = true;
    }else{
      error = false;
    }
    return error;
  }

  bool createTable(string sqlStmt){
    sqlite3 *database;
    sqlite3_stmt *statement;
    bool error;
    int exit = 0;

    exit = sqlite3_open(dbName.c_str(), &database);
    if(exit != SQLITE_OK){
      cerr << "Errore durante l'apertura del db" << endl;
    }else{
      // cout << "Db aperto correttamente" << endl;
    }

    char *errorMessage;
    exit = sqlite3_exec(database, sqlStmt.c_str(), NULL, 0, &errorMessage);
    if(exit != SQLITE_OK){
      cout << errorMessage << endl;
      sqlite3_free(errorMessage);
      error = true;
    }else{
      error = false;
    }
    return error;
  }

  void readDB(int nameOrDate, string parameters){

    sqlite3 *database;
    sqlite3_stmt *stmt;
    char* errorMessage;
    string sqlQueryStatement;

    int exit = 0;
    exit = sqlite3_open(dbName.c_str(), &database);
    if(exit != SQLITE_OK){
      cout << "Something went wrong" << endl;
      sqlite3_free(errorMessage);
    }else{
      // cout << "Apertura del db eseguita con successos" << endl;
    }
    // string sql_queryEverything = "SELECT * FROM PASSWORDS";

    sqlQueryStatement = createSqlQueryStatement(nameOrDate, parameters);
    // sqlite3_exec(database, sqlQueryStatement.c_str(), callback, NULL, NULL);

    exit = sqlite3_exec(database, sqlQueryStatement.c_str(), callback, NULL, &errorMessage);
    if (exit != SQLITE_OK){
      cout << "Lettura del db fallita :(" << endl;
    }else{
      /*
      cout << "Lettura del db eseguita con successo..." << endl;
      cout << SQLITE_OK << endl;
      */
    }

    // there's no return statement because to print the results of the research we use the callback method
  }

  bool updatePassword(string name, string newPassword){
    sqlite3 *database;
    sqlite3_stmt *stmt;
    char *errorMessage;
    int exit;

    bool error;
    string sqlUpdateStatement = createSqlUpdateStatement(name, newPassword);

    exit = sqlite3_open(dbName.c_str(), &database);
    if (exit){
      cerr << "Errore nell'apertura del db" << endl;
    }else{
      // cout << "db aperto correttamente" << endl;
    }
    // cout << name << endl;
    // cout << newPassword << endl;
    // cout << sqlUpdateStatement << endl;

    exit = sqlite3_exec(database, sqlUpdateStatement.c_str(), NULL, 0, &errorMessage);
    if (exit != SQLITE_OK){
      error = true;
    }else{
      error = false;
    }

    return error;
  }

};

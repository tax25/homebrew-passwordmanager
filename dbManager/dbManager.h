#include<iostream>
#include<sstream>
#include"sqlite3/sqlite3.h"

class DbManager{

private:

  std::string webSiteOrAppName;
  std::string password;
  std::string dbName;

  std::string getDate();
  std::string quoteSql(std::string s);
  std::string createSqlInsertStatement();
  std::string createSqlQueryStatement(int nameOrDate, std::string parameters);
  std::string createSqlUpdateStatement(std::string name, std::string newPassword);
  static int callback(void *data, int argc, char** argv, char** azColName);
  void deleteTable();

public:

  void setWebSiteOrAppName(std::string name);
  void setPassword(std::string givenPassword);
  void setDBName(std::string name);
  bool save();
  bool createTable(std::string sqlStmt);
  void readDB(int nameOrDate, std::string parameters);
  bool updatePassword(std::string name, std::string newPassword);

};

#include<iostream>
#include<cstdlib>
#include"dbManager/dbManager.h"

std::string generatePassword(int pwdLenght, bool nums, bool specialChars, bool alphaNumericalChars);
char selectCharacterFromString(std::string stringToUse);
void welcomeUser();
void showGeneratedPassword(std::string pwdToShow);

#define MIN_PWD_LENGHT 7

enum ContinueOrNot{
  CONFIRMED = 'y', 
  DECLINED = 'N'
}; 

enum MainMenuChoices{
  MM_CREATE_PASSWORD = 1,
  MM_SEARCH_PASSWORD = 2, 
  MM_UPDATE_PASSWORD = 3
};

enum SearchPwdChoices{
  SP_THROUGH_NAME = 1,
  SP_THROUGH_DATE = 2
};

int main(){

  srand(time(0));

  DbManager dbManager;

  dbManager.setDBName("passwordsDB.db");

  std::string createTableSqlStatement;

  std::string webAppPwdFor;
  std::string generatedPassword;
  std::string newPassword;

  int choice;
  int passwordLenght;

  char customPassword;

  bool numbers, specialCharacters, alphaNumericalChars;
  bool errorCreatingTable;

  char wishToContinue = CONFIRMED;

  createTableSqlStatement = "CREATE TABLE IF NOT EXISTS PASSWORDS("
                            "DATEOFRECORD DATE, "
                            "WEBSITEORAPPNAME TEXT, "
                            "PASSWORD TEXT);";

  errorCreatingTable = dbManager.createTable(createTableSqlStatement);
  system("clear");
  if(errorCreatingTable){
    std::cerr << "An error occured while trying to create the database" << "\n";
  }

  while(wishToContinue == CONFIRMED){

    welcomeUser();

    std::cin >> choice;

    while((choice < MM_CREATE_PASSWORD) || (choice > MM_UPDATE_PASSWORD)){
      std::cout << "Wrong choice, choose a number between the possible choices" << "\n";
      std::cin >> choice;
    }

    if (choice == MM_CREATE_PASSWORD){
      std::cout << "How much long do you want your password to be?" << "\n";
      std::cin >> passwordLenght;

      while(passwordLenght < MIN_PWD_LENGHT){
        std::cout << "That would be too short, insert a lenght > 7" << "\n";
        std::cin >> passwordLenght;
      }

      std::cout << "Which is the app or website this password is for?" << "\n";
      std::cin >> webAppPwdFor;

      std::cout << "The password normally includes: numbers, special characters and alphanumerical characters" << "\n";
      std::cout << "If you want them all, insert x" << "\n";
      std::cout << "If you prefer to choose which characters use and which not, insert c" << "\n";
      std::cin >> customPassword;
      
      if((customPassword != 'x') && (customPassword != 'c')){
        
        while(true){
          std::cout << "Devi inserire x o c" << "\n";
          std::cin >> customPassword;
          if ((customPassword == 'x')||(customPassword == 'c')){
            break;
          }
        }  
      }

      if (customPassword == 'x'){
        std::cout << "The generated password will have all characters" << "\n";
        generatedPassword = generatePassword(passwordLenght, true, true, true);
        
        showGeneratedPassword(generatedPassword);
        
        std::cout << "Do you want to save it in the database? y/N" << "\n";
        char yes;

        std::cin >> yes;
        if (yes == CONFIRMED){
          dbManager.setWebSiteOrAppName(webAppPwdFor);
          dbManager.setPassword(generatedPassword);
          dbManager.save();
        }
      }else if (customPassword == 'c'){

        std::cout << "Do you want numbers? (0/1)" << "\n";
        std::cin >> numbers;
        
        if((numbers != true) && (numbers != false)){

          while(true){
            std::cout << "You have to insert 0 or 1" << "\n";
            std::cin >> numbers;
            if ((numbers == true)||(numbers == false)){
              break;
            }
          }
        
        }
        
        std::cout << "Do you want special characters? (0/1)" << "\n";
        std::cin >> specialCharacters;
                
        if((specialCharacters != true) && (specialCharacters != false)){
          
          while(true){
            std::cout << "You have to insert 0 or 1" << "\n";
            std::cin >> specialCharacters;
            if ((specialCharacters == true)||(specialCharacters == false)){
              break;
            }
          }
        
        }

        std::cout << "Do you want alphanumerical characters? (0/1)" << "\n";
        std::cin >> alphaNumericalChars;
        
        if((alphaNumericalChars != true) && (alphaNumericalChars != false)){

          while(true){
            std::cout << "You have to insert 0 or 1" << "\n";
            std::cin >> alphaNumericalChars;
            if ((alphaNumericalChars == 1)||(alphaNumericalChars == 0)){
              break;
            }
          }
        }

        generatedPassword = generatePassword(passwordLenght, numbers, specialCharacters, alphaNumericalChars);
       
        showGeneratedPassword(generatedPassword);

        char yes;
        std::cout << "Do you want to save it in the database? y/N" << "\n";

        std::cin >> yes;
        if(yes == CONFIRMED){
          dbManager.setWebSiteOrAppName(webAppPwdFor);
          dbManager.setPassword(generatedPassword);
          dbManager.save();
        }
      }
    } /*if choice == MM_CREATE_PASSWORD*/ else if(choice == MM_SEARCH_PASSWORD){
      std::cout << "By which method do you want to search the password?" << "\n";
      std::cout << "(1) Through the name of the website / app" << "\n";
      std::cout << "(2) Through creation date" << "\n";

      int mode;
      std::cin >> mode;

      while((mode < SP_THROUGH_NAME) || (mode > SP_THROUGH_DATE)){
        std::cout << "Wrong choice, choose a number between the possible choices" << "\n";
        std::cin >> mode;
      }

      if (mode == SP_THROUGH_NAME){
        std::cout << "Ok, insert the name of the app or website" << "\n";
        std::cin >> webAppPwdFor;
        dbManager.readDB(mode, webAppPwdFor);
      }else if (mode == SP_THROUGH_DATE){
        std::cout << "Ok, insert the creation date of the password (like this: dd-mm-yy)" << "\n";
        std::string dateOfCreation;
        std::cin >> dateOfCreation;
        dbManager.readDB(mode, dateOfCreation);
      }

    }/*if choice == MM_SEARCH_PASSWORD*/ else{ // if choice == MM_UPDATE_PASSWORD
      std::cout << "Of which app or website do you want to change the password?" << "\n";
      std::cin >> webAppPwdFor;
      std::cout << "Insert the new password (if you want me to create a new one, insert 'new'):" << "\n";
      std::cin >> newPassword;

      if (newPassword.compare("new") == 0){
        std::cout << "How much long does the password have to be? (> 7 characters)" << "\n";
        std::cin >> passwordLenght;

        while(passwordLenght < MIN_PWD_LENGHT){
          std::cout << "That would be too short, insert a lenght > 7" << "\n";
          std::cin >> passwordLenght;
        }
        
        std::cout << "The password normally includes: numbers, special characters and alphanumerical characters" << "\n";
        std::cout << "If you want them all, insert x" << "\n";
        std::cout << "If you prefer to choose which characters use and which not, insert c" << "\n";
        std::cin >> customPassword;
          
        if((customPassword != 'x') && (customPassword != 'c')){

          while(true){
            std::cout << "You have to insert x or c" << "\n";
            std::cin >> customPassword;
            if ((customPassword == 'x')||(customPassword == 'c')){
              break;
            }
          }
        
        }

        if (customPassword == 'x'){
          std::cout << "The password will have all the characters mentioned before" << "\n";
          generatedPassword = generatePassword(passwordLenght, true, true, true);
          std::cout << "--------------------------" << "\n";
          std::cout << "The password has been generated: \n" <<  generatedPassword << "\n";
          std::cout << "--------------------------" << "\n";

        }else if (customPassword == 'c'){

          std::cout << "Do you want numbers? (0/1)" << "\n";
          std::cin >> numbers;
          
          if((numbers != true) && (numbers != false)){

            while(true){
              std::cout << "You have to insert 0 or 1" << "\n";
              std::cin >> numbers;
              if ((numbers == true)||(numbers == false)){
                break;
              }
            }
          }

          std::cout << "Do you want special characters?" << "\n";
          std::cin >> specialCharacters;

          if((specialCharacters != true) && (specialCharacters != false)){
          
            while(true){
              std::cout << "You need to insert 0 or 1" << "\n";
              std::cin >> specialCharacters;
              if ((specialCharacters == true) || (specialCharacters == false)){
                break;
              }
            }
        
          }

          std::cout << "Do you want alphanumerical characters?" << "\n";
          std::cin >> alphaNumericalChars;
          
          if ((alphaNumericalChars == true) || (alphaNumericalChars == false)){
            // do nothing
          }else{
            while(true){
              std::cout << "You have to insert 0 or 1" << "\n";
              std::cin >> alphaNumericalChars;
              if ((alphaNumericalChars == true) || (alphaNumericalChars == false)){
                break;
              }
            }
          }

          generatedPassword = generatePassword(passwordLenght, numbers, specialCharacters, alphaNumericalChars);
            std::cout << "\n--------------------------" << "\n";
          std::cout << "The password has been generated: \n" << generatedPassword << "\n";
          std::cout << "--------------------------" << "\n";
        }
        char yes;
        std::cout << "Do you want to update the password? y/N" << "\n";

        std::cin >> yes;
        if (yes == CONFIRMED){
          dbManager.updatePassword(webAppPwdFor, generatedPassword);
        }else if (yes == 'N'){
          std::cout << "Ok, the password hasn't been changed" << std::endl;
        }else{
          while(true){
            std::cout << "You have to insert 0 or 1" << "\n";
            std::cin >> yes;
            if (yes == CONFIRMED || yes == DECLINED){
              break;
            }
          }
        }
      }else{
        char yes;
        std::cout << "Do you want to update the password? y/N" << "\n";
        std::cin >> yes;
        if (yes == CONFIRMED){
          dbManager.updatePassword(webAppPwdFor, newPassword);
        }else if (yes == DECLINED){
          // do nothing
        }else{
          while(true){
            std::cout << "You have to insert y or N" << "\n";
            std::cin >> yes;
            if (yes == CONFIRMED || yes == DECLINED){
              break;
            }
          }
        }
      }
    } /*if choice == 3*/
    std::cout << "Would you want to do another operation? y/N" << "\n";
    std::cin >> wishToContinue;
    if ((wishToContinue != CONFIRMED) && (wishToContinue != DECLINED)){
      while(true){
        std::cout << "You have to insert y or N" << "\n";
        std::cin.clear();
        std::cin >> wishToContinue;
        if ((wishToContinue == CONFIRMED)||(wishToContinue == DECLINED)){
          break;
        }
      }
    }
    system("clear");
  } /* while(wishToContinue == CONFIRMED) */

}

std::string generatePassword(int pwdLenght, bool nums, bool specialChars, bool alphaNumericalChars){

  std::string generatedPwd;

  std::string uppercaseAlphabet = "ABCDEFGHIJLMNOPQRSTUVWYZ";
  std::string lowercaseAlphabet = "abcdefghijlmnopqrstuvwyz";
  std::string specialCharacters = "!£$%&/()=*+-";
  std::string alphaNumericalCharacters = "{}[]#@§;:,.°";
  std::string numbers = "0123456789";


  for (int i = 0; i < pwdLenght+1; i++){
    int randomNumber = (rand() % 4);
    switch (randomNumber){
      case 0:
        generatedPwd += selectCharacterFromString(uppercaseAlphabet);
        break;

      case 1:
        generatedPwd += selectCharacterFromString(lowercaseAlphabet);
        break;

      case 2:
        if (specialChars){
          generatedPwd += selectCharacterFromString(specialCharacters);
        }else{
          i--; // subtract one as one cycle has been used for nothing
        }
        break;

      case 3:
        if (alphaNumericalChars){
          generatedPwd += selectCharacterFromString(alphaNumericalCharacters);
        }else{
          i--;
        }
        break;

      case 4:
        if (nums){
          generatedPwd += selectCharacterFromString(numbers);
        }else{
          i--;
        }
        break;
    }

  }

  return generatedPwd;

}

char selectCharacterFromString(std::string stringToUse){
  int randomNumber = (rand() % stringToUse.length());
  char selectedChar = stringToUse[randomNumber];
  return selectedChar;
}

void welcomeUser(){

    std::cout << "--------------------------" << "\n";
    std::cout << "Welcome to passwordmanager!" << "\n";
    std::cout << "--------------------------" << "\n";
    std::cout << "Insert the number connected to what you want to do" << "\n";
    std::cout << "(1) Create a new password" << "\n";
    std::cout << "(2) Search for a password" << "\n";
    std::cout << "(3) Change/Update a password" << "\n";

}
void showGeneratedPassword(std::string pwdToShow){

    std::cout << "--------------------------" << "\n";
    std::cout << "The password has been generated: \n" <<  pwdToShow << "\n";
    std::cout << "--------------------------" << "\n";

}

#include<iostream>
#include<cstdlib>
#include"dbManager.h"

std::string generatePassword(int pwdLenght, bool nums, bool specialChars, bool alphaNumericalChars);
char selectCharacterFromString(std::string stringToUse);

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

enum UpdatePwdChoices{

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
    std::cerr << "Errore nella creazione della tabella del database" << "\n";
  }

  while(wishToContinue == CONFIRMED){

    std::cout << "--------------------------" << "\n";
    std::cout << "Generatore di Password" << "\n";
    std::cout << "--------------------------" << "\n";
    std::cout << "Inserisci il numero collegato a cio che vuoi fare" << "\n";
    std::cout << "(1) Creare una nuova password" << "\n";
    std::cout << "(2) Cercare una password" << "\n";
    std::cout << "(3) Cambiare una password" << "\n";
    std::cin >> choice;

    while((choice < MM_CREATE_PASSWORD) || (choice > MM_UPDATE_PASSWORD)){
      std::cout << "Scelta errata, inscerisci un numero compreso tra le scelte" << "\n";
      std::cin >> choice;
    }

    if (choice == MM_CREATE_PASSWORD){
      std::cout << "Quanto deve essere lunga la password?" << "\n";
      std::cin >> passwordLenght;

      while(passwordLenght < MIN_PWD_LENGHT){
        std::cout << "La password sarebbe troppo corta, inserisci una lunghezza maggiore" << "\n";
        std::cin >> passwordLenght;
      }

      std::cout << "Per che sito / applicazione è la password? (nel caso del sito, inserisci anche il .com/it ecc...)" << "\n";
      std::cin >> webAppPwdFor;

      std::cout << "La password normalmente include: numeri, caratteri speciali e caratteri alfanumerici." << "\n";
      std::cout << "Se vuoi che vengano inclusi tutti nella password, inserisci x" << "\n";
      std::cout << "Altrimenti inserisci c per creare una password custom" << "\n";
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
        std::cout << "La password avrà tutti i caratteri sopra menzionati" << "\n";
        generatedPassword = generatePassword(passwordLenght, true, true, true);
        std::cout << "--------------------------" << "\n";
        std::cout << "La password e' stata generata: \n" <<  generatedPassword << "\n";
        std::cout << "--------------------------" << "\n";
        std::cout << "Vuoi salvare la password nel database? y/N" << "\n";
        char yes;

        std::cin >> yes;
        if (yes == CONFIRMED){
          dbManager.setWebSiteOrAppName(webAppPwdFor);
          dbManager.setPassword(generatedPassword);
          dbManager.save();
        }
      }else if (customPassword == 'c'){

        std::cout << "Vuoi i numeri? (0/1)" << "\n";
        std::cin >> numbers;
        
        if((numbers != true) && (numbers != false)){

          while(true){
            std::cout << "Devi inserire 0 o 1" << "\n";
            std::cin >> numbers;
            if ((numbers == true)||(numbers == false)){
              break;
            }
          }
        
        }
        
        std::cout << "Vuoi i caratteri speciali?" << "\n";
        std::cin >> specialCharacters;
                
        if((specialCharacters != true) && (specialCharacters != false)){
          
          while(true){
            std::cout << "Devi inserire 0 o 1" << "\n";
            std::cin >> specialCharacters;
            if ((specialCharacters == true)||(specialCharacters == false)){
              break;
            }
          }
        
        }

        std::cout << "Vuoi i caratteri alfaNumerici?" << "\n";
        std::cin >> alphaNumericalChars;
        
        if((alphaNumericalChars != true) && (alphaNumericalChars != false)){

          while(true){
            std::cout << "Devi inserire 0 o 1" << "\n";
            std::cin >> alphaNumericalChars;
            if ((alphaNumericalChars == 1)||(alphaNumericalChars == 0)){
              break;
            }
          }
        }

        generatedPassword = generatePassword(passwordLenght, numbers, specialCharacters, alphaNumericalChars);
        std::cout << "\n--------------------------" << "\n";
        std::cout << "La password e' stata generata: \n" << generatedPassword << "\n";
        std::cout << "--------------------------" << "\n";
        char yes;
        std::cout << "Vuoi salvare la password nel database? y/N" << "\n";

        std::cin >> yes;
        if(yes == CONFIRMED){
          dbManager.setWebSiteOrAppName(webAppPwdFor);
          dbManager.setPassword(generatedPassword);
          dbManager.save();
        }
      }
    } /*if choice == MM_CREATE_PASSWORD*/ else if(choice == MM_SEARCH_PASSWORD){
      std::cout << "Come vuoi cercare la password?" << "\n";
      std::cout << "(1) Per nome del sito / app" << "\n";
      std::cout << "(2) Per data di creazione" << "\n";

      int mode;
      std::cin >> mode;

      while((mode < SP_THROUGH_NAME) || (mode > SP_THROUGH_DATE)){
        std::cout << "Scelta errata, inscerisci un numero compreso tra le scelte" << "\n";
        std::cin >> mode;
      }

      if (mode == SP_THROUGH_NAME){
        std::cout << "Ok, inserisci il nome del sito o app (nel caso del sito, inserisci anche il .com/it ecc...)" << "\n";
        std::cin >> webAppPwdFor;
        dbManager.readDB(mode, webAppPwdFor);
      }else if (mode == SP_THROUGH_DATE){
        std::cout << "Ok, inserisci la data di creazione della password, in questo modo dd-mm-yy" << "\n";
        std::string dateOfCreation;
        std::cin >> dateOfCreation;
        dbManager.readDB(mode, dateOfCreation);
      }

    }/*if choice == MM_SEARCH_PASSWORD*/ else{ // if choice == MM_UPDATE_PASSWORD
      std::cout << "Di quale sito o app vuoi cambiare la password? (nel caso dei siti, inserisci anche .com/it ecc...)" << "\n";
      std::cin >> webAppPwdFor;
      std::cout << "Inserisci la nuova password (Se vuoi che ne crei un'altra, scrivi new)" << "\n";
      std::cin >> newPassword;

      if (newPassword.compare("new") == 0){
        std::cout << "Quanto deve essere lunga la password?" << "\n";
        std::cin >> passwordLenght;

        while(passwordLenght < MIN_PWD_LENGHT){
          std::cout << "La password sarebbe troppo corta, inserisci una lunghezza maggiore" << "\n";
          std::cin >> passwordLenght;
        }

        std::cout << "La password normalmente include: numeri, caratteri speciali e caratteri alfanumerici." << "\n";
        std::cout << "Se vuoi che vengano inclusi tutti nella password, inserisci x" << "\n";
        std::cout << "Altrimenti inserisci c per creare una password custom" << "\n";
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
          std::cout << "La password avrà tutti i caratteri sopra menzionati" << "\n";
          generatedPassword = generatePassword(passwordLenght, true, true, true);
          std::cout << "--------------------------" << "\n";
          std::cout << "La password e' stata generata: \n" <<  generatedPassword << "\n";
          std::cout << "--------------------------" << "\n";

        }else if (customPassword == 'c'){

          std::cout << "Vuoi i numeri? (0/1)" << "\n";
          std::cin >> numbers;
          
          if((numbers != true) && (numbers != false)){

            while(true){
              std::cout << "Devi inserire 0 o 1" << "\n";
              std::cin >> numbers;
              if ((numbers == true)||(numbers == false)){
                break;
              }
            }
          }

          std::cout << "Vuoi i caratteri speciali?" << "\n";
          std::cin >> specialCharacters;

          if((specialCharacters != true) && (specialCharacters != false)){
          
            while(true){
              std::cout << "Devi inserire 0 o 1" << "\n";
              std::cin >> specialCharacters;
              if ((specialCharacters == true)||(specialCharacters == false)){
                break;
              }
            }
        
          }

          std::cout << "Vuoi i caratteri alfaNumerici?" << "\n";
          std::cin >> alphaNumericalChars;
          

          if ((alphaNumericalChars == true)||(alphaNumericalChars == false)){
            // do nothing
          }else{
            while(true){
              std::cout << "Devi inserire 0 o 1" << "\n";
              std::cin >> alphaNumericalChars;
              if ((alphaNumericalChars == true)||(alphaNumericalChars == false)){
                break;
              }
            }
          }

          generatedPassword = generatePassword(passwordLenght, numbers, specialCharacters, alphaNumericalChars);
            std::cout << "\n--------------------------" << "\n";
          std::cout << "La password e' stata generata: \n" << generatedPassword << "\n";
          std::cout << "--------------------------" << "\n";
        }
        char yes;
        std::cout << "Vuoi aggiornare la password? y/N" << "\n";

        std::cin >> yes;
        if (yes == 'y'){
          dbManager.updatePassword(webAppPwdFor, generatedPassword);
        }else if (yes == 'N'){
          // do nothing
        }else{
          while(true){
            std::cout << "Devi inserire y o N" << "\n";
            std::cin >> yes;
            if (yes == 'y' || yes == 'N'){
              break;
            }
          }
        }
      }else{
        char yes;
        std::cout << "Vuoi aggiornare la password? y/N" << "\n";
        std::cin >> yes;
        if (yes == CONFIRMED){
          dbManager.updatePassword(webAppPwdFor, newPassword);
        }else if (yes == DECLINED){
          // do nothing
        }else{
          while(true){
            std::cout << "Devi inserire y o N" << "\n";
            std::cin >> yes;
            if (yes == CONFIRMED || yes == DECLINED){
              break;
            }
          }
        }
      }
    } /*if choice == 3*/
    std::cout << "Desideri fare qualche altra operazione? y/N" << "\n";
    std::cin >> wishToContinue;
    if ((wishToContinue != CONFIRMED) && (wishToContinue != DECLINED)){
      while(true){
        std::cout << "Devi inserire y o N" << "\n";
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

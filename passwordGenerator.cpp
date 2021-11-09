#include <iostream>
#include <cstdlib>
#include"databaseManager.cpp"

using namespace std;

string generatePassword(int pwdLenght, bool nums, bool specialChars, bool alphaNumericalChars);
char selectCharacterFromString(string stringToUse);

int main(){

  srand(time(0));

  DatabaseManager dbManager;
  dbManager.setDBName("passwordsDB.db");

  string createTableSqlStatement;

  string webAppPwdFor, generatedPassword, newPassword;
  int choice, passwordLenght;
  char customPassword;
  bool numbers, specialCharacters, alphaNumericalCharacters;
  bool errorCreatingTable;
  char wishToContinue = 'y'; // Initialized to 'y', because if not the loop won't even start

  createTableSqlStatement = "CREATE TABLE IF NOT EXISTS PASSWORDS("
                            "DATEOFRECORD DATE, "
                            "WEBSITEORAPP TEXT, "
                            "PASSWORD TEXT );";
  errorCreatingTable = dbManager.createTable(createTableSqlStatement);

  if (errorCreatingTable){
    cerr << "errore nella creazione della tabella" << endl;
  }else{
    // cout << "creazione tabella eseguita con successo" << endl;
  }

  while (wishToContinue == 'y'){
    // system("clear");
    cout << "--------------------------" << endl;
    cout << "Generatore di Password" << endl;
    cout << "--------------------------" << endl;
    cout << "Inserisci il numero collegato a cio che vuoi fare" << endl;
    cout << "(1) Creare una nuova password" << endl;
    cout << "(2) Cercare una password" << endl;
    cout << "(3) Cambiare una password" << endl;
    cin >> choice;

    while((choice < 1)||(choice > 3)){
      cout << "Scelta errata, inscerisci un numero compreso tra le scelte" << endl;
      cin >> choice;
    }

    if (choice == 1){
      cout << "Quanto deve essere lunga la password?" << endl;
      cin >> passwordLenght;

      while(passwordLenght < 7){
        cout << "La password sarebbe troppo corta, inserisci una lunghezza maggiore" << endl;
        cin >> passwordLenght;
      }

      cout << "Per che sito / applicazione è la password? (nel caso del sito, inserisci anche il .com/it ecc...)" << endl;
      cin >> webAppPwdFor;

      cout << "La password normalmente include: numeri, caratteri speciali e caratteri alfanumerici." << endl;
      cout << "Se vuoi che vengano inclusi tutti nella password, inserisci x" << endl;
      cout << "Altrimenti inserisci c per creare una password custom" << endl;
      cin >> customPassword;
      if ((customPassword == 'x')||(customPassword == 'c')){
        // do nothing
      }else{
        while(true){
          cout << "Devi inserire x o c" << endl;
          cin >> customPassword;
          if ((customPassword == 'x')||(customPassword == 'c')){
            break;
          }
        }
      }

      if (customPassword == 'x'){
        cout << "La password avrà tutti i caratteri sopra menzionati" << endl;
        generatedPassword = generatePassword(passwordLenght, true, true, true);
        cout << "--------------------------" << endl;
        cout << "La password e' stata generata: \n" <<  generatedPassword << endl;
        cout << "--------------------------" << endl;
        cout << "Vuoi salvare la password nel database? y/N" << endl;
        char yes;

        cin >> yes;
        if (yes == 'y'){
          dbManager.setWebSiteOrAppName(webAppPwdFor);
          dbManager.setPassword(generatedPassword);
          dbManager.save();
        }
      }else if (customPassword == 'c'){

        cout << "Vuoi i numeri? (0/1)" << endl;
        cin >> numbers;

        if ((numbers == true)||(numbers == false)){
          // do nothing
        }else{
          while(true){
            cout << "Devi inserire 0 o 1" << endl;
            cin >> numbers;
            if ((numbers == true)||(numbers == false)){
              break;
            }
          }
        }

        cout << "Vuoi i caratteri speciali?" << endl;
        cin >> specialCharacters;

        if ((specialCharacters == true)||(specialCharacters == false)){
          // do nothing
        }else{
          while(true){
            cout << "Devi inserire 0 o 1" << endl;
            cin >> specialCharacters;
            if ((specialCharacters == true)||(specialCharacters == false)){
              break;
            }
          }
        }

        cout << "Vuoi i caratteri alfaNumerici?" << endl;
        cin >> alphaNumericalCharacters;

        if ((alphaNumericalCharacters == true)||(alphaNumericalCharacters == false)){
          // do nothing
        }else{
          while(true){
            cout << "Devi inserire 0 o 1" << endl;
            cin >> alphaNumericalCharacters;
            if ((alphaNumericalCharacters == 1)||(alphaNumericalCharacters == 0)){
              break;
            }
          }
        }

        generatedPassword = generatePassword(passwordLenght, numbers, specialCharacters, alphaNumericalCharacters);
        cout << "\n--------------------------" << endl;
        cout << "La password e' stata generata: \n" << generatedPassword << endl;
        cout << "--------------------------" << endl;
        char yes;
        cout << "Vuoi salvare la password nel database? y/N" << endl;
        cin >> yes;
        if(yes == 'y'){
          dbManager.setWebSiteOrAppName(webAppPwdFor);
          dbManager.setPassword(generatedPassword);
          dbManager.save();
        }
      }
    } /*if choice == 1*/ else if(choice == 2){
      cout << "Come vuoi cercare la password?" << endl;
      cout << "(1) Per nome del sito / app" << endl;
      cout << "(2) Per data di creazione" << endl;

      int mode;
      cin >> mode;

      while((mode < 1)||(mode > 2)){
        cout << "Scelta errata, inscerisci un numero compreso tra le scelte" << endl;
        cin >> mode;
      }

      if (mode == 1){
        cout << "Ok, inserisci il nome del sito o app (nel caso del sito, inserisci anche il .com/it ecc...)" << endl;
        cin >> webAppPwdFor;
        dbManager.readDB(mode, webAppPwdFor);
      }else if (mode == 2){
        cout << "Ok, inserisci la data di creazione della password, in questo modo dd-mm-yy" << endl;
        string dateOfCreation;
        cin >> dateOfCreation;
        dbManager.readDB(mode, dateOfCreation);
      }

    }/*if choice == 2*/ else{
      cout << "Di quale sito o app vuoi cambiare la password? (nel caso dei siti, inserisci anche .com/it ecc...)" << endl;
      cin >> webAppPwdFor;
      cout << "Inserisci la nuova password (Se vuoi che ne crei un'altra, scrivi new)" << endl;
      cin >> newPassword;
      if (newPassword.compare("new") == 0){
        cout << "Quanto deve essere lunga la password?" << endl;
        cin >> passwordLenght;

        while(passwordLenght < 7){
          cout << "La password sarebbe troppo corta, inserisci una lunghezza maggiore" << endl;
          cin >> passwordLenght;
        }

        cout << "La password normalmente include: numeri, caratteri speciali e caratteri alfanumerici." << endl;
        cout << "Se vuoi che vengano inclusi tutti nella password, inserisci x" << endl;
        cout << "Altrimenti inserisci c per creare una password custom" << endl;
        cin >> customPassword;
        if ((customPassword == 'x')||(customPassword == 'c')){
          // do nothing
        }else{
          while(true){
            cout << "Devi inserire x o c" << endl;
            cin >> customPassword;
            if ((customPassword == 'x')||(customPassword == 'c')){
              break;
            }
          }
        }

        if (customPassword == 'x'){
          cout << "La password avrà tutti i caratteri sopra menzionati" << endl;
          generatedPassword = generatePassword(passwordLenght, true, true, true);
          cout << "--------------------------" << endl;
          cout << "La password e' stata generata: \n" <<  generatedPassword << endl;
          cout << "--------------------------" << endl;

        }else if (customPassword == 'c'){

          cout << "Vuoi i numeri? (0/1)" << endl;
          cin >> numbers;

          if ((numbers == true)||(numbers == false)){
            // do nothing
          }else{
            while(true){
              cout << "Devi inserire 0 o 1" << endl;
              cin >> numbers;
              if ((numbers == true)||(numbers == false)){
                break;
              }
            }
          }

          cout << "Vuoi i caratteri speciali?" << endl;
          cin >> specialCharacters;

          if ((specialCharacters == true)||(specialCharacters == false)){
            // do nothing
          }else{
            while(true){
              cout << "Devi inserire 0 o 1" << endl;
              cin >> specialCharacters;
              if ((specialCharacters == true)||(specialCharacters == false)){
                break;
              }
            }
          }

          cout << "Vuoi i caratteri alfaNumerici?" << endl;
          cin >> alphaNumericalCharacters;

          if ((alphaNumericalCharacters == true)||(alphaNumericalCharacters == false)){
            // do nothing
          }else{
            while(true){
              cout << "Devi inserire 0 o 1" << endl;
              cin >> alphaNumericalCharacters;
              if ((alphaNumericalCharacters == 1)||(alphaNumericalCharacters == 0)){
                break;
              }
            }
          }

          generatedPassword = generatePassword(passwordLenght, numbers, specialCharacters, alphaNumericalCharacters);
          cout << "\n--------------------------" << endl;
          cout << "La password e' stata generata: \n" << generatedPassword << endl;
          cout << "--------------------------" << endl;
        }
        char yes;
        cout << "Vuoi aggiornare la password? y/N" << endl;
        cin >> yes;
        if (yes == 'y'){
          dbManager.updatePassword(webAppPwdFor, generatedPassword);
        }else if (yes == 'N'){
          // do nothing
        }else{
          while(true){
            cout << "Devi inserire y o N" << endl;
            cin >> yes;
            if (yes == 'y' || yes == 'n'){
              break;
            }
          }
        }
      } /*if choice == 3*/
    }
    cout << "Desideri fare qualche altra operazione? y/N" << endl;
    cin >> wishToContinue;
    if ((wishToContinue != 'y')|| (wishToContinue != 'N')){
      while(true){
        cout << "Devi inserire y o N" << endl;
        cin >> wishToContinue;
        if ((wishToContinue == 'y')||(wishToContinue == 'N')){
          break;
        }
      }
    }
    system("clear");
  } /* while(wishToContinue == 'y') */

}

string generatePassword(int pwdLenght, bool nums, bool specialChars, bool alphaNumericalChars){

  string generatedPwd;

  string uppercaseAlphabet = "ABCDEFGHIJLMNOPQRSTUVWYZ";
  string lowercaseAlphabet = "abcdefghijlmnopqrstuvwyz";
  string specialCharacters = "!£$%&/()=*+-";
  string alphaNumericalCharacters = "{}[]#@§;:,.°";
  string numbers = "0123456789";


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

char selectCharacterFromString(string stringToUse){
  int randomNumber = (rand() % stringToUse.length());
  char selectedChar = stringToUse[randomNumber];
  return selectedChar;
}

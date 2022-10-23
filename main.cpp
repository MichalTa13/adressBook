#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cstdio>

using namespace std;

struct User {
    int id;
    string name, password;
};

struct Contact {
    int id, userID;
    string name, surname, phoneNumb, email, adress;
};

char getChar () {
    string inputStr = "";
    char inputChar = (0);

    while (true) {
        getline (cin, inputStr);

        if (inputStr.length() == 1) {
            inputChar = inputStr[0];
            break;
        }
        cout << "To nie jest pojedynczy znak." << endl;
        break;
    }
    return inputChar;
}

void menu() {
    system ("cls");
    cout << "***KSIAZKA ADRESOWA***" << endl;
    cout << endl << "1. Logowanie" << endl;
    cout << "2. Rejestracja" << endl;
    cout << "3. Zakoncz program" << endl;
    cout << endl << "Wybrano: ";
}

User splitDataLine (string dataLine) {
    string singleData[3];
    int markerPosition = 0;
    User person;

    for (int i = 0; i <= 2; i++) {
        markerPosition = dataLine.find ('|');
        singleData[i] = dataLine.substr (0, markerPosition);
        dataLine.erase (0, markerPosition + 1);

        switch (i) {
        case 0:
            person.id = atoi (singleData[i].c_str());
            break;
        case 1:
            person.name = singleData[i];
            break;
        case 2:
            person.password = singleData[i];
            break;
        }
    }
    return person;
}

void importUsers (vector <User> &userDetails) {
    string singleUserLine;
    userDetails.clear();
    fstream file;
    file.open ("users.txt", ios::in);

    if (file.good() == true) {
        while (getline (file, singleUserLine)) {
            userDetails.push_back (splitDataLine (singleUserLine));
        }
    }
}

string newUserID (vector <User> &userDetails) {
    int newID;

    if (!userDetails.empty()) {
        newID = userDetails.back().id + 1;
    } else {
        newID = 1;
    }
    ostringstream conversionToString;
    conversionToString << newID;
    string userID = conversionToString.str();
    return userID;
}

void addUser2File (string data) {
    fstream file;
    file.open ("users.txt",ios::out | ios::app);
    file << data << endl;
    file.close();
}

void addUser (vector <User> &userDetails) {
    string separationSign = "|";
    string newUser = newUserID (userDetails) + separationSign;
    string singleData;
    int usersAmmount = userDetails.size();

    system ("cls");
    cout << "***KSIAZKA ADRESOWA - DODAWANIE UZYTKOWNIKA***" << endl << endl;

    for (int i = 0; i <= 1; i++) {
        cin.sync();
        switch (i) {
        case 0:
            cout << "Podaj nazwe nacisnij ENTER: ";
            getline (cin, singleData);
            for (int j = 0; j < usersAmmount; j++ ) {
                if (singleData == (userDetails[j].name) ) {
                    cout << endl << "Uzytkownik juz istnieje." << endl;
                    system ("pause");
                    return;
                }
            }
            newUser += singleData;
            break;
        case 1:
            cout << "Podaj haslo i nacisnij ENTER: ";
            getline (cin, singleData);
            newUser += singleData;
            break;
        }
        newUser += separationSign;
    }
    addUser2File (newUser);
    struct User registeredUser = splitDataLine (newUser);
    userDetails.push_back (registeredUser);
    cout << endl << "*** Nowy uzytkownik zapisany poprawnie ***" << endl << endl;
    system("pause");
}

void showMenu () {
    system ("cls");
    cout << "***KSIAZKA ADRESOWA***" << endl;
    cout << endl << "1. Dodaj adresata" << endl;
    cout << "2. Wyszukaj po imieniu" << endl;
    cout << "3. Wyszukaj po nazwisku" << endl;
    cout << "4. Wyswietl wszystkich adresatow" << endl;
    cout << "5. Usun adresata" << endl;
    cout << "6. Edytuj adresata" << endl;
    cout << "7. Zmien haslo" << endl;
    cout << "8. Wyloguj sie" << endl;
    cout << endl << "Wybrano: ";
}

Contact splitContactDataLine (string dataLine) {
    string singleData[7];
    int markerPosition = 0;
    Contact person;

    for (int i = 0; i <= 6; i++) {
        markerPosition = dataLine.find ('|');
        singleData[i] = dataLine.substr (0, markerPosition);
        dataLine.erase (0, markerPosition + 1);

        switch (i) {
        case 0:
            person.id = atoi (singleData[i].c_str());
            break;
        case 1:
            person.userID = atoi (singleData[i].c_str());
            break;
        case 2:
            person.name = singleData[i];
            break;
        case 3:
            person.surname = singleData[i];
            break;
        case 4:
            person.phoneNumb = singleData[i];
            break;
        case 5:
            person.email = singleData[i];
            break;
        case 6:
            person.adress = singleData[i];
            break;
        }
    }
    return person;
}

int lastID () {
    int lastID = 0;
    string singleContactLine;
    fstream file;
    Contact personalContact;
    file.open ("contacts.txt", ios::in);

    if (file.good() == true) {
        while (getline (file, singleContactLine)) {
            personalContact = splitContactDataLine (singleContactLine);
            lastID = personalContact.id;
        }
    }
    return lastID;
}

void importContacts (vector <Contact> &contactDetails, int loggedID) {
    string singleContactLine;
    fstream file;
    Contact personalContact;
    file.open ("contacts.txt", ios::in);

    if (file.good() == true) {
        while (getline (file, singleContactLine)) {
            personalContact = splitContactDataLine (singleContactLine);
            if (loggedID == personalContact.userID) {
                contactDetails.push_back (personalContact);
            }
        }
    }
}

void showContact (vector <Contact> &contactDetails, int whichOne) {
    cout << "     ***     " << endl;
    cout << "ID: " << contactDetails[whichOne].id << endl;
    cout << contactDetails[whichOne].name << " " << contactDetails[whichOne].surname << endl;
    cout << "nr. telefonu: " << contactDetails[whichOne].phoneNumb <<endl;
    cout << "e-mail: " << contactDetails[whichOne].email <<endl;
    cout << "adres: " << contactDetails[whichOne].adress <<endl;
}

void searchBy (vector <Contact> &contactDetails, char choice) {
    string typeYourSearch;
    int itemsFound = 0;
    int contactsAmmount = contactDetails.size();

    system ("cls");
    cout << "***KSIAZKA ADRESOWA - SZUKANIE KONTAKTOW***" << endl << endl;
    cout << "Podaj szukana fraze: ";
    cin.sync();
    getline (cin, typeYourSearch);

    for (int i = 0; i < contactsAmmount; i++) {
        if (choice == '2') {
            if (typeYourSearch.compare (contactDetails[i].name) == 0) {
                showContact (contactDetails, i);
                itemsFound++;
            }
        } else if (choice == '3') {
            if (typeYourSearch.compare(contactDetails[i].surname) == 0) {
                showContact (contactDetails, i);
                itemsFound++;
            }
        }
    }
    cout << endl << "*** Znaleziono " << itemsFound << " kontaktow ***" << endl;
    system("pause");
}

void showAll (vector <Contact> &contactDetails) {
    int contactsAmmount = contactDetails.size();
    for (int i = 0; i < contactsAmmount; i++) {
        showContact (contactDetails, i);
    }
    cout << endl << "*** Znaleziono " << contactsAmmount << " kontaktow ***" << endl;
    system("pause");
}

string newPersonID () {
    int newID;
    newID = lastID() + 1;

    ostringstream conversionToString;
    conversionToString << newID;
    string personID = conversionToString.str();
    return personID;
}


void addContact2File (string data) {
    fstream file;
    file.open ("contacts.txt",ios::out | ios::app);
    file << data << endl;
    file.close();
}


void addPerson (vector <Contact> &contactDetails, int userID) {
    string separationSign = "|";
    string newPerson = newPersonID () + separationSign;
    string singleData, loggedUserID;
    ostringstream conversionIDToString;
    conversionIDToString << userID;
    loggedUserID = conversionIDToString.str();

    system ("cls");
    cout << "***KSIAZKA ADRESOWA - DODAWANIE KONTAKTU***" << endl << endl;

    for (int i = 0; i <= 5; i++) {
        cin.sync();
        switch (i) {
        case 0:
            newPerson += loggedUserID;
            break;
        case 1:
            cout << "Podaj imie i nacisnij ENTER: ";
            getline (cin, singleData);
            newPerson += singleData;
            break;
        case 2:
            cout << "Podaj nazwisko i nacisnij ENTER: ";
            getline (cin, singleData);
            newPerson += singleData;
            break;

        case 3:
            cout << "Podaj nr telefonu i nacisnij ENTER: ";
            getline (cin, singleData);
            newPerson += singleData;
            break;
        case 4:
            cout << "Podaj e-mail i nacisnij ENTER: ";
            getline (cin, singleData);
            newPerson += singleData;
            break;
        case 5:
            cout << "Podaj adres i nacisnij ENTER: ";
            getline (cin, singleData);
            newPerson += singleData;
            break;
        }
        newPerson += separationSign;
    }
    addContact2File (newPerson);
    Contact newContact = splitContactDataLine (newPerson);
    contactDetails.push_back (newContact);
    cout << endl << "*** Dane zapisane poprawnie ***" << endl << endl;
    system("pause");
}

void saveNewPassword (vector <User> users) {
    string singleLine;
    int linesAmmount = users.size();
    remove ("users.txt");
    for (int i = 0; i < linesAmmount; i++) {
        fstream file;
        file.open ("users.txt",ios::out | ios::app);
        file << users[i].id << "|" << users[i].name << "|" << users[i].password << "|" << endl;
        file.close();
    }
}

void changePassword (int userID) {
    vector <User> users;
    string singleUserLine;
    string newPassword;
    fstream file;
    file.open ("users.txt", ios::in);

    if (file.good() == true) {
        while (getline (file, singleUserLine)) {
            users.push_back (splitDataLine (singleUserLine));
            if (users.back().id == userID) {
                cout << endl << "Podaj nowe haslo: " << endl;
                getline (cin, newPassword);
                users.back().password = newPassword;
                cout << endl << "Haslo zmienione poprawnie." << endl;
                system ("pause");
            }
        }
    }
    file.close();
    saveNewPassword(users);
}

void copyContactsFile (int contactID) {
    string singleUserLine;
    Contact newContacts;
    fstream file, newFile;
    file.open ("contacts.txt", ios::in);
    if (file.good() == true) {
        while (getline (file, singleUserLine)) {
            newContacts = (splitContactDataLine (singleUserLine));
            if ( newContacts.id != contactID ) {
                newFile.open ("newContacts.txt", ios::out | ios::app);
                newFile << singleUserLine << endl;
                newFile.close();
            }
        }
    }
    file.close();
    remove ("contacts.txt");
    rename ("newContacts.txt", "contacts.txt");

}

void deleteContact (vector <Contact> &contactDetails, int userID) {
    int contactID, adressAmount = contactDetails.size();
    char confirm;
    string singleUserLine;
    cout << endl << "Podaj ID adresata, ktorego chcesz usunac:  " << endl;
    cin.sync();
    cin >> contactID;
    cin.sync();
    for (int i = 0; i < adressAmount; i++) {
        if (contactID == contactDetails[i].id) {
            showContact (contactDetails, i);
            cout << endl << "Nacisnij 't' aby potwierdzic usuwanie...";
            cin.sync();
            cin >> confirm;
            cin.sync();
            if (confirm == 't') {
                copyContactsFile(contactID);
                contactDetails.clear();
                importContacts(contactDetails, userID);
                cout << "Adresat usuniety." << endl;
                system ("pause");
                break;
            } else return;
        } else if ( i == adressAmount - 1 ) {
            cout << "Kontakt nie istnieje. " << endl;
            system ("pause");
            return;
        }
    }
}

string convertStructureToSingleLine (Contact editedContact) {
    string singleData, singleLine;
    string separationSign = "|";

    ostringstream convToString, convToString2;
    convToString << editedContact.id;
    singleData = convToString.str();
    singleLine = singleData + separationSign;
    convToString2 << editedContact.userID;
    singleData = convToString2.str();
    singleLine += singleData + separationSign;

    for (int i = 0; i <= 4; i++) {
        switch (i) {
        case 0:
            singleLine += editedContact.name;
            break;
        case 1:
            singleLine += editedContact.surname;
            break;
        case 2:
            singleLine += editedContact.phoneNumb;
            break;
        case 3:
            singleLine += editedContact.email;
            break;
        case 4:
            singleLine += editedContact.adress;
            break;
        }
        singleLine += separationSign;
    }
    return singleLine;
}

void copyEditedContactFile (Contact editedContact) {
    string singleUserLine;
    Contact newContacts;
    fstream file, newFile;
    file.open ("contacts.txt", ios::in);
    if (file.good() == true) {
        while (getline (file, singleUserLine)) {
            newContacts = (splitContactDataLine (singleUserLine));
            if ( newContacts.id == editedContact.id ) {
                newFile.open ("newContacts.txt", ios::out | ios::app);
                newFile << convertStructureToSingleLine (editedContact) << endl;
                newFile.close();
            } else {
                newFile.open ("newContacts.txt", ios::out | ios::app);
                newFile << singleUserLine << endl;
                newFile.close();
            }
        }
    }
    file.close();
    remove ("contacts.txt");
    rename ("newContacts.txt", "contacts.txt");
}

bool checkID (string idFromUser) {
    int idLength = idFromUser.length();
    for (int i = 0; i < idLength; i++) {
        if ( !isdigit (idFromUser[i])) return false;
    }
    return true;
}

void editContact (vector <Contact> &contactDetails, int userID) {

    string typeWantedID = "";
    string newData;
    int contactID = 0;
    int contactsAmmount = contactDetails.size();
    char choice;
    system ("cls");
    cout << "***KSIAZKA ADRESOWA - EDYTOWANIE KONTAKTOW***" << endl << endl;
    cout << "Podaj ID kontaktu, ktory chcesz eydtowac: ";
    cin.sync();
    cin >> typeWantedID;
    cin.sync();
    if (checkID (typeWantedID)) {
        contactID = atoi (typeWantedID.c_str());
        for (int i = 0; i < contactsAmmount; i++) {
            if (contactID == contactDetails[i].id) {
                showContact (contactDetails, i);
                cout << endl << "Jakie dane chcesz edytowac?" << endl;
                cout << endl << "1. imie" << endl;
                cout << "2. nazwisko" << endl;
                cout << "3. numer telefonu" << endl;
                cout << "4. email" << endl;
                cout << "5. adres" << endl;
                cout << "6. powrot do menu" << endl;
                cout << endl << "Wybrano: ";
                cin >> choice;
                cin.sync();

                switch (choice) {

                case '1':
                    cout << endl << "Podaj nowe imie" <<endl;
                    getline (cin, newData);
                    contactDetails[i].name = newData;
                    copyEditedContactFile (contactDetails[i]);
                    contactDetails.clear();
                    importContacts(contactDetails, userID);
                    cout << endl << "Kontakt edytowany pomyslnie." << endl;
                    system("pause");
                    return;

                case '2':
                    cout << endl << "Podaj nowe nazwisko" <<endl;
                    getline (cin, newData);
                    contactDetails[i].surname = newData;
                    copyEditedContactFile (contactDetails[i]);
                    contactDetails.clear();
                    importContacts(contactDetails, userID);
                    cout << endl << "Kontakt edytowany pomyslnie." << endl;
                    system("pause");
                    return;

                case '3':
                    cout << endl << "Podaj nowy nr. telefonu" <<endl;
                    getline (cin, newData);
                    contactDetails[i].phoneNumb = newData;
                    copyEditedContactFile (contactDetails[i]);
                    contactDetails.clear();
                    importContacts(contactDetails, userID);
                    cout << endl << "Kontakt edytowany pomyslnie." << endl;
                    system("pause");
                    return;

                case '4':
                    cout << endl << "Podaj nowy e-mail" <<endl;
                    getline (cin, newData);
                    contactDetails[i].email = newData;
                    copyEditedContactFile (contactDetails[i]);
                    contactDetails.clear();
                    importContacts(contactDetails, userID);
                    cout << endl << "Kontakt edytowany pomyslnie." << endl;
                    system("pause");
                    return;

                case '5':
                    cout << endl << "Podaj nowy adres" <<endl;
                    getline (cin, newData);
                    contactDetails[i].adress = newData;
                    copyEditedContactFile (contactDetails[i]);
                    contactDetails.clear();
                    importContacts(contactDetails, userID);
                    cout << endl << "Kontakt edytowany pomyslnie." << endl;
                    system("pause");
                    return;

                case '6':
                    return;
                }
            } else if (i == contactsAmmount - 1) {
                cout << "Nie znaleziono kontaktu. " << endl;
                system("pause");
            }
        }
    } else {
        cout << "Numer ID powinien zawierac jedynie cyfry" << endl;
        system("pause");
    }
}

void loggedUserMenu(int loggedID) {
    char choice;
    vector <Contact> contactDetails;
    importContacts(contactDetails, loggedID);

    while (true) {
        showMenu();
        choice = getChar();

        switch (choice) {

        case '1':
            addPerson (contactDetails, loggedID);
            break;
        case '2':
            searchBy (contactDetails, choice);
            break;
        case '3':
            searchBy (contactDetails, choice);
            break;
        case '4':
            showAll (contactDetails);
            break;
        case '5':
            deleteContact (contactDetails, loggedID);
            break;
        case '6':
            editContact (contactDetails, loggedID);
            break;
        case '7':
            changePassword (loggedID);
            break;
        case '8':
            return;
        default:
            cout << "Bledny wybor. Sprobuj ponownie" << endl;
            system("pause");
            break;
        }
    }
}

void loginMenu (vector <User> &userDetails) {

    int userID = 0;
    int usersAmmount;
    string userName, userPassword;
    system ("cls");
    if (userDetails.empty()) {
        cout << "Brak uzytkownikow, zarejestruj sie." << endl;
        system ("pause");
    } else {
        usersAmmount = userDetails.size();
        cout << "***KSIAZKA ADRESOWA***" << endl;
        cout << endl << "Podaj nazwe uzytkownika: " << endl;
        cin.sync();
        getline (cin, userName);
        for (int i = 0; i < usersAmmount; i++) {
            if (userName.compare (userDetails[i].name) == 0) {
                cout << "Podaj haslo: " ;
                cin.sync();
                getline (cin, userPassword);
                if (userPassword.compare (userDetails[i].password) == 0) {
                    userID = userDetails[i].id;
                    cout << "Zalogowano poprawinie. " << endl;
                    system ("pause");
                    loggedUserMenu(userID);

                } else cout << endl << "Niepoprawne haslo. " << endl;
                system ("pause");
                break;
            }
            if (i == usersAmmount - 1) {
                cout << endl << "Nie ma takiego uzytkownika." << endl;
                system ("pause");
            }
        }
    }
}

int main() {

    vector <User> userDetails;
    char loginChoice;

    while (true) {
        menu();
        importUsers (userDetails);
        loginChoice = getChar();

        switch (loginChoice) {

        case '1':
            loginMenu(userDetails);
            break;
        case '2':
            addUser (userDetails);
            break;
        case '3':
            exit (0);
            break;

        default:
            cout << "Bledny wybor. Sprobuj ponownie" << endl;
            system("pause");
            break;
        }
    }
}

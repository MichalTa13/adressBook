#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <vector>


using namespace std;


struct contact {
    int id;
    string name, surname, phoneNumb, email, adress;
};


struct contact splitDataLine (string dataLine) {
    string singleData[6];
    int markerPosition = 0;
    struct contact person;

    for (int i = 0; i <= 5; i++) {
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
            person.surname = singleData[i];
            break;
        case 3:
            person.phoneNumb = singleData[i];
            break;
        case 4:
            person.email = singleData[i];
            break;
        case 5:
            person.adress = singleData[i];
            break;
        }

    }
    return person;
}


void importContacts (vector <contact> &contactDetails) {
    string singleContactLine;
    fstream file;
    file.open ("contacts.txt", ios::in);

    if (file.good() == true) {
        while (getline (file, singleContactLine)) {
            contactDetails.push_back (splitDataLine (singleContactLine));
        }
    }
}

string newPersonID (vector <contact> &contactDetails) {
    int newID;

    if (!contactDetails.empty()) {
        newID = contactDetails.back().id + 1;
    } else {
        newID = 1;
    }
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


void addPerson (vector <contact> &contactDetails) {
    string separationSign = "|";
    string newPerson = newPersonID (contactDetails) + separationSign;
    string singleData;

    system ("cls");
    cout << "***KSIAZKA ADRESOWA - DODAWANIE KONTAKTU***" << endl << endl;

    for (int i = 0; i <= 4; i++) {
        cin.sync();
        switch (i) {
        case 0:
            cout << "Podaj imie i nacisnij ENTER: ";
            getline (cin, singleData);
            newPerson += singleData;
            break;
        case 1:
            cout << "Podaj nazwisko i nacisnij ENTER: ";
            getline (cin, singleData);
            newPerson += singleData;
            break;
        case 2:
            cout << "Podaj nr telefonu i nacisnij ENTER: ";
            getline (cin, singleData);
            newPerson += singleData;
            break;
        case 3:
            cout << "Podaj e-mail i nacisnij ENTER: ";
            getline (cin, singleData);
            newPerson += singleData;
            break;
        case 4:
            cout << "Podaj adres i nacisnij ENTER: ";
            getline (cin, singleData);
            newPerson += singleData;
            break;
        }
        newPerson += separationSign;
    }
    addContact2File (newPerson);
    struct contact newContact = splitDataLine (newPerson);
    contactDetails.push_back (newContact);
    cout << endl << "*** Dane zapisane poprawnie ***" << endl << endl;
    system("pause");
}

void showContact (vector <contact> &contactDetails, int whichOne) {
    cout << "     ***     " << endl;
    cout << "ID: " << contactDetails[whichOne].id << endl;
    cout << contactDetails[whichOne].name << " " << contactDetails[whichOne].surname << endl;
    cout << "nr. telefonu: " << contactDetails[whichOne].phoneNumb <<endl;
    cout << "e-mail: " << contactDetails[whichOne].email <<endl;
    cout << "adres: " << contactDetails[whichOne].adress <<endl;
}


void searchBy (vector <contact> &contactDetails, char choice) {
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


void showAll (vector <contact> &contactDetails) {
    int contactsAmmount = contactDetails.size();
    for (int i = 0; i < contactsAmmount; i++) {
        showContact (contactDetails, i);
    }
    cout << endl << "*** Znaleziono " << contactsAmmount << " kontaktow ***" << endl;
    system("pause");
}


bool checkID (string idFromUser) {
    int idLength = idFromUser.length();
    for (int i = 0; i < idLength; i++) {
        if ( !isdigit (idFromUser[i])) return false;
    }
    return true;
}


string convertStructureToSingleLine (vector <contact> &contactDetails, int whichContact) {
    string singleLine;
    string separationSign = "|";

    ostringstream convToString;
    convToString << contactDetails[whichContact].id;
    singleLine = convToString.str() + separationSign;


    for (int i = 0; i <= 4; i++) {
        switch (i) {
        case 0:
            singleLine += contactDetails[whichContact].name;
            break;
        case 1:
            singleLine += contactDetails[whichContact].surname;
            break;
        case 2:
            singleLine += contactDetails[whichContact].phoneNumb;
            break;
        case 3:
            singleLine += contactDetails[whichContact].email;
            break;
        case 4:
            singleLine += contactDetails[whichContact].adress;
            break;
        }
        singleLine += separationSign;
    }
    return singleLine;
}

void createNewFile (vector <contact> &contactDetails) {
    int howManyLines = contactDetails.size();
    string singleLine;

    for (int i = 0; i < howManyLines; i++) {
        singleLine = convertStructureToSingleLine (contactDetails, i);
        addContact2File (singleLine);
    }
}


void deleteContact (vector <contact> &contactDetails) {
    int contactID;
    int contactsAmmount = contactDetails.size();
    char confirm;
    string typeWantedID = "";

    system ("cls");
    cout << "***KSIAZKA ADRESOWA - USUWANIE KONTAKTOW***" << endl << endl;
    cout << "Podaj ID kontaktu, ktory chcesz usunac: ";
    cin.sync();
    cin >> typeWantedID;

    if (checkID (typeWantedID)) {                     // program dziwnie siê zachowywa³ przy przypadkowym wpisaniu liter lub innych znaków
        contactID = atoi (typeWantedID.c_str());
        for (int i = 0; i < contactsAmmount; i++) {
            if (contactID == contactDetails[i].id) {
                showContact (contactDetails, i);
                cout << endl << "Nacisnij 't' aby potwierdzic usuwanie...";
                cin >> confirm;
                if (confirm == 't') {
                    contactDetails.erase(contactDetails.begin()+i);
                    remove ("contacts.txt");
                    createNewFile(contactDetails);
                    cout << endl << "Kontakt usuniety pomyslnie." << endl;
                    system("pause");
                    break;
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


void editContact (vector <contact> &contactDetails) {
    string typeWantedID = "";
    string newData;
    int contactID;
    int contactsAmmount = contactDetails.size();
    char choice;

    system ("cls");
    cout << "***KSIAZKA ADRESOWA - EDYTOWANIE KONTAKTOW***" << endl << endl;
    cout << "Podaj ID kontaktu, ktory chcesz eydtowac: ";
    cin.sync();
    cin >> typeWantedID;

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
                    remove ("contacts.txt");
                    createNewFile(contactDetails);
                    cout << endl << "Kontakt edytowany pomyslnie." << endl;
                    system("pause");
                    return;

                case '2':
                    cout << endl << "Podaj nowe nazwisko" <<endl;
                    getline (cin, newData);
                    contactDetails[i].surname = newData;
                    remove ("contacts.txt");
                    createNewFile(contactDetails);
                    cout << endl << "Kontakt edytowany pomyslnie." << endl;
                    system("pause");
                    return;

                case '3':
                    cout << endl << "Podaj nowy nr. telefonu" <<endl;
                    getline (cin, newData);
                    contactDetails[i].phoneNumb = newData;
                    remove ("contacts.txt");
                    createNewFile(contactDetails);
                    cout << endl << "Kontakt edytowany pomyslnie." << endl;
                    system("pause");
                    return;

                case '4':
                    cout << endl << "Podaj nowy email" <<endl;
                    getline (cin, newData);
                    contactDetails[i].email = newData;
                    remove ("contacts.txt");
                    createNewFile(contactDetails);
                    cout << endl << "Kontakt edytowany pomyslnie." << endl;
                    system("pause");
                    return;

                case '5':
                    cout << endl << "Podaj nowy adres" <<endl;
                    getline (cin, newData);
                    contactDetails[i].adress = newData;
                    remove ("contacts.txt");
                    createNewFile(contactDetails);
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


int main() {
    vector <contact> contactDetails;
    char choice;

    importContacts(contactDetails);

    while (true) {
        system ("cls");
        cout << "***KSIAZKA ADRESOWA***" << endl;
        cout << endl << "1. Dodaj adresata" << endl;
        cout << "2. Wyszukaj po imieniu" << endl;
        cout << "3. Wyszukaj po nazwisku" << endl;
        cout << "4. Wyswietl wszystkich adresatow" << endl;
        cout << "5. Usun adresata" << endl;
        cout << "6. Edytuj adresata" << endl;
        cout << "7. Zakoncz program" << endl;
        cout << endl << "Wybrano: ";
        cin >> choice;

        switch (choice) {

        case '1':
            addPerson (contactDetails);
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
            deleteContact (contactDetails);
            break;
        case '6':
            editContact (contactDetails);
            break;
        case '7':
            exit (0);
        }
    }
}

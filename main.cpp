#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <limits>
#include <cstdlib>
#include <windows.h>
#include <sstream>
#include <cstdio>
#include <set>
#include<algorithm>

using namespace std;

struct User {
    int id = 0;
    string username = "", password = "", loggedInUsername;
};

struct Person {
    int id = 0;
    int userID;
    string firstName = "", lastName = "", phoneNumber = "", email = "", address = "";
};

string readLine() {
    string input;
    cin.sync();
    getline(cin, input);
    return input;
}

int getLoggedInUserID(const string& loggedInUsername, const vector<User>& users) {
    for (const User& user : users) {
        if (user.username == loggedInUsername) {
            return user.id;
        }
    }
    return -1;
}

string readLine() {
    string input;
    cin.sync();
    getline(cin, input);
    return input;
}

int getLoggedInUserID(const string& loggedInUsername, const vector<User>& users) {
    for (const User& user : users) {
        if (user.username == loggedInUsername) {
            return user.id;
        }
    }
    return -1;
}

void readUserFromFile(vector<User>& users) {
    ifstream file("users.txt", ios::in);

    if (!file.is_open()) {
        // cerr << "Nie udalo sie otworzyc pliku: users.txt" << endl;
        file.open("users.txt", ios::out);
        file.close();
        return;
    }

    string line;
    while (getline(file, line)) {
        User user;
        istringstream iss(line);
        char delimiter = '|';

        iss >> user.id >> delimiter;
        getline(iss, user.username, delimiter);
        getline(iss, user.password, delimiter);

        users.push_back(user);
    }
    file.close();
}

void saveUserToFile(const vector<User>& users) {
    ofstream file("users.txt");

    if (!file.is_open()) {
        cerr << "Nie udalo sie otworzyc pliku: users.txt" << endl;
        return;
    }

    for (const User& user : users) {
        file << user.id << '|' << user.username << '|' << user.password << endl;
    }
    file.close();
}

void registerUser(vector<User>& users) {
    User newUser;

    cout << "Podaj nazwe uzytkownika: ";
    newUser.username = readLine();

    for (const User& user : users) {
        if (user.username == newUser.username) {
            cout << "Uzytkownik o podanej nazwie juz istnieje. Wybierz inna nazwe uzytkownika." << endl;
            cout << endl;
            Sleep(3000);
            return;
        }
    }

    cout << "Podaj haslo: ";
    newUser.password = readLine();

    newUser.id = users.empty() ? 1 : users.back().id + 1;

    users.push_back(newUser);
    saveUserToFile(users);

    cout << endl;
    cout << "Uzytkownik zostal pomyslnie zarejestrowany" << endl;
    cout << endl;
    Sleep(1000);
}

void changeUserPassword(vector<User>& users) {

    string username;
    cout << "Podaj nazwe uzytkownika: ";
    username = readLine();

    bool userFound = false;
    for (User& user : users) {
        if (user.username == username) {
            cout << "Podaj nowe haslo: ";
            user.password = readLine();
            userFound = true;
            break;
        }
    }

    if (userFound) {
        saveUserToFile(users);
        cout << "Haslo zostalo zmienione." << endl;
        Sleep(1000);
    } else {
        cout << "Uzytkownik o podanej nazwie nie zostal znaleziony." << endl;
    }
}

void userLogin(vector<User>& users, string& loggedInUsername, bool& isLoggedIn) {
    User user;

    int attempts = 0;
    while (attempts < 3) {

        cout << endl;
        cout << "Podaj nazwe uzytkownika: ";
        user.username = readLine();

        cout << "Podaj haslo: ";
        user.password = readLine();

        bool loggedIn = false;
        for (const User& existingUser : users) {
            if (existingUser.username == user.username && existingUser.password == user.password) {
                loggedIn = true;
                loggedInUsername = existingUser.username;
                break;
            }
        }

        if (loggedIn) {
            isLoggedIn = true;
            return;
        } else {
            cout << endl;
            cout << "Niepoprawna nazwa uzytkownika lub haslo." << endl;
            attempts++;
            if (attempts < 3) {
                cout << endl;
                cout << "Pozostalo prob: " << 3 - attempts << endl;
                Sleep(1000);
            } else {
                cout << endl;
                cout << "Przekroczono limit prob wpisania hasla. Program zostanie wylaczony." << endl;
                Sleep(1000);
                exit(0);
            }
        }
    }
}

void loggedOut(bool isLoggedIn) {
    if (isLoggedIn) {
        cout << "Wylogowano." << endl;
        cout << endl;
        Sleep(1000);
    }
}

int readChoice() {
    int choice;
    cout << endl;
    cout << "Twoj wybor: ";
    cin >> choice;
    cout << endl;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Nieprawidlowy wybor. Sprobuj ponownie." << endl;
        Sleep(1000);
    }
    return choice;
}

int loginMenu() {
    system("cls");
    cout << ">> MENU GLOWNE <<" << endl;
    cout << "----------------------" << endl;
    cout << "1. Logowanie" << endl;
    cout << "2. Rejestracja" << endl;
    cout << "3. Koniec programu" << endl;
    cout << "----------------------" << endl;
    cout << endl;

    return readChoice();
}

int userMenu() {
    system("cls");
    cout << ">> Menu uzytkownika <<" << endl;
    cout << "----------------------------------------" << endl;
    cout << "1. Dodaj nowa osobe " << endl;
    cout << "2. Wyszukaj po imieniu" << endl;
    cout << "3. Wyszukaj po nazwisku" << endl;
    cout << "4. Wyswietl wszystkich adresatow" << endl;
    cout << "5. Usun adresata" << endl;
    cout << "6. Edytuj adresata" << endl;
    cout << "----------------------------------------" << endl;
    cout << "7. Zmien haslo " << endl;
    cout << "8. Wyloguj sie " << endl;
    cout << "----------------------------------------" << endl;

    return readChoice();
}

void editPersonMenu() {

    cout << ">> EDYCJA DANYCH ADRESATA <<" << endl;
    cout << "----------------------------------------" << endl;
    cout << "1. Imie" << endl;
    cout << "2. Nazwisko" << endl;
    cout << "3. Numer telefonu" << endl;
    cout << "4. Email" << endl;
    cout << "5. Adres" << endl;
    cout << "6. Powrot do menu glownego" << endl;
    cout << endl;
}
void readDataFromFile(vector<Person>& people) {
    people.clear();

    ifstream file("address_book.txt", ios::in);
    if (!file.is_open()) {
        //cerr << "Nie udalo sie otworzyc pliku: address_book.txt" << endl;
        file.open("address_book.txt", ios::out);
        file.close();
        return;
    }

    string line;
    while (getline(file, line)) {
        Person person;
        stringstream ss(line);
        string field;

        getline(ss, field, '|');
        person.id = atoi(field.c_str());

        getline(ss, field, '|');
        person.userID = atoi(field.c_str());

        getline(ss, field, '|');
        person.firstName = field;

        getline(ss, field, '|');
        person.lastName = field;

        getline(ss, field, '|');
        person.phoneNumber = field;

        getline(ss, field, '|');
        person.email = field;

        getline(ss, field);
        person.address = field;

        people.push_back(person);
    }
    file.close();
}

void saveToFile(const vector<Person>& people) {
    ofstream file("address_book.txt", ios::app);

    if (file.is_open()) {
        const Person& person = people.back();
        {
            file << person.id << '|'
                 << person.userID << '|'
                 << person.firstName << '|'
                 << person.lastName << '|'
                 << person.phoneNumber << '|'
                 << person.email << '|'
                 << person.address << endl;
        }
    } else {
        cerr << "Nie udalo sie otworzyc pliku: " << "address_book.txt" << endl;
    }
    file.close();
}

void saveChangesToFile(const vector<Person>& people) {
    ofstream file("temp_address_book.txt");
    if (file.is_open()) {
        for (const Person& person : people) {
            file << person.id << '|'
                 << person.userID << '|'
                 << person.firstName << '|'
                 << person.lastName << '|'
                 << person.phoneNumber << '|'
                 << person.email << '|'
                 << person.address << endl;
        }
        file.close();

        remove("address_book.txt");
        rename("temp_address_book.txt", "address_book.txt");
    } else {
        cerr << "Nie udalo sie otworzyc pliku." << endl;
    }
}

int getLastPersonID(const vector<Person>& people) {
    int maxPersonID = 0;
    for (const Person& existingPerson : people) {
        if (existingPerson.id > maxPersonID) {
            maxPersonID = existingPerson.id;
        }
    }
    return maxPersonID;
}

void addPerson(vector<Person>& people, const vector<User>& users, const string& loggedInUsername) {
    system("cls");
    Person person;
    cout << ">> NOWY ADRESAT <<" << endl;
    cout << "------------------" << endl;
    cout << "Podaj imie: ";
    person.firstName = readLine();

    cout << "Podaj nazwisko: ";
    person.lastName = readLine();

    cout << "Podaj numer telefonu: ";
    person.phoneNumber = readLine();

    cout << "Podaj e-mail: ";
    person.email = readLine();

    cout << "Podaj adres: ";
    person.address= readLine();

    readDataFromFile(people);

    int lastPersonID = getLastPersonID(people);
    person.id = lastPersonID + 1;
    person.userID = getLoggedInUserID(loggedInUsername, users);

    cout << endl;
    people.push_back(person);

    cout << "Osoba zostala poprawnie dodana do ksiazki adresowej." << endl;
    cout << endl;
    Sleep(1000);

    saveToFile(people);
}

void displayPerson(const Person& person) {
    cout << "ID:                " << person.id << endl;
    cout << "Imie:              " << person.firstName << endl;
    cout << "Nazwisko:          " << person.lastName << endl;
    cout << "Numer telefonu:    " << person.phoneNumber << endl;
    cout << "Adres e-mail:      " << person.email << endl;
    cout << "Adres:             " << person.address << endl;
}

void displayAllPeople(const vector<Person>& people, const vector<User>& users, const string& loggedInUsername) {
    system("cls");
    bool foundPeople = false;
    bool isFirstPerson = true;

    for (const Person& person : people) {
        if (person.userID == getLoggedInUserID(loggedInUsername, users)) {
            if (isFirstPerson) {
                cout << " >>LISTA WSZYSTKICH TWOICH ADRESATOW << " << endl;
                isFirstPerson = false;
            } else {
                cout << "----------------------------------------" << endl;
            }
            displayPerson(person);
            cout << endl;
            foundPeople = true;
        }
    }

    if (!foundPeople) {
        cout << "Ksiazka adresowa jest pusta." << endl;
    }

    cout << endl;
    system("pause");
}

void searchByFirstName(const vector<Person>& people, const vector<User>& users, const string& loggedInUsername) {
    system("cls");
    bool nameFound = false;
    string firstName;

    cout << ">> WYSZUKUJESZ PO IMIENIU <<" <<endl;
    cout << "----------------------------" <<endl;
    cout << "Podaj imie: ";
    firstName = readLine();
    cout << endl;

    if (people.empty()) {
        cout << "Ksiazka adresowa pusta." << endl;
        cout << endl;
        system("pause");
        return;
    }

    for (const Person& person : people) {
        if (person.userID == getLoggedInUserID(loggedInUsername, users) && person.firstName == firstName) {
            displayPerson(person);
            cout << endl;
            nameFound = true;
        }
    }

    if (!nameFound) {
        cout << "Nie znaleziono osob o podanym imieniu." << endl;
        cout << endl;
    }
    system("pause");
}

void searchByLastName(const vector<Person>& people, const vector<User>& users, const string& loggedInUsername) {
    system("cls");
    bool nameFound = false;
    string lastName;
    cout << " >> WYSZUKUJESZ PO NAZWISKU <<" <<endl;
    cout << "------------------------------" <<endl;
    cout << "Podaj nazwisko: ";
    lastName = readLine();
    cout << endl;

    if (people.empty()) {
        cout << "Ksiazka adresowa pusta." << endl;
        cout << endl;
        system("pause");
        return;
    }
    for (const Person& person : people) {
        if (person.userID == getLoggedInUserID(loggedInUsername, users) && person.lastName == lastName) {
            displayPerson(person);
            cout << endl;
            nameFound = true;
        }
    }

    if (!nameFound) {
        cout << "Nie znaleziono osob o podanym nazwisku." << endl;
        cout << endl;
    }
    system("pause");
}

void displayEditableIDs(const vector<Person>& people, const vector<User>& users, const string& loggedInUsername) {

    set<int> uniqueIDs;

    for (const Person& person : people) {
        if (person.userID == getLoggedInUserID(loggedInUsername, users)) {
            uniqueIDs.insert(person.id);
        }
    }

    cout << "Nr ID Twoich adresatow: ";
    for (int id : uniqueIDs) {
        cout << id << " ";
    }
    cout << endl << endl;
}



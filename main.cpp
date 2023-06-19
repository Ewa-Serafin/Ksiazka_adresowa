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

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

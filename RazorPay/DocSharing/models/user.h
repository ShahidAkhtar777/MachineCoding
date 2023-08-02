#pragma once
#include <string>
using namespace std;

class User {
public:
    User() : username("") {}

    User(string username): username(username) {}

    string getUsername(){
        return username;
    }

private:
    string username;
};

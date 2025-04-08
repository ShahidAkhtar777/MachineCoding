#pragma once
#include <iostream>
#include <string>
using namespace std;

class User {
public:
    User() = default;

    User(int userId, string username): userId(userId), username(username) {}

    string getUsername() { return username; }

    int getUserId() { return userId; }

private:
    int userId;
    string username;
};

#pragma once
#include <unordered_map>
#include "../models/user.h"

class UserRepository {
public:
    void createUser(string username) {
        users[username] = User(username);
    }

    User* getUser(string username) {
        if (users.count(username)) {
            return &users[username];
        }
        return nullptr;
    }

private:
    unordered_map<string, User> users;
};





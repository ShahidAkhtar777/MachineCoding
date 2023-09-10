#pragma once

#include <unordered_map>
#include <string>
#include "../models/User.h"
using namespace std;

class UserRepository
{
public:
    void addUser(string name, string email) {
        int userId = getNextUserId();
        User *newUser = new User(userId, name, email);
        usersById[userId] = *newUser;
    }

    User *getUserById(int userId)
    {
        auto it = usersById.find(userId);
        return (it != usersById.end()) ? &it->second : nullptr;
    }

    int getNextUserId() {
        static int userIdCounter = 1;
        return userIdCounter++;
    }

private:
    unordered_map<int, User> usersById;
};

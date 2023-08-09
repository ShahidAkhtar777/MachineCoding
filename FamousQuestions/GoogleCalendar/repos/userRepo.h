#pragma once
#include <unordered_map>
#include "../models/user.h"
#include <iostream>
using namespace std;

class UserRepository
{
public:
    User* addUser(string username)
    {
        int newUserId = getNextUserId();
        User *u = new User(newUserId, username);
        users[newUserId] = *u;
        return u;
    }

    User* getUserById(int userId)
    {
        auto userIt = users.find(userId);
        if (userIt != users.end())
        {
            return &userIt->second;
        }
        return nullptr;
    }

private:
    int getNextUserId()
    {
        static int userIdCounter = 1;
        return userIdCounter++;
    }

    unordered_map<int, User> users;
};

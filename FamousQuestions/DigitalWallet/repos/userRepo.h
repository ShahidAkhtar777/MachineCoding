#pragma once
#include <iostream>
#include <unordered_map>
#include "../models/user.h"
using namespace std;

class UserRepository {
private:
    unordered_map<int, User> userMap; // userId to User

public:
    User addUser(int userId, string name){
        User *u = new User(userId, name);
        userMap[userId] = *u;
        return *u;
    }
    
    void deleteUser(int userId){
        userMap.erase(userId);
    }

    User* getUserById(int userId){
        if(userMap.find(userId)!=userMap.end()){
            return &userMap[userId];
        }
        else
            return NULL;   
    }   
};

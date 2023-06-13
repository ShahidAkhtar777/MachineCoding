#pragma once
#include "../models/user.h"
#include<bits/stdc++.h>
using namespace std;

class UserRepo {
private:
    vector<User> users;
    int userIdCounter = 0;

public:
    User* addUser(string userName, string password, string email) {
        for(auto &u: users) {
            if(u.getEmail() == email){
                return NULL;
            }
        }

        User *user = new User(userIdCounter, userName, email, password);
        users.push_back(*user);
        userIdCounter +=1; 
        return user;
    }

    User* getUserById(int user_id) {
       for(auto& u: users) {
            if(u.getUserId() == user_id){
                return &u;
            }
        }
        return NULL;
    }

    User* getUserByEmail(string email){
        for(auto &u: users){
            if(u.getEmail() == email){
                return &u;
            }
        }
        return NULL;
    }
};
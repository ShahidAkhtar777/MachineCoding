#pragma once
#include<bits/stdc++.h>
#include "../models/user.h"
using namespace std;

class SessionRepo {
private:
    vector<int> activeUsers;
public:
    void addToSession(int userId){
        activeUsers.push_back(userId);
    }

    void removeFromSession(int userId){
        auto it = activeUsers.begin();
   
        while (it != activeUsers.end()){
            if (*it == userId){
                it = activeUsers.erase(it);
            }
            else{
                it++;
            }
        }
    }

    bool isActiveSession(int userId){
        auto it = activeUsers.begin();
   
        while (it != activeUsers.end()){
            if (*it == userId){
                return true;
            }
            else{
                it++;
            }
        }
        return false;
    }
};
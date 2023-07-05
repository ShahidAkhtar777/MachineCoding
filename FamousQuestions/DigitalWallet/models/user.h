#pragma once
#include <iostream>
#include <string>
using namespace std;

class User{
private:
    int userId;
    string name;
public:
    User() = default;

    User(int userId, string name):userId(userId), name(name){}

    int getUserId(){
        return userId;
    }
    
    string getName(){
        return name;
    }

    int setUserId(int userId){
        this->userId = userId;
    }

    string setName(string name){
        this->name = name;
    }
};

#pragma once
#include<bits/stdc++.h>
using namespace std;

class User{
private:
    int userId;
    string name;
    string email;
    string password;
public:
    User(int userId, string name, string email, string password): userId(userId), name(name), email(email),
    password(password){}

    int getUserId(){
        return userId;
    }

    string getName(){
        return name;
    }

    string getEmail(){
        return email;
    }

    string getPassword(){
        return password;
    }
};
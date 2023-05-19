#ifndef USERSERVICE_H
#define USERSERVICE_H


#include "../repo/userRepo.h"
#include "../repo/sessionRepo.h"
#include<bits/stdc++.h>
using namespace std;

class UserService {
private:
    UserRepo* userRepo;
    SessionRepo* sessionRepo;

public:
    UserService(UserRepo* userRepo, SessionRepo* sessionRepo) {
        this->userRepo = userRepo;
        this->sessionRepo = sessionRepo;
    }

    User* signup(string userName, string password, string email) {
        User* existingUser = userRepo->getUserByEmail(email);
        if (existingUser != NULL) {
            cout<<"User already exists";
            return NULL;
        }
        User* newUser = userRepo->addUser(userName, password, email);
        cout<<userName<<" SignUp Successful. Your userId is: "<<newUser->getUserId()<<endl;
        return newUser;
    }

    void login(string email, string password) {
        User* user = userRepo->getUserByEmail(email);
        if (user == NULL || user->getPassword() != password) {
            cout<<"Invalid username or password";
        }

        cout<<user->getName()<<" having userId: "<<user->getUserId()<<" Logged in Successfully"<<endl;
        sessionRepo->addToSession(user->getUserId());
    }

    void logout(int userId){
        User* user = userRepo->getUserById(userId);
        if (user == NULL) {
            cout<<"Invalid userId";
        }

        cout<<user->getName()<<"having userId: "<<user->getUserId()<<" Logged out Successfully"<<endl;
        sessionRepo->removeFromSession(user->getUserId());
    }

    bool isUserLoggedIn(int userId) {
        return sessionRepo->isActiveSession(userId);
    }

    User* getUserByUserId(int userId){
        User* user = userRepo->getUserById(userId);
        if(user==NULL){
            cout<<"User not exists"<<endl;
            return NULL;
        }
        return user;
    }
};

#endif
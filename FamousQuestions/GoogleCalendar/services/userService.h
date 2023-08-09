#pragma once
#include "../repos/userRepo.h"
#include <iostream>
using namespace std;

class UserService {
public:
    UserService(UserRepository* userRepository) : userRepository(userRepository) {}

    User* createUser(string username) {
        return userRepository->addUser(username);
    }

    User* getUserById(int userId) {
        return userRepository->getUserById(userId);
    }

private:
    UserRepository* userRepository;
};

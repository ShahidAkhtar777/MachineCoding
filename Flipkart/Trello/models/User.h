#pragma once
#include <string>

class User {
public:
    User(int userId, string name, string email): userId(userId), name(name), email(email) {} 

    int getUserId() { return userId; }
    string getName() { return name; }
    string getEmail() { return email; }

private:
    int userId;
    string name;
    string email;
};


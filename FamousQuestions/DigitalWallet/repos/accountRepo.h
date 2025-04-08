#pragma once
#include <iostream>
#include <unordered_map>
#include "../models/account.h"
using namespace std;

class AccountRepository {
private:
    unordered_map<int, Account> accountMap; // userId to Account

public:
    Account createWallet(int userId, double balance){
        Account *acc = new Account(userId, balance);
        accountMap[userId] = *acc;
        return *acc;
    }

    void deleteWallet(int userId){
        accountMap.erase(userId);
    }

    Account* getAccountByUserId(int userId){
        if(accountMap.find(userId)!=accountMap.end())
            return &accountMap[userId];
        else
            return NULL;
    }

    unordered_map<int, Account> getAccountMap(){
        return accountMap;
    }


};

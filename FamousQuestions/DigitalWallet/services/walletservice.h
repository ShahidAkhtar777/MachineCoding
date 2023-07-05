#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <cmath>
#include "../repos/accountRepo.h"
#include "../repos/userRepo.h"
using namespace std;

class WalletService {
private:
    AccountRepository *acc;
    UserRepository *user;
public:
    WalletService(AccountRepository *acc, UserRepository *user) {
        this->acc = acc;
        this->user = user;
    }

    void createWallet(int userId, string name, double amount) {
        User *usr = user->getUserById(userId);

        if(usr==NULL){
            user->addUser(userId, name);
            cout<<"User created"<<endl;
        }

        Account *ac = acc->getAccountByUserId(userId);
        if(ac!=NULL)
            cout<<"Account already exists for this userId with AccNo: "<<ac->getAccountNumber()<<endl;
        else{
            Account account = acc->createWallet(userId, amount);
            cout << "Account created for userId " << userId << " with account number " << account.getAccountNumber() << endl;
        }
    }

    void transferAmount(int fromUserId, int toUserId, double transferAmount) {
        if (!validate(fromUserId, toUserId, transferAmount)) {
            return;
        }

        Account *fromAccount = acc->getAccountByUserId(fromUserId);
        Account *toAccount = acc->getAccountByUserId(toUserId);
        if (fromAccount->getBalance() < transferAmount) {
            cout << "Insufficient Balance" << endl;
            return;
        }

        Transaction tran(fromUserId, toUserId, transferAmount, time(0));
        fromAccount->setBalance(fromAccount->getBalance() - transferAmount);
        toAccount->setBalance(toAccount->getBalance() + transferAmount);
        fromAccount->addTransaction(tran);
        toAccount->addTransaction(tran);
        cout << "Transfer Successful" << endl;
    }

    bool validate(int fromUserId, int toUserId, double transferAmount) {
        if (fromUserId == toUserId) {
            cout << "Sender and Receiver cannot be the same." << endl;
            return false;
        }
        if (transferAmount < 0.0001) {
            cout << "Amount too low" << endl;
            return false;
        }
        if (acc->getAccountByUserId(fromUserId)==NULL) {
            cout << "Invalid Sender account number" << endl;
            return false;
        }
        if (acc->getAccountByUserId(toUserId)==NULL) {
            cout << "Invalid Receiver account number" << endl;
            return false;
        }
        return true;
    }

    void printStatements(int userId) {
        Account *userAcccount = acc->getAccountByUserId(userId);
        if (userAcccount==NULL) {
            cout << "No wallet exists for this user" << endl;
            return;
        }
        cout << "Summary for account number: " << userAcccount->getAccountNumber() << endl;
        cout << "Current Balance: " << userAcccount->getBalance() << endl;
        cout << "Your Transaction History" << endl;
        for (auto tran : userAcccount->getTransactions()) {
            time_t date = tran.getDate();
            cout << "SenderId: "<< tran.getsenderId() <<" ReceiverId: "<< tran.getReceiverId() << " Amount: "<< tran.getAmount() << " Date: "<< ctime(&date) << endl;
        }
    }

    void overview() {
        for (auto entry : acc->getAccountMap()) {
            int userId = entry.first;
            Account *userAcc = acc->getAccountByUserId(userId);
            cout << "Balance for Account No " << entry.second.getAccountNumber() << ": " << entry.second.getBalance() << endl;
        }
    }
};

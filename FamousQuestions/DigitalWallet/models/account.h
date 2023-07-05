#pragma once
#include <iostream>
#include <string>
#include <cmath>
#include <set>
#include "transaction.h"

struct TransactionComparator {
    bool operator()(Transaction a, Transaction b) {
        return a.getDate() < b.getDate();
    }
};

class Account {
private:
    int accountNumber;
    int userId;
    double balance;
    set<Transaction, TransactionComparator> transactions;

public:
    Account() = default;

    Account(int userId, double balance) {
        this->accountNumber = getNextAccountNumber();
        this->userId = userId;
        this->balance = balance;
    }

    int getNextAccountNumber() {
        static int counter = 1000;
        return ++counter;
    }

    string toString() {
        return "Account [accountNumber=" + to_string(accountNumber) + ", userId=" + to_string(userId) + ", balance=" + to_string(balance)
            + ", transactions=" + to_string(transactions.size()) + "]";
    }

    int getAccountNumber() {
        return accountNumber;
    }

    void setAccountNumber(int accountNumber) {
        this->accountNumber = accountNumber;
    }

    int getUserId() {
        return userId;
    }

    void setUserId(int userId) {
        this->userId = userId;
    }

    double getBalance() {
        return balance;
    }

    void setBalance(double balance) {
        this->balance = balance;
    }

    set<Transaction, TransactionComparator> getTransactions() {
        return transactions;
    }

    void setTransactions(set<Transaction, TransactionComparator> transactions) {
        this->transactions = transactions;
    }

    void addTransaction(Transaction transaction){
        this->transactions.insert(transaction);
    }
};

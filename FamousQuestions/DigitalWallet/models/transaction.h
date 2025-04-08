#pragma once
#include <iostream>
#include <string>
#include <cmath>
#include <ctime>
using namespace std;

class Transaction {
private:
    int transactionId;
    int senderId;
    int receiverId;
    double amount;
    time_t date;

public:
    Transaction(int senderId, int receiverId, double amount, time_t date) {
        this->senderId = senderId;
        this->receiverId = receiverId;
        this->amount = amount;
        this->date = date;
        this->transactionId = getNextTransactionId();
    }

    int getNextTransactionId(){
        static int transactionId = 100;
        return ++transactionId;
    }

    string toString() {
        return "Transaction [senderId=" + to_string(senderId) + ", receiverId=" + to_string(receiverId) + ", amount=" + to_string(amount)
            + ", date=" + to_string(date) + "]";
    }

    int getsenderId() {
        return senderId;
    }

    void setsenderId(int senderId) {
        this->senderId = senderId;
    }

    int getReceiverId() {
        return receiverId;
    }

    void setReceiverId(int receiverId) {
        this->receiverId = receiverId;
    }

    double getAmount() {
        return amount;
    }

    void setAmount(double amount) {
        this->amount = amount;
    }

    time_t getDate() {
        return date;
    }

    void setDate(time_t date) {
        this->date = date;
    }

    int getTransactionId(){
        return transactionId;
    }

    void updateTransactionId(int tId){
        this->transactionId = tId;
    }

};
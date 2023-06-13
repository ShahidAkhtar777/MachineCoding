#pragma once
#include<bits/stdc++.h>
#include<ctime>
#include <iomanip>
#include "user.h"
#include "cart.h"
using namespace std;

class Order{
private:
    int orderId;
    int totalCost;
    vector<CartItem> cartItems;
    string shippingAddress;
    std::time_t orderedOn;
public:
    Order(int orderId, User user, int totalCost, string shippingAddress, vector<CartItem> cartItems): orderId(orderId), cartItems(cartItems),
     totalCost(totalCost),shippingAddress(shippingAddress), orderedOn(std::time(0)) {}

    int getOrderId(){
        return orderId;
    }

    int getTotalCost(){
        return totalCost;
    }

    string getShippingAddress(){
        return shippingAddress;
    }

    std::time_t getOrderedOn() {
        return orderedOn;
    }

    vector<CartItem> getCartItems(){
        return cartItems;
    }
};


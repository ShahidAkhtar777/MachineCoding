#ifndef ORDERREPO_H
#define ORDERREPO_H

#include "../models/order.h"
#include "../models/cart.h"
#include<bits/stdc++.h>
using namespace std;

class OrderRepo {
private:
    unordered_map<int, vector<Order>> orders; // userid - [] orders
    int orderIdCounter = 0; 
public:
    Order* createOrder(User user, int totalCost, string shippingAddress, vector<CartItem> cartItems) {
        Order *orderObj = new Order(orderIdCounter, user, totalCost, shippingAddress, cartItems);

        int userId = user.getUserId();
        orders[userId].push_back(*orderObj);
        return orderObj;
    }

    vector<Order> getOrderHistoryByUserId(int user_id) {
        if (orders.find(user_id) != orders.end()) {
            return orders[user_id];
        }
        return vector<Order>{};
    }
};

#endif
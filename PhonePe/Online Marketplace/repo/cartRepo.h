#pragma once
#include "../models/cart.h"
#include "../models/user.h"
#include "productRepo.h"
#include<bits/stdc++.h>
using namespace std;

class CartRepo {
private:
    unordered_map<int, vector<CartItem>> userCart; // userid - cart
public:
    void addProductToCart(int userId, int productId, int quantity) {
        if(quantity<0){
            return;
        }

        if(userCart.find(userId) != userCart.end()){
            vector<CartItem>& cart = userCart[userId];
            for(int i=0;i<cart.size();i++){
                if(cart[i].getProductId() == productId){
                    cart[i].setQuantity(cart[i].getQuantity()+quantity);
                    return;
                }
            }
        }

        CartItem cartObject = CartItem(productId, quantity);
        userCart[userId].push_back(cartObject);
    }

    vector<CartItem> getCartItemsByUserId(int userId){
        if(userCart.find(userId) != userCart.end()){
            return userCart[userId];
        }
        return vector<CartItem> {};
    }

    void clearCart(int userId){
        userCart[userId] = vector<CartItem>{};
    }

    void removeCartItem(int userId, int productId){
        if(userCart.find(userId) == userCart.end()){
            cout<<"User does not have any CartItem present";
        }
        vector<CartItem> activeCart = userCart[userId];

        for(int i=0;i<activeCart.size();i++){
            if(activeCart[i].getProductId() == productId){
                activeCart.erase(activeCart.begin()+i);
            }else if(i == activeCart.size()){
                cout<<"Product not present in the cart";
            }
        }
        cout<<"Product removed from the cart";
        return;
    }

};

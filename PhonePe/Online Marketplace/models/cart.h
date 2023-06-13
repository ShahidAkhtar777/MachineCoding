#pragma once
#include <bits/stdc++.h>
#include "product.h"
#include "user.h"
using namespace std;

class CartItem{
private:
    int productId;
    int quantity;
public:
    CartItem(int productId, int quantity): productId(productId), quantity(quantity) {}

    int getProductId(){
        return productId;
    }

    int getQuantity(){
        return quantity;
    }

    void setQuantity(int quantity){
        this->quantity = quantity;
    }
};


#pragma once
#include<bits/stdc++.h>
#include<ctime>
using namespace std;

class Product{
private:
    int productId;
    string name;
    double price;
    string description;
    int inventory;
public:

    Product(int productId, string name, double price, string description, int inventory){
        this->productId = productId;
        this->name = name;
        this->price = price;
        this->description = description;
        this->inventory = inventory;
    }

    int getProductId(){
        return productId;
    }

    string getName(){
        return name;
    }

    int getPrice(){
        return price;
    }

    string getDescription(){
        return description;
    }

    int getInventory(){
        return inventory;
    }

    void setInventory(int inventory){
        this->inventory = inventory;
    }
};

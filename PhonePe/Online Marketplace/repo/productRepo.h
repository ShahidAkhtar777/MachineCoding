#pragma once
#include<bits/stdc++.h>
#include "../models/product.h"
using namespace std;

class ProductRepo {
    vector<Product> products;
    int productIdCounter = 0;

public:
    Product* addProduct(string name, string desc, double price, int inventory) {
        Product *productObj = new Product(productIdCounter, name, price, desc, inventory);
        products.push_back(*productObj);
        productIdCounter += 1;
        return productObj;
    }

    Product* getProductById(int product_id) {
        for(auto& product: products) {
            if(product.getProductId() == product_id){
                return &product;
            }
        }
        return NULL;
    }

    Product* getProductByName(string productName) {
        for(auto &product: products) {
            if(product.getName() == productName){
                return &product;
            }
        }
        return NULL;
    }


    void updateProduct(Product newProduct, Product oldProduct){
        for(int i=0;i<products.size();i++){
            if(products[i].getProductId() == oldProduct.getProductId()){
                products[i] = newProduct;
            }
            if(i==products.size()){
                addProduct(newProduct.getName(), newProduct.getDescription(), newProduct.getPrice(), newProduct.getInventory());
                return;
            }
        }
    }

    vector<Product> getAllProducts(){
        return products;
    }
};
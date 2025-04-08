#pragma once
#include "../repo/productRepo.h"
#include<bits/stdc++.h>
using namespace std;

class ProductService {
private:
    ProductRepo* productRepo;

public:
    ProductService(ProductRepo* productRepo) {
        this->productRepo = productRepo;
    }

    void addProducts(string name, string desc, double price, int inventory) {
        Product* product = productRepo->getProductByName(name);
        if (product != nullptr) {
            cout<<"We already have a product with a similar name";
        }

        Product* newProduct = productRepo->addProduct(name, desc, price, inventory);
        cout << "Added new product with id " << newProduct->getProductId() << endl;
    }

    Product* getProduct(int productId) {
        Product* product = productRepo->getProductById(productId);
        if (product == NULL) {
            cout << "No product found with the given product id" << endl;
        }
        return product;
    }

    void displayAllProducts(){
        vector<Product> productCatalogue = productRepo->getAllProducts();;
        for(int i=0;i<productCatalogue.size();i++){
            Product p = productCatalogue[i];
            cout<<"Product "<<p.getName()<<" stock: "<< p.getInventory()<<endl;
        }
        return;
    }

    void updateProduct(Product* newProduct) {
        Product* oldProduct = productRepo->getProductById(newProduct->getProductId());
        if (oldProduct == nullptr) {
            cout<<"Product not found";
        }
        productRepo->updateProduct(*oldProduct, *newProduct);
    }
};
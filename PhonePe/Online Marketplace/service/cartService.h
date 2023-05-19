#ifndef CARTSERVICE_H
#define CARTSERVICE_H

#include "../repo/cartRepo.h"
#include "userService.h"
#include "productService.h"
#include<bits/stdc++.h>
using namespace std;

class CartService {
private:
    CartRepo* cartRepo;
    UserService* userService;
    ProductService* productService;

public:
    CartService(CartRepo* cartRepo, UserService* userService, ProductService* productService) {
        this->cartRepo = cartRepo;
        this->userService = userService;
        this->productService = productService;
    }

    void addToCart(int userId, int productId, int quantity) {
        User* user = userService->getUserByUserId(userId);
        if (user == NULL) {
            cout<<"You need to log in first to add to cart";
            return;
        }

        if (productService->getProduct(productId) == NULL) {
            cout<<"Product not found with product id " + to_string(productId);
            return;
        }

        if (quantity <= 0) {
            cout<<"Quantity must be a positive integer";
            return;
        }

        cartRepo->addProductToCart(user->getUserId(), productId, quantity);
    }

    vector<CartItem> getCartItems(int userId) {
        User* user = userService->getUserByUserId(userId);
        if (user == NULL) {
            cout<<"You need to log in first to fetch cart items";
            return vector<CartItem> {};
        }

        vector<CartItem> cartItems = cartRepo->getCartItemsByUserId(userId);
        return cartItems;
    }

    void clearCart(int userId) {
        User* user = userService->getUserByUserId(userId);
        if (user == NULL) {
            throw std::runtime_error("You need to log in first to fetch cart items");
        }

        cartRepo->clearCart(user->getUserId());
        cout << "Cart cleared for userId: " << user->getUserId() << endl;
    }

    void removeItemFromCart(int userId, int productId) {
        cartRepo->removeCartItem(userId, productId);
    }
};

#endif
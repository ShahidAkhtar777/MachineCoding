#pragma once
#include "../repo/orderRepo.h"
#include "userService.h"
#include "productService.h"
#include "cartService.h"
#include<bits/stdc++.h>
using namespace std;

class OrderService {
private:
    OrderRepo* orderRepo;
    UserService* userService;
    CartService* cartService;
    ProductService* productService;

public:
    OrderService(OrderRepo* orderRepo, UserService* userService, CartService* cartService, ProductService* productService) {
        this->orderRepo = orderRepo;
        this->userService = userService;
        this->cartService = cartService;
        this->productService = productService;
    }

    void checkout(int userId, string shippingAddress) {
        User* user = userService->getUserByUserId(userId);
        if (user == NULL) {
            cout<<"No user exits"<<endl;
            return;
        }

        if(!userService->isUserLoggedIn(userId)){
            cout<<"User not Logged In"<<endl;
            return;
        }

        vector<CartItem> items;
        double totalCost = 0;
        vector<CartItem> cartItems = cartService->getCartItems(userId);
        if (cartItems.size()==0) {
            cout<<"Cart is empty for the userId:"<<userId<<endl;
            return;
        }

        for (auto item : cartItems) {
            int productId = item.getProductId();
            Product* product = productService->getProduct(productId);

            if (product->getInventory() < item.getQuantity()) {
                cout<<"Product Inv: "<<product->getInventory()<<endl;
                cout<<"Item Quantity: "<<item.getQuantity()<<endl;
                cout << "The product " << product->getName() << " does not have enough inventory. Skipping this item" <<endl;
                continue;
            }

            items.push_back(item);
            product->setInventory(product->getInventory() - item.getQuantity());
            totalCost += product->getPrice() * item.getQuantity();
            productService->updateProduct(product);
        }

        if (items.empty()) {
            cout << "No items to order" << endl;
            return;
        }

        Order* order = orderRepo->createOrder(*user, totalCost, shippingAddress, items);
        cartService->clearCart(userId);

        // Call email service
        cout << "Thank you for your order !!" << endl;
        cout<<user->getName()<<" Checkout Successful"<<endl;
        cout << "Ordered on: " << order->getOrderedOn() << ", Order Details: cost: " << totalCost << ", shipping address: " << shippingAddress << endl;
        cout << user->getName()<<" Order Items:" << endl;
        for (auto item : items) {
            cout << productService->getProduct(item.getProductId())->getName() << "->" << item.getQuantity() << endl;
        }
        
    }

    void getOrderHistory(int userId) {
        User* user = userService->getUserByUserId(userId);
        if (user == NULL) {
            cout<<"You need to log in first to get order history"<<endl;
            return;
        }

        vector<Order> orderHistory = orderRepo->getOrderHistoryByUserId(user->getUserId());
        if (orderHistory.empty()) {
            cout << "No items ordered yet!" <<endl;
            return;
        }

        cout << user->getName() <<" Order History --------" << endl;
        for (auto order : orderHistory) {
            cout << "Ordered on: " << order.getOrderedOn() << ", TotalCost: " << order.getTotalCost() << ", shipping address: " << order.getShippingAddress() << endl;
            cout << "Ordered Items:" << endl;
            for (CartItem item : order.getCartItems()) {
                std::cout << productService->getProduct(item.getProductId())->getName() << " " << item.getQuantity() << endl;
            }
        }
    }
};
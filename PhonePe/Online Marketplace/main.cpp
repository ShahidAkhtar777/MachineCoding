#include <iostream>
#include "service/cartService.h"
#include "service/orderService.h"
#include "service/productService.h"
#include "service/userService.h"

int main() {
    string userName1 = "Rohan";
    string passWord1 = "password1";
    string email1 = "rohan@gmail.com";

    string userName2 = "Mohan";
    string password2 = "password2";
    string email2 = "mohan@gmail.com";

    UserRepo userRepo;
    SessionRepo sessionRepo;
    UserService userService(&userRepo, &sessionRepo);

    ProductRepo productRepo;
    ProductService productService(&productRepo);

    CartRepo cartRepo;
    CartService cartService(&cartRepo, &userService, &productService);

    OrderRepo orderRepo;
    OrderService orderService(&orderRepo, &userService, &cartService, &productService);

    // 1 - Signup
    // 2 - Login
    // 3 - Create Products
    // 4 - Add Product to user Cart
    // 5 - User Checkout
    // 6 - Get user order history


    // User1 signUp and Login
    User *user1 = userService.signup(userName1, passWord1, email1);
    userService.login(email1, passWord1);
    cout<<endl;

    // User2 signUp and Login
    User *user2 = userService.signup(userName2, password2, email2);
    userService.login(email2, password2);
    cout<<endl;

    // Add products
    productService.addProducts("Shirt", "hawaian shirt", 600, 4); // product 0
    productService.addProducts("Pant", "hot pant", 500, 10);  // product 1
    productService.addProducts("Trouser", "comfortable fit", 600, 8); // product 2
    productService.addProducts("Sun Glasses", "Anti Glare", 100, 20); // product 3
    cout<<endl;

    // User1 adds in cart
    cartService.addToCart(0, 0, 2); // userId, ProductId, quantity
    cartService.addToCart(0, 1, 3);
    cartService.addToCart(0, 2, 4);
    cartService.addToCart(0, 3, 4);

    // User1 totalCost = 600*2 + 500*3 + 600*4 + 100*4

    // User2 adds in cart
    cartService.addToCart(1, 0, 2);
    cartService.addToCart(1, 1, 5);
    cartService.addToCart(1, 2, 2);
    cartService.addToCart(1, 3, 4);

    // cout << productService.getProduct(cartService.getCartItems(user1->getUserId())[0].getProductId())->getName() << " " << cartService.getCartItems(0)[0].getQuantity() << endl;

    // User1 checkout's
    cout<<"Checking out------"<<endl;
    orderService.checkout(0, "Ranchi Main Road"); // userId with address

    cout<<endl;
    // User1 orderHistory
    orderService.getOrderHistory(user1->getUserId());
    cout<<endl;

    // Now check user1 cart
    vector<CartItem> c = cartService.getCartItems(user1->getUserId());
    cout<<user1->getName()<<" has now "<< c.size() << " number of items in his cart";
    cout<<endl;

    // Show all left product inventory
    cout<<"Stock Left::"<<endl;
    productService.displayAllProducts();

    cout<<endl;
    // User2 checkout's
    orderService.checkout(1, "Near Gandhi Chowk"); // userId with address
    cout<<endl;

    // User2 orderHistory
    orderService.getOrderHistory(user2->getUserId());
    cout<<endl;

    // Show all left product inventory
     cout<<"Stock Left::"<<endl;
    productService.displayAllProducts();
   
    return 0;
}

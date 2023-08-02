#include <iostream>
using namespace std;

class restaurantEmployee {
    public : 
        virtual void washDishes() {}
        virtual void serveCustomers() {}
        virtual void cookFood() {}
};

class waiter : public restaurantEmployee {
    public : 
        void washDished() {
            /* NOT MY JOB */
        }

        void cookFood() {
            /* NOT MY JOB */
        }
};


int main() {}
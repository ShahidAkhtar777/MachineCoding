#include <iostream> 
using namespace std;

class marker {
    public : 
        marker(int price, string name): price(price), name(name) {}

        int getprice() {
            return price;
        }
        
    private: 
        int price;
        string name;
};

class invoice {

    public :
        invoice(marker mk, int qu) : mk(mk), qu(qu) {}

        int calTotal() {
            return mk.getprice()*qu;
        }

        void printInvoice() {}

        void savetoDB() {}

    private: 
        marker mk;
        int qu; 
};

/*
1. calTotal logic can change
2. printing logic can change
3. storing logic can change

*/

/*
    The SRP suggests that a class should have a single responsibility,
    but in this case, the invoice class is responsible for both
    handling business logic (calculating the total price) and
    handling presentation logic (printing the invoice) and
    data persistence (saving to the database).
*/

int main() {

}

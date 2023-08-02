
/*  
    SINGLE RESPONSIBILITY :-
    EVERY CLASS SHOULD HAVE ONLY ONE RESPONSIBILITY
    IT DOES NOT MEAN EACH CLASS WILL HAVE ONLY ONE FUNCTION
*/

#include <iostream> 
using namespace std;

class marker {
    private:
        int price;
        string name;
    public:
        marker(int price, string name): price(price), name(name) {}

        int getprice(){
            return price;
        }

        string getname() {
            return name;
        }
};

class invoicePrice {
    private:
        marker mk;
        int qty;
    public:
        invoicePrice(marker mk, int qty): mk(mk), qty(qty) {}

        int calTotal() {
            return mk.getprice() * qty;
        }
};

class invoiceDao {
    private:
        invoicePrice inP;
    public:
        invoiceDao(invoicePrice inP): inP(inP) {}

        void savetoDB() {}
};

class invoicePrint {
    private : 
        invoicePrice inP;
    public : 
        invoicePrint(invoicePrice inP): inP(inP) {}

        void print() {}
};

/*
1. calTotal logic can change
2. printing logic can change
3. storing logic can change
*/

int main() {

}

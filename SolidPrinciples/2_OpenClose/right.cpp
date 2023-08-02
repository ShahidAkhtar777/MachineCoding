/*  
    Open Closed Principle:-
    Open for EXTENSION but Closed for MODIFICATIONS
*/

#include <iostream> 
using namespace std;

class invoiceDao {
    public : 
        virtual void save() {}    
};

class invoiceDaoDB : public invoiceDao {
    public : 
        void save() {
            /* Save to DB */
        }
};

class invoiceDaoFile : public invoiceDao {
    public : 
        void save() {
            /* Save to FILE */
        }
};

/*
    this is the correct way to write extensible code
*/

int main() {}
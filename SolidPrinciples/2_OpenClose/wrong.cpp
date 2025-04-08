#include <iostream> 
using namespace std;

class invoiceDao {
    public : 
        void saveToDB() {}
        void saveToFile() {}
    
};


/*
if we only had one function savetodb but now we are adding a new function
savetoFile to the same class which is present in live code then it can cause problems, 
therefore this code is wrong.
*/


int main() {}
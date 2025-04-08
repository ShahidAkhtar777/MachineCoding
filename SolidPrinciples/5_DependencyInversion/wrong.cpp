#include <iostream>
using namespace std;

class keyboard {

};

class wiredKeyboard : public keyboard {

};

class wirelessKeyboard : public keyboard {

};

class macbook {
public:
    wiredKeyboard* k;
};


int main() {
    // Incorrect: Direct dependency on concrete class wiredKeyboard
    // This should be avoided to follow the Dependency Inversion Principle
    wiredKeyboard wk;

    macbook m;
    m.k = &wk;
    // Now, we can use the wiredKeyboard object to perform keyboard operations, which is not ideal.
    // In the correct implementation, we should use the Keyboard interface.

    return 0;
}

/*
 classes should depend on interfaces rather than concrete classes 
*/

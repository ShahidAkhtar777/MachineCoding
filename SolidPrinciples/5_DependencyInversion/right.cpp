#include <iostream>
using namespace std;

class Keyboard {
public:
    virtual void pressKey() = 0;
};

class WiredKeyboard : public Keyboard {
public:
    void pressKey() override {
        cout << "Wired Keyboard: Key pressed." << endl;
    }
};

class WirelessKeyboard : public Keyboard {
public:
    void pressKey() override {
        cout << "Wireless Keyboard: Key pressed." << endl;
    }
};

class MacBook {
public:
    MacBook(Keyboard* k) : keyboard(k) {}

    void useKeyboard() {
        keyboard->pressKey();
    }

private:
    Keyboard* keyboard;
};

int main() {
    // Instead of creating a WiredKeyboard directly, we create a pointer to Keyboard (an interface)
    Keyboard* wiredKb = new WiredKeyboard();

    MacBook macbook(wiredKb);
    macbook.useKeyboard();

    // Clean up the allocated memory
    delete wiredKb;

    return 0;
}

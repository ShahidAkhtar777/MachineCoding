#include <iostream>
using namespace std;

class bike {
    public : 
    
    virtual bool isegineOn() = 0;
    virtual int getSpeed() = 0;

    protected : 
        bool engineOn;
        int speed;
};

class motorBike : public bike {
    public : 
        bool isengineOn() {
            return true;
        }

        int getSpeed() {
            return speed;
        }
};

class cycle : public bike {
    public : 
        bool isengineOn() {
            // ERROR FUNCTIONALITY BREAKS AS CYCLE DOES NOT HAVE ANY ENGINE 
        }

        int getSpeed() {
            return speed;
        }
};

int main() {}

/*
    subclass should extend the capability of parent class not narrow it down
*/
/*
    The Liskov Substitution Principle states that if a class is a subclass of another class,
    it should be able to substitute its superclass in any context without causing unexpected
    behavior or breaking the code.
*/


// 1. Using Separate Base Classes:

// Instead of trying to represent both motorbikes and cycles with a single bike base class,
// we can create separate base classes for motorbikes and cycles. This ensures that each 
// subclass only has the methods relevant to its type:

#include <iostream>
using namespace std;

class MotorBike {
public:
    virtual bool isEngineOn() = 0;
    virtual int getSpeed() = 0;
};

class Cycle {
public:
    virtual int getSpeed() = 0;
};

class MotorizedCycle : public MotorBike {
public:
    bool isEngineOn() override {
        return true;
    }

    int getSpeed() override {
        return speed;
    }

protected:
    int speed;
};

class NonMotorizedCycle : public Cycle {
public:
    int getSpeed() override {
        return speed;
    }

protected:
    int speed;
};

int main() {
    MotorizedCycle mBike;
    NonMotorizedCycle myCycle;

    cout << "Motorbike Engine On: " << mBike.isEngineOn() << endl;
    cout << "Cycle Speed: " << myCycle.getSpeed() << endl;

    return 0;
}

// 2. Using Optional Engine for Cycles:

// Another approach is to have a conditional engine for cycles, but still, differentiate 
// between the two types:


#include <iostream>
using namespace std;

class bike {
public:
    virtual bool isEngineOn() = 0;
    virtual int getSpeed() = 0;
};

class motorBike : public bike {
public:
    bool isEngineOn() override {
        return true;
    }

    int getSpeed() override {
        return speed;
    }

protected:
    int speed;
};

class cycle : public bike {
public:
    cycle(bool hasEngine) : hasEngine(hasEngine) {}

    bool isEngineOn() override {
        return hasEngine;
    }

    int getSpeed() override {
        return speed;
    }

protected:
    bool hasEngine;
    int speed;
};

int main() {
    motorBike mBike;
    cycle myCycle(true); // Cycle with an engine

    cout << "Motorbike Engine On: " << mBike.isEngineOn() << endl;
    cout << "Cycle Engine On: " << myCycle.isEngineOn() << endl;

    return 0;
}

// These approaches demonstrate that there are multiple ways to organize the class
// hierarchy to follow LSP, and the choice depends on the specific requirements and
// design considerations of the system. The key is to ensure that the subclasses extend
// the capabilities of their base class appropriately and don't break the expected behavior
// when used in place of their superclass.
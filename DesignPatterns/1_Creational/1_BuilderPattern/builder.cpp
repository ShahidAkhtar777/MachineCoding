#include <iostream>
using namespace std;

class IAircraft {
public:
    virtual ~IAircraft() {}
    virtual void fly() = 0; // Pure virtual function
};

class Boeing747 : public IAircraft {
public:
    void fly() override {
        cout << "Boeing 747 is flying!" << endl;
    }
};

class F16 : public IAircraft {
public:
    void fly() override {
        cout << "F-16 is flying!" << endl;
    }
};

class AircraftBuilder {
public:
    virtual void buildEngine() {
        cout << "Building engine" << endl;
    }
    virtual void buildCockpit() {
        cout << "Building cockpit" << endl;
    }
    virtual void buildWings() {
        cout << "Building wings" << endl;
    }

    virtual void buildBathrooms() {
        cout << "Building Bathroom" << endl;
    }

    virtual IAircraft* getResult() = 0;
};

class Boeing747Builder : public AircraftBuilder {
    Boeing747* boeing747;

public:
    Boeing747Builder() : boeing747(new Boeing747()) { }

    void buildCockpit() override {
        AircraftBuilder::buildCockpit();
        cout << "Building Boeing 747 cockpit" << endl;
    }
    void buildEngine() override {
        AircraftBuilder::buildEngine();
        cout << "Building Boeing 747 engine" << endl;
    }
    void buildBathrooms() {
        cout << "Building Boeing 747 bathrooms" << endl;
    }
    void buildWings() override {
        AircraftBuilder::buildWings();
        cout << "Building Boeing 747 wings" << endl;
    }

    IAircraft* getResult() override {
        cout << "Returning Boeing 747" << endl;
        return boeing747;
    }
};

class F16Builder : public AircraftBuilder {
    F16* f16;

public:
    void buildEngine() override {
        AircraftBuilder::buildEngine();
        cout << "Building F-16 engine" << endl;
    }
    void buildWings() override {
        AircraftBuilder::buildWings();
        cout << "Building F-16 wings" << endl;
    }
    void buildCockpit() override {
        f16 = new F16();
        AircraftBuilder::buildCockpit();
        cout << "Building F-16 cockpit" << endl;
    }

    IAircraft* getResult() override {
        cout << "Returning F-16" << endl;
        return f16;
    }
};

// Directing contruction of Aircraft in steps
class Director {
    AircraftBuilder* aircraftBuilder;

public:
    Director(AircraftBuilder* builder) : aircraftBuilder(builder) {}

    void construct(bool isPassenger) {
        aircraftBuilder->buildCockpit();
        aircraftBuilder->buildEngine();
        aircraftBuilder->buildWings();
        if (isPassenger)
            aircraftBuilder->buildBathrooms();
    }
};

class Client {
public:
    void main() {
        Boeing747Builder boeing747Builder;
        Director director(&boeing747Builder);
        director.construct(true);
        IAircraft* boeing747 = boeing747Builder.getResult();
        boeing747->fly();
    }
};

int main() {
    Client client;
    client.main();
    return 0;
}

/*
In the provided code, the Builder Pattern is working as follows:

1. **IAircraft Interface**: Defines the common interface for all aircraft, which includes the `fly` method.

2. **Boeing747 and F16 Classes**: Concrete implementations of the `IAircraft` interface, representing different types of aircraft.

3. **AircraftBuilder Abstract Class**: Defines the interface for building an aircraft. It includes methods like `buildEngine`, `buildCockpit`, and `buildWings`.

4. **Boeing747Builder and F16Builder Classes**: Concrete implementations of `AircraftBuilder`. They implement the methods to build specific aircraft components and return the corresponding aircraft instances.

5. **Director Class**: Manages the construction process. It takes an instance of `AircraftBuilder` and calls the builder's methods in a specific order to create the desired aircraft. The `construct` method includes optional steps, like building bathrooms for the Boeing 747.

6. **Client Class**: This is where the pattern is demonstrated. It creates an instance of `Boeing747Builder` and passes it to the `Director`. The `Director` constructs a Boeing 747 based on the steps defined in the builder. Finally, the client gets the constructed aircraft using `getResult` and calls its `fly` method.

In this code, the Builder Pattern separates the construction process of complex aircraft objects from their representation. The `Director` class abstracts the construction steps and coordinates them through a `Builder`. This structure allows for flexibility in creating different types of aircraft while maintaining a clean separation between the construction process and the final product.
*/

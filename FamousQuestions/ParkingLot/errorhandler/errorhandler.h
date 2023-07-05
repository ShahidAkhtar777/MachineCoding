class InvalidInputException : public exception {
public:
    InvalidInputException(const string& message) : message(message) {}
    const char* what() const noexcept override {
        return "Invalid Input!";
    }
};

class ParkingLotFullException : public exception {
public:
    const char* what() const noexcept override {
        return "Parking lot is full.";
    }
};

class VehicleNotFoundException : public exception {
public:
    const char* what() const noexcept override {
        return "Vehicle not found in the parking lot.";
    }
};


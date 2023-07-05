#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

enum class VehicleType { CAR, TRUCK, BIKE };

class Vehicle {
private:
    VehicleType type;
    string licensePlate;
    string color;

public:
    Vehicle(VehicleType type, const string& licensePlate, const string& color)
        : type(type), licensePlate(licensePlate), color(color) {}

    VehicleType getType() const {
        return type;
    }

    string getLicensePlate() const {
        return licensePlate;
    }

    string getColor() const {
        return color;
    }
};

class Slot {
private:
    int floorNumber;
    int slotNumber;
    bool occupied;
    VehicleType vehicleType;
    Vehicle* vehicle;

public:
    Slot(int floorNumber, int slotNumber, VehicleType vehicleType)
        : floorNumber(floorNumber), slotNumber(slotNumber), vehicleType(vehicleType), occupied(false) {}

    bool isOccupied() const {
        return occupied;
    }

    VehicleType getVehicleType() const {
        return vehicleType;
    }

    Vehicle* getVehicle() const {
        return vehicle;
    }

    void parkVehicle(VehicleType type, Vehicle* vehicle) {
        occupied = true;
        vehicleType = type;
        this->vehicle = vehicle;
    }

    void vacateSlot() {
        occupied = false;
        vehicleType = VehicleType::CAR;  
    }
};

class Floor {
private:
    int floorNumber;
    unordered_map<int, Slot> slots;

public:
    Floor(int floorNumber) : floorNumber(floorNumber) {}

    int getFloorNumber() const {
        return floorNumber;
    }

    int getTotalSlots() const {
        return slots.size();
    }

    void addSlot(int slotNumber, VehicleType vehicleType = VehicleType::CAR) {
        slots.emplace(slotNumber, Slot(floorNumber, slotNumber, vehicleType));
    }

    int getFreeSlotsCount(VehicleType vehicleType) const {
        int count = 0;
        for (const auto& slot : slots) {
            if (!slot.second.isOccupied() && slot.second.getVehicleType() == vehicleType) {
                count++;
            }
        }
        return count;
    }

    vector<int> getFreeSlots(VehicleType vehicleType) const {
        vector<int> freeSlots;
        for (const auto& slot : slots) {
            if (!slot.second.isOccupied() && slot.second.getVehicleType() == vehicleType) {
                freeSlots.push_back(slot.first);
            }
        }
        return freeSlots;
    }

    vector<int> getOccupiedSlots(VehicleType vehicleType) const {
        vector<int> occupiedSlots;
        for (const auto& slot : slots) {
            if (slot.second.isOccupied() && slot.second.getVehicleType() == vehicleType) {
                occupiedSlots.push_back(slot.first);
            }
        }
        return occupiedSlots;
    }

    bool parkVehicle(VehicleType vehicleType, Vehicle* vehicle, string& ticket) {
        vector<int> freeSlots = getFreeSlots(vehicleType);
        if (!freeSlots.empty()) {
            int slotNumber = freeSlots[0];
            auto& slot = slots[slotNumber];
            slot.parkVehicle(vehicleType, vehicle);
            ticket = "PR" + vehicle->getLicensePlate() + "_" + to_string(floorNumber) + "_" + to_string(slotNumber);
            return true;
        }
        return false;
    }

    bool unparkVehicle(const string& ticket) {
        size_t pos = ticket.find('_');
        if (pos != string::npos && pos < ticket.length() - 1) {
            int floorNumber = stoi(ticket.substr(2, pos - 2));
            int slotNumber = stoi(ticket.substr(pos + 1));
            auto it = slots.find(slotNumber);
            if (it != slots.end() && it->second.getVehicle()->getLicensePlate() == ticket.substr(2)) {
                it->second.vacateSlot();
                return true;
            }
        }
        return false;
    }
};

class ParkingLot {
private:
    string name;
    unordered_map<int, Floor> floors;

public:
    ParkingLot(const string& name) : name(name) {}

    const string& getName() const {
        return name;
    }

    int getTotalFloors() const {
        return floors.size();
    }

    int getTotalSlots() const {
        int totalSlots = 0;
        for (const auto& floor : floors) {
            totalSlots += floor.second.getTotalSlots();
        }
        return totalSlots;
    }

    int getFreeSlotsCount(VehicleType vehicleType) const {
        int count = 0;
        for (const auto& floor : floors) {
            count += floor.second.getFreeSlotsCount(vehicleType);
        }
        return count;
    }

    vector<int> getFreeSlots(VehicleType vehicleType) const {
        vector<int> freeSlots;
        for (const auto& floor : floors) {
            vector<int> floorFreeSlots = floor.second.getFreeSlots(vehicleType);
            freeSlots.insert(freeSlots.end(), floorFreeSlots.begin(), floorFreeSlots.end());
        }
        return freeSlots;
    }

    vector<int> getOccupiedSlots(VehicleType vehicleType) const {
        vector<int> occupiedSlots;
        for (const auto& floor : floors) {
            vector<int> floorOccupiedSlots = floor.second.getOccupiedSlots(vehicleType);
            occupiedSlots.insert(occupiedSlots.end(), floorOccupiedSlots.begin(), floorOccupiedSlots.end());
        }
        return occupiedSlots;
    }

    bool parkVehicle(VehicleType vehicleType, Vehicle* vehicle, string& ticket) {
        for (auto& floor : floors) {
            if (floor.second.parkVehicle(vehicleType, vehicle, ticket)) {
                return true;
            }
        }
        return false;
    }

    bool unparkVehicle(const string& ticket) {
        for (auto& floor : floors) {
            if (floor.second.unparkVehicle(ticket)) {
                return true;
            }
        }
        return false;
    }

    Floor& addFloor(int floorNumber) {
        return floors.emplace(floorNumber, Floor(floorNumber)).first->second;
    }

    const Floor* getFloor(int floorNumber) const {
        auto it = floors.find(floorNumber);
        return (it != floors.end()) ? &(it->second) : nullptr;
    }
};

void processCommand(const string& command, ParkingLot& parking_lot) {
    // Parse the command and perform the corresponding action
    if (command == "total_floors") {
        cout << "Total Floors: " << parking_lot.getTotalFloors() << endl;
    } else if (command == "total_slots") {
        cout << "Total Slots: " << parking_lot.getTotalSlots() << endl;
    } else if (command == "free_slots") {
        cout << "Free Slots: " << parking_lot.getFreeSlotsCount(VehicleType::CAR) << endl;
    } else if (command == "free_bike_slots") {
        cout << "Free Bike Slots: " << parking_lot.getFreeSlotsCount(VehicleType::BIKE) << endl;
    } else if (command == "free_truck_slots") {
        cout << "Free Truck Slots: " << parking_lot.getFreeSlotsCount(VehicleType::TRUCK) << endl;
    } else if (command == "occupancy") {
        cout << "Occupancy: " << (parking_lot.getTotalSlots() - parking_lot.getFreeSlotsCount(VehicleType::CAR)) << endl;
    } else if (command == "occupancy_bike") {
        cout << "Occupancy (Bike): " << (parking_lot.getTotalSlots() - parking_lot.getFreeSlotsCount(VehicleType::BIKE)) << endl;
    } else if (command == "occupancy_truck") {
        cout << "Occupancy (Truck): " << (parking_lot.getTotalSlots() - parking_lot.getFreeSlotsCount(VehicleType::TRUCK)) << endl;
    } else if (command == "add_floor") {
        int floorNumber;
        cout << "Enter floor number: ";
        cin >> floorNumber;
        parking_lot.addFloor(floorNumber);
        cout << "Floor " << floorNumber << " added." << endl;
    } else if (command == "park") {
        int type;
        string licensePlate, color;
        cout << "Enter vehicle type (0 - Car, 1 - Truck, 2 - Bike): ";
        cin >> type;
        cout << "Enter license plate: ";
        cin >> licensePlate;
        cout << "Enter color: ";
        cin >> color;

        VehicleType vehicleType;
        switch (type) {
            case 0:
                vehicleType = VehicleType::CAR;
                break;
            case 1:
                vehicleType = VehicleType::TRUCK;
                break;
            case 2:
                vehicleType = VehicleType::BIKE;
                break;
            default:
                cout << "Invalid vehicle type." << endl;
                return;
        }

        Vehicle vehicle(vehicleType, licensePlate, color);
        string ticket;
        if (parking_lot.parkVehicle(vehicleType, &vehicle, ticket)) {
            cout << "Vehicle parked successfully." << endl;
            cout << "Ticket: " << ticket << endl;
        } else {
            cout << "No available slots for parking." << endl;
        }
    } else if (command == "unpark") {
        string ticket;
        cout << "Enter ticket: ";
        cin >> ticket;

        if (parking_lot.unparkVehicle(ticket)) {
            cout << "Vehicle unparked successfully." << endl;
        } else {
            cout << "Invalid ticket or vehicle not found." << endl;
        }
    } else if (command == "exit") {
        cout << "Exiting..." << endl;
        exit(0);
    } else {
        cout << "Invalid command." << endl;
    }
}

int main() {
    ParkingLot parking_lot("My Parking Lot");

    // Add some floors and slots to the parking lot
    Floor& floor1 = parking_lot.addFloor(1);
    floor1.addSlot(1, VehicleType::CAR);
    floor1.addSlot(2, VehicleType::BIKE);
    floor1.addSlot(3, VehicleType::BIKE);

    Floor& floor2 = parking_lot.addFloor(2);
    floor2.addSlot(1, VehicleType::TRUCK);
    floor2.addSlot(2, VehicleType::BIKE);
    floor2.addSlot(3, VehicleType::CAR);
    floor2.addSlot(4, VehicleType::CAR);

    while (true) {
        cout << "Enter a command (type 'help' for available commands): ";
        string command;
        cin >> command;
        processCommand(command, parking_lot);
        cout << endl;
    }

    return 0;
}

#pragma once
#include "vehicle.h"
#include <string>

class Slot {
private:
    int slotNo;
    VehicleType type;
    bool isOccupied;
    Vehicle* parkedVehicle;

public:
    Slot(int slotNo, VehicleType type, bool isOccupied): slotNo(slotNo), type(type), isOccupied(isOccupied) {}

    Slot(int SlotNo, VehicleType type): slotNo(slotNo), type(type) {}

    VehicleType getType(){
        return type;
    }

    int getSlotNo(){
        return slotNo;
    }

    bool getIsOccupied(){
        return isOccupied;
    }

    Vehicle* getParkedVehicle() const {
        return parkedVehicle;
    }

    void parkVehicle(Vehicle* vehicle) {
        parkedVehicle = vehicle;
        isOccupied = true;
    }

    void unparkVehicle() {
        parkedVehicle = NULL;
        isOccupied = false;
    }
};
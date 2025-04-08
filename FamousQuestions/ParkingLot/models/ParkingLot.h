#pragma once
#include "slot.h"

class ParkingLot {
private:
    int parkingLotId;
    int noOfFloors;
    int slotsPerFloor;

public:
    ParkingLot(int parkingLotId, int noOfFloors, int slotsPerFloor): parkingLotId(parkingLotId), noOfFloors(noOfFloors), slotsPerFloor(slotsPerFloor){}

    int getParkingLotId(){
        return parkingLotId;
    }

    int getSlotsPerFloor(){
        return slotsPerFloor;
    }

    int getNoOfFloors(){
        return noOfFloors;
    }
};
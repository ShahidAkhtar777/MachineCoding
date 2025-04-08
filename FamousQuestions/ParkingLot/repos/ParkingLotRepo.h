#pragma once
#include <bits/stdc++.h>
#include "../models/ParkingLot.h"
#include "FloorRepo.h"
using namespace std;

class ParkingLotRepository {
private:
    vector<ParkingLot> parkingLots;
public:
    void AddParkingLot(int parkingLotId, int totalFloors, int totalSlots) {
        ParkingLot p = ParkingLot(parkingLotId, totalFloors, totalSlots); 
        parkingLots.push_back(p);
    }

    void RemoveParkingLot(int ParkingLotNo){
        for(int i=0;i<parkingLots.size();i++){
            if(parkingLots[i].getParkingLotId() == ParkingLotNo){
                parkingLots.erase(parkingLots.begin() + i);
            }
        }
    }

    ParkingLot* getParkingLotById(int ParkingLotNo){
        for(int i=0;i<parkingLots.size();i++){
            if(parkingLots[i].getParkingLotId() == ParkingLotNo){
                return &parkingLots[i];
            }
        }
        return NULL;
    }

    vector<ParkingLot> GetAllparkingLots() {
        return parkingLots;
    }
};
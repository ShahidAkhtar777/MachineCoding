#pragma once
#include <bits/stdc++.h>
#include "../models/Floor.h"
using namespace std;

class FloorRepository {
private:
    unordered_map<int, vector<Floor>> floors; //parkingLot - floor
    int floorIdCounter = 0;
public:
    void AddFloor(int parkingLotId) {
        Floor f = Floor(floorIdCounter);
        floorIdCounter += 1;
        floors[parkingLotId].push_back(f);
    }

    void RemoveFloor(int parkingLotId, int floorNo){
        for(int i=0;i<floors[parkingLotId].size();i++){
            if(floors[parkingLotId][i].getFloorNo() == floorNo){
                floors[parkingLotId].erase(floors[parkingLotId].begin() + i);
            }
        }
    }

    Floor* getFloorByFloorId(int parkingLotId, int floorId){
        vector<Floor> currFloors = floors[parkingLotId];
        for(int i=0;i<currFloors.size();i++){
            if(currFloors[i].getFloorNo() == floorId){
                return &currFloors[i];
            }
        }
        return NULL;
    }

    vector<Floor> GetAllFloors(int parkingLotId) {
        return floors[parkingLotId];
    }
};
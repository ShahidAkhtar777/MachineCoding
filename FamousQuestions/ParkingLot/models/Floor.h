#pragma once
#include <vector>
#include "slot.h"
using namespace std;

class Floor {
private:
    int floorNo;
    vector<Slot> slots; 

public:
    Floor(int floorNo, vector<Slot> slots): floorNo(floorNo), slots(slots){}

    Floor(int floorNo): floorNo(floorNo){}

    int getFloorNo(){
        return floorNo;
    }

    vector<Slot> getSlots(){
        return slots;
    }

    void setSlots(vector<Slot> slots){
        this->slots = slots;
    }
};
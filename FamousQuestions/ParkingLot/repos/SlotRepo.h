#pragma once
#include <bits/stdc++.h>
#include "../models/Slot.h"
using namespace std;

class SlotRepository {
private:
    unordered_map<int, vector<Slot>> Slots; // floorId - Slot
    int slotIdCounter = 0; 
public:
    void AddSlot(int floorId, VehicleType type) {
        Slot s = Slot(slotIdCounter, type, false);
        slotIdCounter += 1;
        Slots[floorId].push_back(s);
    }

    void RemoveSlot(int floorId, int SlotNo){
        for(int i=0;i<Slots[floorId].size();i++){
            if(Slots[floorId][i].getSlotNo() == SlotNo){
                Slots[floorId].erase(Slots[floorId].begin() + i);
            }
        }
    }

    Slot* getSlotBySlotId(int floorId, int SlotId){
        vector<Slot> currSlot = Slots[floorId];
        for(int i=0;i<currSlot.size();i++){
            if(currSlot[i].getSlotNo() == SlotId){
                return &currSlot[i];
            }
        }
        return NULL;
    }

    vector<Slot> GetAllSlots(int floorId) {
        return Slots[floorId];
    }

    void bookSlot(int floorNo, int slotNo, Vehicle vehicle){
        vector<Slot> currSlots = Slots[floorNo];

        for(int i=0;currSlots.size();i++){
            if(currSlots[i].getSlotNo() == slotNo)
                currSlots[i].parkVehicle(&vehicle);
        }
    }

    void unBookSlot(int floorNo, int slotNo){
        vector<Slot> currSlots = Slots[floorNo];

        for(int i=0;currSlots.size();i++){
            if(currSlots[i].getSlotNo() == slotNo)
                currSlots[i].unparkVehicle();
        }
    }

    bool isSlotBooked(int floorNo, int slotNo){
        vector<Slot> currSlots = Slots[floorNo];

        for(int i=0;currSlots.size();i++){
            if(currSlots[i].getSlotNo() == slotNo)
                return currSlots[i].getIsOccupied();
        }
        return false;
    }
};
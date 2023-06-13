#pragma once
#include "../repos/SlotRepo.h"
#include "VehicleService.h"

class SlotService {
private:
    SlotRepository* slotRepo;
    VehicleService* vehicleService;
public:
    SlotService(SlotRepository* slotRepo, VehicleService* vehicleService): slotRepo(slotRepo), vehicleService(vehicleService) {}

    void CreateSlot(int FloorId, int SlotId, VehicleType type) {
        Slot* Slot = slotRepo->getSlotBySlotId(FloorId, SlotId);

        if(Slot != NULL){
            cout<<"Slot number "<< SlotId <<" already exists!!"<<endl;
            return;
        }
        slotRepo->AddSlot(FloorId, type);
    }

    vector<Slot> GetAllSlots(int floorId) {
        return slotRepo->GetAllSlots(floorId);
    }

    Slot* GetSlotBySlotId(int floorId, int slotId){
        Slot* s = slotRepo->getSlotBySlotId(floorId, slotId);
        if(s==NULL){
            cout<<"Slot not exists with slotId: "<<slotId<<endl;
            return NULL;
        }
        return s;
    }

    void DeleteSlot(int floorId, int SlotId){
        Slot* Slot = slotRepo->getSlotBySlotId(floorId, SlotId);

        if(Slot==NULL){
            cout<<"No Slot exists with this SlotId"<<endl;
        }
        slotRepo->RemoveSlot(floorId, SlotId);
    }

    void bookSlot(int floorId, int slotNo, string vehicleRegNo){
        Slot* Slot = slotRepo->getSlotBySlotId(floorId, slotNo);

        if(Slot==NULL){
            cout<<"No Slot exists with this SlotId"<<endl;
            return;
        }

        if(Slot->getIsOccupied()){
            cout<<"Slot is already booked! Book a different slot!"<<endl;
            return;
        }

        Vehicle* vehicle = vehicleService->getVehicleByRegNo(vehicleRegNo);
        slotRepo->bookSlot(floorId, slotNo, *vehicle);
        cout<<"SlotId "<<slotNo<<" booked in the floorNo: "<<floorId<<" for the vehicle: "<<vehicleRegNo<<endl; 
    }

    void unBookSlot(int floorId, int slotId){
        Slot* Slot = slotRepo->getSlotBySlotId(floorId, slotId);

        if(Slot==NULL){
            cout<<"No Slot exists with this SlotId"<<endl;
            return;
        }
        slotRepo->unBookSlot(floorId, slotId);
    }

};

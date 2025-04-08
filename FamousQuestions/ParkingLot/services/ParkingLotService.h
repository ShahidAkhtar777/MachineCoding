#pragma once
#include "../repos/ParkingLotRepo.h"
#include "FloorService.h"
#include "SlotService.h"

class ParkingLotService {
private:
    ParkingLotRepository* parkingLotRepo;
    FloorService* floorService;
    SlotService* slotService;

public:
    ParkingLotService(ParkingLotRepository* parkingLotRepo, FloorService* floorService, SlotService* slotService): parkingLotRepo(parkingLotRepo), floorService(floorService), slotService(slotService)  {}

    void CreateParkingLot(int parkingLotId, int totalFloors, int totalSlots) {
        ParkingLot* oldLot = parkingLotRepo->getParkingLotById(parkingLotId);

        if(oldLot != NULL){
            cout<<"ParkingLot with Id "<< parkingLotId <<" already exists!!"<<endl;
            return;
        }

        parkingLotRepo->AddParkingLot(parkingLotId, totalFloors, totalSlots);
        cout<<"Created parking lot with"<< totalFloors<<" floors and "<<totalSlots<<" slots per floor"<<endl;
    }

    string getVehicleTypeString(VehicleType type) {
        if (type == VehicleType::CAR) {
           return "CAR";
        } else if (type == VehicleType::BIKE) {
            return "BIKE";
        } else if (type == VehicleType::TRUCK) {
            return "TRUCK";
        } else {
            return "Unknown Vehicle Type";
        }
    }

    void DisplayFreeSlotsForVehicle(int parkingLotId, VehicleType vehicleType){
        vector<Floor> f = floorService->GetAllFloors(parkingLotId);
        for(int i=0;i<f.size();i++){
            vector<Slot> s = slotService->GetAllSlots(f[i].getFloorNo());
            
            cout<<"Free Slots for "<< getVehicleTypeString(vehicleType) <<" on Floor "<< f[i].getFloorNo() << ": ";
            for(int j=0;j<s.size();j++){
                if(s[j].getType() == vehicleType && !s[i].getIsOccupied()){
                    cout<<s[j].getSlotNo()<<", ";
                }
            }
            cout<<endl;
        }
    }

    void DisplayOccupiedSlotsForVehicle(int parkingLotId, VehicleType vehicleType){
        vector<Floor> f = floorService->GetAllFloors(parkingLotId);
        for(int i=0;i<f.size();i++){
            vector<Slot> s = slotService->GetAllSlots(f[i].getFloorNo());
            
            cout<<"Free Slots for "<< getVehicleTypeString(vehicleType) <<" on Floor "<< f[i].getFloorNo() << ": ";
            for(int j=0;j<s.size();j++){
                if(s[j].getType() == vehicleType && s[i].getIsOccupied()){
                    cout<<s[j].getSlotNo()<<", ";
                }
            }
            cout<<endl;
        }
    }



    void displayFreeSlotsCountPerFloorForVehicle(int parkingLotId, VehicleType vehicleType){
        vector<Floor> f = floorService->GetAllFloors(parkingLotId);

        for(int i=0;i<f.size();i++){
            vector<Slot> s = slotService->GetAllSlots(f[i].getFloorNo());
            cout<<"No. of free slots for "<< getVehicleTypeString(vehicleType) <<" on Floor "<< f[i].getFloorNo() <<" : ";
            int freeSlot = 0; 
            for(int j=0;j<s.size();j++){
                if(s[j].getIsOccupied() && s[j].getType() == vehicleType){
                    freeSlot++;
                }
            }
            cout<<freeSlot<<endl;
        }
    }

    vector<ParkingLot> GetAllParkingLots() {
        return parkingLotRepo->GetAllparkingLots();
    }

    ParkingLot* getParkingLotById(int parkingLotId){
        ParkingLot* p = parkingLotRepo->getParkingLotById(parkingLotId);

        if(p == NULL){
            cout<<"ParkingLot with Id: "<< parkingLotId << " does not exists."<<endl;
            return NULL; 
        }
        return p;
    }

    void DeleteParkingLot(int parkingLotId){
        ParkingLot* oldLot = parkingLotRepo->getParkingLotById(parkingLotId);

        if(oldLot==NULL){
            cout<<"No ParkingLot exists with this parkingLotId";
            return;
        }

        parkingLotRepo->RemoveParkingLot(parkingLotId);
    }


};

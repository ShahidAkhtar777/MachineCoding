#pragma once
#include "../repos/FloorRepo.h"

class FloorService {
private:
    FloorRepository* floorRepo;
public:
    FloorService(FloorRepository* floorRepo) {
        this->floorRepo = floorRepo;
    }

    void CreateFloor(int parkingLotId) {
        floorRepo->AddFloor(parkingLotId);
    }

    vector<Floor> GetAllFloors(int parkingLotId) {
        return floorRepo->GetAllFloors(parkingLotId);
    }

    Floor* GetFloorByFloorId(int parkingLotId, int FloorId){
        Floor* f = floorRepo->getFloorByFloorId(parkingLotId, FloorId);
        if(f==NULL){
            cout<<"Floor not exists"<<endl;
            return NULL;
        }
        return f;
    }

    void DeleteFloor(int parkingLotId, int floorId){
        Floor* floor = floorRepo->getFloorByFloorId(parkingLotId, floorId);

        if(floor==NULL){
            cout<<"No Floor exists with this FloorId in the parkingLot:"<< parkingLotId<<endl;
        }
        floorRepo->RemoveFloor(parkingLotId, floorId);
    }

};

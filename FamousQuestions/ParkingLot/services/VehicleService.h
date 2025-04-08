#pragma once
#include "../repos/VehicleRepo.h"

class VehicleService {
private:
    VehicleRepository* vehicleRepo;
public:
    VehicleService(VehicleRepository* vehicleRepo): vehicleRepo(vehicleRepo) {}

    void CreateVehicle(string regNo, VehicleType type, string color) {
        Vehicle* Vehicle = vehicleRepo->getVehicleByRegNo(regNo);

        if(Vehicle != NULL){
            cout<<"Vehicle number "<< regNo <<" already exists!!"<<endl;
            return;
        }
        vehicleRepo->AddVehicle(regNo, type, color);
    }

    vector<Vehicle> GetAllVehicles() {
        return vehicleRepo->GetAllVehicles();
    }

    void DeleteVehicle(string regNo){
        Vehicle* Vehicle = vehicleRepo->getVehicleByRegNo(regNo);

        if(Vehicle==NULL){
            cout<<"No Vehicle exists with this VehicleId";
        }
        vehicleRepo->RemoveVehicle(regNo);
    }

    Vehicle* getVehicleByRegNo(string regNo){
        Vehicle* v = vehicleRepo->getVehicleByRegNo(regNo);

        if(v==NULL){
            cout<<"No vehicle exists with this regNo: "<< regNo<< endl;
            return NULL;
        }
        return v;
    }

    VehicleType getVehicleType(string type) {
        if (type == "CAR") {
           return VehicleType::CAR;
        } else if (type == "BIKE") {
            return VehicleType::BIKE;
        } else {
            return VehicleType::TRUCK;
        }
    }
    
};

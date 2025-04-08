#pragma once
#include <bits/stdc++.h>
#include "../models/Vehicle.h"
using namespace std;

class VehicleRepository {
private:
    vector<Vehicle> vehicles;
public:
    void AddVehicle(string regNo, VehicleType type, string color) {
        Vehicle v = Vehicle(type, regNo, color);
        vehicles.push_back(v);
    }

    void RemoveVehicle(string regNo){
        for(int i=0;i<vehicles.size();i++){
            if(vehicles[i].getRegNo() == regNo){
                vehicles.erase(vehicles.begin() + i);
            }
        }
    }

    Vehicle* getVehicleByRegNo(string regNo){
        for(int i=0;i<vehicles.size();i++){
            if(vehicles[i].getRegNo() == regNo){
                return &vehicles[i];
            }
        }
        return NULL;
    }

    vector<Vehicle> GetAllVehicles() {
        return vehicles;
    }
};
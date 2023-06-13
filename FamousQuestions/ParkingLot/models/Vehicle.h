#pragma once
#include<bits/stdc++.h>
using namespace std;

enum class VehicleType {
    CAR,
    BIKE,
    TRUCK
};

class Vehicle {
private:
    VehicleType type;
    string regNo;
    string color;

public:
    Vehicle(VehicleType type, string regNo, string color): type(type), regNo(regNo), color(color) {}

    VehicleType getType(){
        return type;
    }

    string getRegNo(){
        return regNo;
    }

    string getColor(){
        return color;
    }
};
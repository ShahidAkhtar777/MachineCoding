#include "controllers/InputParser.h"
#include "services/FloorService.h"
#include "services/ParkingLotService.h"
#include "services/SlotService.h"
#include "services/TicketService.h"
#include "services/VehicleService.h"
#include <bits/stdc++.h>
using namespace std;

// void handleCommand(Command command) {
    
// }

int main() {
    string input;

    VehicleRepository vehicleRepo;
    VehicleService vehicleService(&vehicleRepo);

    SlotRepository slotRepo;
    SlotService slotService(&slotRepo, &vehicleService);

    FloorRepository floorRepo;
    FloorService floorService(&floorRepo);

    ParkingLotRepository parkingLotRepo;
    ParkingLotService parkingLotService(&parkingLotRepo, &floorService, &slotService);

    TicketRepository ticketRepo;
    TicketService ticketService(&ticketRepo, &parkingLotService, &floorService, &slotService, &vehicleService);

    parkingLotService.CreateParkingLot(24556, 4, 5); // pid, TotFloors, TotSlots

    vehicleService.CreateVehicle("JH034-56", VehicleType::BIKE, "black");
    vehicleService.CreateVehicle("PB089-46", VehicleType::CAR, "yellow");
    vehicleService.CreateVehicle("RJ789-67", VehicleType::TRUCK, "brown");

    for(int i=0;i<4;i++){
        floorService.CreateFloor(24556);
    }

    // slotService.CreateSlot(1, )
    
    return 0;
}

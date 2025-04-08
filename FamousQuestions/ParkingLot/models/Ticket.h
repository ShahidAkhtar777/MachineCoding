#pragma once
#include "vehicle.h"

class Ticket {
private:
    int ticketNo;
    int parkingLotId;
    int floorNo;
    int slotNo;

public:
    Ticket(int ticketNo, int parkingLotId, int floorNo, int slotNo):ticketNo(ticketNo), parkingLotId(parkingLotId), floorNo(floorNo), slotNo(slotNo) {}

    int getTicketNo(){
        return ticketNo;
    }

    int getparkingLotId(){
        return parkingLotId;
    }

    int getSlotNo(){
        return slotNo;
    }

    int getFloorNo(){
        return floorNo;
    }
};
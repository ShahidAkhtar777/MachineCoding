#pragma once
#include "../repos/TicketRepo.h"
#include "ParkingLotService.h"
#include "FloorService.h"
#include "SlotService.h"
#include "VehicleService.h"

class TicketService {
private:
    TicketRepository* ticketRepo;
    ParkingLotService* parkingService;
    FloorService* floorService;
    SlotService* slotService;
    VehicleService* vehicleService;

    // bool FloorComparator(Floor a, Floor b){
    //     return a.getFloorNo() < b.getFloorNo();
    // }

    // bool SlotComparator(Slot a, Slot b){
    //     return a.getSlotNo() < b.getSlotNo();
    // }

public:
    TicketService(TicketRepository* ticketRepo, ParkingLotService* parkingService,
    FloorService* floorService,
    SlotService* slotService,
    VehicleService* vehicleService): ticketRepo(ticketRepo), parkingService(parkingService), floorService(floorService),
    slotService(slotService), vehicleService(vehicleService) {}

    void BuyTicket(int parkingLotId, Vehicle vehicle) {
        ParkingLot* p  = parkingService->getParkingLotById(parkingLotId);
        if(p==NULL){
            cout<<"Ticket could not be bought! Sorry!"<<endl;
            return;
        }

        vector<Floor> f = floorService->GetAllFloors(parkingLotId);
        if(f.size()==0){
            cout<<"No floor available"<<endl;
            return;
        }

        // Sort the floors to get smallest FloorId
        // sort(f.begin(),f.end(), FloorComparator);

        for(int i=0;i<f.size();i++){
            vector<Slot> s = slotService->GetAllSlots(i);
            // Sort for getting smallest slot number
            // sort(s.begin(), s.end(), SlotComparator);
            for(int j=0;j<s.size();j++){
                if(s[j].getType() == vehicle.getType() && !s[j].getIsOccupied()){
                    slotService->bookSlot(f[i].getFloorNo(), s[j].getSlotNo(), vehicle.getRegNo());
                    ticketRepo->BuyTicket(parkingLotId, f[i].getFloorNo(), s[j].getSlotNo());
                    cout<<"Ticket Bought Park Your Vehicle in FloorNo: "<< f[i].getFloorNo()<< "SlotNo: "<< s[j].getSlotNo()<<endl;
                    break;
                }
            }
        }
    }

    vector<Ticket> GetAllTickets(int parkingLotId) {
        return ticketRepo->GetAllTickets(parkingLotId);
    }

    void RemoveTicket(int parkingLotId, int TicketId){
        Ticket* Ticket = ticketRepo->getTicketByTicketId(parkingLotId, TicketId);

        if(Ticket==NULL){
            cout<<"No Ticket exists with this TicketId";
        }

        int floorNo = Ticket->getFloorNo();
        int slotNo = Ticket->getSlotNo();

        slotService->unBookSlot(floorNo, slotNo);     
        ticketRepo->CancelTicket(parkingLotId, TicketId);
    }
};

#pragma once
#include <bits/stdc++.h>
#include "../models/Ticket.h"
using namespace std;

class TicketRepository {
private:
    unordered_map<int, vector<Ticket>> Tickets; // parkingLotId, Tickets
    int TicketIdCounter = 0;
public:
    void BuyTicket(int parkingLotId, int floorId, int slotNo) {
        Ticket t = Ticket(TicketIdCounter ,parkingLotId, floorId, slotNo);
        TicketIdCounter += 1;
        Tickets[parkingLotId].push_back(t);
    }

    void CancelTicket(int parkingLotId, int TicketId){
        for(int i=0;i<Tickets[parkingLotId].size();i++){
            if(Tickets[parkingLotId][i].getparkingLotId() == TicketId){
                Tickets[parkingLotId].erase(Tickets[parkingLotId].begin() + i);
            }
        }
    }

    Ticket* getTicketByTicketId(int parkingLotId, int TicketId){
        for(int i=0;i<Tickets[parkingLotId].size();i++){
            if(Tickets[parkingLotId][i].getTicketNo() == TicketId){
                return &Tickets[parkingLotId][i];
            }
        }
        return NULL;
    }

    vector<Ticket> GetAllTickets(int parkingLotId) {
        return Tickets[parkingLotId];
    }
};
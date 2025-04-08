// #include <bits/stdc++.h>

// using namespace std;

// // Define a class to represent a Vehicle
// class Vehicle {
// public:
//     string type;
//     string reg_no;
//     string color;
//     Vehicle(string t, string r, string c){
//         type = t;
//         reg_no = r;
//         color = c;
//     }
// };

// // Define a class to represent a Parking Slot
// class Slot {
// public:
//     string slot_id;
//     string vehicle_type;
//     string reg_no;
//     string color;
//     bool is_occupied;
//     Slot(string id, string vt, bool occupied){
//         slot_id = id;
//         is_occupied = occupied;
//         vehicle_type = vt;
//     }
// };

// // Define a class to represent a Parking Lot
// class ParkingLot {
// public:
//     string id;
//     int num_floors;
//     int num_slots_per_floor;
//     unordered_map<string, Slot*> slots;
//     ParkingLot(string i, int nf, int ns) {
//         id = i;
//         num_floors = nf;
//         num_slots_per_floor = ns;
//     }

//     // Create the parking lot
//     void createParkingLot() {
//         for (int i = 1; i <= num_floors; i++) {
//             for (int j = 1; j <= num_slots_per_floor; j++) {
//                 string slot_id = id + "" + to_string(i) + "" + to_string(j);
//                 // cout<<slot_id<<"\n";
//                 if (j == 1) {
//                     slots[slot_id] = new Slot(slot_id, "truck", false);
//                 } else if (j <= 3) {
//                     slots[slot_id] = new Slot(slot_id, "bike", false);
//                 } else {
//                     slots[slot_id] = new Slot(slot_id, "car", false);
//                 }
//             }
//         }
//         cout << "Created parking lot with " << num_floors <<
//          " floors and " << num_slots_per_floor << " slots per floor\n";
//     }

//     // Add a parking lot slot to a specific floor
//     void addParkingSlot(int floor_no, string vehicle_type) {
//         if (floor_no <= num_floors) {
//             for (int j = 1; j <= num_slots_per_floor; j++) {
//                 string slot_id = id + "" + to_string(floor_no) + "" + to_string(j);
//                 if (slots.find(slot_id) == slots.end()) {
//                     slots[slot_id] = new Slot(slot_id, vehicle_type, false);
//                     cout << "Added parking slot of type " << vehicle_type << " to floor " << floor_no << "\n";
//                     return;
//                 }
//             }
//             cout << "No available parking slot on floor " << floor_no << "\n";
//         } else {
//             cout << "Invalid floor number\n";
//         }
//     } 

//     // Book a parking slot for a vehicle and return the ticket id
//     string bookParkingSlot(Vehicle* vehicle) {
//         // Find the first available parking slot that can fit the vehicle
//         string slot_id;
//         for (int i = 1; i <= num_floors; i++) {
//             for (int j = 1; j <= num_slots_per_floor; j++) {
//                 string curr_slot_id = id + "" + to_string(i) + "" + to_string(j);
//                 // cout<<curr_slot_id<<" ";
//                 Slot* curr_slot = slots[curr_slot_id];
                
//                 if ((curr_slot->vehicle_type == vehicle->type) and !(curr_slot->is_occupied)) {
//                     curr_slot->is_occupied = true;
//                     curr_slot->reg_no = vehicle->reg_no;
//                     curr_slot->color = vehicle->color;
//                     slot_id = curr_slot_id;
//                     return slot_id;
//                 }
//             }
//         }
        
//         cout<<"No available slots"<<"\n";
//         return "";
//     }

//     void unBookVehicle(string ticketId){
//         //PR1234_2_5
//         int floor, slot;
//         int ind = ticketId.find("_");
//         string st = ticketId.substr(ind+1);
//         int newInd = st.find("_");
//         floor = stoi(st.substr(0,newInd+1));
//         slot = stoi(st.substr(newInd+1));
//         // invalid floor, slot check;
//         string slotId = id + "" + to_string(floor) + "" + to_string(slot);
//         slots[slotId]->is_occupied = false;
//     }

//     void displayAllFreeSlots(){

//     }

//     void displayOccupidSlots(){

//     }
// };

// int main(){

//     ParkingLot* parkingLot;
//     while(1){
//         string cmd;
//         cin>>cmd;
//         if (cmd == "create_parking_lot"){
//                 string plId;
//                 cin>>plId;
//                 int numFloor, numSlots;
//                 cin>>numFloor>>numSlots;
//                 parkingLot = new ParkingLot(plId, numFloor, numSlots);
//                 parkingLot->createParkingLot();
//         }else if(cmd == "park_vehicle"){
//                 string type, regNo, color;
//                 cin>>type>>regNo>>color;
//                 cout<<parkingLot->bookParkingSlot(new Vehicle(type, regNo, color))<<"\n";
//         }else if(cmd == "unpark_vehicle"){
//             string ticketId;
//             cin>>ticketId;
//             parkingLot->unBookVehicle(ticketId);
//         }
//         else if (cmd == "exit"){
//             break;
//         }
//     }

//     return 0;
// }
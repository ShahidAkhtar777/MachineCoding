# Parking Lot Management System

## Problem Statement

A parking lot is an area where cars can be parked for a certain amount of time. A parking lot can have multiple floors with each floor having a different number of slots, and each slot being suitable for different types of vehicles.

For this problem, we need to design a next-generation parking lot system that can manage a parking lot without any human intervention.

## Requirements

Create a command-line application for the parking lot system with the following requirements:

1. Create the parking lot.
2. Add floors to the parking lot.
3. Add a parking lot slot to any of the floors.
4. Given a vehicle, find the first available slot, book it, create a ticket, park the vehicle, and return the ticket.
5. Unpark a vehicle given the ticket ID.
6. Display the number of free slots per floor for a specific vehicle type.
7. Display all the free slots per floor for a specific vehicle type.
8. Display all the occupied slots per floor for a specific vehicle type.

### Details about the Vehicles

- Every vehicle will have a type, registration number, and color.
- Different Types of Vehicles:
  - Car
  - Bike
  - Truck

### Details about the Parking Slots

- Each type of slot can park a specific type of vehicle.
- No other vehicle should be allowed by the system.
- Finding the first available slot should be based on:
  - The slot should be of the same type as the vehicle.
  - The slot should be on the lowest possible floor in the parking lot.
  - The slot should have the lowest possible slot number on the floor.
- Numbered serially from 1 to n for each floor where n is the number of parking slots on that floor.

### Details about the Parking Lot Floors

- Numbered serially from 1 to n where n is the number of floors.
- Might contain one or more parking lot slots of different types.
- We will assume that the first slot on each floor will be for a truck, the next 2 for bikes, and all the other slots for cars.

### Details about the Tickets

- The ticket ID would be of the following format:
  - \<parking_lot_id>_<floor_no>_<slot_no>
  - Example: PR1234_2_5 (denotes 5th slot of 2nd floor of parking lot PR1234)
- We can assume that there will only be 1 parking lot. The ID of that parking lot is PR1234.

## Input/Output Format

The code should strictly follow the input/output format and will be tested with provided test cases.

### Input Format

Multiple lines, with each line containing a command.

Possible commands:

- create_parking_lot \<parking_lot_id> \<no_of_floors> \<no_of_slots_per_floor>
- park_vehicle \<vehicle_type> \<reg_no> \<color>
- unpark_vehicle \<ticket_id>
- display \<display_type> \<vehicle_type>
  - Possible values of display_type: free_count, free_slots, occupied_slots
- exit

Stop taking input when you encounter the word "exit".

### Output Format

Print output based on the specific commands as mentioned below.

- create_parking_lot:
  - Created parking lot with \<no_of_floors> floors and \<no_of_slots_per_floor> slots per floor
- park_vehicle:
  - Parked vehicle. Ticket ID: \<ticket_id>
  - Print "Parking Lot Full" if a slot is not available for that vehicle type.
- unpark_vehicle:
  - Unparked vehicle with Registration Number: \<reg_no> and Color: \<color>
  - Print "Invalid Ticket".

##

 Sample Input/Output

#### Sample Input 1:
```
create_parking_lot PR1234 3 5
park_vehicle Car ABC123 Red
park_vehicle Bike DEF456 Blue
park_vehicle Car GHI789 Black
unpark_vehicle PR1234_2_2
display free_count Car
display free_slots Bike
exit
```

#### Sample Output 1:
```
Created parking lot with 3 floors and 5 slots per floor
Parked vehicle. Ticket ID: PR1234_1_1
Parked vehicle. Ticket ID: PR1234_1_2
Parked vehicle. Ticket ID: PR1234_1_3
Unparked vehicle with Registration Number: GHI789 and Color: Black
Free slots for Car: 12
Free slots for Bike: 2, 4, 5
```

#### Sample Input 2:
```
create_parking_lot PR5678 2 3
park_vehicle Car ABC123 Red
park_vehicle Car DEF456 Blue
display occupied_slots Car
exit
```

#### Sample Output 2:
```
Created parking lot with 2 floors and 3 slots per floor
Parked vehicle. Ticket ID: PR5678_1_1
Parked vehicle. Ticket ID: PR5678_1_2
Occupied slots for Car: 1, 2
```
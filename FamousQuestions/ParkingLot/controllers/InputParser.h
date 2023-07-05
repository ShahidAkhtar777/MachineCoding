#include <bits/stdc++.h>
using namespace std;

class Command {
public:
    string action;
    vector<string> arguments;
};

Command parseInput(string input) {
    Command command;

    // Split the input string by whitespace
    istringstream iss(input);
    vector<string> tokens(istream_iterator<string>{iss}, istream_iterator<string>());

    // Check if the input is empty
    if (tokens.empty()) {
        command.action = "INVALID";
        return command;
    }

    // Get the action from the first token and map it to CommandType
    command.action = tokens[0];
    // The rest of the tokens are the arguments
    if (tokens.size() > 1) {
        command.arguments = vector<string>(tokens.begin() + 1, tokens.end());
    }

    return command;
}

// Ignore below code

// while (true) {
//         cout << "Enter command: ";
//         getline(cin, input);

//         Command command = parseInput(input);
//         vector<string> args = command.arguments;

//         cout<<command.action;

//         if (command.action == "add_floor") {
//             floorService.CreateFloor(stoi(args[0]));
//         } else if (command.action == "remove_floor") {
//             std::cout << "Handling remove_floor command..." << std::endl;
//         } else if (command.action == "create_parking_lot") {
//             int pid = stoi(args[0]);
//             cout<<"Pid: "<< pid<<endl;
//             int fId = stoi(args[1]);
//             cout<<"fId: "<< fId<<endl;
//             int sId = stoi(args[2]);
//             parkingLotService.CreateParkingLot(pid,fId, sId);
//         } else if (command.action == "display_free_slot") {
//             std::cout << "Handling display_free_slot command..." << std::endl;
//         } else if (command.action == "display_occupied_slot") {
//             std::cout << "Handling display_occupied_slot command..." << std::endl;
//         } else if (command.action == "display_slot_count") {
//             std::cout << "Handling display_slot_count command..." << std::endl;
//         } else if (command.action == "add_slot") {
//             std::cout << "Handling add_slot command..." << std::endl;
//         } else if (command.action == "remove_slot") {
//             std::cout << "Handling remove_slot command..." << std::endl;
//         } else if (command.action == "buy_ticket") {
//             std::cout << "Handling buy_ticket command..." << std::endl;
//         } else if (command.action == "remove_ticket") {
//             std::cout << "Handling remove_ticket command..." << std::endl;
//         } else if (command.action == "add_vehicle") {
//             std::cout << "Handling add_vehicle command..." << std::endl;
//         } else if (command.action == "remove_vehicle") {
//             std::cout << "Handling remove_vehicle command..." << std::endl;
//         } else if (command.action == "exit") {
//             break;
//         }else {
//             std::cout << "Invalid command!" << std::endl;
//         }
//     }


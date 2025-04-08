#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include "../services/walletservice.h"
using namespace std;

class Driver {
    WalletService wService;
    AccountRepository accRepo;
    UserRepository userRepo;
public:
    Driver(): wService(&accRepo, &userRepo){}

    void run() {
        while (true) {
            cout << "\nOPTIONS:" << endl;
            cout << "1. Create wallet" << endl;
            cout << "2. Transfer Amount" << endl;
            cout << "3. Account Statement" << endl;
            cout << "4. Overview" << endl;
            cout << "5. Exit" << endl;
            cout << "Enter your choice: ";
            int choice;
            cin >> choice;
            switch (choice) {
                case 1: {
                    cout << "YOU SELECTED CREATE WALLET" << endl;
                    cout << "Enter userId: ";
                    int uId;
                    cin >> uId;
                    cout<< "Enter name: ";
                    string name;
                    cin>>name;
                    cout << "Enter amount: ";
                    double amount;
                    cin >> amount;
                    wService.createWallet(uId, name, amount);
                    break;
                }
                case 2: {
                    cout << "YOU SELECTED TRANSFER" << endl;
                    cout << "Enter SENDER userID: ";
                    int from;
                    cin >> from;
                    cout << "Enter RECEIVER userID: ";
                    int to;
                    cin >> to;
                    cout << "Enter amount: ";
                    double amount;
                    cin >> amount;
                    wService.transferAmount(from, to, amount);
                    break;
                }
                case 3: {
                    cout << "YOU SELECTED ACCOUNT STATEMENT" << endl;
                    cout << "Enter user Id: ";
                    int userId;
                    cin >> userId;
                    wService.printStatements(userId);
                    break;
                }
                case 4: {
                    cout << "YOU SELECTED OVERVIEW" << endl;
                    wService.overview();
                    break;
                }
                case 5: {
                    cout << "APPLICATION STOPPED" << endl;
                    return;
                }
                default:
                    cout << "YOU HAVE SELECTED INVALID OPTION. PLEASE REENTER" << endl;
                    break;
            }
        }
    }
};

int main() {
    Driver driver;
    driver.run();
    return 0;
}

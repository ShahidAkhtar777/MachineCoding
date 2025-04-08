#pragma once
#include "docService.h"
#include <iostream>
using namespace std;

class Driver {
public:
    Driver(): documentService(&documentRepository, &userRepository) {}

    void run() {
        while (true) {
            std::cout << "Menu:\n"
                    << "1. Create User\n"
                    << "2. Create Document\n"
                    << "3. Read Document\n"
                    << "4. Edit Document\n"
                    << "5. Grant Read Access\n"
                    << "6. Grant Edit Access\n"
                    << "7. Delete Document\n"
                    << "8. Exit\n"
                    << "Enter your choice: ";

            int choice;
            std::cin >> choice;

            std::string name, content, owner, reader, editor, grantor;
            switch (choice) {
                case 1:
                    std::cout << "Enter username: ";
                    std::cin >> owner;
                    documentService.createUser(owner);
                    break;
                case 2:
                    std::cout << "Enter document name: ";
                    std::cin >> name;
                    std::cout << "Enter document content: ";
                    std::cin >> content;
                    std::cout << "Enter owner username: ";
                    std::cin >> owner;
                    documentService.createUserDocument(name, content, owner);
                    break;
                case 3:
                    std::cout << "Enter document name: ";
                    std::cin >> name;
                    std::cout << "Enter reader username: ";
                    std::cin >> reader;
                    std::cout << "Document content: " << documentService.readUserDocument(name, reader) << std::endl;
                    break;
                case 4:
                    std::cout << "Enter document name: ";
                    std::cin >> name;
                    std::cout << "Enter new content: ";
                    std::cin >> content;
                    std::cout << "Enter editor username: ";
                    std::cin >> editor;
                    documentService.editUserDocument(name, content, editor);
                    break;
                case 5:
                    std::cout << "Enter document name: ";
                    std::cin >> name;
                    std::cout << "Enter reader username: ";
                    std::cin >> reader;
                    std::cout << "Enter grantor username: ";
                    std::cin >> grantor;
                    documentService.grantReadAccess(name, reader, grantor);
                    break;
                case 6:
                    std::cout << "Enter document name: ";
                    std::cin >> name;
                    std::cout << "Enter editor username: ";
                    std::cin >> editor;
                    std::cout << "Enter grantor username: ";
                    std::cin >> grantor;
                    documentService.grantEditAccess(name, editor, grantor);
                    break;
                case 7:
                    std::cout << "Enter document name: ";
                    std::cin >> name;
                    std::cout << "Enter owner username: ";
                    std::cin >> owner;
                    documentService.deleteUserDocument(name, owner);
                    break;
                case 8:
                    std::cout << "Exiting.\n";
                    return;
                default:
                    std::cout << "Invalid choice. Please select again.\n";
            }
        }
    }

private:
    DocumentRepository documentRepository;
    UserRepository userRepository;
    DocumentService documentService;
};

#pragma once
#include "../repos/docRepo.h"
#include "../repos/userRepo.h"

class DocumentService {
public:
    DocumentService(DocumentRepository* documentRepository, UserRepository* userRepository)
    : docRepo(documentRepository), userRepo(userRepository) {}

    void createUser(string username) {
        User *u = userRepo->getUser(username);
        if(u!=nullptr){
            cout<<"User already exists with this username\n";
            return;
        }
            
        userRepo->createUser(username);
        cout<<"User Created\n";
    }

    void createUserDocument(string name, string content, string owner) {
        User* user = userRepo->getUser(owner);
        if (user) {
            docRepo->createDocument(name, content, *user);
            cout<<"Document Created\n";
        } else {
            cout<<"The owner does not exists\n";
            return;
        }
    }

    string readUserDocument(string name, string reader) {
        User* user = userRepo->getUser(reader);
        if (!user) {
            return "Invalid reader.";
        }

        Document* document = docRepo->readDocument(name, *user);
        if (document) {
            return document->getDocContent();
        }
        return "Access denied or document not found.";
    }

    void editUserDocument(string name, string content, string editor) {
        User* user = userRepo->getUser(editor);
        if (user) {
            docRepo->editDocument(name, content, *user);
        } else {
            cout<< "User does not exists\n";
            return;
        }
    }      

    void grantReadAccess(string name, string reader, string grantor) {
        User* grantorUser = userRepo->getUser(grantor);
        User* readerUser = userRepo->getUser(reader);

        if (grantorUser && readerUser) {
            docRepo->grantReadAccess(name, *readerUser, *grantorUser);
        } else{
            cout<<"Grantor or reader does not exists\n";
            return;
        }
    }

    void grantEditAccess(string name, string editor, string grantor) {
        User* grantorUser = userRepo->getUser(grantor);
        User* editorUser = userRepo->getUser(editor);

        if (grantorUser && editorUser) {
            docRepo->grantEditAccess(name, *editorUser, *grantorUser);
        } else {
            cout<<"Grantor or Editor does not exists\n";
            return;
        }
    }

    void deleteUserDocument(string name, string owner) {
        User* ownerUser = userRepo->getUser(owner);
        if (ownerUser) {
            docRepo->deleteDocument(name, *ownerUser);
        } else{
            cout<<"No user exists with this username\n";
        }
    }

private:
    DocumentRepository* docRepo;
    UserRepository* userRepo;
};
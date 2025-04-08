#pragma once
#include <unordered_map>
#include <unordered_set>
#include "../models/document.h"

class DocumentRepository {
public:

    void createDocument(string name, string content, User owner) {
        documents[name] = Document(name, content, owner);
        readAccess[name].insert(owner.getUsername());
        editAccess[name].insert(owner.getUsername());
    }

    Document* readDocument(string name, User reader) {
        if (readAccess[name].count(reader.getUsername()) || editAccess[name].count(reader.getUsername())) {
            return &documents[name];
        }
        return nullptr;
    }

    void editDocument(string name, string content, User editor) {
        if (editAccess[name].count(editor.getUsername())) {
            documents[name].setDocContent(content);
            cout<<"Document Updated\n";
        } else {
            cout<<"User does not has edit access\n";
        }
    }
    
    void grantReadAccess(string name, User reader, User grantor) {
        if (editAccess[name].count(grantor.getUsername())) {
            readAccess[name].insert(reader.getUsername());
            cout<<"Read Access Granted\n";
            return;
        } else {
            cout<<"Grantor does not has edit access\n";
            return;
        }
    }

    void grantEditAccess(string name, User editor, User grantor) {
        if (editAccess[name].count(grantor.getUsername())) {
            editAccess[name].insert(editor.getUsername());
            cout<<"Edit Access Granted\n";
            return;
        } else {
            cout<<"Grantor does not has edit access\n";
            return;
        }
    }

    void deleteDocument(string name, User owner) {
        if (documents.count(name) && documents[name].getOwner().getUsername() == owner.getUsername()) {
            documents.erase(name);
            readAccess.erase(name);
            editAccess.erase(name);
        } else {
            cout<<"User if not owner or document not exists\n";
        }
    }

private:
    unordered_map<string, Document> documents;
    unordered_map<string, unordered_set<string>> readAccess;
    unordered_map<string, unordered_set<string>> editAccess;
};

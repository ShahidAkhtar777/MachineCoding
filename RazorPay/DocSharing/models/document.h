#pragma once
#include <string>
#include "User.h"
using namespace std;

class Document {
public:
    Document() : name(""), content(""), owner(User("")) {}
    
    Document(string name, string content, User owner)
    : name(name), content(content), owner(owner) {}

    User getOwner() {
        return owner;
    }

    string getDocName(){
        return name;
    }

    string getDocContent() {
        return content;
    }

    void setDocContent(string content){
        this->content = content;
    }

    User setOwner(User owner){
        this->owner = owner;
    }

private:
    string name;
    string content;
    User owner;
};

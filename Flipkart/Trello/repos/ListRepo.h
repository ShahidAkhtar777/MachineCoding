#pragma once

#include <unordered_map>
#include "../models/List.h"
using namespace std;

class ListRepository
{
public:
    void addList(string name)
    {
        int listId = getNextListId();
        List *newList = new List(listId, name);
        listsById[listId] = *newList;
    }

    List *getListById(int listId)
    {
        auto it = listsById.find(listId);
        return (it != listsById.end()) ? &it->second : nullptr;
    }

    int getNextListId()
    {
        static int listIdCounter = 1;
        return listIdCounter++;
    }

private:
    unordered_map<int, List> listsById;
};
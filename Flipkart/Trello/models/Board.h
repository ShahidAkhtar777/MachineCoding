#pragma once
#include <string>
#include <vector>
#include "User.h"
#include "List.h"

enum class Privacy {
    PUBLIC,
    PRIVATE
};

class Board
{
public:
    Board(int id, string name, string privacy, string url)
        : id(id), name(name), privacy(privacy), url(url) {}

    int getId() { return id; }
    string getName() { return name; }
    Privacy getPrivacy() { return privacy; }
    string getUrl() { return url; }
    vector<User> getMembers() { return members; }
    vector<List> getLists() { return lists; }

    void addMember(User &user) { members.push_back(user); }

    void removeMember(User &user)
    {
        for (auto it = members.begin(); it != members.end(); ++it)
        {
            if (it->getUserId() == user.getUserId())
            {
                members.erase(it);
                break;
            }
        }
    }

    void addList(List &list)
    {
        lists.push_back(list);
    }

    void removeList(int listId)
    {
        for (auto it = lists.begin(); it != lists.end(); ++it)
        {
            if (it->getId() == listId)
            {
                lists.erase(it);
                break;
            }
        }
    }
    void moveCard(int sourceListId, int targetListId, int cardId)
    {
        List *sourceList = nullptr;
        List *targetList = nullptr;

        for (auto &list : lists)
        {
            if (list.getId() == sourceListId)
            {
                sourceList = &list;
            }
            if (list.getId() == targetListId)
            {
                targetList = &list;
            }
        }

        if (sourceList && targetList)
        {
            for (auto it = sourceList->getCards().begin(); it != sourceList->getCards().end(); ++it)
            {
                if (it->getId() == cardId)
                {
                    targetList->addCard(*it);
                    sourceList->getCards().erase(it);
                    break;
                }
            }
        }
    }

private:
    int id;
    string name;
    Privacy privacy;
    string url;
    vector<User> members;
    vector<List> lists;
};

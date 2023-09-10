#pragma once

#include <string>
#include <vector>
#include "Card.h"

class List
{
public:
    List(int id, string &name)
        : id(id), name(name) {}

    int getId() 
    {
        return id;
    }

    string getName() 
    {
        return name;
    }

    vector<Card> getCards() 
    {
        return cards;
    }

    void addCard(Card card)
    {
        cards.push_back(card);
    }

    void removeCard(int cardId)
    {
        for (auto it = cards.begin(); it != cards.end(); ++it)
        {
            if (it->getId() == cardId)
            {
                cards.erase(it);
                break;
            }
        }
    }

private:
    int id;
    string name;
    vector<Card> cards;
};


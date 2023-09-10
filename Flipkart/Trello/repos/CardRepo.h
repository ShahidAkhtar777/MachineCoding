#pragma once

#include <unordered_map>
#include "../models/Card.h"
using namespace std;


class CardRepository
{
public:
    void addCard(Card &card)
    {
        int listId = getNextListId();
        List *newList = new List(listId, name);
        listsById[listId] = *newList;
    }

    Card *getCardById(int cardId)
    {
        auto it = cardsById.find(cardId);
        return (it != cardsById.end()) ? &it->second : nullptr;
    }

    int getNextCardId()
    {
        static int cardIdCounter = 1;
        return cardIdCounter++;
    }

private:
    unordered_map<int, Card> cardsById;
};

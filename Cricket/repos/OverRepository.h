#pragma once
#include <vector>
#include<unordered_map>
#include "../models/Over.h"
using namespace std;

class OverRepository
{
public:
    void addOver(Over over, int teamId)
    {
        teamOvers[teamId].push_back(over);
    }
    
    vector<Over> getOvers(int teamId)
    {
        return teamOvers[teamId];
    }

private:
    unordered_map<int, vector<Over>> teamOvers;  // teamId -> <overs>
};

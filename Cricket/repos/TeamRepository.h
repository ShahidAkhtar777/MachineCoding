#pragma once
#include <vector>
#include "../models/Team.h"
using namespace std;

class TeamRepository
{
public:
    void addTeam(int teamId, string teamName)
    {
        Team *team = new Team(teamId, teamName);
        teamsMap[teamId] = *team;
    }

    Team* getTeamById(int teamId) {
        if(teamsMap.count(teamId))
            return &teamsMap[teamId];
        return nullptr;
    }

private:
    unordered_map<int, Team> teamsMap; // temid -> team
    int teamId = 1;
};

#pragma once

#include <vector>
#include "Player.h"
#include "Over.h"

class Team
{
public:
    Team() {}
    Team(int teamId, string name): teamId(teamId), name(name) {}

    string getTeamName() {
        return name;
    }

    void setTeamName(string name) {
        this->name = name;
    }

    vector<Player> getPlayers() {
        return players;
    }

    void addPlayer(Player player) {
        players.push_back(player);
    }

    void addOver(Over over) {
        overs.push_back(over);
    }

    int getTeamId() {
        return teamId;
    }

    void addRuns(int runs) {
        totalRuns += runs;
    }

    void addWickets() {
        totalWickets++;
    }

private:
    int teamId;
    string name;
    int totalRuns;
    int totalWickets;
    vector<Player> players;
    vector<Over> overs;
};

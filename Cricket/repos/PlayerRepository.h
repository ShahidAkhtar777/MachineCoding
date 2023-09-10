#pragma once
#include <vector>
#include "../models/Player.h"

class PlayerRepository
{
public:
    void addPlayer(string playerName, string teamName, int teamId)
    {
        Player newPlayer(playerId, playerName, teamName);
        playerId += 1;
        players[teamId].push_back(newPlayer);
    }

    vector<Player> getPlayers(int teamId)
    {
        return players[teamId];
    }

    Player* getPlayerByName(string playerName, int teamId) {
        for (auto& player : players[teamId]) {
            if (player.getName() == playerName) {
                return &player;
            }
        }
        return nullptr;
    }

    Player* getPlayerById(int playerId, int teamId) {
        for (auto& player : players[teamId]) {
            if (player.getPlayerId() == playerId) {
                return &player;
            }
        }
        return nullptr;
    }

    Player* incomingBatsman(int batsmanId1, int batsmanId2, int teamId) {
        int nextBatsmanId = max(batsmanId1, batsmanId2) + 1;
        vector<Player> teamPlayers = players[teamId];

        if(nextBatsmanId == teamPlayers.size())
            return nullptr;

        for(auto player: teamPlayers) {
            if(player.getPlayerId() == nextBatsmanId)
                return &player;
        }
        return nullptr;
    }

private:
    unordered_map<int, vector<Player>> players; // TeamId -> <players>
    int playerId = 1;
};
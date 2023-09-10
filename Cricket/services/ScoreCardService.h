#pragma once
#include "../repos/PlayerRepository.h"
#include "../repos/OverRepository.h"
#include "../repos/TeamRepository.h"

class ScorecardService {
public:
    ScorecardService(PlayerRepository& PlayerRepository, OverRepository& OverRepository, TeamRepository& TeamRepository)
    : PlayerRepository(PlayerRepository), OverRepository(OverRepository), TeamRepository(TeamRepository) {}

void updatePlayerStats(int strikerId ,int nonStrikerId ,int teamId, int runs, bool isBoundary, bool isWicket) {
    Player* player = PlayerRepository.getPlayerById(strikerId, teamId);
    if (player) {
        player->addRuns(runs, isBoundary);
        player->addBallsFaced();

        if(runs%2!=0) {
            player->setStriker(false);
            
        }


        if (isWicket) {
            player->setStriker(false);
            Team* team = TeamRepository.getTeamById(teamId);
            if (team) {
                team->addWickets();
                Player* nextBatsman = PlayerRepository.incomingBatsman(strikerId, nonStrikerId, teamId);
                if (nextBatsman) {
                    nextBatsman->setStriker(true);
                }
            }
        }
    }
}

void addOver(Over over) {
    OverRepository.addOver(over);
}
    
private:
    PlayerRepository& PlayerRepository;
    OverRepository& OverRepository;
    TeamRepository& TeamRepository;
};

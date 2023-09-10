#pragma once
#include <vector>
#include "../repos/TeamRepository.h"
#include "../repos/PlayerRepository.h"
#include "../repos/OverRepository.h"
#include <bits/stdc++.h>
using namespace std;

class MatchService
{
public:
    MatchService(TeamRepository& teamRepo, PlayerRepository& playerRepo, OverRepository& overRepo)
        : teamRepository(teamRepo), playerRepository(playerRepo), overRepository(overRepo) {}

    void startMatch(int teamId1, int teamId2, int overs)
    {
        battingTeamId = teamId1;
        bowlingTeamId = teamId2;
        totalOvers = overs;
        currentOver = 0;
        currentBall = 0;
        currentPlayerIndex = 0;
        currentBowlerIndex = 0;
        initializePlayers();
    }

    void recordBall(int runs, bool isExtra, bool isWicket)
    {
        Player* batsman = &battingTeamPlayers[currentPlayerIndex];

        if (isExtra) {
            if (runs > 0) {
                batsman->addRuns(runs, false);
                battingTeam.addRuns(runs);
            }
            // Handle extras separately
            over.addBall(runs, true, false);
        } else {
            if (isWicket) {
                batsman->setStriker(false);
                batsman->addBallsFaced();
                over.addBall(runs, false, true);
                currentPlayerIndex++;
            } else {
                batsman->addRuns(runs, (runs == 4 || runs == 6));
                batsman->addBallsFaced();
                over.addBall(runs, false, false);
            }

            currentBall++;
            if (currentBall == 6 || currentPlayerIndex >= battingTeamPlayers.size()) {
                currentBall = 0;
                currentPlayerIndex = 0;
                currentBowlerIndex++;
                rotateStrike();
            }
        }

        if (currentBowlerIndex >= bowlingTeamPlayers.size()) {
            currentBowlerIndex = 0;
        }

        if (currentBall == 0) {
            overRepository.addOver(over, battingTeamId);
            over = Over();
            currentOver++;
        }

        if (currentOver == totalOvers) {
            displayMatchSummary();
        }
    }

    void displayMatchSummary()
    {
        Team* winningTeam = (battingTeam.getTotalRuns() > bowlingTeam.getTotalRuns()) ? &battingTeam : &bowlingTeam;
        Team* losingTeam = (winningTeam == &battingTeam) ? &bowlingTeam : &battingTeam;

        cout << "Match Summary" << endl;
        cout << "--------------------------------------" << endl;
        cout << "Winning Team: " << winningTeam->getTeamName() << endl;
        cout << "Total Runs: " << winningTeam->getTotalRuns() << "/" << winningTeam->getTotalWickets() << endl;
        cout << "Overs: " << currentOver << "/" << totalOvers << endl;
        cout << "--------------------------------------" << endl;

        cout << "Batting Team: " << battingTeam.getTeamName() << endl;
        displayPlayerScores(battingTeamPlayers);

        cout << "--------------------------------------" << endl;
        cout << "Bowling Team: " << bowlingTeam.getTeamName() << endl;
        displayPlayerBowlingStats(bowlingTeamPlayers);

        cout << "--------------------------------------" << endl;
    }

    // Add more functions for match management

private:
    TeamRepository& teamRepository;
    PlayerRepository& playerRepository;
    OverRepository& overRepository;

    int battingTeamId;
    int bowlingTeamId;
    int totalOvers;
    int currentOver;
    int currentBall;
    int currentPlayerIndex;
    int currentBowlerIndex;

    Team battingTeam;
    Team bowlingTeam;
    vector<Player> battingTeamPlayers;
    vector<Player> bowlingTeamPlayers;
    Over over;

    void initializePlayers()
    {
        battingTeam = *teamRepository.getTeamById(battingTeamId);
        bowlingTeam = *teamRepository.getTeamById(bowlingTeamId);
        battingTeamPlayers = playerRepository.getPlayers(battingTeamId);
        bowlingTeamPlayers = playerRepository.getPlayers(bowlingTeamId);

        for (Player& player : battingTeamPlayers) {
            player.setStriker(false);
        }

        battingTeamPlayers[0].setStriker(true);
    }

    void rotateStrike()
    {
        for (Player& player : battingTeamPlayers) {
            player.setStriker(!player.isStriker());
        }
    }

    void displayPlayerScores(const vector<Player>& players)
    {
        for (Player player : players) {
            cout << player.getName() << ": " << player.getScore() << " runs (" << player.getBallsFaced() << " balls)";
            cout << " | Fours: " << player.getFours() << " | Sixes: " << player.getSixes() << endl;
        }
    }

    void displayPlayerBowlingStats(const vector<Player>& players)
    {
        for (const Player& player : players) {
            cout << player.getName() << ": " << player.getTotalWickets() << " wickets for " << player.getTotalRunsGiven() << " runs";
            cout << " in " << player.getTotalOversBowled() << " overs" << endl;
        }
    }
};

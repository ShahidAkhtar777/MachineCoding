#pragma once
#include <string>
using namespace std;

class Player
{
public:
    Player(int playerId, string playerName, string teamName)
        : playerId(playerId), name(playerName), teamName(teamName), score(0), ballsFaced(0), fours(0), sixes(0), striker(false)
    {}

    string getName()
    {
        return name;
    }

    int getPlayerId() {
        return playerId;
    }

    int getScore()
    {
        return score;
    }

    int getBallsFaced()
    {
        return ballsFaced;
    }

    int getFours()
    {
        return fours;
    }

    int getSixes()
    {
        return sixes;
    }

    bool isStriker()
    {
        return striker;
    }

    void setName(string newName)
    {
        name = newName;
    }

    string getTeamName() {
        return teamName;
    }

    void addRuns(int runs, bool isBoundary) {
        score += runs;
        if (isBoundary) {
            if (runs == 4) fours++;
            else if (runs == 6) sixes++;
        }
    }

    void addBallsFaced() {
        ballsFaced++;
    }

    void setStriker(bool value)
    {
        striker = value;
    }


private:
    int playerId; 
    string name;
    string teamName;
    int score;
    int ballsFaced;
    int fours;
    int sixes;
    bool striker;
};

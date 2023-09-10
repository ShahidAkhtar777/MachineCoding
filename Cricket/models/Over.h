#pragma once
#include <vector>

// ToDo Implement BallType to handle all cases
// emum class BallType {
//     N, // Normal
//     Wd, // Wide
//     NB, // No Ball
//     W, // Wicket
//     B, // Boundary
// };

class Over
{
public:
    Over(): {}

    void addBall(int runs, bool isExtra, bool isWicket)
    {
        runsPerBall.push_back(runs);
        extras.push_back(isExtra);
        wicketsPerBall.push_back(isWicket);
    }

    string getBowler()
    {
        return bowler;
    }

    int getTotalRuns()
    {
        int total = 0;
        for (int runs : runsPerBall)
        {
            total += runs;
        }
        return total;
    }

    int getExtras() {
        int total = 0;
        for(auto extra: extras) {
            if(extra)
                total++;
        }
        return total;
    }

    int getWickets()
    {
        int noOfWickets = 0;
        for (bool isWicket : wickets)
        {
            if (isWicket)
            {
                noOfWickets++;
            }
        }
        return noOfWickets;
    }

    vector<int> getBalls()
    {
        return runsPerBall;
    }

    void addBall(int runs)
    {
        runsPerBall.push_back(runs);
    }

    string getBowler()
    {
        return bowler;
    }

    void setBowler(string bowlerName)
    {
        bowler = bowlerName;
    }

private:
    vector<int> runsPerBall; // Holds the runs for each ball
    vector<bool> extras;
    vector<bool> wickets;
};

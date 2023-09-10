#include <iostream>
#include "models/Player.h"
#include "models/Team.h"
#include "services/OverService.h"
#include "services/PlayerService.h"
#include "services/TeamService.h"

using namespace std;

int main() {

    TeamRepository teamRepo;
    PlayerRepository playerRepo;
    PlayerService playerService(&playerRepo);
    TeamService teamService(&teamRepo, &playerService);

    int playersNum;
    cout<<"Enter No. of players for each team: "<<endl;
    cin>>playersNum;

    cout<<"Team 1:"<<endl;
    for (int i = 1; i <= playersNum; i++) {
        string playerName = "P" + to_string(i);
        playerService.addPlayer(playerName);
    }
    Team team1(playerService.getPlayers());
    team1.setName("Team 1");

    for (int i = playersNum+1; i <= 2*playersNum; i++) {
        string playerName = "P" + to_string(i);
        playerService.addPlayer(playerName);
    }
    Team team2(playerService.getPlayers());
    team2.setName("Team 2");
    

    teamService.addTeam(team1);
    teamService.addTeam(team2);

    cout << "No. of overs: 2" << endl;

    cout << "Batting Order for " << team1.getName() << ": ";
    for (Player player : team1.getPlayers()) {
        cout << player.getName() << " ";
    }
    cout << endl;

    // Simulate Over 1 for Team 1
    teamService.updateTeamScore(team1.getName(), 1, false, false);
    teamService.updateTeamScore(team1.getName(), 1, false, false);
    teamService.updateTeamScore(team1.getName(), 1, false, false);
    teamService.updateTeamScore(team1.getName(), 1, false, false);
    teamService.updateTeamScore(team1.getName(), 1, false, false);
    teamService.updateTeamScore(team1.getName(), 2, false, false);

    teamService.printScorecard(team1);

    // Simulate Over 2 for Team 1
    teamService.updateTeamScore(team1.getName(), 0, false, true); // Wicket
    teamService.updateTeamScore(team1.getName(), 4, false, false);
    teamService.updateTeamScore(team1.getName(), 4, false, false);
    teamService.updateTeamScore(team1.getName(), 1, true, false); // Wide
    teamService.updateTeamScore(team1.getName(), 0, false, true); // Wicket
    teamService.updateTeamScore(team1.getName(), 1, false, false);
    teamService.updateTeamScore(team1.getName(), 6, false, false);

    teamService.printScorecard(team1);

    cout << "Fall of wicket: ";
    for (const string &fall : team1.getFallOfWickets()) {
        cout << fall << ", ";
    }
    cout << endl;

    cout << "Batting Order for " << team2.getName() << ": ";
    for (Player player : team2.getPlayers()) {
        cout << player.getName() << " ";
    }
    cout << endl;

    // Simulate Over 1 for Team 2
    teamService.updateTeamScore(team2.getName(), 4, false, false);
    teamService.updateTeamScore(team2.getName(), 6, false, false);
    teamService.updateTeamScore(team2.getName(), 0, false, true); // Wicket
    teamService.updateTeamScore(team2.getName(), 0, false, true); // Wicket
    teamService.updateTeamScore(team2.getName(), 1, false, false);
    teamService.updateTeamScore(team2.getName(), 1, false, false);

    teamService.printScorecard(team2);

    // Simulate Over 2 for Team 2
    teamService.updateTeamScore(team2.getName(), 6, false, false);
    teamService.updateTeamScore(team2.getName(), 1, false, false);
    teamService.updateTeamScore(team2.getName(), 0, false, true); // Wicket
    teamService.updateTeamScore(team2.getName(), 0, false, true); // Wicket

    teamService.printScorecard(team2);

    cout << "Fall of wicket: ";
    for (const string &fall : team2.getFallOfWickets()) {
        cout << fall << ", ";
    }
    cout << endl;

    teamService.printMatchResult(team1, team2);

    return 0;
}

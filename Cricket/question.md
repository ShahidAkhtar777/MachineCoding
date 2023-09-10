## Cricket Scorecard Design Problem

### Problem Statement

Given the count of players in each team, the number of overs, and the batting order as input, the task is to record ball-by-ball actions during a cricket match, including runs scored (which could be wide, no ball, or wicket). At the end of each over, individual scores, balls faced, fours, and sixes for all players from the batting team should be displayed. Additionally, the total score and wickets should be printed. The focus is on maintaining player statistics, handling strike changes (end of the over or after singles/3s), and tracking extra deliveries (like wides or no balls). The program should also indicate the winning team at the end.

This constitutes the essential solution, and additional features like bowler statistics (overs bowled, runs conceded, wickets taken, maiden overs, dot balls, economy, etc.), team extras, batsman strike rates, etc., can be added as enhancements. However, the priority is to accomplish the core functionality first.

### Features

1. **Input:**
   - Num. of players per team.
   - Num. of overs in the match.
   - Batting order of each team.

2. **Ball-by-ball Input:**
   - Runs scored on each ball (runs, extras, wicket).

3. **Output:**
   - Player stats (scores, balls, 4s, 6s) at each over.
   - Total team score and wickets.
   - Winning team.

### Rules

- P1 at striker's end, P2 at non-striker's end initially.
- Scoring:
  - 1 run: P1 moves, P2 at strike.
  - 2 runs: P1 at strike.
  - 3 runs: P1 moves, P2 at strike.
  - 4/6 runs: P1 at strike.
  - W: Player out, new player replaces P1.
  - Wide: No strike change, 1 run to extras.
  - No ball: No strike change, 1 run to extras.

- After over:
  - Strike rotates: Striker becomes non-striker.

- Innings end:
  - When all out or required overs bowled.

### Sample Input and Output

#### Sample Input

```
No. of players for each team: 5 
No. of overs: 2

Batting Order for team 1: P1 P2 P3 P4 P5 

Over 1: 1 1 1 1 1 2

Batting Order for team 2: P6 P7 P8 P9 P10

Over 1: W 4 4 Wd W 1 6
```

#### Sample Output

```
Scorecard for Team 1: 
Player Score 4s 6s Balls 
P1*        3  0  0    3 
P2*        4  0  0    3 
P3         0  0  0    0  
P4         0  0  0    0
P5         0  0  0    0
Total: 7/0 Overs: 1

Scorecard for Team 2: 
Player Score 4s 6s Balls 
P6        10  1  1    3 
P7*        1  0  0    1 
P8         0  0  0    1 
P9*        1  0  0    1 
P10        0  0  0    0
Total: 12/1 Overs: 1
```

### Evaluation Criteria

- Demoable, correct code.
- Readable, maintainable code.
- Proper entity modeling, modularity.
- Separation of concerns, abstractions.
- Use design patterns where applicable.
- In-memory data structures, no external DB.
- Bonus features after completing required ones.

### Bonus Features

- **SDE1 Bonus:** Show fall of wickets after an innings is over.
- **SDE2 Bonus:** Implement custom rule changes to the game.

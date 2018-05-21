#ifndef BBS_H
#define BBS_H

#include <climits>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <pair>


using namespace std;

const int worldSize = 10; // for a 10x10 board
//create a structure that holds ship placements and distances
const struct distances
{
        //keeps track of how far from each ship
        int friendly;
        int enemy;
};
//create structure that holds what agent can see - shots taken, if they hit, and the number distances
const struct agentData
{
        vector<pair<int, int> > shotsTaken; //keeps track of where every shot was taken
        vector<char> hits; //F = friendly, E = enemy, N = none
        vector<distances> nearestShips; //keeps track of all the distance from a shot taken


};


class battleMap
{
public:
//pair<int, int> locationShot; //agents shot choice
//pair<int, int> distances; //how far from a ship

//need a constructor


private:
//pair<int, int> shipPlacement;
int map[worldSize][worldSize];
bool shipHit;     //true if shot hit
bool shipSank;     //true if ship sank
vector<ship> agent1, agent2;    // agent 1 and agent 2;
int misses1, misses2;     //
int hits1, hits2;
vector<agentData> agent1, agent2;     //agent 1 and agent2

};



class ship
{
public:

//recall that ships are only 3 squares long in size.

ship();        //default constructor.
ship(int length, char direction, bow, stern);     //constructor


private:



int length;     // how long - always 3 for our purposes. it may get changed (who knows)



pair<int, int> bow;     //location of the front of the ship, in (x,y) coordinates
pair<int, int> middle;     //location of the middle of the ship, in (x,y) coordinates.
pair<int, int> stern;     //location of the back of the ship, in (x,y) coordinates.



bool direction;     //horizontal or vertical
bool sank;     //if it's dead
bool bow, middle, stern;     //true = hit, false = not hit
//pair<int,int> hit; //what location was hit


};

#endif // #ifndef BBS_H

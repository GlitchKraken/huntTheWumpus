/*
    CS 4318, spring 2018
    Agent Challenge 6: Hunt the wumpus

    Chad Fry

    Description:

    This agent is a variation of the Coward agent!
    He searches every room possible for gold,
    (provided there is NO risk involved), and once he's done
    he just goes back to the start.
 */


struct Room
{


        //how dangerous the room is. this goes up as more things are discovered.
        //a danger level of -1 means nothing is known about the room.
        int DangerLevel;

        //this will keep track of the order in which we have visited a room.
        //for example, the first room we have ever been to will be room 0.
        //the next room we have been to will be order 1, and so on.
        int orderVisited;

        bool visitedBefore;

};


#include "htw.h"
#include <vector>
#include <stack>
//this guy uses a vector of actions to go backwards.

action htwAgentRoomVector(WumpusWorldSensor currentSensor, bool shouldReset)
{
        // Declare all static variables.
        static bool hasGold;
        static int whereX, whereY;

        //create a 2-dimentional array, with rows and cols.
        //that way each room can be accessed by (whereX, whereY)
        static Room Cave[4][4]; // a 4 by 4 Cave of rooms! just like the cave we're in.

        static vector<action> Path;


        if (shouldReset)
        {





                //reset all of the info we have on the rooms to "unknown" (or -1)
                for(int i = 0; i < 4; i++)
                {
                        for(int j = 0; j < 4; j++)
                        {
                                Cave[i][j].orderVisited = -1;
                                Cave[i][j].DangerLevel = -1;
                                Cave[i][j].visitedBefore= false;
                        }
                }

                //we also need to reset our path...
                while(!Path.empty())
                {
                        Path.pop_back();
                }

                Cave[0][0].visitedBefore = true;
                Cave[0][0].DangerLevel = -1;



                // Initialize all static variables.
                // Agent starts in lower left corner.
                whereX = 0;
                whereY = 0;
                // Agent starts with no gold.
                hasGold = false;
                // After initializing all static variables, return without taking an action.
                return doNothing;
        }
        // At this point, shouldReset must be false.
        // Learn new things and figure out what to do next.

        //ALWAYS check for gold before we do anything. if we have the gold, we
        //can skedaddle.



        if (!hasGold && currentSensor.perceiveGlitter())
        {
                // It glitters!  Grab it!
                hasGold = true;
                return grab;
        }

        if(whereX == 0 && whereY == 0)
        {
                //we're in square 0,0...
                if(currentSensor.perceiveBreeze())
                {
                        //don't take the risk of a breeze in 0,0 . just don't.
                        //there's too much gambling.
                        return climbOut;
                }
        }


        //update the surrounding squares as to if they're dangerous.
        if(currentSensor.perceiveBreeze() || currentSensor.perceiveStench())
        {

                //mark all possible adjacent rooms as dangerous, because we've
                //encountered a dangerous percept. we will take NO Risks!
                //since we will never go into a dangerous room,
                //we will never shoot, either.



                if(whereX - 1 >= 0)
                {
                        //only mark a room as dangerous if we haven't been there before.
                        //also, only mark rooms that can actually exist. for example, we don't
                        //consider (-1,-1) .


                        if(Cave[whereX-1][whereY].visitedBefore == false)
                        {
                                Cave[whereX-1][whereY].DangerLevel++;
                        }
                }
                if(whereX + 1 <= 3)
                {
                        if(Cave[whereX+1][whereY].visitedBefore == false)
                        {
                                Cave[whereX+1][whereY].DangerLevel++;
                        }
                }
                if(whereY - 1 >= 0)
                {
                        if(Cave[whereX][whereY-1].visitedBefore == false)
                        {
                                Cave[whereX][whereY-1].DangerLevel++;
                        }
                }
                if(whereY + 1 <= 3)
                {
                        if(Cave[whereX][whereY+1].visitedBefore == false)
                        {
                                Cave[whereX][whereY+1].DangerLevel++;
                        }
                }

        }



        if(!hasGold)
        {
                //if we don't have the gold, ***explore the first safe unexplored room.***

                //look east
                if(whereX +1 <= 3)
                {
                        if(Cave[whereX+1][whereY].DangerLevel == -1 && Cave[whereX+1][whereY].visitedBefore == false  )
                        {



                                whereX++;
                                Path.push_back(moveE);
                                Cave[whereX][whereY].visitedBefore = true;
                                return moveE;
                        }
                }
//look north
                if(whereY +1 <= 3)
                {
                        if(Cave[whereX][whereY+1].DangerLevel == -1 && Cave[whereX][whereY+1].visitedBefore == false)
                        {


                                whereY++;
                                Path.push_back(moveN);
                                Cave[whereX][whereY].visitedBefore = true;
                                return moveN;
                        }
                }
//look west
                if(whereX -1 >= 0)
                {
                        if(Cave[whereX-1][whereY].DangerLevel == -1 && Cave[whereX-1][whereY].visitedBefore == false)
                        {


                                whereX--;
                                Path.push_back(moveW);
                                Cave[whereX][whereY].visitedBefore = true;
                                return moveW;
                        }
                }
//look south
                if(whereY-1 >= 0)
                {
                        if(Cave[whereX][whereY-1].DangerLevel == -1 && Cave[whereX][whereY-1].visitedBefore == false)
                        {


                                whereY--;
                                Path.push_back(moveS);
                                Cave[whereX][whereY].visitedBefore = true;
                                return moveS;
                        }
                }

                //if we're down here, there is no safe, unexplored room to go to,
                //so we should just go back to the last room we were in, and see
                //if there's a safe room from there.



                //get ready for the huge copypasta.



                //if, there are no safe, unexplored rooms, and we're at 0,0....
                //forget it, we tried, lets go home.
                if(whereX== 0 && whereY == 0)
                {



                        //just leave, man.
                        return climbOut;
                }

                //otherwise, wee need to retrace our steps.
                //look at our last move, and return its opposite.
                if(Path.back() == moveN)
                {
                        //remove the last move made, as we are undoing it
                        //by retracing our steps.
                        Path.pop_back();
                        whereY--;
                        return moveS;
                }
                if(Path.back() == moveS)
                {
                        Path.pop_back();
                        whereY++;
                        return moveN;
                }
                if(Path.back() ==moveW)
                {
                        Path.pop_back();
                        whereX++;
                        return moveE;
                }
                if(Path.back() == moveE)
                {
                        Path.pop_back();
                        whereX--;
                        return moveW;
                }

        }

        if(hasGold)
        {
                //we need to escape, because we have the gold.


                //if we're at the beginning, we can just leave.
                //yaaaay, we're rich!
                if(whereX== 0 && whereY == 0)
                {
                        //just leave, man.
                        return climbOut;
                }

                //otherwise, wee need to retrace our steps.
                //look at our last move, and return its opposite.
                if(Path.back() == moveN)
                {
                        Path.pop_back();
                        whereY--;
                        return moveS;
                }
                if(Path.back() == moveS)
                {
                        Path.pop_back();
                        whereY++;
                        return moveN;
                }
                if(Path.back() ==moveW)
                {
                        Path.pop_back();
                        whereX++;
                        return moveE;
                }
                if(Path.back() == moveE)
                {
                        Path.pop_back();
                        whereX--;
                        return moveW;
                }

        }


}

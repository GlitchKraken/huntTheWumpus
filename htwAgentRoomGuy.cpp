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



};


#include "htw.h"

action htwAgentRoomGuy(WumpusWorldSensor currentSensor, bool shouldReset)
{
        // Declare all static variables.
        static bool hasGold;
        static int whereX, whereY;
        static int roomNum;
        //create a 2-dimentional array, with rows and cols.
        //that way each room can be accessed by (whereX, whereY)
        static Room Cave[4][4]; // a 4 by 4 Cave of rooms! just like the cave we're in.




        if (shouldReset)
        {

                roomNum = 0;

                //reset all of the info we have on the rooms to "unknown" (or -1)
                for(int i = 0; i < 4; i++)
                {
                        for(int j = 0; j < 4; j++)
                        {
                                Cave[i][j].orderVisited = -1;
                                Cave[i][j].DangerLevel = -1;
                        }
                }


                Cave[0][0].orderVisited = roomNum;
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


                        if(Cave[whereX-1][whereY].orderVisited == -1)
                        {
                                Cave[whereX-1][whereY].DangerLevel++;
                        }
                }
                if(whereX + 1 <= 3)
                {
                        if(Cave[whereX+1][whereY].orderVisited == -1)
                        {
                                Cave[whereX+1][whereY].DangerLevel++;
                        }
                }
                if(whereY - 1 >= 0)
                {
                        if(Cave[whereX][whereY-1].orderVisited == -1)
                        {
                                Cave[whereX][whereY-1].DangerLevel++;
                        }
                }
                if(whereY + 1 <= 3)
                {
                        if(Cave[whereX][whereY+1].orderVisited == -1)
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
                        if(Cave[whereX+1][whereY].DangerLevel == -1 && Cave[whereX+1][whereY].orderVisited == -1  )
                        {

                                roomNum++;
                                Cave[whereX+1][whereY].orderVisited = roomNum;
                                whereX++;
                                return moveE;
                        }
                }
//look north
                if(whereY +1 <= 3)
                {
                        if(Cave[whereX][whereY+1].DangerLevel == -1 && Cave[whereX][whereY+1].orderVisited == -1)
                        {

                                roomNum++; //update the rooms number, as we visit new rooms, this static int will only increase.
                                Cave[whereX][whereY+1].orderVisited = roomNum;
                                whereY++;
                                return moveN;
                        }
                }
//look west
                if(whereX -1 >= 0)
                {
                        if(Cave[whereX-1][whereY].DangerLevel == -1 && Cave[whereX-1][whereY].orderVisited == -1)
                        {

                                roomNum++;
                                Cave[whereX-1][whereY].orderVisited = roomNum;
                                whereX--;
                                return moveW;
                        }
                }
//look south
                if(whereY-1 >= 0)
                {
                        if(Cave[whereX][whereY-1].DangerLevel == -1 && Cave[whereX][whereY-1].orderVisited == -1)
                        {

                                roomNum++;
                                Cave[whereX][whereY-1].orderVisited = roomNum;
                                whereY--;
                                return moveS;
                        }
                }

                //if we're down here, there is no safe room to go to,
                //so we should go to the room adjacent to me with room num = thisRoomNum-1.
                //this will put us in the room we were previously in. we can then keep doing that
                //until we reach 0,0


                //get ready for the huge copypasta.


                //if we're at the beginning, we can just leave.
                if(whereX== 0 && whereY == 0)
                {
                        //just leave, man.
                        return climbOut;
                }

                //otherwise, wee need to retrace our steps.

                //look east.
                if(whereX + 1 <=3)
                {
                        //check if it was where we were.
                        if(Cave[whereX+1][whereY].orderVisited == Cave[whereX][whereY].orderVisited-1)
                        {
                                whereX++;
                                return moveE;
                        }
                }
                //look west.
                if(whereX -1 >= 0 )
                {
                        if(Cave[whereX-1][whereY].orderVisited == Cave[whereX][whereY].orderVisited-1)
                        {
                                whereX--;
                                return moveW;
                        }
                }

                //look north
                if(whereY + 1 <= 3)
                {
                        if(Cave[whereX][whereY+1].orderVisited == Cave[whereX][whereY].orderVisited-1)
                        {
                                whereY++;
                                return moveN;
                        }
                }

                //look south
                if(whereY - 1 >= 0)
                {
                        if(Cave[whereX][whereY-1].orderVisited == Cave[whereX][whereY].orderVisited-1)
                        {
                                whereY--;
                                return moveS;
                        }
                }

        }

        if(hasGold)
        {
                //we need to escape, because we have the gold.


                //if we're at the beginning, we can just leave.
                if(whereX== 0 && whereY == 0)
                {
                        //just leave, man.
                        return climbOut;
                }

                //otherwise, wee need to retrace our steps.

                //look east.
                if(whereX + 1 <=3)
                {
                        //check if it was where we were.
                        if(Cave[whereX+1][whereY].orderVisited == Cave[whereX][whereY].orderVisited-1)
                        {
                                whereX++;
                                return moveE;
                        }
                }
                //look west.
                if(whereX -1 >= 0 )
                {
                        if(Cave[whereX-1][whereY].orderVisited == Cave[whereX][whereY].orderVisited-1)
                        {
                                whereX--;
                                return moveW;
                        }
                }

                //look north
                if(whereY + 1 <= 3)
                {
                        if(Cave[whereX][whereY+1].orderVisited == Cave[whereX][whereY].orderVisited-1)
                        {
                                whereY++;
                                return moveN;
                        }
                }

                //look south
                if(whereY - 1 >= 0)
                {
                        if(Cave[whereX][whereY-1].orderVisited == Cave[whereX][whereY].orderVisited-1)
                        {
                                whereY--;
                                return moveS;
                        }
                }
        }


        //return climbOut;
}

/*
    CS 4318, spring 2018
    Agent Challenge 6: Hunt the wumpus

    Chad Fry


    --------------------------------------------------------------------------
    Description:


    Forgive the ludicrously long code below, I've documented it well,
    and there IS method to the madness!

    The main idea I came up with this first iteration was:

    "go into every safe room possible, but take no risks whatsoever."

    once I've gotten an agent working that can safely explore and return,
    THEN I'll begin work on one that shoots, and adjusts risks.

    ========================================================================
    ITERATION 2:

    This time around, I coded in some logic to deal with the grumpy wumpus!
    still not taking any risks with the pits though, as everything I've
    tried with them, from calculating probabilities to only occasionally
    risking a pit results in a massive loss in points.


    I DID IT!!!! I GOT TO 355!!! IM SO PROUD OF ME!!!!!!!
    --------------------------------------------------------------------------
 */


//try to narrow down the wumpusseses location first, THEN shoot the arrow... perhaps only shoot
// if .Wumpus > 1?


struct Room
{


        //how dangerous the room is. this goes up as more things are discovered.
        //a danger level of -1 means nothing is known about the room, or that it is
        //proabbly safe.
        int DangerLevel;




        bool visitedBefore;

        //these two ints will replace the dangerlevel, essentially.
        int Wumpus;
        int Pit;

};


#include "htw.h"
#include <vector>
#include <stack>
//this guy uses a vector of actions to go backwards.

action htwAgentHollowKnight(WumpusWorldSensor currentSensor, bool shouldReset)
{
        // Declare all static variables.
        static bool hasGold;
        static bool shotArrow;
        static int whereX, whereY;

        //create a 2-dimentional array, with rows and cols.
        //that way each room can be accessed by (whereX, whereY)
        static Room Cave[4][4]; // a 4 by 4 Cave of rooms! just like the cave we're in.

        //this here will represent the path we've taken thus far.
        //as we adventure, more moves will be pushed back to it- just like agent challenge orr.
        static vector<action> Path;


        if (shouldReset)
        {



                shotArrow = false;

                //reset all of the info we have on the rooms to "unknown" (or -1)
                for(int i = 0; i < 4; i++)
                {
                        for(int j = 0; j < 4; j++)
                        {
                                Cave[i][j].DangerLevel = -1;
                                Cave[i][j].visitedBefore= false;
                                Cave[i][j].Wumpus = 0;
                                Cave[i][j].Pit = 0;
                        }
                }

                //we also need to reset our path...
                while(!Path.empty())
                {
                        Path.pop_back();
                }


                //the spawn room is definitely safe.
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





        //if the wumpus dies, mark every room wumpus-free.
        if(currentSensor.perceiveScream())
        {

            for(int i = 0; i < 4; i++)
            {
                for(int j = 0; j < 4; j++)
                {
                    Cave[i][j].Wumpus = -100;
                }
            }
        }


        //find the stinkiest room, and fire in that direction.



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

        //if we're in a non-breezy room, the rooms adjacent to us
        //CANNOT contain pits.
        if(!currentSensor.perceiveBreeze())
        {
            if(whereX+1 <=3)
            {
                Cave[whereX+1][whereY].Pit = -5;
            }
            if(whereX-1 >=0)
            {
                Cave[whereX-1][whereY].Pit = -5;
            }
            if(whereY-1 >=0)
            {
                Cave[whereX][whereY-1].Pit = -5;
            }
            if(whereY+1 <=3)
            {
                Cave[whereX][whereY+1].Pit =-5;
            }
        }



        //update the surrounding squares as to if they're dangerous.
        //here we don't even care why they're dangerous, just that they are.
        if(currentSensor.perceiveBreeze() || currentSensor.perceiveStench())
        {

                //mark all possible adjacent rooms as dangerous, because we've
                //encountered a dangerous percept. we will take NO Risks!
                //since we will never go into a dangerous room,
                //we will never shoot, either. (hey, more arrows for me!)



                //consider the room to the west of us.

                if(whereX - 1 >= 0)
                {
                        //only mark a room as dangerous if we haven't been there before.
                        //a room can only be dangerous if we weren't there, since nothing moves.
                        //also, only mark rooms that can actually exist. for example, we don't
                        //consider (-1,-1).


                        if(Cave[whereX-1][whereY].visitedBefore == false)
                        {
                                if(currentSensor.perceiveStench() && !currentSensor.perceiveBreeze())
                                {
                                    Cave[whereX-1][whereY].Wumpus++;
                                    if(!shotArrow && Cave[whereX-1][whereY].Wumpus >= 1)
                                    {

                                        shotArrow = true;

                                        //now we'll mark all of the other rooms in this direction as
                                        //safe from wumpi.
                                        for(int i = whereX; i >= 0; i--)
                                        {
                                            Cave[i][whereY].Wumpus = -5;
                                            //the point of using such a low number is
                                            //that if I ever smell the stentch again,
                                            //I can still go here now
                                        }

                                        return shootW;
                                    }
                                }
                                else
                                {
                                    //this must be a pit.
                                    Cave[whereX-1][whereY].Pit++;
                                }

                        }
                }

                //consider the room east of us.
                if(whereX + 1 <= 3)
                {
                        if(Cave[whereX+1][whereY].visitedBefore == false)
                        {
                            if(currentSensor.perceiveStench() && !currentSensor.perceiveBreeze())
                            {
                                Cave[whereX+1][whereY].Wumpus++;
                                if(!shotArrow && Cave[whereX+1][whereY].Wumpus >= 1)
                                {
                                    shotArrow = true;

                                    for(int i = whereX; i <= 3; i++)
                                    {
                                        Cave[i][whereY].Wumpus = -5;
                                    }

                                    return shootE;
                                }
                            }
                            else
                            {
                                //this must be a pit.
                                Cave[whereX+1][whereY].Pit++;
                            }
                        }
                }

                //consider the room south of us.
                if(whereY - 1 >= 0)
                {
                        if(Cave[whereX][whereY-1].visitedBefore == false)
                        {
                            if(currentSensor.perceiveStench() && !currentSensor.perceiveBreeze())
                            {
                                Cave[whereX][whereY-1].Wumpus++;
                                if(!shotArrow && Cave[whereX][whereY-1].Wumpus >= 1)
                                {
                                    shotArrow = true;

                                    for(int i = whereY; i >= 0; i--)
                                    {
                                        Cave[whereX][i].Wumpus = -5;
                                    }

                                    return shootS;
                                }
                            }
                            else
                            {
                                //this must be a pit.
                                Cave[whereX][whereY-1].Pit++;
                            }
                        }
                }

                //consider the room north of us.
                if(whereY + 1 <= 3)
                {
                        if(Cave[whereX][whereY+1].visitedBefore == false)
                        {
                            if(currentSensor.perceiveStench() && !currentSensor.perceiveBreeze())
                            {
                                Cave[whereX][whereY+1].Wumpus++;
                                if(!shotArrow && Cave[whereX][whereY+1].Wumpus >= 1)
                                {
                                    shotArrow = true;

                                    for(int i = whereY; i <= 3; i++)
                                    {
                                        Cave[whereX][i].Wumpus = -5;
                                    }

                                    return shootN;
                                }
                            }
                            else
                            {
                                //this must be a pit.
                                Cave[whereX][whereY+1].Pit++;
                            }
                        }
                }

        }



        if(!hasGold)
        {
                //if we don't have the gold, ***explore the first safe unexplored room.***

                //look east
                if(whereX +1 <= 3)
                {
                        if(Cave[whereX+1][whereY].Wumpus <= 0 && Cave[whereX+1][whereY].Pit <= 0  && Cave[whereX+1][whereY].visitedBefore == false  )
                        {


                                //update position
                                whereX++;
                                //update our path that we use to go back to the beginning.
                                Path.push_back(moveE);
                                //mark the room we're moving into as explored.
                                Cave[whereX][whereY].visitedBefore = true;
                                //actually move there.
                                return moveE;
                        }
                }
//look north
                if(whereY +1 <= 3)
                {
                        if(Cave[whereX][whereY+1].Wumpus <= 0 && Cave[whereX][whereY+1].Pit <= 0 && Cave[whereX][whereY+1].visitedBefore == false)
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
                        if(Cave[whereX-1][whereY].Wumpus <= 0 && Cave[whereX-1][whereY].Pit <= 0 &&  Cave[whereX-1][whereY].visitedBefore == false)
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
                        if(Cave[whereX][whereY-1].Wumpus <= 0 && Cave[whereX][whereY-1].Pit <= 0  && Cave[whereX][whereY-1].visitedBefore == false)
                        {


                                whereY--;
                                Path.push_back(moveS);
                                Cave[whereX][whereY].visitedBefore = true;
                                return moveS;
                        }
                }

                //if we're down here, there IS NO safe, unexplored room to go to,
                //so we should just go back to the last room we were in, and see
                //if there's a safe room from there.

                //doing this makes it such that we explore all possible safe rooms!



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
        //if by some black magic we wind up here, something crazy is going on,
        //so its probably best we just sit still while reality collapses.
        return doNothing;
}

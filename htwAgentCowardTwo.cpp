// CS 4318, spring 2018
// Agent Challenge 6: Hunt the wumpus
//
// Here's an example agent function.

#include "htw.h"

action htwAgentCowardTwo(WumpusWorldSensor currentSensor, bool shouldReset)
{
        // Declare all static variables.
        static bool hasGold;
        static int whereX, whereY;
        static bool moveEast;
        static bool moveNorth;
        static bool haveArrow;

        if (shouldReset)
        {

                moveEast = true; //we start by moving right first... we'll move counter clockwise.
                moveNorth = false;
                haveArrow = true;
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

        if (!hasGold && currentSensor.perceiveGlitter())
        {
                // It glitters!  Grab it!
                hasGold = true;
                return grab;
        }


        if (whereX == 0)
        {


                if (hasGold)
                {
                        return climbOut;
                }

                if (currentSensor.perceiveBreeze())
                {
                    moveEast = false;
                    whereX -= 1;
                    return moveW;
                }

                if (currentSensor.perceiveBreeze() && currentSensor.perceiveStench())
                {
                        return climbOut;
                }

                if (!currentSensor.perceiveBreeze() && currentSensor.perceiveStench() && haveArrow)
                {
                        haveArrow = false;
                        return shootE;
                }

                if (moveEast)
                {
                        whereX += 1;
                        return moveE;
                }

                if (!moveEast)
                {
                    return climbOut;
                }
        }

        if (whereX == 1)
        {
                if (hasGold)
                {
                        moveEast = false;
                        whereX -= 1;
                        return moveW;
                }

                if (currentSensor.perceiveBreeze())
                {
                    moveEast = false;
                    whereX -= 1;
                    return moveW;
                }

                if (currentSensor.perceiveBreeze() && currentSensor.perceiveStench())
                {
                        moveEast = false;
                        whereX -= 1;
                        return moveW;
                }

                if (!currentSensor.perceiveBreeze() && currentSensor.perceiveStench() && haveArrow)
                {
                        haveArrow = false;
                        return shootE;
                }


                if (moveEast)
                {
                        whereX += 1;
                        return moveE;
                }

                if(!moveEast)
                {
                    whereX -= 1;
                    return moveW;
                }
        }

        if (whereX == 2)
        {
            if (hasGold)
            {
                    moveEast = false;
                    whereX -= 1;
                    return moveW;
            }

            if (currentSensor.perceiveBreeze())
            {
                moveEast = false;
                whereX -= 1;
                return moveW;
            }

            if (currentSensor.perceiveBreeze() && currentSensor.perceiveStench())
            {
                    moveEast = false;
                    whereX -= 1;
                    return moveW;
            }

            if (!currentSensor.perceiveBreeze() && currentSensor.perceiveStench() && haveArrow)
            {
                    haveArrow = false;
                    return shootE;
            }


            if (moveEast)
            {
                    whereX += 1;
                    return moveE;
            }

            if(!moveEast)
            {
                whereX -= 1;
                return moveW;
            }
        }

        if (whereX == 3)
        {
            if (hasGold)
            {
                    moveEast = false;
                    whereX -= 1;
                    return moveW;
            }

            if (currentSensor.perceiveBreeze())
            {
                moveEast = false;
                whereX -= 1;
                return moveW;
            }

            if (currentSensor.perceiveBreeze() && currentSensor.perceiveStench())
            {
                    moveEast = false;
                    whereX -= 1;
                    return moveW;
            }

            if (whereX == 3)
            {
                    moveEast = false;
                    whereX -= 1;
                    return moveW;
            }

            if(!moveEast)
            {
                whereX -= 1;
                return moveW;
            }
        }

        // Must be in lower left corner then!
        return climbOut;
}

// CS 4318, spring 2018
// Agent Challenge 6: Hunt the wumpus
//
// Here's an example agent function.

//adding a new comment here, but also deleting some old text.

#include "htw.h"

action htwAgentCoward(WumpusWorldSensor currentSensor, bool shouldReset)
{
        // Declare all static variables.
        static bool hasGold;
        static int whereX, whereY;

        if (shouldReset)
        {
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
        if (whereX > 0)
        {
                // Not on western edge, so move west.
                whereX -= 1;
                return moveW;
        }
        if (whereY > 0)
        {
                // Not on southern edge, so move south.
                whereY -= 1;
                return moveS;
        }
        // Must be in lower left corner then!
        return climbOut;
}

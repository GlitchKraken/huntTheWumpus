# Hunt The Wumpus!

A short project I did to create the "perfect" gold-hunting robot for the age-old game:  "hunt the wumpus". 

## What exactly is the "hunt the wumpus" game?

In the original Hunt The Wumpus game, the goal was to go into a spooky cave- to actually hunt down and kill
a beast known as the "Wumpus". In this variation, however, the goal is a little different. Here, we design bots that
search the wumpus' lair for gold, and then run back out to escape. To do so, each "bot", or "agent"  will return an action upon being called:
 "move-east", "move-west", "do-nothing", "shoot-arrow", etc.  

Each agent is started in the bottom left corner of a 4 x 4 grid of rooms. a (0,0) if you will.
Since it is the entrance (and also the only exit) of the cave, this one room is guaranteed to
be safe. 

Of course, the lair of the wumpus is no place for the meek! there are bottomless pits all over the cave,
and worse yet, somewhere inside is the fearsome wumpus itself! 

currently, the wumpus is rather lazy, and does not move. 

#### Senses-
- Breeze (there is a pit in an adjacent room)
- Stench (there is a wumpus in an adjacent room)
- Bump (you feel a wall nearby)
- Scream (you heard an awful scream -- the wumpus is dead! +100 points)
- Glitter (the gold is in your room! better nab it!)

#### Available Actions- 
- DoNothing (don't move. -1 point)
- Grab (you try to pick something up. -1 point)
- Shoot[N, S, E, W] (you shoot the arrow in a direction  -10 points)
- Move[N, S, E, W] (you attempt to move in a direction. you might walk into a wall and feel a bump though!)

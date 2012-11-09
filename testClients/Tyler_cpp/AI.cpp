#include "AI.h"
#include "util.h"
#include <cstdlib>
#include <cmath>

AI::AI(Connection* conn) : BaseAI(conn) {}

const char* AI::username()
{
  return "darklordtyler";
}

const char* AI::password()
{
  return "password";
}
bool AI::isValid(int x, int y)
{
   bool valid = true;
   if(x >= mapWidth() || x < 0 || y >= mapHeight() || y < 0)
   {
      valid = false;
   }
   for(int i = 0; i < mappables.size(); i++)
   {
      if(mappables[i].x() == x && mappables[i].y() == y)
      {
         
         valid = false;
      }
   }
   return valid;
}
/*
float distance(float x1, float x2, float y1, float y2)
{
   return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}
*/
Creature* AI::findAdjacentEnemy(Creature* & c)
{
   int creaturex = c -> x();
   int creaturey = c -> y();
   Creature* tmp = NULL;
   
   for(int i = 0; i < creatures.size(); i++)
   {
      if(creatures[i].owner() != playerID())
      {
         if(creatures[i].x() == creaturex + 1 && creatures[i].y() == creaturey) // right
         {
            tmp = &creatures[i];
         }
         if(creatures[i].x() == creaturex - 1 && creatures[i].y() == creaturey) // left
         {
            tmp = &creatures[i];
         }
         if(creatures[i].x() == creaturex && creatures[i].y() == creaturey + 1) // down
         {
            tmp = &creatures[i];
         }
         if(creatures[i].x() == creaturex && creatures[i].y() == creaturey - 1) // up
         {
            tmp = &creatures[i];
         }
      }
   }
   
   return tmp;
}

Creature* AI::findAdjacentFriend(Creature* & c)
{
   int creaturex = c -> x();
   int creaturey = c -> y();
   Creature* tmp = NULL;
   
   for(int i = 0; i < creatures.size(); i++)
   {
      if(creatures[i].owner() == playerID())
      {
         if(creatures[i].x() == creaturex + 1 && creatures[i].y() == creaturey) // right
         {
            tmp = &creatures[i];
         }
         if(creatures[i].x() == creaturex - 1 && creatures[i].y() == creaturey) // left
         {
            tmp = &creatures[i];
         }
         if(creatures[i].x() == creaturex && creatures[i].y() == creaturey + 1) // down
         {
            tmp = &creatures[i];
         }
         if(creatures[i].x() == creaturex && creatures[i].y() == creaturey - 1) // up
         {
            tmp = &creatures[i];
         }
      }
   }
   
   return tmp;
}

Plant* AI::findAdjacentPlant(Creature* & c)
{
   int creaturex = c -> x();
   int creaturey = c -> y();
   Plant* tmp = NULL;
   
   for(int i = 0; i < plants.size(); i++)
   {
      if(plants[i].x() == creaturex + 1 && plants[i].y() == creaturey) // right
      {
         tmp = &plants[i];
      }
      if(plants[i].x() == creaturex - 1 && plants[i].y() == creaturey) // left
      {
         tmp = &plants[i];
      }
      if(plants[i].x() == creaturex && plants[i].y() == creaturey + 1) // down
      {
         tmp = &plants[i];
      }
      if(plants[i].x() == creaturex && plants[i].y() == creaturey - 1) // up
      {
         tmp = &plants[i];
      }
   }
   
   return tmp;
}

bool AI::goLeft(Creature* & c)
{
   if(isValid(c -> x() - 1, c -> y()))
   {
      c -> move(c -> x() - 1, c -> y());
      return true;
   }
   return false;
}

bool AI::goRight(Creature* & c)
{
   if(isValid(c -> x() + 1, c -> y()))
   {
      c -> move(c -> x() + 1, c -> y());
      return true;
   }
   return false;
}

bool AI::goUp(Creature* & c)
{
   if(isValid(c -> x(), c -> y() - 1))
   {
      c -> move(c -> x(), c -> y() - 1);
      return true;
   }
   return false;
}

bool AI::goDown(Creature* & c)
{
   if(isValid(c -> x(), c -> y() + 1))
   {
      c -> move(c -> x(), c -> y() + 1);
      return true;
   }
   return false;
}

void AI::stupidMove(Creature* & c)
{
   int moves = 0;
   int max = (c -> movementLeft() / 2) + 1;
   int centerx = mapWidth() / 2;
   int centery = mapHeight() / 2;
   bool right = true;
   bool up = false;
   bool left = false;
   bool down = false;
   int badrun = 2;
   int trial = 0;
   
   while(moves < max)
   {
      int x = c -> x();
      int y = c -> y();
      
      if((centery - y > centerx - x && centery - y > 0 && trial == 0) || (badrun == 4 && trial != 0))
      {
         if(goDown(c))
         {
            moves++;
            trial = 0;
            badrun = 2;
         }
         else
         {
            badrun = 1;
            trial++;
         }
      }
      else if((centerx - x > centery - y && centerx - x > 0 && trial == 0) || (badrun == 1 && trial != 0))
      {
         if(goRight(c))
         {
            moves++;
            trial = 0;
            badrun = 2;
         }
         else
         {
            badrun = 2;
            trial++;
         }
      }
      else if((centerx - x > centery - y && centery - y < 0 && trial == 0) || (badrun == 2 && trial != 0))
      {
         if(goUp(c))
         {
            moves++;
            trial = 0;
            badrun = 2;
         }
         else
         {
            badrun = 3;
            trial++;
         }
      }
      else if((((centery - y > centerx - x && centerx - x < 0) || centerx - x == centery - y) && trial == 0) || (badrun == 3 && trial != 0))
      {
         if(goLeft(c))
         {
            moves++;
            trial = 0;
            badrun = 2;
         }
         else
         {
            badrun = 4;
            trial++;
         }
      }
      else
      {
         return;
      }
   }
}


//This function is run once, before your first turn.
void AI::init(){}


//This function is called each time it is your turn.
//Return true to end your turn, return false to ask the server for updated information.
bool AI::run()
{
  Creature* myCreatures[100];
  Creature* enemies[100];
  Creature* bestCreatures[5];
  int numMyCreatures = 0;
  int numEnemies = 0;
  int position1 = 0;
  int position2 = 0;
  // dudes with max stats
  int maxStrength = 0;
  int maxHerbivore = 0;
  int maxCarnivore = 0;
  int maxSpeedster = 0;
  int maxShield = 0;
  int bestlocx = mapWidth() / 2;
  int bestlocy = mapHeight() / 2;
  int plantx = -1;
  int planty = -1;
  float dist = mapWidth();
   
  for(int i = 0; i < creatures.size(); i++)
  {
    if(creatures[i].owner() == playerID())
    {
      myCreatures[position1] = &creatures[i];
      numMyCreatures++;
      position1++;
      int health = creatures[i].maxHealth();
      int herb = creatures[i].herbivorism();
      int carn = creatures[i].carnivorism();
      int speed = creatures[i].speed();
      int def = creatures[i].defense();
      if(health > maxStrength)
      {
         bestCreatures[0] = &creatures[i];
      }
      if(herb > maxHerbivore)
      {
         bestCreatures[1] = &creatures[i];
      }
      if(carn > maxCarnivore)
      {
         bestCreatures[2] = &creatures[i];
      }
      if(speed > maxSpeedster)
      {
         bestCreatures[3] = &creatures[i];
      }
      if(def > maxShield)
      {
         bestCreatures[4] = &creatures[i];
      }
    }
    else
    {
      enemies[position2] = &creatures[i];
      numEnemies++;
      position2++;
    }
  }
  /*
  for(int i = 0; i < plants.size(); i++)
  {
    float plantdist = distance(plants[i].x(), bestlocx, plants[i].y(), bestlocy);
    if(plantdist < dist)
    {
      dist = plantdist;
      plantx = plants[i].x();
      planty = plants[i].y();
    }
  }
  
  float munchies = distance(bestCreatures[1] -> x(), plantx, bestCreatures[1] -> y(), planty);
  if(munchies == 1)
  {
    bestCreatures[1] -> eat(plantx, planty);
  }
  else
  {
    int movesLeft = bestCreatures[1] -> movementLeft() / 3;
    while(movesLeft > 0 && munchies > 1)
    {
      pathfind(bestCreatures[1], bestCreatures[1] -> x(), bestCreatures[1] -> y(), plantx, planty, movesLeft);
    }
  }
  */
  
  for(int i = 0; i < numMyCreatures; i++)
  {
    int movesLeft = myCreatures[i] -> movementLeft();
    int xloc = myCreatures[i] -> x();
    int yloc = myCreatures[i] -> y();
    int health = myCreatures[i] -> maxHealth();
    int herb = myCreatures[i] -> herbivorism();
    int carn = myCreatures[i] -> carnivorism();
    int speed = myCreatures[i] -> speed();
    int def = myCreatures[i] -> defense();
    Creature* food = NULL;
    Creature* mate = NULL;
    Plant* shrub = NULL;
    
    if(myCreatures[i] -> canEat())
    {
      food = findAdjacentEnemy(myCreatures[i]);
      shrub = findAdjacentPlant(myCreatures[i]);
      if(food != NULL)
      {
         myCreatures[i] -> eat(food -> x(), food -> y());
      }
      else if(shrub != NULL)
      {
         myCreatures[i] -> eat(shrub -> x(), shrub -> y());
      }
    }
    
    stupidMove(myCreatures[i]);
    
    if(myCreatures[i] -> canBreed())
    {
      mate = findAdjacentFriend(myCreatures[i]);
      if(mate != NULL)
      {
         myCreatures[i] -> breed(*mate);
         stupidMove(mate);
      }
    }
    stupidMove(myCreatures[i]);
    
   
  }
  
  return true;
}

//This function is run once, after your last turn.
void AI::end(){}

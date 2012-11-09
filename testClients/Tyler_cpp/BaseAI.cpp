//Copyright (C) 2009 - Missouri S&T ACM AI Team
//Please do not modify this file while building your AI
//See AI.h & AI.cpp for that

#include "BaseAI.h"
#include "game.h"

int BaseAI::turnNumber()
{
  return getTurnNumber(c);
}
int BaseAI::playerID()
{
  return getPlayerID(c);
}
int BaseAI::gameNumber()
{
  return getGameNumber(c);
}
int BaseAI::mapWidth()
{
  return getMapWidth(c);
}
int BaseAI::mapHeight()
{
  return getMapHeight(c);
}
/*
int BaseAI::energyPerBreed()
{
  return getEnergyPerBreed(c);
}

int BaseAI::energyPerAction()
{
  return getEnergyPerAction(c);
}
int BaseAI::energyPerTurn()
{
  return getEnergyPerTurn(c);
}
*/
bool BaseAI::startTurn()
{
  static bool initialized = false;
  int count = 0;
  count = getMappableCount(c);
  mappables.clear();
  mappables.resize(count);
  for(int i = 0; i < count; i++)
  {
    mappables[i] = Mappable(getMappable(c, i));
  }

  count = getCreatureCount(c);
  creatures.clear();
  creatures.resize(count);
  for(int i = 0; i < count; i++)
  {
    creatures[i] = Creature(getCreature(c, i));
  }

  count = getPlantCount(c);
  plants.clear();
  plants.resize(count);
  for(int i = 0; i < count; i++)
  {
    plants[i] = Plant(getPlant(c, i));
  }

  count = getPlayerCount(c);
  players.clear();
  players.resize(count);
  for(int i = 0; i < count; i++)
  {
    players[i] = Player(getPlayer(c, i));
  }

  if(!initialized)
  {
    initialized = true;
    init();
  }
  return run();
}

BaseAI::BaseAI(Connection* conn) : c(conn) {}
BaseAI::~BaseAI() {}

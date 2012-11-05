#-*-python-*-
from BaseAI import BaseAI
from GameObject import *
import random
import math
import heapq
		
class AI(BaseAI):
  """The class implementing gameplay logic."""
  @staticmethod
  def username():
    return "Kellogg"

  @staticmethod
  def password():
    return "password"

  ##This function is called once, before your first turn
  def init(self):
    pass
 
  ##This function is called once, after your last turn
  def end(self):
    pass

  def moveTo(self,creature,target):
     path = self.pathFind(creature.x,creature.y,target.x,target.y)
     if path != None:
       while creature.movementLeft>0 and len(path)>0:
         next = path.pop()
         if next!=(creature.x,creature.y):
           creature.move(next[0],next[1])
      
  def distance(self,sourceX,sourceY,destX,destY):
    return int(math.sqrt((sourceX-destX)**2+(sourceY-destY)**2))
    
  def maxStat(self,creature):
    return max([creature.herbivorism,creature.carnivorism,creature.speed,creature.energy,creature.defense])

#TODO FIX    
  def findMate(self,creature):
      pass
        
  def getObject(self,x,y):
    return [lifeform for lifeform in self.creatures+self.plants if lifeform.x == x and lifeform.y == y]
    
  def findNearest(self,source,list):
    d = {self.distance(source.x,source.y,lifeform.x,lifeform.y):lifeform for lifeform in list if lifeform.id != source.id}
    return d[min(d)]    
  
  
  def adjacent(self,x,y,points):
    walls = [(lifeform.x,lifeform.y) for lifeform in self.plants+self.creatures if (lifeform.x,lifeform.y) not in points or isinstance(lifeform,Plant) and lifeform.size==0]
    adj = []
    if x+1<self.mapWidth and (x+1,y) not in walls:
        adj.append((x+1,y))
    if y-1>=0 and (x,y-1) not in walls:
        adj.append((x,y-1))
    if x-1>=0 and (x-1,y) not in walls:
        adj.append((x-1,y))
    if y+1<self.mapHeight and (x,y+1) not in walls:
        adj.append((x,y+1))
    return adj
  
  def pathFind(self,startX,startY,goalX,goalY):
    closedSet = set();closedTup=set()
    open = [(self.distance(startX,startY,goalX,goalY),(startX,startY),(startX,startY),0)];openTup=[(startX,startY)]
    path = []#;ii=0
    while len(open)>0:
        open.sort()
        current = open[0]
        if current[1] == (goalX,goalY):
            node = current
            path = []
            while node[2]!=(startX,startY):
#              print "ii",ii
#              ii+=1
              for closed in closedSet:
#                print len(closedSet)
                if node[2] == closed[1]:
                  path.append(node[2])
                  node = closed
            return path
        closedSet.add(current);closedTup.add(current[1])
        open.remove(current); openTup.remove(current[1])
        for neighbor in self.adjacent(current[1][0],current[1][1],[(startX,startY),(goalX,goalY)]):
          if neighbor in closedTup:
          #if neighbor in [b[1] for b in closedSet]:
           continue
#          print current[3],neighbor[0],neighbor[1],current[1][0],current[1][1]
          g = current[3]+self.distance(neighbor[0],neighbor[1],current[1][0],current[1][1])
          if neighbor == (goalX,goalY) or self.distance(neighbor[0],neighbor[1],startX,startY)<=g+1 and neighbor not in openTup:
#          if self.distance(neighbor[0],neighbor[1],startX,startY)<=g+1 and neighbor not in [b[1] for b in open]:
            neighborTup = (g+self.distance(neighbor[0],neighbor[1],goalX,goalY),(neighbor[0],neighbor[1]),(current[1]),g)
            open.append(neighborTup);openTup.append(neighbor)
    return None
    
  ##This function is called each time it is your turn
  ##Return true to end your turn, return false to ask the server for updated information
  def run(self):   
    adjacent = [[1,0],[-1,0],[0,1],[0,-1]]    
    herbivores = [creature for creature in self.creatures if creature.owner == self.playerID and creature.herbivorism == self.maxStat(creature)]  
    carnivores = [creature for creature in self.creatures if creature.owner == self.playerID and creature.carnivorism == self.maxStat(creature)] 
    
    for creature in self.creatures:
     if creature.owner == self.playerID:             
       randPlant = self.plants[random.randrange(-1,len(self.plants))];room = True
       for adj in adjacent:
         if len(self.getObject(randPlant.x+adj[0],randPlant.y+adj[1]))>0:
           room = False
       if room:
         self.moveTo(creature,self.plants[self.playerID])
      # randx=random.randrange(-1,2); 
      # randy = abs(randx)^1*((-1)**random.randrange(1,100)%2)
      # x=0;y=0
      # if self.getObject(creature.x+randx,creature.y+randy) is None and (0<creature.x+randx<self.mapWidth) and (0<creature.y+randy<self.mapHeight):
        # creature.move(creature.x+randx,creature.y+randy)
      # for location in adjacent:
        # thingList=self.getObject(creature.x+location[0],creature.y+location[1]); thing = None
        # if len(thingList)>0:
          # thing = thingList[0]
        # if isinstance(thing,Plant) and thing.size>0 and creature.canEat:
         # creature.eat(thing.x,thing.y)
        # if isinstance(thing,Creature):
          # if thing.owner==self.playerID and thing.currentHealth > self.healthPerBreed and creature.currentHealth > self.healthPerBreed:
            # creature.breed(thing)
          # elif creature.canEat:
            # creature.eat(thing.x,thing.y)
    return 1

  def __init__(self, conn):
    BaseAI.__init__(self, conn)


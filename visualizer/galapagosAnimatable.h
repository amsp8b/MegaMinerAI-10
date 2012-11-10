#ifndef GALAPAGOS_ANIMATABLE_H
#define GALAPAGOS_ANIMATABLE_H

#include "irenderer.h"
#include "parser/structures.h"

#include "math.h"

#include <glm/glm.hpp>
#include <string>

namespace visualizer
{
    class Map : public Animatable
    {
      public:

        struct Tile
        {
          explicit Tile(int t = -1) : turn(t)  {}

          int turn;
          // todo: add more?
        };
        
        Map(int w, int h, int hud, float pc, float mc, float xp) : m_tiles(w*h), width(w), height(h), hudHeight(hud), prevMapColor(pc), mapColor(mc), xPos(xp) 
        {
        }
     
        
        Tile& operator()(unsigned int r, unsigned int c)
        {
          return m_tiles[c + r*width];
        }
        
        const Tile& operator()(unsigned int r, unsigned int c) const
        {
          return m_tiles[c + r*width];
        }
        
        int GetWidth() const { return width; }
        int GetHeight() const { return height; }
        float GetPrevMapColor() const { return prevMapColor; }
        float GetxPos() const { return xPos; }
        float GetMapColor() const { return mapColor; }
        int GetHUDHeight() const { return hudHeight; }

        int waterTile;
        int groundTile;

    private:
    
      std::vector<Tile> m_tiles;
      int width;
      int height;
      int hudHeight;
      
      // lighting
      float prevMapColor;
      float mapColor;
      float xPos;
        
        // todo: add more?
    };
    
    struct Plant : public Animatable
    {
      int x;
      int y;
      int size;
      int growth;
      // todo: add more
    };
    
    struct Creature : public Animatable
    {
      struct Moves
      {
        Moves() {}
        Moves(const glm::vec2& t, const glm::vec2& f) : to(t), from(f)
        {
        }

        // todo: maybe rename these
        glm::vec2 to;
        glm::vec2 from;
      };

      int owner;

      int energy;
      int health;
      int maxHealth;
      int carnivorism;
      int herbivorism;
      int speed;
      int defense;

      //useful for visualizer?
      int movementLeft;
      int canEat;
      int canBreed;
      int parentID;

      SmartPointer<Map> map;

      std::vector<Moves> m_moves;
    	// todo: add more
    };

    struct SpriteAnimation : public Animatable
    {
        // todo: maybe reorder these
        SpriteAnimation(float posX, float posY, int f, float dx, float dy,const string& a, const string& e = "") :
            x(posX), y(posY), frames(f), dx(dx), dy(dy), animation(a), enable(e) {}

        float x;
        float y;
        int frames;
        float dx;
        float dy;
        string animation;
        string enable;
    };

    struct SplashScreen : public Animatable
    {
      SplashScreen(string win, string msg, int id, int w, int h, float en, float def, float carn, float herb, float spd) : 
        winner(win), reason(msg), winnerID(id), width(w), height(h), 
        energy(en), defense(def), carnivorism(carn), herbivorism(herb), speed(spd)
        {}

      string winner;
      string reason;
      int winnerID;
      int width;
      int height;
      float energy;
      float defense;
      float carnivorism;
      float herbivorism;
      float speed;
    };
    
    struct EatAnimation : public Animatable
    {
      EatAnimation(int X, int Y) : x(X), y(Y) {}
      
      int x;
      int y;
    };

    struct HUD : public Animatable
    {
      HUD(int mw, int mh, int h, string name, int id, float t, int ti, int currentCrea, int totalCrea, SmartPointer<Creature> c) :
          time(t), playerName(name), playerID(id), mapWidth(mw), mapHeight(mh), height(h),
          tile(ti), currentCreatures(currentCrea), totalCreatures(totalCrea),
          creature(c)
          {}
      
      float time;
      string playerName;
      int playerID;
      int mapWidth;
      int mapHeight;
      int height;
      int tile;
      int currentCreatures;
      int totalCreatures;
      SmartPointer<Creature> creature;
    };

    struct Nest : public Animatable
    {
      Nest(int X, int Y) : x(X), y(Y) {}

      int x;
      int y;
    };

    struct Lovin : public Animatable
    {
      Lovin(int mX, int mY, int dX, int dY) : momX(mX), momY(mY), dadX(dX), dadY(dY) {}

      int momX;
      int momY;
      int dadX;
      int dadY;
    };

} // visualizer

#endif // GALAPAGOS_ANIMATABLE_H

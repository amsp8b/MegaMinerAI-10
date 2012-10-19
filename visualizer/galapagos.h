#ifndef GALAPAGOS_H
#define GALAPAGOS_H

#include <QObject>
#include <QThread>
#include "igame.h"
#include "animsequence.h"
#include <map>
#include <string>
#include <list>

// The Codegen's Parser
#include "parser/parser.h"
#include "parser/structures.h"

using namespace std;

namespace visualizer
{
    struct Rect
    {
        int left;
        int top;
        int right;
        int bottom;
    };

    class Galapagos: public QThread, public AnimSequence, public IGame
    {
        Q_OBJECT;
        Q_INTERFACES( visualizer::IGame );
        public: 
            Galapagos();
            ~Galapagos();

            PluginInfo getPluginInfo();
            void loadGamelog( std::string gamelog );

            void run();
            void setup();
            void destroy();

            void preDraw();
            void postDraw();

            void addCurrentBoard();
    
            map<string, int> programs;
            
            list<int> getSelectedUnits();
        private:
            parser::Game *m_game;  // The Game Object from parser/structures.h that is generated by the Codegen
            bool m_suicide;
            list<int> m_selectedUnitIDs;
            
            void GetSelectedRect(Rect& out) const;
            
            void SeedRand() const;
            
            // this would not be needed if polymorphism was used... wtf
            template< class T >
            void AddSelectedObjsToList(const T& datastruct, const Rect& R)
            {
              for(auto& iter : datastruct)
              {  
                const auto& obj = iter.second;
                
                // todo: move this logic into another function
                if(R.left <= obj.x && R.right >= obj.x && R.top <= obj.y && R.bottom >= obj.y)
                {
                  m_selectedUnitIDs.push_back(obj.id);
                }
                
              }
        
            }
            
            template< class T >
            bool DrawQuadAroundObj(const T& datastruct, const typename T::key_type& key)
            {       
              auto iter = datastruct.find(key);
      
              if(iter != datastruct.end())
              {
                const auto& obj = iter->second;
                
                renderer->setColor( Color( 1.0, 0.5, 0.5, 0.5 ) );
                renderer->drawQuad(obj.x,obj.y,1,1);
                
                return true;
              }
              
              return false;

            }
    }; 

} // visualizer

#endif // GALAPAGOS_H

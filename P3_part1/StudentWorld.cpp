#include "StudentWorld.h"
#include "GameConstants.h"
#include "GraphObject.h"
#include "Actor.h"
#include "Level.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class GameWorld;
class Peach;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}


// CONSTROCTOR OF STUDENTWORLD CLASS //
StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
}

// DESTRUCTOR OF STUDENTWORLD CLASS THAT DOES EXACTLY SAME THING AS WHAT CLEANUP FUNCTION DO //
StudentWorld::~StudentWorld()
{
    cleanUp();
}
    
// FUNCTION THAT LOADS DATA FROM "LEVELXX.TXT" FILE AND GETS THE POSITION OF ACTORS AND PLUGS IN THE ACTORS //
int StudentWorld::init()
{
    Level lev(assetPath());
    string level_file = "level0" + to_string(getLevel()) + ".txt";
    Level::LoadResult result = lev.loadLevel(level_file);
    if (result == Level::load_success)
    {
        cerr << level_file << " Successfully Created!" << endl;
        Level::GridEntry ge;
        for (int x = 0; x < GRID_WIDTH; x++)
        {
            for (int y = 0; y < GRID_HEIGHT; y++)
            {
                ge = lev.getContentsOf(x, y);
                switch (ge)
                {
                    case Level::empty:
                        break;
                    case Level::peach:
                        m_peach = new Peach(this, x, y);
                        break;
                    case Level::block:
                        actors.push_back(new Block(this, x, y, false));
                        break;
                    default:
                        break;
                        //etc...
                }
            }
        }
    }
    return GWSTATUS_CONTINUE_GAME;
}

// FUNCTION THAT CALLS ACTORS TO DO SOMETHING AND CHECK IF MAIN CHARACTER(PEACH) IS DEAD(GAME ENDS) OR NOT //
int StudentWorld::move()
{
    m_peach->doSomething();
    for(vector<Actor*>::iterator it = actors.begin(); it != actors.end(); ++it)
    {
        if((*it)->is_Alive())
        {
            (*it)->doSomething();
            if(!(m_peach->is_Alive()))
            {
                decLives();
                playSound(GWSTATUS_PLAYER_DIED);
                return GWSTATUS_PLAYER_DIED;
            }
        }
    }
    return GWSTATUS_CONTINUE_GAME;
}

// FUNCTION FOR CLEANING UP THE ACTORS TO NOT LEAD THE MEMORY LEAK OR DANGLING POINTER //
void StudentWorld::cleanUp()
{
    delete m_peach;
    m_peach = nullptr;
    
    while(!actors.empty())
    {
        delete actors[0];
        actors[0] = nullptr;
        actors.erase(actors.begin());
    }
}

// FUNCTION FOR CHECKING IS ACTOR OVERLAPING WITH OTHER OBJECT OR NOT //
bool StudentWorld::isBlockingObjectAt(double x, double y)
{
    for(Actor* a : actors)
    {
        if (x + SPRITE_WIDTH - 1 > a->getX() && x < a->getX() + SPRITE_WIDTH - 1)
            if (y + SPRITE_HEIGHT - 1 > a->getY() && y < a->getY() + SPRITE_HEIGHT - 1)
                return true;
    }
    return false;
}

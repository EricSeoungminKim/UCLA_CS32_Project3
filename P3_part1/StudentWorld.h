#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Level.h"
#include "Actor.h"
#include <string>
#include <vector>
#include <cmath>

class Actor;
class Peach;
class Block;

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetPath);
    ~StudentWorld();
  
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    
// FUNCTIONS THAT ARE ADDED FOR PART 1 //
    bool isBlockingObjectAt(double x, double y);
    
private:
// PRIVATE MEMBERS THAT ARE ADDED FOR PART 1 //
    std::vector<Actor*> actors;
    Peach* m_peach;
};


#endif // STUDENTWORLD_H_

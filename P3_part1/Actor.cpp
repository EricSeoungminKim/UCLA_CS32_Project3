#include "Actor.h"
#include "StudentWorld.h"
using namespace std;

// ACTOR //
Actor::Actor(StudentWorld* sw, int imageID, int x, int y, int dir, int depth, double size, bool is_alive)
            :GraphObject(imageID, x * SPRITE_WIDTH, y * SPRITE_HEIGHT)
{
    m_ID = imageID;
    m_alive = is_alive;
}

// CHECK IF THE PLAYER IS ALIVE OR DEAD //
bool Actor::is_Alive()
{
    if(m_alive) { return true; }
    else { return false; }
}

Actor::~Actor() {}


// PEACH //
// CONSTRUCTOR //
Peach::Peach(StudentWorld* sw, int x, int y): Actor(sw, IID_PEACH, x, y, 0, 0, 1, true), m_world(sw)
{
    int health_point = 1;

    bool invincibility = false;
    bool starPower = false;
    bool shootPower = false;
    bool superJumpPower = false;

    m_hp = health_point;
    m_Invincibility = invincibility;
    m_ShootPower = shootPower;
    m_SuperJumpPower = superJumpPower;
    m_StarPower = starPower;
}

// DO SOMETHING //
void Peach::doSomething()
{
    // IF PEACH HAS NO HEALTH, THEN DO NOTHING
    if(getHP() == 0)
        return;
    // OTHERWISE, GET KEY WHAT USER TYPED
    int key;
    if (m_world->getKey(key))
    {
        switch (key)
        {
            case KEY_PRESS_LEFT:
                if(getDirection() == left && !(m_world->isBlockingObjectAt(getX() - 4, getY())))
                    moveTo(getX()-4, getY());
                else if(m_world->isBlockingObjectAt(getX() - 4, getY()))
                    m_world->playSound((SOUND_PLAYER_BONK));
                else if(!(getDirection() == left))
                    setDirection(left);
                break;
            case KEY_PRESS_RIGHT:
                if(getDirection() == right && !(m_world->isBlockingObjectAt(getX() + 4, getY())))
                    moveTo(getX()+4, getY());
                else if(m_world->isBlockingObjectAt(getX() + 4, getY()))
                    m_world->playSound((SOUND_PLAYER_BONK));
                else if(!(getDirection() == right))
                    setDirection(right);
                break;
                
//                     ***** FOR PART 2 *****
//            case KEY_PRESS_UP:
//                m_world->playSound(SOUND_PLAYER_JUMP);
//                break;
//            case KEY_PRESS_SPACE:
//                if(hasShootPower())
//                    m_world->playSound(SOUND_PLAYER_FIRE);
//                else if(!hasShootPower())
//                    m_world->playSound(SOUND_NONE);
//                break;
            default:
                break;
            // TODO: FOR PART 2, MORE ACTORS SHOULD BE ADDED
        }
     }
}

// DO NOTHING
void Peach::bonked() {}
Peach::~Peach() {}


// BLOCK //
Block::Block(StudentWorld* sw, int x, int y, bool goodie_released = false)
            :Actor(sw, IID_BLOCK, x, y, 0, 2, 1, true), m_world(sw)
{
    // FOR PART 1
    int goodie = 0;         //   this int could be 0 (no goodie in block), 1 (starpower), 2 (shootpower), 3(superjumppower)
    m_goodie = goodie;      //   not using for part 1 so assuming that every blocks don't have goodies inside
}

void Block::bonked() {
    if (m_goodie == 0) { getWorld()->playSound(SOUND_PLAYER_BONK); }
//    TODO: NEED TO UPDATE THIS FOR PART 2
    else if(m_goodie == 1) {}   // THIS CASE, STAR POWER POP ON THE MAP
    else if(m_goodie == 2) {}   // THIS CASE, SHOOT POWER POP ON THE MAP
    else if(m_goodie == 3) {}   // THIS CASE, JUMP POWER POP ON THE MAP
    return;
}

// DO NOTHING //
void Block::doSomething() {}
Block::~Block() {}

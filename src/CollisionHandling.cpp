//--------------------------- Include section  ---------------------------
#include <map>
#include <string>
#include <typeinfo>
#include <typeindex>
#include "CollisionHandling.h"

// Moveable Objects
#include "MoveObjects_Headers/Player.h"
#include "MoveObjects_Headers/Enemy.h"
#include "MoveObjects_Headers/Bear.h"
#include "MoveObjects_Headers/Wolf.h"
#include "MoveObjects_Headers/Crow.h"
#include "MoveObjects_Headers/StoneArrow.h"
#include "MoveObjects_Headers/FireArrow.h"
#include "MoveObjects_Headers/Box.h"

// Static Objects.
#include "StaticObjects_Headers/Block.h"
#include "StaticObjects_Headers/Hurricane.h"
#include "StaticObjects_Headers/Key.h"
#include "StaticObjects_Headers/SpecialAbilty_Headers/FastMoving.h"
#include "StaticObjects_Headers/SpecialAbilty_Headers/FireArrows.h"
#include "StaticObjects_Headers/SpecialAbilty_Headers/JumpBoost.h"
#include "StaticObjects_Headers/ExtraLife.h"
#include "StaticObjects_Headers/Door.h"
#include "StaticObjects_Headers/Spike.h"


//----------------------------- PlayerFloor ------------------------------
// Handle the event that the player collides with the floor.
// Push the player back to his previous position before the collision.
//------------------------------------------------------------------------
void PlayerFloor(GameObject& p, GameObject& f)
{ 
    static_cast<MoveObject&>(p).handleCollision(static_cast<Block&>(f));
}


//--------------------------- playerHurricane ----------------------------
// Handle the event that the player collides with a hurricane.
// The hurricane lifts the player upwards.
//------------------------------------------------------------------------
void playerHurricane(GameObject& p, GameObject& h)
{
    static_cast<Player&>(p).handleCollision(static_cast<Hurricane&>(h));
}


//----------------------------- playerBox --------------------------------
// Handle the event that the player collides with a box.
// If possible, allow the player to push the box.
//------------------------------------------------------------------------
void playerBox(GameObject& player, GameObject& box)
{
    static_cast<Player&>(player).handleCollision(static_cast<Box&>(box));
}


//----------------------------- playerKey --------------------------------
// Handle the event that the player collides with a key.
// Let the player to pick up the key and update the key status of the
// player.
//------------------------------------------------------------------------
void playerKey(GameObject& player, GameObject& key)
{
    //static_cast<Player&>(player).setKeyStatus(true);
    if (!key.getDisapperStatus()) {
        static_cast<Player&>(player).addKey();
        key.setDisappear(true);
        Resources::instance().playSound(COLLECT_KEY_SOUND);
    }
}


//---------------------------- playerSpike -------------------------------
// Handle the event that the player collides with a key.
// Let the player to pick up the key and update the key status of the
// player.
//------------------------------------------------------------------------
void playerSpike(GameObject& p, GameObject& s)
{
    static_cast<Player&>(p).handleCollision(static_cast<Spike&>(s));
}


//-------------------------- playerFastMoving ----------------------------
// Handle the event that the player collides with a fast moving ability 
// gem. Update the player's special ability and also update that the gem
// object does not exist anymore.
//------------------------------------------------------------------------
void playerFastMoving(GameObject& player, GameObject& fastMoving)
{
    static_cast<Player&>(player).setSpecialAbility(EXTRA_SPEED_ABILITY);
    fastMoving.setDisappear(true);
}


//-------------------------- playerFireArrows ----------------------------
// Handle the event that the player collides with a fire arrows ability 
// gem. Update the player's special ability and also update that the gem
// object does not exist anymore.
//------------------------------------------------------------------------
void playerFireArrows(GameObject& player, GameObject& fireArrows)
{
    static_cast<Player&>(player).setSpecialAbility(FIRE_ARROWS_ABILITY);
    fireArrows.setDisappear(true);
}


//-------------------------- playerJumpBoost -----------------------------
// Handle the event that the player collides with a jump boot ability gem.
// Update the player's special ability and also update that the gem object
// does not exist anymore.
//------------------------------------------------------------------------
void playerJumpBoost(GameObject& player, GameObject& jumpBoost)
{
    static_cast<Player&>(player).setSpecialAbility(EXTRA_JUMP_ABILITY);
    jumpBoost.setDisappear(true);
}


//------------------------- playerExtraLife ------------------------------
// Handle the event that the player collides with a heart that adds life 
// to the player current health. Also, update that the heart object does
// not exist anymore.
//------------------------------------------------------------------------
void playerExtraLife(GameObject& player, GameObject& extraLife)
{
    static_cast<Player&>(player).incLife();
    Resources::instance().playSound(LIFE_BOOST_SOUND);
    extraLife.setDisappear(true);
}


//---------------------------- playerGold --------------------------------
// Handle the event that the player collides with gold.
// 1. Update the amount of gold the player has accumulated so far.
// 2. Update that the object of gold no longer exists.
//------------------------------------------------------------------------
void playerGold(GameObject& p, GameObject& g)
{
    auto gold = static_cast<Gold&>(g);

    if (!g.getDisapperStatus())
    {
        static_cast<Player&>(p).increaseScore();
        Resources::instance().playSound(COLLECT_GEM_SOUND);
        g.setDisappear(true);
    }
}


//----------------------------- playerDoor -------------------------------
// Handle the event that the player collides with the door.
// If the player has already collected the key, update that the level is
// over.
//------------------------------------------------------------------------
void playerDoor(GameObject& p, GameObject& d)
{
    static_cast<Player&>(p).handleCollision(static_cast<Door&>(d));
}


//---------------------------- playerEnemy -------------------------------
// Handle the event that the enemy collides with a player.
// If the player attacks absorb the blow.
//------------------------------------------------------------------------
void playerEnemy(GameObject& p, GameObject& e)
{
    auto& enemy = static_cast<Enemy&>(e);

    if (static_cast<Player&>(p).isHiting())
    {
        enemy.handleHit(enemy, FIST_DMG);
    }
}


//--------------------------- enemyFloor ---------------------------------
// Handle the event that the enemy collides with the floor.
// Push the enemy back to his previous position before the collision.
//------------------------------------------------------------------------
void enemyFloor(GameObject& e, GameObject& f)
{
    static_cast<Enemy&>(e).handleCollision(static_cast<Block&>(f));
}


//----------------------------- enemyBox ---------------------------------
// Handle the event that the enemy collides with a box.
// Push the enemy back to his previous position before the collision.
//------------------------------------------------------------------------
void enemyBox(GameObject& e, GameObject& b)
{
    static_cast<Enemy&>(e).handleCollision(static_cast<Box&>(b));
}


//----------------------------- bearPlayer -------------------------------
// Handle the event that the enemy collides with a bear.
// 1. Attack the player - Displays the necessary animations.
// 2. Lower the player's amount of life.
//------------------------------------------------------------------------
void bearPlayer(GameObject& b, GameObject& p)
{
    auto& bear = static_cast<Bear&>(b);
    bear.hit(bear);
    static_cast<Player&>(p).handleCollision(bear);
}


//----------------------------- crowPlayer -------------------------------
// Handle the event that the enemy collides with a bear.
// 1. Attack the player - Displays the necessary animations.
// 2. Lower the player's amount of life.
//------------------------------------------------------------------------
void crowPlayer(GameObject& c, GameObject& p)
{
    auto& crow = static_cast<Crow&>(c);
    crow.hit(crow);
    static_cast<Player&>(p).handleCollision(crow);
}

//----------------------------- crowPlayer -------------------------------
// Handle the event that the enemy collides with a bear.
// 1. Attack the player - Displays the necessary animations.
// 2. Lower the player's amount of life.
//------------------------------------------------------------------------
void wolfPlayer(GameObject& w, GameObject& p)
{
    auto& wolf = static_cast<Wolf&>(w);
    wolf.hit(wolf);
    static_cast<Player&>(p).handleCollision(wolf);
}

//---------------------------- enemyPlayer -------------------------------
// Handle the event that the enemy collides with an Arrow.
// 1. Absorb the damage from the arrow.
// 2. Update that the arrow no longer exists.
//------------------------------------------------------------------------
void enemyArrow(GameObject& enemy, GameObject& arrow)
{
    auto& e = static_cast<Enemy&>(enemy);
    auto& a = static_cast<StoneArrow&>(arrow);

    e.handleHit(e, a.getDamage());
    a.setDisappear(true);
}


//----------------------------- boxFloor ---------------------------------
// Handle the event that the box collides with the floor.
// Push back the box from the floor.
//------------------------------------------------------------------------
void boxFloor(GameObject& b, GameObject& f)
{
    static_cast<Box&>(b).handleCollision(static_cast<Block&>(f));
}


//------------------------- arrowStaticObject ----------------------------
// Handle the event that the arrow collides with the a block.
// Disappear the arrow.
//------------------------------------------------------------------------
void arrowStaticObject(GameObject& arrow, GameObject& floor)
{
    arrow.setDisappear(true);
}


namespace // anonymous namespace — the standard way to make function "static"
{
using HitFunctionPtr = void (*)(GameObject&, GameObject&);
using MapKey = std::pair<std::type_index, std::type_index>;
using HitMap = std::map<MapKey, HitFunctionPtr>;


//---------------------- setPlayerCollisionHandling ----------------------
// Insert all the players collision functions into the map Data Structure.
//------------------------------------------------------------------------
void setPlayerCollisionHandling(HitMap& phm)
{
    // Player & floor.
    phm[MapKey(typeid(Player), typeid(Block))] = &PlayerFloor;

    // Player & Gold.
    phm[MapKey(typeid(Player), typeid(Gold))] = &playerGold;

    // Player & Box.
    phm[MapKey(typeid(Player), typeid(Box))] = &playerBox;

    // Player & Hurricane.
    phm[MapKey(typeid(Player), typeid(Hurricane))] = &playerHurricane;

    // Player & Key.
    phm[MapKey(typeid(Player), typeid(Key))] = &playerKey;

    // Player & FastMoving
    phm[MapKey(typeid(Player), typeid(FastMoving))] = &playerFastMoving;

    // Player & FireArrows
    phm[MapKey(typeid(Player), typeid(FireArrows))] = &playerFireArrows;

    // Player & JumpBoost
    phm[MapKey(typeid(Player), typeid(JumpBoost))] = &playerJumpBoost;

    // Player & ExtraLife
    phm[MapKey(typeid(Player), typeid(ExtraLife))] = &playerExtraLife;

    // Player & Bear
    phm[MapKey(typeid(Player), typeid(Bear))] = &playerEnemy;

    // Player & Wolf
    phm[MapKey(typeid(Player), typeid(Wolf))] = &playerEnemy;

    // Player & Crow
    phm[MapKey(typeid(Player), typeid(Crow))] = &playerEnemy;

    // Player & Door
    phm[MapKey(typeid(Player), typeid(Door))] = &playerDoor;

    // Player & Spike
    phm[MapKey(typeid(Player), typeid(Spike))] = &playerSpike;
}


//---------------------- setEnemyCollisionHandling -----------------------
// Insert all the enemy's collision functions into the map Data Structure.
//------------------------------------------------------------------------
void setEnemyCollisionHandling(HitMap& phm)
{
    // Bear & Block.
    phm[MapKey(typeid(Bear), typeid(Block))] = &enemyFloor;

    // Bear & player.
    phm[MapKey(typeid(Bear), typeid(Player))] = &bearPlayer;
    
    // Bear & Box.
    phm[MapKey(typeid(Bear), typeid(Box))] = &enemyBox;

    // Bear & Arrow.
    phm[MapKey(typeid(Bear), typeid(StoneArrow))] = &enemyArrow;

    // Bear & FireArrow.
    phm[MapKey(typeid(Bear), typeid(FireArrow))] = &enemyArrow;


    // Wolf & Block.
    phm[MapKey(typeid(Wolf), typeid(Block))] = &enemyFloor;

    // Wolf & Player.
    phm[MapKey(typeid(Wolf), typeid(Player))] = &wolfPlayer;

    // Wolf & Box.
    phm[MapKey(typeid(Wolf), typeid(Box))] = &enemyBox;

    // Wolf & Arrow.
    phm[MapKey(typeid(Wolf), typeid(StoneArrow))] = &enemyArrow;

    // Wolf & FireArrow.
    phm[MapKey(typeid(Wolf), typeid(FireArrow))] = &enemyArrow;


    // Crow & block.
    phm[MapKey(typeid(Crow), typeid(Block))] = &enemyFloor;

    // Crow & Player.
    phm[MapKey(typeid(Crow), typeid(Player))] = &crowPlayer;

    // Crow & Box.
    phm[MapKey(typeid(Crow), typeid(Box))] = &enemyBox;

    // Crow & Arrow.
    phm[MapKey(typeid(Crow), typeid(StoneArrow))] = &enemyArrow;

    // Crow & FireArrow.
    phm[MapKey(typeid(Crow), typeid(FireArrow))] = &enemyArrow;
}


//---------------------- setStaticCollisionHandling ----------------------
// Insert all the static collision functions into the map Data Structure.
//------------------------------------------------------------------------
void setStaticCollisionHandling(HitMap& phm)
{
    // Box & floor
    phm[MapKey(typeid(Box), typeid(Block))] = &boxFloor;

    
    // StoneArrow & Block
    phm[MapKey(typeid(StoneArrow), typeid(Block))] = &arrowStaticObject;

    // StoneArrow & Box
    phm[MapKey(typeid(StoneArrow), typeid(Box))] = &arrowStaticObject;


    // FireArrow & Block
    phm[MapKey(typeid(FireArrow), typeid(Block))] = &arrowStaticObject;

    // FireArrow & Box
    phm[MapKey(typeid(FireArrow), typeid(Box))] = &arrowStaticObject;
}


//------------------------ initializeCollisionMap ------------------------
// Intialize the collision handling map.
// Calls to auxiliary functions that insert the keys of the objects that
// collide and the corresponding function for that collision.
//------------------------------------------------------------------------
HitMap initializeCollisionMap()
{
    HitMap phm;

    setPlayerCollisionHandling(phm);

    setEnemyCollisionHandling(phm);

    setStaticCollisionHandling(phm);

    return phm;
}


//------------------------------ lookup ----------------------------------
// Look up and find out if there is a suitable collision between the
// 2 objects that committed a collision.
//------------------------------------------------------------------------
HitFunctionPtr lookup(const std::type_index& class1,
    const std::type_index& class2)
{
    static HitMap collisionMap = initializeCollisionMap();

    auto mapEntry = collisionMap.find(std::make_pair(class1, class2));
    if (mapEntry == collisionMap.end())
    {
        return nullptr;
    }
    return mapEntry->second;
}

} // end namespace


//------------------------- processCollision -----------------------------
// Process the collision.
// Calls the function lookup that searches if there is a suitable function
// for the current collision. If a suitable function is found, it 
// activates it.
//------------------------------------------------------------------------
void processCollision(GameObject& object1, GameObject& object2)
{
    auto phf = lookup(typeid(object1), typeid(object2));
    if (phf)
    {
        phf(object1, object2);
    }
}
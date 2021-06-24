#pragma once

//-------------------------- Include section  ----------------------------
#include "SFML/Graphics.hpp"


//--------------------------* Window consts *-----------------------------
const int WINDOW_WIDTH = 1920, WINDOW_HEIGHT = 1080,
CAMERA_WIDTH = 360, CAMERA_HEIGHT = 240,
LOADING_BAR_WIDTH = 100, LOADING_BAR_HEIGHT = 100,
FPS_LIMIT = 60;
const float
CAMERA_MOVE_SPEED = -0.78f,
WINDOW_PLAYER_ICON_WIDTH = 20.f,
WINDOW_PLAYER_ICON_HEIGHT = 10.f,
SCORE_ICON_WIDTH = 18.f,
SCORE_ICON_HEIGHT = 10.f,
SPECIAL_ABILITY_ICON_WIDTH = 20.f,
SPECIAL_ABILITY_ICON_HEIGHT =10.f,
STAGE_TWO_LOAD_TIME = 5.f,
LOADING_CIRCLE_RADIUS = 100.f;

const std::string GAME_TITLE("Lost In The Forest");

const int STAGE_ONE = 1, STAGE_TWO = 2, STAGE_THREE = 3;


//------------- screen consts -------------------
const int CIRCLES_LOAD_NUM = 5, ROTATION = 1;

const float
MINIMUN_BRIGHTNESSS = 200.f,
MAXIMUM_BRIGHTNESS = 250.f;

const std::string ENABLE("Enable");
const std::string DISABLE("Disable");

//---------------------------* board consts *-----------------------------
const int BLOCK_SIZE = 40;

const char
PLAYER = '@',
BEAR = 'B',
WOLF = 'W',
CROW = 'C',
FLOOR = '#',
FLOOR_EDGE_LEFT = '(',
FLOOR_EDGE_RIGHT = ')',
WALL = '|',
HURRICANE = 'H',
DOOR = 'D',
BOX = 'O',
KEY = 'K',
GOLD = '*',
FIRE_ARROWS = '>',
SPEED_BOOST = '~',
JUMP_BOOST = '^',
LIFE = '.',
SPIKE = '!',
STAGE1_TREE = '1',
STAGE1_LOG = '2',
STAGE2_CRYSTAL1 = '3',
STAGE2_CRYSTAL2 = '4',
STAGE3_TREE = '5',
STAGE3_BUSH = '6';

//-------------------------* MoveObject consts *--------------------------
const sf::Vector2f ARRROW_SIZE(BLOCK_SIZE / 2, BLOCK_SIZE / 2);


//------------------- Player ---------------------
const float PLAYER_SPEED = 125.f;
const float PLAYER_FALL_SPEED = 400.f;
const int PLAYER_LIVES = 3;
const int HIT_PUSH_BACK = -2;

const sf::Vector2f SCALE_RIGHT{ 1,1 };
const sf::Vector2f SCALE_LEFT{ -1,1 };


// Special Ability
const std::string
EXTRA_JUMP_ABILITY("jumpBoost"),
EXTRA_SPEED_ABILITY("speedBoost"),
FIRE_ARROWS_ABILITY("m_damageBoost");

const int JUMP_BOOST_BONUS = 10;
const int EXTRA_SPEED_BONUS = 50;


// player and enemy movements - for switch()
const int
UP = 1,
DOWN = 2,
LEFT = 3,
RIGHT = 4;


// movement consts
const sf::Vector2f UP_MOVEMENT(0, -1);
const sf::Vector2f LEFT_MOVEMENT(-1, 0);
const sf::Vector2f RIGHT_MOVEMENT(1, 0);
const sf::Vector2f DOWN_MOVEMENT(0, 1);
const sf::Vector2f STAY_IN_PLACE(0, 0);
const sf::Vector2f PUSH_FROM(5, 0);
const sf::Vector2f PUSH_FROM_SPIKE(2, 0);
const sf::Vector2f FALL_PUSH(0, 5);


// scale consts
const sf::Vector2f RIGHT_AND_LEFT_SCALE(0.9f, 1);
const sf::Vector2f JUMP_SCALE(1.2f, 1);
const sf::Vector2f SHOOT_SCALE(0.8f, 1);
const sf::Vector2f HURT_SCALE(0.8f, 1);

const sf::Vector2f LEFT_SCALE(-1, 1);
const sf::Vector2f RIGHT_SCALE(1, 1);


const float PUSH_FROM_BOX = 9.5;
const float HALF_SIZE = 10.f;
const int FIST_DMG = 35; 
const float SHOOT_RATIO = 750.f;
const float FIST_RATIO = 450.f;
const int FIST_ATTACK = 0;
const int ARROW_ATTACK = 1;

// case consts
const int ZERO = 0;
const int ONE = 1;
const int TWO = 2;
const int THREE = 3;
const int FOUR = 4;


const float HANDLE_JUMP_SPEED = 80.f;
const int JUMP_COUNTER = 20;
const int HEALTH_INC = 10;


//------------------ Enemy ----------------------
const float ENEMY_HIT_RATIO = 1000.f;
const float ENEMY_SPEED = 62.5f;
const int BEAR_HIT_DMG = 80,
WOLF_HIT_DMG = 20,
WOLF_HP = 90,
CROW_HIT_DMG = 10,
CROW_HP = 75;
const float SPIKE_DAMAGE = 100;
const sf::Vector2f 
WOLF_SIZE = sf::Vector2f(BLOCK_SIZE * 0.8, BLOCK_SIZE * 0.8),
CROW_SIZE = sf::Vector2f(BLOCK_SIZE * 0.8, BLOCK_SIZE * 0.8),
BEAR_SIZE = sf::Vector2f(BLOCK_SIZE * 2, BLOCK_SIZE);

// movement seconds.
const int TWO_SEC = 2;
const int FOUR_SEC = 4;
const int SIX_SEC = 6;
const int EIGHT_SEC = 8;


//---------------------------* Sounds consts *----------------------------
const int MULTIPLE_SOUNDS_ALLOWED = 3;

//------------------- Arrow ---------------------
const int STONE_ARRROW_DMG = 15;
const int FIRE_ARRROW_DMG = 40;

const float ARROW_STAY_IN_PLACE_TIME = 0.5f;
const float ARROW_EXIST_TIME = 4.f;


//-------------------------- Color consts --------------------------------
const sf::Color GREY_COLOR(128, 128, 128);
  

//--------------------------- String consts ------------------------------
const std::string GAMEPLAY_DISCIPRION
("Lost In The Forest is a 2D platform game with an emphasis on\
 exploration and collecting items, and keys to open\n\
the door to the next level. The player controls Mori, a white guardian\
 fox. Mori, must jump, climb, and use various\n\
other abilities to navigate the game's world. During the game Mori is\
 faced with various enemies making the experience\n\
more challenging.\n\n\
Mori's abilitys:\n\
Fist - Normal fist\n\
Jump - Lets jump when on top of floor and hurricane.\n\
Arrows - Shoots magical stone arrows. \n\n\
Gems and items:\n\
Jump Gem - Green gem. Increases jumping distance.\n\
Speed Gem - Blue gem. Increases Movement speed on floor.\n\
Fire Arrows Gem - Red gem. Gives magical fire Arrow and increases\
 arrows damage.");

const std::string CONTROLS_DISCIPRION
("Right & Left -\n\n\
	   \tJump - \n\n\
	       \tHit - \n\n\
	  \tShoot - \n\n\
    \tRestart - ");

const std::string 
STAGE_TWO_START_MSG = "               \n				Danger!\n\
The floor is getting flooded.",
PAUSE_TEXT = "Pause";

//-------------------------- IntRect consts ------------------------------
const
sf::IntRect LOADING_INTRECT(0, 0, 182, 204),
STAGE1_TREE_INTRECT(356, 314, 125, 196),
STAGE1_BUSH_INTRECT(0, 367, 315, 84),
STAGE2_CRYSTAL1_INTRECT(65, 595, 106, 101),
STAGE2_CRYSTAL2_INTRECT(361, 589, 115, 115),
STAGE3_BUSH_INTRECT(246, 167, 135, 91),
STAGE3_TREE_INTRECT(26, 35, 185, 211);


const std::string BOX_FILE("box.png");
const std::string DOOR_FILE("door.png");

const sf::IntRect
WALL_INRECT(871, 358, 90, 90),
FLOOR_INRECT_FIRST_STAGE(713, 137, 90, 90),
FLOOR_EDGE_FIRST_STAGE(554, 137, 90, 90),
FLOOR_EDGE_INRECT_SECOND_STAGE(713, 358, 90, 90),
FLOOR_INRECT_SECOND_STAGE(555, 358, 90, 90),
FLOOR_INRECT_THRID_STAGE(554, 242, 90, 90),
FLOOR_EDGE_INRECT_THIRD_STAGE(713, 242, 90, 90);

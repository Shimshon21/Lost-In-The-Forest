//-------------------------- Include section  ----------------------------
#include "Screens_Headers\GameScreen.h"


//------------------------- intialScreenSet ------------------------------
// Initializes the basic features of the game screen.
//------------------------------------------------------------------------
GameScreen::GameScreen(sf::RenderWindow& window, Controller* controller) :
    m_controller(controller),
    m_world(this),
    m_window(&window),
    playerIcon({ WINDOW_PLAYER_ICON_WIDTH,WINDOW_PLAYER_ICON_HEIGHT }),
    scoreIcon({ SCORE_ICON_WIDTH,SCORE_ICON_HEIGHT }),
    specailAbilityIcon({ SPECIAL_ABILITY_ICON_WIDTH,
        SPECIAL_ABILITY_ICON_HEIGHT }),
    m_stageBackground({ CAMERA_WIDTH,CAMERA_HEIGHT }),
    m_animatedBackground({ CAMERA_WIDTH,CAMERA_HEIGHT }), 

    m_scoreIconAnimation(Resources::instance().animationWorldData
    (Resources::GOLD_DATA), Operation::Stay, scoreIcon,
        Resources::instance().
        getStaticObjectTexture(Resources::STATIC_ANIMATED)),

    m_stage2BackgroundAnim(Resources::instance().animationWorldData
    (Resources::STAGE2_BACKGROUND_DATA), Operation::Stay,
        m_animatedBackground, Resources::instance().
        getWindowObjectTexture(Resources::STAGE2_BACKGROUND))
{
    setIcons();     // Sets the game icons.

    setTextData();  // Sets the games text.
}


//---------------------------- intialScreenSet ---------------------------
// Sets the intial screen.
//------------------------------------------------------------------------
void GameScreen::intialScreenSet()
{
    m_moveObjects.clear();

    this->currentScreen = GAME;

    m_world.load_map(currentStage);

    setStage();
}


//------------------------------ screenRun -------------------------------
// The main function that controls the events of the game.
// Depending on the state of the game, manages the functions responsible
// for it.
// For example: If the player finished a level, calls a function to load
// the next level Or if the player wants to eneter the menu, calls a
// function that load the main menu screen of the game.
//------------------------------------------------------------------------
void GameScreen::screenRun(sf::RenderWindow& window, bool& switchScreen,
    int& nextScreenWanted)
{
    if (m_player->isFinishedLevel(m_world.getKeysCounter()))
    {
        onComplatedStage(switchScreen, nextScreenWanted);
        return;
    }

    runGame();

    if (this->toSwitchScreen) {

        if (this->currentScreen == RELOAD) {

            reloadMap();

            m_view.setCenter(m_player->getPosition());

            nextScreenWanted = GAME;

            this->currentScreen = GAME;

            playerLost = false;

        }
        else if (this->currentScreen == MENU) {

            switchScreen = true;

            nextScreenWanted = MENU;

            currentStage = STAGE_ONE;
        }

        else if (this->currentScreen == EXIT)
            exit(EXIT_SUCCESS);
    }
}


//------------------------------ runGame ---------------------------------
// Runs the game.
// Manages a loop that checks the status of the game at any given moment
// and acts accordingly.
//------------------------------------------------------------------------
void GameScreen::runGame()
{
    auto time = animationTime.restart();
    float deltaTime = time.asSeconds();

    if (allowMovment()) {
        handleGameMovment(deltaTime);
    }
    else if (playerLost)
    {
        handleGameOver();
    }
    else if (pauseGame)
    {
        handlePausedGame();
    }

    setCurrentStageView(deltaTime);

    draw(time);
}

//---------------------------- onComplatedStage --------------------------
// When player complated stage count the scores collected and were in the
// stage. 
//If there is next stage put loading screen, else Set the end game screen.
//------------------------------------------------------------------------
void GameScreen::onComplatedStage(bool& switchScreen, int& nextScreenWanted)
{
    m_controller->addCollectedStageGems(m_player->getScore());
    m_controller->addExistedStageGems(m_world.getGoldCounter());

    currentStage++;

    m_window->setView(m_window->getDefaultView());

    if (currentStage <= 3) {

        nextScreenWanted = LOADING;
        switchScreen = true;
    }
    else
    {
        switchScreen = true;
        nextScreenWanted = WIN;
        currentStage = STAGE_ONE;
    }
}


//----------------------- updateStatsToViewPosition ---------------------
// Update the game stats appeared in the game on the top left.
//------------------------------------------------------------------------
void GameScreen::updateStatsToViewPosition()
{
    playerIcon.setPosition(sf::Vector2f(m_view.getCenter().x - 180,
        m_view.getCenter().y - 115));

    //Score data draw
    scoreIcon.setPosition(sf::Vector2f(m_view.getCenter().x - 178,
        m_view.getCenter().y - 100));

    specailAbilityIcon.setPosition(sf::Vector2f(m_view.getCenter().x - 178,
        m_view.getCenter().y - 85));

    currentAbilityTxt.setPosition(sf::Vector2f(m_view.getCenter().x - 155,
        m_view.getCenter().y - 85));

    scoreGemsTxt.setPosition(sf::Vector2f(m_view.getCenter().x - 155,
        m_view.getCenter().y - 102));
}


//---------------------------- drawGameStats -----------------------------
// Draw the stats on top left side of the game screen View.
//------------------------------------------------------------------------
void GameScreen::drawGameStats(sf::Time& deltaTime)
{
    updateStatsToViewPosition();

    m_window->draw(playerIcon);

    m_window->draw(specailAbilityIcon);

    m_window->draw(currentAbilityTxt);

    m_scoreIconAnimation.update(deltaTime);

    m_window->draw(scoreIcon);
             
    m_window->draw(scoreGemsTxt);
}


//----------------------------- setTextData ------------------------------
// Sets the text data of the game screen.
//------------------------------------------------------------------------
void GameScreen::setTextData(sf::Text& text, const int fontSize,
    const sf::Vector2f& pos, const std::string& str, const int style)
{
    text.setFont(*Resources::instance().getArialfont());
    text.setCharacterSize(fontSize);
    text.setString(str);
    text.setColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);
    text.setPosition(pos);
}


//----------------------------- setTextData ------------------------------
// Sets the text data.
// calls the auxillary function setTextData(overload) that sets the 
// specific characteristics of the text.
//------------------------------------------------------------------------
void GameScreen::setTextData()
{
    setTextData(scoreGemsTxt, 10, { 0,0 }, "0/0", (sf::Text::Bold));

    setTextData(currentAbilityTxt, 8, { 0,0 }, " :", (sf::Text::Bold));

    setTextData(stageTwoStartText, 20, { 0,0 },
        STAGE_TWO_START_MSG, (sf::Text::Bold));

    stageTwoStartText.setOrigin(
        stageTwoStartText.getLocalBounds().width / 2,
        stageTwoStartText.getLocalBounds().height / 2);

    setTextData(pauseText, 20, { 0,0 }, PAUSE_TEXT, (sf::Text::Bold));

    pauseText.setOrigin(
        pauseText.getLocalBounds().width / 2,
        pauseText.getLocalBounds().height / 2);
}


//---------------------------- setBoxObejct ------------------------------
// Sets the box object in the game.
// The box is moveable object (The player moves and uses the box to reach
// high places. 
//------------------------------------------------------------------------
void GameScreen::setBoxObejct(const sf::Vector2f& pos)
{
    m_moveObjects.push_back(std::make_unique<Box>
        (sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE), pos));
}


//--------------------------- ControlPlayer ------------------------------
// Controls the player.
// Sets the current delta time and moves the player.
// After moving the player, if the player is still alive, handles all 
// possible events that can accure during the game.
//------------------------------------------------------------------------
void GameScreen::controlPlayer(const float& deltaTime)
{
    setPlayerData(deltaTime);

    m_player->move();

    if (m_player->isAlive())
    {
        handlePlayerEvents();
    }
}


//-------------------------- setPlayerData -------------------------------
// Sets the players data.
//------------------------------------------------------------------------
void GameScreen::setPlayerData(const float& deltaTime)
{
    m_player->setMapIt(m_world.getStaticObjBegIt(),
        m_world.getStaticObjEndIt());
    m_player->setDeltaTime(deltaTime);
}


//-------------------------- handlePlayerEvents --------------------------
// Handles all the possible events that can accure during the game to 
// the player. 
//------------------------------------------------------------------------
void GameScreen::handlePlayerEvents()
{
    m_player->handleMoveObjects(m_moveObjects.begin(), m_moveObjects.end());
    m_player->handleJump(false);
    m_player->handleFall();
    m_player->setHittingStatus(false);
}


//------------------------ controlMoveObjects ----------------------------
// Moves the moveable objects of the game.
//------------------------------------------------------------------------
void GameScreen::controlMoveObjects(const float& deltaTime)
{
    for (auto i = m_moveObjects.begin(); i != m_moveObjects.end(); i++)
    {
        moveEnemy(i->get(), deltaTime);
        moveArrow(i->get());
        moveBox(i->get());
    }

    deleteMoveObject();
}


//------------------------------ moveEnemy -------------------------------
// Moves the current enemy.
// Sets the current delta time of the game, moves the enemy and then 
// handle all the events that can accure to the enemy.
//------------------------------------------------------------------------
void GameScreen::moveEnemy(MoveObject* e, const float& deltaTime)
{
    if (dynamic_cast<Enemy*>(e))
    {
        setEnemyData(e, deltaTime);
        e->move();
        enemyHandleEvents(e);
    }
}


//------------------------------- moveBox --------------------------------
// Moves the box and calls a function to handle all the possible events
// that can happen to the box. For example, the box can fall, hit the 
// floor or the wall.
//------------------------------------------------------------------------
void GameScreen::moveBox(MoveObject* b)
{
    auto box = dynamic_cast<Box*>(b);
    if (box)
    {
        box->setMapIt(m_world.getStaticObjBegIt(),
            m_world.getStaticObjEndIt());
        box->handleEvents();
    }
}


//---------------------------- allowMovment ------------------------------
// Returns if the player(That play the game) can move the hero of the 
// game.
//------------------------------------------------------------------------
const bool GameScreen::allowMovment() const
{
    return (!playerLost && !pauseGame && !stageTwoIntialWait);
}


//----------------------------- setEnemyData -----------------------------
// Sets the enemy data.
// sets the delta time of the enemy, position, and iterator of the 
// static object of the game to handle collision with them.
//------------------------------------------------------------------------
void GameScreen::setEnemyData(MoveObject* e, const float& deltaTime)
{
    e->setDeltaTime(deltaTime);
    e->setPlayerPos(m_player->getPosition());
    e->setMapIt(m_world.getStaticObjBegIt(), m_world.getStaticObjEndIt());
}


//-------------------------- enemyHandleEvents ---------------------------
// Handles all the events that enemy can have.
// 1. Handles fall.
// 2. Handles collision with all the moveable objects of the game.
//------------------------------------------------------------------------
void GameScreen::enemyHandleEvents(MoveObject* e)
{
    e->handleFall();
    e->handleMoveObjects(m_moveObjects.begin(), m_moveObjects.end());
}


//----------------------------- moveArrow --------------------------------
// Moves the arrow and handles all the events that an arrow can accure.
//------------------------------------------------------------------------
void GameScreen::moveArrow(MoveObject* arrow)
{
    if (dynamic_cast<Arrow*>(arrow) && m_player->isAlive())
    {
        if (!arrow->getDisapperStatus())
        {
            arrow->setMapIt(m_world.getStaticObjBegIt(),
                m_world.getStaticObjEndIt());
            arrow->move();
        }
    }
}


//-------------------------- handleGameMovment ---------------------------
// Handle game events like key or mouse pressing.
// Also, calls functions to control the movement of the moveable objects 
// of the game. 
//------------------------------------------------------------------------
void GameScreen::handleGameMovment(const float deltaTime)
{
    if (auto event = sf::Event{}; m_window->pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            m_window->close();
            break;
        case sf::Event::KeyPressed:
            handleKeyPressed(event.key.code);
            break;
        case sf::Event::KeyReleased:
            handleKeyReleased(event.key.code);
            break;
        }
    }

    controlPlayer(deltaTime);

    controlMoveObjects(deltaTime);

    m_world.clearStaticObjects();

    if (!m_player->isAlive())
    {
        handlePlayerLost();
    }
}


//---------------------------- handlePausedGame --------------------------
// Handle the event the player pressed Escape to pause the game.
//------------------------------------------------------------------------
void GameScreen::handlePausedGame()
{
    if (auto event = sf::Event{}; m_window->pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            m_window->close();
            break;
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape)
                pauseGame = false;
            break;
        }
    }
}


//----------------------------- handleGameOver ---------------------------
// Handle the event that the player lost.
// Prints the game over screen.
// (We enter this function only if the player has lost).
//------------------------------------------------------------------------
void GameScreen::handleGameOver()
{
    gameOverPopUp.setPostion(m_view.getCenter());
    gameOverPopUp.screenRun(*m_window, toSwitchScreen, currentScreen);
}


//------------------------ setCurrentStageView ---------------------------
// 
//------------------------------------------------------------------------
void GameScreen::setCurrentStageView(const float deltaTime)
{
    if (!playerLost) 
    {
        if (currentStage != STAGE_TWO)
        {
            setView();
        }
        else
        {
            setSecondStageView(deltaTime);
        }
    }
}


//-------------------------- updateScoreText -----------------------------
// 
//------------------------------------------------------------------------
void GameScreen::updateTextInfo()
{
    std::string currentAbility = " "
        , currentScore = std::to_string(m_player->getScore()) + "/";

    int gold = m_world.getGoldCounter();

    currentScore.append(std::to_string(gold));

    scoreGemsTxt.setString(currentScore);

    if (m_player->getExtraSpeed())
    {
        currentAbility = "Speed";
    }
    else if (m_player->getExtraJump())
    {
        currentAbility = "Jump";
    }
    else if (m_player->hasSpecialArrow())
    {
        currentAbility = "Fire";
    }

    currentAbilityTxt.setString(currentAbility);
}


//------------------------------ reloadMap -------------------------------
// 
//------------------------------------------------------------------------
void GameScreen::reloadMap()
{
    m_moveObjects.clear();
    m_world.reloadStage();
    Resources::instance().pauseMusic();
    setStageSoundTrack();
}


//------------------------------ reloadMap -------------------------------
//
//------------------------------------------------------------------------
void GameScreen::setStage()
{
    playerLost = false;

    gameMovementClock.restart();

    animationTime.restart();

    setStageBackground();

    setStageSoundTrack();

    m_stageBackground.setOrigin(m_stageBackground.getSize().x / 2,
        m_stageBackground.getSize().y / 2);

    m_animatedBackground.setOrigin(m_animatedBackground.getSize() / 2.f);

    if (currentStage == STAGE_TWO) {
        stageTwoIntialWait = true;
        stageTwoLoadTime = STAGE_TWO_LOAD_TIME;
    }
}


//------------------------------ reloadMap -------------------------------
//
//------------------------------------------------------------------------
void GameScreen::setIcons()
{
    playerIcon.setTexture(Resources::instance().
        getWindowObjectTexture(Resources::PLAYER_ICON));

    specailAbilityIcon.setTexture(Resources::instance().
        getWindowObjectTexture(Resources::SPECIAL_ABILITY_ICON));
}


//--------------------------- handlePlayerLost ---------------------------
//
//------------------------------------------------------------------------
void GameScreen::handlePlayerLost()
{
    playerLost = true;
    m_controller->addPlayerLostCount();
    Resources::instance().pauseMusic();
    Resources::instance().playGameOverSoundTrack();
}


//------------------------------ reloadMap -------------------------------
//
//------------------------------------------------------------------------
void GameScreen::setView()
{
    m_view.setCenter(m_player->getPosition().x,
        m_player->getPosition().y);

    m_view.setSize(CAMERA_WIDTH, CAMERA_HEIGHT);

    m_window->setView(m_view);

    m_stageBackground.setPosition(m_view.getCenter());
}


//------------------------------ reloadMap -------------------------------
// Reloads the current game.
// The player start the stage from the beginning.
//------------------------------------------------------------------------
void GameScreen::deleteMoveObject()
{
    for (int i = 0; i < m_moveObjects.size(); i++)
    {
        if (m_moveObjects[i] &&
            m_moveObjects[i]->getDisapperStatus())
        {
            m_moveObjects.erase(m_moveObjects.begin() + i);
            break;
        }
    }
}


//------------------------- handleKeybaordPressed ------------------------
// Handles he event the the keyboard keys are pressed.
//------------------------------------------------------------------------
void GameScreen::handleKeyPressed(const sf::Keyboard::Key& key)
{
    switch (key)
    {
    case sf::Keyboard::Key::Space:   m_player->handleJump(true);   break;
    case sf::Keyboard::Key::R:       reloadMap();                  break;
    case sf::Keyboard::Key::Escape:  pauseGame = true;             break;
    }
}


//-------------------------- handleKeyReleased ---------------------------
// Handle the event that a key is released.
//------------------------------------------------------------------------
void GameScreen::handleKeyReleased(const sf::Keyboard::Key& key)
{
        switch (key)
        {
        case sf::Keyboard::Key::X: m_player->hit();
            break;

        case sf::Keyboard::Key::Z:
            playerPreformShoot();
            break;
        }
}


//------------------------- playerPreformShoot --------------------------
// The player preforms shooting. 
//------------------------------------------------------------------------
void GameScreen::playerPreformShoot() 
{
    sf::Vector2f pos = sf::Vector2f(m_player->getPosition().x +
            (m_player->getShape().x / 2) * m_player->getScale(),
            m_player->getPosition().y);

    if (m_player->isShootValid())       // Checks if shooting is valid.
    {
        if (!m_player->hasSpecialArrow())
        {
            m_moveObjects.push_back(std::make_unique<StoneArrow>
                (ARRROW_SIZE, pos, m_player->getScale()));
        }
        else
        {
            m_moveObjects.push_back(std::make_unique<FireArrow>
                (ARRROW_SIZE, pos, m_player->getScale()));
        }
        m_player->shoot();
    }
}


//-------------------------------- draw ----------------------------------
// Draws the screen of the game and all of it's content.
// i.e. prints calls functions that print background, all the static
// objects and moveable objects, stats, health bar, and so on. 
//------------------------------------------------------------------------
void GameScreen::draw(sf::Time& deltaTime)
{
    if (currentStage != STAGE_TWO)
        m_window->draw(m_stageBackground);
    else {
        m_stage2BackgroundAnim.update(deltaTime);
        m_window->draw(m_animatedBackground);
    }

    m_world.setDoorKeyString(m_player->getKeyCount());

    m_world.draw(*m_window, deltaTime);


    m_player->setHealthBarPosition(sf::Vector2f
    (m_view.getCenter().x - 155, m_view.getCenter().y - 115));

    for (auto i = m_moveObjects.begin(); i < m_moveObjects.end(); i++)
    {
        (*i)->update(deltaTime);
        (*i)->draw(*m_window);
    }

    updateTextInfo();

    drawGameStats(deltaTime);

    if (playerLost)
    {
        gameOverPopUp.draw(*m_window);
    }

    if (currentStage == STAGE_TWO && stageTwoLoadTime>0) 
    {
        stageTwoStartText.setPosition(sf::Vector2f(m_view.getCenter().x,
            m_view.getCenter().y - 0.25f*CAMERA_HEIGHT));
        m_window->draw(stageTwoStartText);
    }

    if (pauseGame)
    {
        pauseText.setPosition
        (sf::Vector2f(m_view.getCenter().x,
            m_view.getCenter().y - 0.25f * CAMERA_HEIGHT));
        m_window->draw(pauseText);
    }
}


//------------------------- setStageBackground ---------------------------
// Set the stage background.
//------------------------------------------------------------------------
void GameScreen::setStageBackground()
{

    m_stageBackground = sf::RectangleShape(sf::Vector2f
    ({ CAMERA_WIDTH,CAMERA_HEIGHT }));
    m_stageBackground.setOrigin(m_stageBackground.getSize() / 2.f);

    if (currentStage == STAGE_ONE)
    {
        m_stageBackground.setTexture(Resources::instance().
            getWindowObjectTexture(Resources::STAGE1_BACKGROUND));
    }

    else if (currentStage == STAGE_TWO)
    {
        m_view.setCenter(m_player->getPosition());
    }

    else if (currentStage == STAGE_THREE)
    {
        m_stageBackground.setTexture(Resources::instance().
            getWindowObjectTexture(Resources::STAGE3_BACKGROUND));
    }
}


//--------------------------- secondStageRun -----------------------------
// Set the view of the second stage by move up on the Y-axis
// and following the player on X-axist
//------------------------------------------------------------------------
void  GameScreen::setSecondStageView(float deltaTime)
{
    if (stageTwoLoadTime <= 0 && !pauseGame)
        m_view.move(0, CAMERA_MOVE_SPEED);

    else  if (stageTwoLoadTime > 0) 
    {
        stageTwoLoadTime -= deltaTime;

        if(stageTwoLoadTime<=0)
            stageTwoIntialWait = false;
    }

    m_view.setCenter(m_player->getPosition().x, m_view.getCenter().y);

    m_view.setSize(CAMERA_WIDTH, CAMERA_HEIGHT);

    if (m_player->getPosition().y - 150 > m_view.getCenter().y) 
    {
        handlePlayerLost();
    }

    m_window->setView(m_view);

    m_animatedBackground.setPosition(m_view.getCenter());

}


//-------------------------- setStageSoundTrack --------------------------
// Play the soundtrack according to the current stage.
//------------------------------------------------------------------------
void GameScreen::setStageSoundTrack()
{
    auto& res = Resources::instance();

    res.pauseMusic();

    if (currentStage == STAGE_ONE)
    {
        res.playStage1SoundTrack();
    }
    else if (currentStage == STAGE_TWO)
    {
        res.playStage2SoundTrack();
    }
    else if (currentStage == STAGE_THREE)
    {
        res.playStage3SoundTrack();
    }
}


//--------------------------- setPlayerObject ----------------------------
// Sets the player object inside the vector that hold all the moveable
// objects.
//------------------------------------------------------------------------
void GameScreen::setPlayerObject(const sf::Vector2f& pos)
{
    auto playerIndex = m_moveObjects.size();
    m_moveObjects.push_back(std::make_unique<Player>
        (sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE), pos));

    // New player ==> new pointer to the player class.
    // Needed for functions that are not accessible
    // from the base department. 
    // Note: we use static cast because we know the location of the player.
    m_player = static_cast<Player*>(m_moveObjects[playerIndex].get());
}


//---------------------------- setBearObject -----------------------------
// Sets the Bear object into the vector that hold all the moveable objects.
//------------------------------------------------------------------------
void GameScreen::setBearObject(const sf::Vector2f& pos)
{
    m_moveObjects.push_back(std::make_unique<Bear>(BEAR_SIZE, pos));
}


//---------------------------- setCrowObject -----------------------------
// Sets the Crow object into the vector that hold all the moveable objects.
//------------------------------------------------------------------------
void GameScreen::setCrowObject(const sf::Vector2f& pos)
{
    m_moveObjects.push_back(std::make_unique<Crow>(CROW_SIZE, pos));
}


//---------------------------- setWolfObject -----------------------------
// Sets the Wolf object into the vector that hold all the moveable objects.
//------------------------------------------------------------------------
void GameScreen::setWolfObject(const sf::Vector2f& pos)
{
    m_moveObjects.push_back(std::make_unique<Wolf>(WOLF_SIZE, pos));
}


void GameScreen::draw(sf::RenderWindow&) {}

void GameScreen::handleHover(const sf::Vector2f&, sf::RenderWindow&) {}

void GameScreen::handleClick(const sf::Vector2f&, bool&, int&) {}

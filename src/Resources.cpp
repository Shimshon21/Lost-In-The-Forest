
//-------------------------- Include section  ----------------------------
#include "Resources.h"
#include "AnimationData.h"
#include "Macros.h"


namespace {

	//---------------------- getStaticAnimationData ----------------------
	//			Set the Static objects animations data and time.
	//--------------------------------------------------------------------
	AnimationData getStaticAnimationData
	(const sf::Vector2i size,
		const sf::Vector2i initSpace,
		const sf::Vector2i middleSpace,
		const int count)
	{

		auto staticData = AnimationData{};
		auto currentStart = initSpace;

		auto nextStart = [&]()
		{
			currentStart += middleSpace;
			currentStart.x += size.x;
			return currentStart;
		};

		staticData.m_data[Operation::Stay].
			emplace_back(currentStart, size);
		for (int i = 0; i < count; i++) {
			staticData.m_data[Operation::Stay].
				emplace_back(nextStart(), size);
		}
		staticData.m_time[Operation::Stay] = 0.1f;
		staticData.playOnce[Operation::Stay] = false;
		return staticData;
	}


	//----------------------- getLifeAnimationData -----------------------
	//			Get the animation data of the HP boost item
	//--------------------------------------------------------------------
	AnimationData getLifeAnimationData() 
	{
		auto lifeData = AnimationData{};
		auto currentStart = sf::Vector2i(0,330);

		lifeData.m_data[Operation::Stay].
			emplace_back(currentStart,sf::Vector2i{ 16,17 });

		currentStart = sf::Vector2i(21, 330);

		lifeData.m_data[Operation::Stay].
			emplace_back(currentStart, sf::Vector2i{ 24,21 });

		currentStart = sf::Vector2i(50, 330);

		lifeData.m_data[Operation::Stay].
			emplace_back(currentStart, sf::Vector2i{ 28,28 });

		currentStart = sf::Vector2i(21, 330);

		lifeData.m_data[Operation::Stay].
			emplace_back(currentStart, sf::Vector2i{ 24,21 });

		lifeData.playOnce[Operation::Stay] = false;

		return lifeData;
	}


	//---------------------- getWaterFallAnimationData ----------------------
	//		Get the animation data of the water fall background that
	//		used in stage 2 in the game.
	//-----------------------------------------------------------------------
	AnimationData getWaterFallAnimationData()
	{
		auto waterFall = AnimationData{};

		waterFall.playOnce[Operation::Stay] = false;

		sf::Vector2i size = { 300,532 },
			initSpace = { 200,0 }, middleSpace = { 445,0 };
		auto currentStart = initSpace;

		auto nextStart = [&]()
		{
			currentStart += middleSpace;
			currentStart.x += size.x;
			return currentStart;
		};

		waterFall.m_data[Operation::Stay].
			emplace_back(currentStart, size);
		for (int i = 0; i < 6; i++) {
			waterFall.m_data[Operation::Stay].
				emplace_back(nextStart(), size);
		}

		currentStart = sf::Vector2i( 200,733 );
		waterFall.m_data[Operation::Stay].
			emplace_back(currentStart, size);
		for (int i = 0; i < 5; i++) {
			waterFall.m_data[Operation::Stay].
				emplace_back(nextStart(), size);
		}

		return waterFall;
	}


	//----------------------- movableAnimationSet ------------------------
	//		Set the Movable objects animations data, time and frequancy.
	//--------------------------------------------------------------------
	std::vector<sf::IntRect> movableAnimationSet(
		const sf::Vector2i size,
		const sf::Vector2i initSpace,
		const sf::Vector2i middleSpace,
		const int count,Operation typeOperation)
	{

		auto stand_anime = AnimationData{};
		auto currentStart = initSpace;

		auto nextStart = [&]()
		{
			currentStart += middleSpace;
			currentStart.x += size.x;
			return currentStart;
		};

		stand_anime.m_data[typeOperation].
			emplace_back(currentStart, size);
		for (int i = 0; i < count; i++) {
			stand_anime.m_data[typeOperation].
				emplace_back(nextStart(), size);
		}

		return stand_anime.m_data[typeOperation];
	}
	

	//-------------------------- setCurrentData --------------------------
	//				Set animation the data,time and frequancy.
	//--------------------------------------------------------------------
	void setCurrentData(AnimationData& data, Operation op,
		std::vector<sf::IntRect> inRect, float time, bool once)
	{
		data.m_data[op] = inRect;
		data.m_time[op] = time;
		data.playOnce[op] = once;
	}


	//--------------------------- playerAnime ----------------------------
	//						Set the player animations.
	//--------------------------------------------------------------------
	AnimationData playerAnime()
	{
		auto player = AnimationData{};
		setCurrentData(player, Operation::Stay, movableAnimationSet
		({ 45, 37 }, { 1, 0 }, { 0, 0 }, 19,
			Operation::Stay), 0.1f, false);

		setCurrentData(player, Operation::Right, movableAnimationSet
		({ 45, 35 }, { 0, 93 }, { 3, 0 }, 7,
			Operation::Right), 0.05f, false);
		
		setCurrentData(player, Operation::Jump, movableAnimationSet
		({ 44, 55 }, { 91, 38 }, { 1, 0 }, 10,
			Operation::Jump), 0.15f, true);

		setCurrentData(player, Operation::Fall, movableAnimationSet
		({ 45, 55 }, { 451, 38 }, { 1, 0 }, 3,
			Operation::Fall), 0.1f, false);

		setCurrentData(player, Operation::Hit, movableAnimationSet
		({ 49, 36 }, { 1, 129 }, { 1, 0 }, 8,
			Operation::Hit), 0.05f, true);

		setCurrentData(player, Operation::Shoot, movableAnimationSet
		({ 39, 37 }, { 1, 166 }, { 0, 0 }, 9,
			Operation::Shoot), 0.08f, true);

		setCurrentData(player, Operation::Pick_up, movableAnimationSet
		({ 39, 47 }, { 0, 202 }, { 0, 0 }, 7,
			Operation::Pick_up), 0.05f, true);

		setCurrentData(player, Operation::Pick_up_Right, movableAnimationSet
		({ 51, 32 }, { 0, 252 }, { 0, 0 }, 7,
			Operation::Pick_up), 0.05f, false);

		setCurrentData(player, Operation::Pick_up_Jump, movableAnimationSet
		({ 42, 53 }, { 0, 288 }, { 0, 0 }, 11,
			Operation::Pick_up_Jump), 0.1f, true);

		setCurrentData(player, Operation::Pick_up_Fall, movableAnimationSet
		({ 42, 53 }, { 462, 288 }, { 0, 0 }, 2,
			Operation::Pick_up_Fall), 0.1f, false);

		setCurrentData(player, Operation::Pick_up_Land, movableAnimationSet
		({ 42, 53 }, { 588, 288 }, { 0, 0 }, 2,
			Operation::Pick_up_Land), 0.1f, true);
		
		setCurrentData(player, Operation::Pick_up_Idle, movableAnimationSet
		({ 40, 39 }, { 0, 360 }, { 0, 0 }, 2,
			Operation::Pick_up_Idle), 0.3f, true);

		setCurrentData(player, Operation::Loading1, movableAnimationSet
		({ 45, 45 }, { 0, 547 }, {  0, 0 }, 4,
			Operation::Loading1), 0.05f, true);


		setCurrentData(player, Operation::Loading2, movableAnimationSet
		({ 45, 45 }, { 271, 547 }, { 0, 0 }, 8,
			Operation::Loading2), 0.15f, false);

		setCurrentData(player, Operation::Loading1, movableAnimationSet
		({ 45, 45 }, { 0, 547 }, { 0, 0 }, 14, 
			Operation::Loading1), 0.05f, false);

		setCurrentData(player, Operation::Hurt, movableAnimationSet
		({ 37, 36 }, { 0, 405 }, { 0, 0 }, 8,
			Operation::Hurt), 0.05f, true);

		setCurrentData(player, Operation::Dead, movableAnimationSet
		({ 50, 30}, { 0, 443 }, { 0, 0 }, 5,
			Operation::Dead), 0.15f, true);

		return player;
	}


	//---------------------------- bearAnime -----------------------------
	//						Set the bear animations.
	//--------------------------------------------------------------------
	AnimationData bearAnime() 
	{
		auto bear = AnimationData{};

		setCurrentData(bear, Operation::Stay, movableAnimationSet
		({ 82,53 }, { 0,9 }, { 15,0 }, 10, Operation::Stay), 0.1f, false);

		setCurrentData(bear, Operation::Right, movableAnimationSet
		({ 82,52 }, { 0,85 }, { 13,0 }, 5, Operation::Right), 0.15f, false);

		setCurrentData(bear, Operation::Hit, movableAnimationSet
		({ 84,78 }, { 0,145 }, { 0,0 }, 4, Operation::Hit), 0.15f, true);

		setCurrentData(bear, Operation::Fall, movableAnimationSet
		({ 72,65 }, { 587,82 }, { 0,0 }, 0, Operation::Fall), 0.15f, false);

		setCurrentData(bear, Operation::Hurt, movableAnimationSet
		({ 66,63 }, { 682,83 }, { 12,0 }, 1, Operation::Hurt), 0.25f, true);

		setCurrentData(bear, Operation::Dead, movableAnimationSet
		({ 88,46 }, { 264,232 }, { 0,0 }, 1, Operation::Dead), 0.25f, true);

		return bear;
	}


	//---------------------------- wolfAnime -----------------------------
	//						Set the wolf animations.
	//--------------------------------------------------------------------
	AnimationData wolfAnime()
	{
		auto wolf = AnimationData{};

		setCurrentData(wolf, Operation::Stay, movableAnimationSet
		({ 65,38 }, { 5,295 }, { 5,0 }, 9, Operation::Stay), 0.1f,false);

		setCurrentData(wolf, Operation::Right, movableAnimationSet
		({ 70,33 }, { 140,340 }, { 0,0 }, 5, Operation::Right), 0.1f, false);

		setCurrentData(wolf, Operation::Fall, movableAnimationSet
		({ 70,33 }, { 280,340 }, { 0,0 }, 0, Operation::Fall), 0.15f, false);

		setCurrentData(wolf, Operation::Hit, movableAnimationSet
		({ 62,43 }, { 0,379 }, { 0,0 }, 9, Operation::Hit), 0.05f, true);

		setCurrentData(wolf, Operation::Hurt, movableAnimationSet
		({ 54,45 }, { 0,426 }, { 0,0 }, 0, Operation::Hurt), 0.25f, true);

		setCurrentData(wolf, Operation::Dead, movableAnimationSet
		({ 54,45 }, { 0,426 }, { 0,0 }, 9, Operation::Dead), 0.25f, true);

		return wolf;
	}


	//---------------------------- crowAnime -----------------------------
	//						Set the crow animations.
	//--------------------------------------------------------------------
	AnimationData crowAnime()
	{
		auto crow = AnimationData{};
		setCurrentData(crow, Operation::Stay, movableAnimationSet
		({ 40,50 }, { 0,491 }, { 0,0 }, 5, Operation::Stay), 0.1f, false);

		setCurrentData(crow, Operation::Right, movableAnimationSet
		({ 40,50 }, { 0,491 }, { 0,0 }, 5, Operation::Right), 0.1f, false);

		setCurrentData(crow, Operation::Hurt, movableAnimationSet
		({ 43,50 }, { 0,542 }, { 0,0 }, 0, Operation::Hurt), 0.25f, true);

		setCurrentData(crow, Operation::Fall, movableAnimationSet
		({ 42,50 }, { 43,542 }, { 14,0 }, 2, Operation::Fall), 0.25f, true);

		setCurrentData(crow, Operation::Hit, movableAnimationSet
		({ 40,50 }, { 0,491 }, { 0,0 }, 0, Operation::Hit), 0.25f, true);

		setCurrentData(crow, Operation::Dead, movableAnimationSet
		({ 53,30 }, { 196,562 }, { 0,0 }, 0, Operation::Dead), 0.25f, true);

		return crow;
	}

}
 

//------------------------------ instance --------------------------------
// Retrun pointer to the single object of class Resources
//------------------------------------------------------------------------
Resources& Resources::instance()
{
	static Resources instance;

	return instance;
}


//--------------------------- setMusicStatues ----------------------------
// Sets the music status.
//------------------------------------------------------------------------
void Resources::setMusicStatues(const bool status)
{
	allow_music = status;
}


//--------------------------- setSoundStatues ----------------------------
// Sets the sound status.
//------------------------------------------------------------------------
void Resources::setSoundStatues(const bool status)
{
	allow_sounds = status;
}


//--------------------------- isMusicAllowed -----------------------------
// Returns of music is player.
//------------------------------------------------------------------------
const bool Resources::isMusicAllowed() const
{
	return allow_music;
}


//-------------------------- isSoundAllowed ------------------------------
// Returns if sound is allowed.
// Returns false if the player turned off the sound in the game.
//------------------------------------------------------------------------
const bool Resources::isSoundAllowed() const
{
	return allow_sounds;
}


//----------------------------- Resources --------------------------------
// Calls auxillary functions to set all the textures, sounds, music of 
// the game.
//------------------------------------------------------------------------
Resources::Resources() :
	m_data(MAX_WORLD_OBJECTS_DATA),
	m_moveableObjectsData(MAX_MOVEABLE),
	m_musicPlayLists(MAX_MUSIC),
	m_sounds(MULTIPLE_SOUNDS_ALLOWED)
{
	setWindowObjectTextures();

	setStaticObjectTextures();

	setMovableObjectTextures();

	setSoundBuffers();

	setMusicPlayList();

	setAnimationsData();

	dataWindowFont.loadFromFile("Roboto_Bold.ttf");
}


//------------------------- getWindowObjectTexture -----------------------
// Return the texture, hold in the vector m_gameObjectTextures,
// in index i.
//------------------------------------------------------------------------
sf::Texture* Resources::getWindowObjectTexture(const int& i)
{

	return &(m_windowObjectTextures[i]);
}



//-------------------getStaticObjectTexture--------------------------
//				Get the static object texutre
//-------------------------------------------------------------------
sf::Texture* Resources::getStaticObjectTexture(const int& i)
{
	return &(m_worldObjectTextures[i]);
}


//----------------------- getMovableObjectTexture ------------------------
// Returns the moveables objects texture.
//------------------------------------------------------------------------
sf::Texture* Resources::getMovableObjectTexture(const int& i)
{
	return &(m_moveableObjectTextures[i]);
}


//---------------------------- getArialfont ------------------------------
// Returns Arial font.
// We use only Arial font in the game.
//------------------------------------------------------------------------
const sf::Font* Resources::getArialfont() const
{
	return &dataWindowFont;
}


//----------------------- setWindowObjectTextures ------------------------
// Set all textures used in screens such stages background,
// buttons texture, icons and etc...
//------------------------------------------------------------------------
void Resources::setWindowObjectTextures()
{
	sf::Texture texture;
	texture.setSmooth(true);
	texture.loadFromFile("stage1_background.png");			// 0
	m_windowObjectTextures.push_back(texture);
	texture.loadFromFile("stage2_background.png");			// 1
	m_windowObjectTextures.push_back(texture);
	texture.loadFromFile("stage3_background.jpg");			// 2
	m_windowObjectTextures.push_back(texture);
	texture.loadFromFile("player_icon.png");				// 3
	m_windowObjectTextures.push_back(texture);
	texture.loadFromFile("special_abilty.png");				// 4
	m_windowObjectTextures.push_back(texture);
	texture.loadFromFile("menu_background.jpg");			// 5 
	m_windowObjectTextures.push_back(texture);
	texture.loadFromFile("menu_title.png");					// 6
	m_windowObjectTextures.push_back(texture);
	texture.loadFromFile("button_background.png");			// 7
	m_windowObjectTextures.push_back(texture);
	texture.loadFromFile("button_background_hover.png");	// 8
	m_windowObjectTextures.push_back(texture);
	texture.loadFromFile("loading_background.png");			// 9
	m_windowObjectTextures.push_back(texture);
	texture.loadFromFile("loading_animation.png");			// 10
	m_windowObjectTextures.push_back(texture);
	texture.loadFromFile("end_game_screen_background.jpg"); // 11
	m_windowObjectTextures.push_back(texture);
	texture.loadFromFile("keyboard_keys.png");				// 12
	m_windowObjectTextures.push_back(texture);
	texture.loadFromFile("letter_z.png");					// 13
	m_windowObjectTextures.push_back(texture);
	texture.loadFromFile("letter_x.png");					// 14
	m_windowObjectTextures.push_back(texture);
	texture.loadFromFile("space_key.png");					// 15
	m_windowObjectTextures.push_back(texture);
	texture.loadFromFile("letter_r.png");					// 16
	m_windowObjectTextures.push_back(texture);
}


//----------------------- setMovableObjectTextures -----------------------
// Set all textures of the moving objects used in the game.
//------------------------------------------------------------------------
void Resources::setMovableObjectTextures()
{
	sf::Texture texture;
	texture.setSmooth(true);
	texture.loadFromFile("player_sprite_sheet.png");		// 0
	m_moveableObjectTextures.push_back(texture);
	texture.setSmooth(false);
	texture.loadFromFile("enemies_sprite_sheet.png");		// 1
	m_moveableObjectTextures.push_back(texture);

}


//--------------------------- setSoundBuffers ----------------------------
// Set the sounds buffer in the game.
//------------------------------------------------------------------------
void Resources::setSoundBuffers()
{
	sf::SoundBuffer m_soundBuff;
	m_soundBuff.loadFromFile("bear_attack_sound.wav");		
	m_soundsBuffer.push_back(m_soundBuff);
	m_soundBuff.loadFromFile("bear_hurt_sound.wav");
	m_soundsBuffer.push_back(m_soundBuff);
	m_soundBuff.loadFromFile("bear_death_sound.wav");
	m_soundsBuffer.push_back(m_soundBuff);
	m_soundBuff.loadFromFile("wolf_attack_sound.wav");
	m_soundsBuffer.push_back(m_soundBuff);
	m_soundBuff.loadFromFile("wolf_hurt_sound.wav");
	m_soundsBuffer.push_back(m_soundBuff);
	m_soundBuff.loadFromFile("wolf_death_sound.wav");
	m_soundsBuffer.push_back(m_soundBuff);
	m_soundBuff.loadFromFile("crow_attack_sound.wav");
	m_soundsBuffer.push_back(m_soundBuff);
	m_soundBuff.loadFromFile("crow_hurt_sound.wav");
	m_soundsBuffer.push_back(m_soundBuff);
	m_soundBuff.loadFromFile("crow_death_sound.wav");
	m_soundsBuffer.push_back(m_soundBuff);
	m_soundBuff.loadFromFile("fire_arrow_sound.wav");
	m_soundsBuffer.push_back(m_soundBuff);
	m_soundBuff.loadFromFile("jump_sound.wav");
	m_soundsBuffer.push_back(m_soundBuff);
	m_soundBuff.loadFromFile("player_hurt_sound.wav");
	m_soundsBuffer.push_back(m_soundBuff);
	m_soundBuff.loadFromFile("player_attack_sound.wav");
	m_soundsBuffer.push_back(m_soundBuff);
	m_soundBuff.loadFromFile("collect_gem_sound.wav");
	m_soundsBuffer.push_back(m_soundBuff);
	m_soundBuff.loadFromFile("key_collected_sound.wav");
	m_soundsBuffer.push_back(m_soundBuff);
	m_soundBuff.loadFromFile("ability_collect_sound.wav");
	m_soundsBuffer.push_back(m_soundBuff);
	m_soundBuff.loadFromFile("button_clicked_sound.wav");
	m_soundsBuffer.push_back(m_soundBuff);
	m_soundBuff.loadFromFile("button_hover_sound.wav");
	m_soundsBuffer.push_back(m_soundBuff);
	m_soundBuff.loadFromFile("arrow_sound.wav");
	m_soundsBuffer.push_back(m_soundBuff);
	m_soundBuff.loadFromFile("health_boost_sound.wav");
	m_soundsBuffer.push_back(m_soundBuff);
}


//------------------------- setMusicPlayList -----------------------------
// Set the musics soundtracks played.
//------------------------------------------------------------------------
void Resources::setMusicPlayList()
{
	m_musicPlayLists[MENU_SOUNDTRACK].openFromFile
	("menu_soundtrack.ogg");
	m_musicPlayLists[MENU_SOUNDTRACK].setVolume(40);

	m_musicPlayLists[STAGE1_SOUNDTRACK].openFromFile
	("stage1_soundtrack.ogg");
	m_musicPlayLists[STAGE1_SOUNDTRACK].setVolume(20);
	m_musicPlayLists[STAGE1_SOUNDTRACK].setLoop(true);

	m_musicPlayLists[STAGE2_SOUNDTRACK].openFromFile
	("stage2_soundtrack.ogg");
	m_musicPlayLists[STAGE2_SOUNDTRACK].setVolume(20);
	m_musicPlayLists[STAGE2_SOUNDTRACK].setLoop(true);

	m_musicPlayLists[STAGE3_SOUNDTRACK].openFromFile
	("stage3_soundtrack.ogg");
	m_musicPlayLists[STAGE3_SOUNDTRACK].setVolume(20);
	m_musicPlayLists[STAGE3_SOUNDTRACK].setLoop(true);

	m_musicPlayLists[ENDING_SOUNTRACK].openFromFile
	("end_game_sountrack.ogg");
	m_musicPlayLists[ENDING_SOUNTRACK].setVolume(20);
	m_musicPlayLists[ENDING_SOUNTRACK].setLoop(true);

	m_musicPlayLists[GAME_OVER_SOUND].openFromFile
	("game_over_sound.ogg");
	m_musicPlayLists[GAME_OVER_SOUND].setVolume(20);
	m_musicPlayLists[GAME_OVER_SOUND].setLoop(false);
}


//-------------------------- setAnimationsData ---------------------------
// Set all animation data used in the game.
//------------------------------------------------------------------------
void Resources::setAnimationsData()
{
	m_data[HURRICANE_DATA] =
		getStaticAnimationData({ 74, 100 }, { 518,0 }, { 0,0 }, 6);

	m_data[GOLD_DATA] =
		getStaticAnimationData({ 28,42 }, { 0,107 }, { 15,0 }, 7);

	m_data[SPEED_ABILITY_DATA] =
		getStaticAnimationData({ 30,37 }, { 0,163 }, { 0,0 }, 11);

	m_data[FIRE_ARROWS_ABILITY_DATA] =
		getStaticAnimationData({ 30,37 }, { 0,201 }, { 0,0 }, 11);

	m_data[JUMP_ABILITY_DATA] =
		getStaticAnimationData({ 30,37 }, { 0,240 }, { 0,0 }, 11);

	m_data[KEY_DATA] =
		getStaticAnimationData({ 18,39 }, { 0,287 }, { 2,0 }, 4);
	m_data[KEY_DATA].m_time[Operation::Stay] = 0.2f;

	m_data[STAGE2_BACKGROUND_DATA] = getWaterFallAnimationData();
	m_data[STAGE2_BACKGROUND_DATA].m_time[Operation::Stay] = 0.1f;
	m_data[STAGE2_BACKGROUND_DATA].playOnce[Operation::Stay] = false;

	m_data[EXTRA_LIFE_DATA] = getLifeAnimationData();
	m_data[EXTRA_LIFE_DATA].m_time[Operation::Stay] = 0.5f;

	m_moveableObjectsData[PLAYER_DATA] = playerAnime();

	m_moveableObjectsData[BEAR_DATA] = bearAnime();

	m_moveableObjectsData[WOLF_DATA] = wolfAnime();

	m_moveableObjectsData[CROW_DATA] = crowAnime();


	m_moveableObjectsData[STONE_ARROWS_DATA] =
		getStaticAnimationData({ 19,29 }, { 1,481 }, { 0,0 }, 5);
	m_moveableObjectsData[STONE_ARROWS_DATA].
		m_time[Operation::Stay] = 0.1f;

	m_moveableObjectsData[STONE_ARROWS_DATA].
		playOnce[Operation::Stay] = true;

	m_moveableObjectsData[FIRE_ARROWS_DATA] =
		getStaticAnimationData({ 19,29 }, { 1,510 }, { 0,0 }, 5);

	m_moveableObjectsData[FIRE_ARROWS_DATA].
		m_time[Operation::Stay] = 0.1f;
	m_moveableObjectsData[FIRE_ARROWS_DATA].
		playOnce[Operation::Stay] = true;
}


//----------------------- setStaticObjectTextures ------------------------
// Set the static object textures.
//------------------------------------------------------------------------
void Resources::setStaticObjectTextures()
{
	sf::Texture texture;
	texture.loadFromFile("world_objects.png");					// 0
	m_worldObjectTextures.push_back(texture);
	texture.loadFromFile("spikes.png");							// 1
	m_worldObjectTextures.push_back(texture);
	texture.loadFromFile("decorations.png");					// 2
	m_worldObjectTextures.push_back(texture);
}


//----------------------------- setVolume --------------------------------
// Set volume according to sound requasted.
//------------------------------------------------------------------------
void Resources::setVolume(const int index,sf::Sound& sound)
{
	if (index == FIRE_ATTACK_SOUND)
		sound.setVolume(20);

	else if(index == ARROW_SOUND)
		sound.setVolume(20);
	else if (index == CROW_ATTACK)
		sound.setVolume(10);
	else if (index == CROW_HURT)
		sound.setVolume(10);
	else if (index == CROW_DEATH)
		sound.setVolume(10);
	else if (index == WOLF_DEATH)
		sound.setVolume(10);

	else
		sound.setVolume(100);
}


//----------------------------- playSound --------------------------------
// Play sound according to given index
//------------------------------------------------------------------------
void Resources::playSound(const int index)
{
	int sound_index = 0;
	if (allow_sounds) {
		while (m_sounds[sound_index].getStatus() == sf::Sound::Playing) {
			sound_index++;
			if (sound_index >= m_sounds.size()) {
				sound_index = 0;
				break;
			}
		}

		setVolume(index, m_sounds[sound_index]);
		m_sounds[sound_index].setBuffer(m_soundsBuffer[index]);
		m_sounds[sound_index].play();
	}
}

 
//---------------------------- pauseMusic --------------------------------
// Pause all music played in the background
//------------------------------------------------------------------------
void Resources::pauseMusic()
{
	for (int i=0;i<MAX_MUSIC-1;i++)
	{
		m_musicPlayLists[i].pause();
	}
	m_musicPlayLists[GAME_OVER_SOUND].stop();
}


//---------------------------- stopMusic ---------------------------------
// Stop all music played in the background
//------------------------------------------------------------------------
void Resources::stopMusic()
{
	for (int i = 0; i < MAX_MUSIC; i++)
	{
		m_musicPlayLists[i].stop();
	}
}


//---------------------- playStage1SoundTrack ---------------------------
// Play Stage 1 soundtrack
//------------------------------------------------------------------------
void Resources::playStage1SoundTrack()
{
	if (allow_music)
	{
		m_musicPlayLists[STAGE1_SOUNDTRACK].play();
	}
}


//------------------------ playStage2SoundTrack --------------------------
// Play Stage 2 soundtrack.
//------------------------------------------------------------------------
void Resources::playStage2SoundTrack()
{
	if (allow_music)
	{
		m_musicPlayLists[STAGE2_SOUNDTRACK].play();
	}
}


//----------------------- playStage3SoundTrack ---------------------------
// play Stage 3 soundtrack 
//------------------------------------------------------------------------
void Resources::playStage3SoundTrack()
{
	if (allow_music)
	{
		m_musicPlayLists[STAGE3_SOUNDTRACK].play();
	}
}



//-------------------------- playMenuSoundTrack --------------------------
// Play Menu soundtrack 
//------------------------------------------------------------------------
void Resources::playMenuSoundTrack()
{
	if (allow_music)
	{
		m_musicPlayLists[MENU_SOUNDTRACK].play();
	}
}


//------------------------ playEndGameSoundTrack -------------------------
// Play End game soundtrack
//------------------------------------------------------------------------
void Resources::playEndGameSoundTrack()
{
	if (allow_music)
	{
		m_musicPlayLists[ENDING_SOUNTRACK].play();
	}
}


//------------------------ playGameOverSoundTrack ------------------------
// Play Player failed soundtrack
//------------------------------------------------------------------------
void Resources::playGameOverSoundTrack()
{
	if (allow_music)
	{
		m_musicPlayLists[GAME_OVER_SOUND].play();
	}
}
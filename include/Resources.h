#pragma once

//-------------------------- Include section  ----------------------------
#include <vector>
#include "SFML/Graphics.hpp"
#include "Animation.h"
#include "SFML/Audio.hpp"

//-------------------------- Class Resources  ----------------------------
class Resources
{
public:
	
	// Return the address of the only object of this class.
	static Resources& instance();

	// d-tor
	virtual ~Resources() = default;

	// Return texture in index i.
	sf::Texture* getWindowObjectTexture(const int& i);

	// Return texture in index i.
	sf::Texture* getStaticObjectTexture(const int& i);

	// Return texture in index i.
	sf::Texture* getMovableObjectTexture(const int& i);

	const sf::Font* getArialfont() const;

	void setVolume(const int index, sf::Sound& sound);

	void playSound(const int index);

	void pauseMusic();

	void stopMusic();

	void playStage1SoundTrack();

	void playStage2SoundTrack();

	void playStage3SoundTrack();

	void playMenuSoundTrack();

	void playEndGameSoundTrack();

	void playGameOverSoundTrack();


	// enum to hold the positions in the 
	// vector that hold the game buttons 
	enum screenTextures
	{
		STAGE1_BACKGROUND,
		STAGE2_BACKGROUND,
		STAGE3_BACKGROUND,
		PLAYER_ICON,
		SPECIAL_ABILITY_ICON,
		MENU_BACKGROUND,
		MENU_TITLE,
		BUTTON_BACKGROUND,
		BUTTON_HOVER_BACKGROUND,
		LOADING_BACKGROUND,
		LOADINGBAR,
		END_GAME_BACKGROUND,
		ARROWS_KEY,
		LETTER_Z,
		LETTER_X,
		SPACE_KEY,
		LETTER_R,
		MAX_WORLD_OBJECTS
	};


	enum gameObjectTextures
	{
		STATIC_ANIMATED,
		SPIKES,
		DECORATIONS,
	};



	enum worldDataAnime
	{
		HURRICANE_DATA,
		GOLD_DATA,
		SPEED_ABILITY_DATA,
		FIRE_ARROWS_ABILITY_DATA,
		JUMP_ABILITY_DATA,
		KEY_DATA,
		EXTRA_LIFE_DATA,
		STAGE2_BACKGROUND_DATA,
		MAX_WORLD_OBJECTS_DATA
	};

	enum movableObjectTextures
	{
		PLAYER,
		ENEMIES,
		MAX_MOVEABLE_OBJECTS
	};

	enum movableDataAnime
	{
		PLAYER_DATA,
		BEAR_DATA,
		WOLF_DATA,
		CROW_DATA,
		STONE_ARROWS_DATA,
		FIRE_ARROWS_DATA,
		MAX_MOVEABLE
	};


	const AnimationData& animationWorldData(worldDataAnime object)
	{ return m_data[object]; }


	const AnimationData& moveableAnimationsData(movableDataAnime object)
	{ return m_moveableObjectsData[object]; }


	void setMusicStatues(const bool);

	void setSoundStatues(const bool);

	const bool isMusicAllowed()const;

	const bool isSoundAllowed()const;

private:
	bool allow_music = true, allow_sounds = true;

	Resources(const Resources&) = default;

	Resources& operator=(const Resources&) = default;

	// c-tor
	Resources();

	sf::Texture m_texture;

	// vector to hold the window objects.
	std::vector<sf::Texture> m_windowObjectTextures;

	// vector to hold the world map objects.
	std::vector<sf::Texture> m_worldObjectTextures;

	// vector to hold the world map objects.
	std::vector<sf::Texture> m_moveableObjectTextures;

	//
	std::vector<AnimationData> m_data;

	//
	std::vector<AnimationData> m_moveableObjectsData;

	// Set general window  gameObjectTextures of the game.
	void setWindowObjectTextures();

	void setStaticObjectTextures();

	void setMovableObjectTextures();

	void setSoundBuffers();

	void setMusicPlayList();

	void setAnimationsData();

	sf::Font dataWindowFont;

	// Vector to hold all the sounds of the game
	std::vector<sf::SoundBuffer>m_soundsBuffer;

	std::vector<sf::Music>m_musicPlayLists;

	std::vector<sf::Sound> m_sounds;
	//sf::Sound m_sound;

	sf::Music m_music;
};


enum sounds
{
	BEAR_ATTACK,
	BEAR_HURT,
	BEAR_DEATH,
	WOLF_ATTACK,
	WOLF_HURT,
	WOLF_DEATH,
	CROW_ATTACK,
	CROW_HURT,
	CROW_DEATH,
	FIRE_ATTACK_SOUND,
	JUMP_SOUND,
	PLAYER_HURT_SOUND,
	PLAYER_ATTACK_SOUND,
	COLLECT_GEM_SOUND,
	COLLECT_KEY_SOUND,
	COLLECT_ABILITY_SOUND,
	BUTTON_CLICKED_SOUND,
	BUTTON_HOVER_SOUND,
	ARROW_SOUND,
	LIFE_BOOST_SOUND
};

enum music
{
	MENU_SOUNDTRACK,
	STAGE1_SOUNDTRACK,
	STAGE2_SOUNDTRACK,
	STAGE3_SOUNDTRACK,
	ENDING_SOUNTRACK,
	GAME_OVER_SOUND,
	MAX_MUSIC
};


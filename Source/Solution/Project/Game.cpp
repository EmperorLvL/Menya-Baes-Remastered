#include "script.h"

namespace Game
{

	namespace Print
	{
		void setupdraw()
		{
			HUD::SET_TEXT_CENTRE(0);
			HUD::SET_TEXT_FONT(0);
			HUD::SET_TEXT_COLOUR(255, 255, 255, 255);
			HUD::SET_TEXT_SCALE(0.3f, 0.3f);
		}

		void drawstring(std::string string, float X, float Y)
		{
			HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
			HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(const_cast<PCHAR>(string.c_str()));
			HUD::END_TEXT_COMMAND_DISPLAY_TEXT(X, Y, 0);
		}

		void drawinteger(int value, float X, float Y)
		{
			HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("NUMBER");
			HUD::ADD_TEXT_COMPONENT_INTEGER(value);
			HUD::END_TEXT_COMMAND_DISPLAY_TEXT(X, Y, 0);
		}

		void drawfloat(float value, int places, float X, float Y)
		{
			HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("NUMBER");
			HUD::ADD_TEXT_COMPONENT_FLOAT(value, places);
			HUD::END_TEXT_COMMAND_DISPLAY_TEXT(X, Y, 0);
		}

		void PrintStringBottomCentre(const char* string)
		{
			HUD::BEGIN_TEXT_COMMAND_PRINT("STRING");
			HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(string);
			HUD::END_TEXT_COMMAND_PRINT(2000, 1);
		}

		void PrintBottomLeft(const char* string)
		{
			HUD::BEGIN_TEXT_COMMAND_THEFEED_POST("STRING");
			HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(string);
			HUD::END_TEXT_COMMAND_THEFEED_POST_MPTICKER(0, 1);
		}
	}

	namespace Sound
	{
		void PlaySoundFrontend(const char* soundDict, const char* soundName)
		{
			AUDIO::PLAY_SOUND_FRONTEND(-1, soundName, soundDict, 0);
		}

		void PlaySoundFrontend_default(const char* soundName)
		{
			AUDIO::PLAY_SOUND_FRONTEND(-1, soundName, "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);
		}
	}
}
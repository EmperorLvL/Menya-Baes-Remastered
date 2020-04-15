#include "script.h"

namespace Game
{

	namespace Print
	{
		void setupdraw()
		{
			SET_TEXT_FONT(0);
			SET_TEXT_SCALE(0.4f, 0.4f);
			SET_TEXT_COLOUR(255, 255, 255, 255);
			SET_TEXT_WRAP(0.0f, 1.0f);
			SET_TEXT_CENTRE(0);
			SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
			SET_TEXT_EDGE(0, 0, 0, 0, 0);
			SET_TEXT_OUTLINE();
		}

		void drawstring(std::string string, float X, float Y)
		{
			BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
			ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(const_cast<PCHAR>(string.c_str()));
			END_TEXT_COMMAND_DISPLAY_TEXT(X, Y);
		}

		void drawinteger(int value, float X, float Y)
		{
			BEGIN_TEXT_COMMAND_DISPLAY_TEXT("NUMBER");
			ADD_TEXT_COMPONENT_INTEGER(value);
			END_TEXT_COMMAND_DISPLAY_TEXT(X, Y);
		}

		void drawfloat(float value, DWORD decimal_places, float X, float Y)
		{
			BEGIN_TEXT_COMMAND_DISPLAY_TEXT("NUMBER");
			ADD_TEXT_COMPONENT_FLOAT(value, decimal_places);
			END_TEXT_COMMAND_DISPLAY_TEXT(X, Y);
		}

		void PrintStringBottomCentre(std::string string)
		{
			BEGIN_TEXT_COMMAND_PRINT("STRING");
			ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(const_cast<PCHAR>(string.c_str()));
			END_TEXT_COMMAND_PRINT(2000, 1);
		}

		void PrintFloatBottomCentre(float text, __int8 decimal_places)
		{
			BEGIN_TEXT_COMMAND_PRINT("NUMBER");
			ADD_TEXT_COMPONENT_FLOAT(text, (DWORD)decimal_places);
			END_TEXT_COMMAND_PRINT(2000, 1);
		}

		void PrintBottomLeft(std::string string)
		{
			_SET_NOTIFICATION_TEXT_ENTRY("STRING");
			ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(const_cast<PCHAR>(string.c_str()));
			_DRAW_NOTIFICATION(0, 1);
		}
	}

	namespace Sound
	{
		void PlaySoundFrontend(char* sound_dict, char* sound_name)
		{
			PLAY_SOUND_FRONTEND(-1, sound_name, sound_dict, 0);
		}

		void PlaySoundFrontend_default(char* sound_name)
		{
			PLAY_SOUND_FRONTEND(-1, sound_name, "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);
		}
	}
}
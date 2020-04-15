#pragma once

#include <string>

namespace Game
{
	namespace Print
	{
		void setupdraw();
		void drawstring(std::string string, float X, float Y);
		void drawinteger(int value, float X, float Y);
		void drawfloat(float value, DWORD decimal_places, float X, float Y);

		void PrintStringBottomCentre(std::string string);
		void PrintFloatBottomCentre(float text, __int8 decimal_places);
		void PrintBottomLeft(std::string string);
	}

	namespace Sound
	{
		void PlaySoundFrontend(char* sound_dict, char* sound_name);
		void PlaySoundFrontend_default(char* sound_name);
	}
}
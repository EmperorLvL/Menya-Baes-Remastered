#pragma once

#include <string>

namespace Game
{
	namespace Print
	{
		void setupdraw();
		void drawstring(std::string string, float X, float Y);
		void drawinteger(int value, float X, float Y);
		void drawfloat(float value, int places, float X, float Y);

		void PrintStringBottomCentre(const char* string);
		void PrintBottomLeft(const char* string);
	}

	namespace Sound
	{
		void PlaySoundFrontend(const char* sound_dict, const char* sound_name);
		void PlaySoundFrontend_default(const char* sound_name);
	}
}
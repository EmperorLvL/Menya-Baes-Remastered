#include "script.h"
#pragma warning(disable : 4244 4305) // double <-> float conversions

namespace
{
	// Declare/Initialise global variables here.
	char str[69];
	float current_timescale = 1.0f;
	// Booleans for loops go here:
	bool loop_massacre_mode = 0, loop_RainbowBoxes = 0, loop_player_invincibility = 0, loop_player_neverwanted = 0;
}

namespace
{
	// Declare subroutines here.

}

namespace
{
	// Define subroutines here.

	void VectorToFloat(Vector3 unk, float* Out)
	{
		Out[0] = unk.x;
		Out[1] = unk.y;
		Out[2] = unk.z;
	}

	int RandomRGB()
	{
		srand(GetTickCount64());
		return (GET_RANDOM_INT_IN_RANGE(0, 255));
	}

	void offset_from_entity(int entity, float X, float Y, float Z, float* Out)
	{
		VectorToFloat(GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(entity, X, Y, Z), Out);
	}

	char* TextKeyboard() 
	{
		DISPLAY_ONSCREEN_KEYBOARD(1, "", "", "", "", "", "", 20);
		while (UPDATE_ONSCREEN_KEYBOARD() == 0) scriptWait(0);
		if (!GET_ONSCREEN_KEYBOARD_RESULT())
			return "";
		return GET_ONSCREEN_KEYBOARD_RESULT();
	}

	int NumberKeyboard()
	{
		DISPLAY_ONSCREEN_KEYBOARD(1, "", "", "", "", "", "", 20);
		while (UPDATE_ONSCREEN_KEYBOARD() == 0) scriptWait(0);
		if (!GET_ONSCREEN_KEYBOARD_RESULT())
			return 0;
		return atof(GET_ONSCREEN_KEYBOARD_RESULT());
	}

	char* AddStrings(char* string1, char* string2)
	{
		memset(str, 0, sizeof(str));
		strcpy_s(str, "");
		strcpy_s(str, string1);
		strcat_s(str, string2);
		return str;
	}

	void PrintError_no_longer_in_mem()
	{
		Game::Print::PrintStringBottomCentre("~r~Error:~s~ No longer in memory.");
	}

	void PrintError_Waypoint()
	{
		Game::Print::PrintStringBottomCentre("~r~Error:~s~ No Waypoint Set.");
	}

	void PrintError_InvalidInput()
	{
		Game::Print::PrintStringBottomCentre("~r~Error:~s~ Invalid Input.");
	}

	void PrintError_InvalidModel()
	{
		Game::Print::PrintStringBottomCentre("~r~Error:~s~ Invalid Model.");
	}

	// Hax functions:
	void set_massacre_mode()
	{
		float tempCoords1[3];
		DWORD tempHash;
		DWORD tempPed = PLAYER_PED_ID();
		DWORD tempVehicle;
		bool tick = 0;

		offset_from_entity(tempPed, GET_RANDOM_FLOAT_IN_RANGE(5.0f, 25.0f), GET_RANDOM_FLOAT_IN_RANGE(5.0f, 25.0f), GET_RANDOM_FLOAT_IN_RANGE(0.4f, 20.0f), tempCoords1);

		// Kick away naughty players
		for (int i = 0; i <= 29; i++)
		{
			if (IS_PLAYER_TARGETTING_ENTITY(i, tempPed) || IS_PLAYER_FREE_AIMING_AT_ENTITY(i, tempPed))
			{
				if (!tick)
				{
					Game::Print::PrintStringBottomCentre("~h~You~s~ are being aimed at. Taking care of it!");
					tick = true;
				}
				APPLY_FORCE_TO_ENTITY(GET_PLAYER_PED(i), 1, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 1, 1, 1, 1, 0, 1);
			}
		}

		// Kick away nearest vehicle
		tempVehicle = GET_CLOSEST_VEHICLE(tempCoords1[0], tempCoords1[1], tempCoords1[2], 400.0f, 0, 4);
		if (DOES_ENTITY_EXIST(tempVehicle)) APPLY_FORCE_TO_ENTITY(tempVehicle, 1, 5.0f, 5.0f, 5.0f, 5.0f, 13.0f, 6.5f, 1, 1, 1, 1, 0, 1);

		// Exploding vehicles
		switch (GET_RANDOM_INT_IN_RANGE(1, 10))
		{
		case 1: tempHash = 3945366167; break;
		case 2: tempHash = 92612664; break;
		case 3: tempHash = 1488164764; break;
		case 4: tempHash = 117401876; break;
		case 5: tempHash = 408192225; break;
		case 6: tempHash = 3863274624; break;
		case 7: tempHash = 165154707; break;
		case 8: tempHash = 1011753235; break;
		case 9: tempHash = 941800958; break;
		case 10: tempHash = 970385471; break;
		}

		tempVehicle = CREATE_VEHICLE(tempHash, tempCoords1[0], tempCoords1[1], tempCoords1[2], GET_RANDOM_FLOAT_IN_RANGE(0.0f, 360.0f), 1, 1);
		APPLY_FORCE_TO_ENTITY(tempVehicle, 1, 5.0f, 5.0f, 5.0f, 5.0f, 13.0f, 6.5f, 1, 1, 1, 1, 0, 1);
		NETWORK_EXPLODE_VEHICLE(tempVehicle, 1, 1, 1);

		// Dying peds
		switch (GET_RANDOM_INT_IN_RANGE(1, 10))
		{
		case 1: tempHash = 1682622302; break;
		case 2: tempHash = 113504370; break;
		case 3: tempHash = 4244282910; break;
		case 4: tempHash = 808859815; break;
		case 5: tempHash = 1004114196; break;
		case 6: tempHash = 3696858125; break;
		case 7: tempHash = 921110016; break;
		case 8: tempHash = 880829941; break;
		case 9: tempHash = 1462895032; break;
		case 10: tempHash = 773063444; break;
		}

		offset_from_entity(tempPed, GET_RANDOM_FLOAT_IN_RANGE(5.0f, 25.0f), GET_RANDOM_FLOAT_IN_RANGE(5.0f, 25.0f), GET_RANDOM_FLOAT_IN_RANGE(0.4f, 20.0f), tempCoords1);
		tempPed = CREATE_PED(22, tempHash, tempCoords1[0], tempCoords1[1], tempCoords1[2], GET_RANDOM_FLOAT_IN_RANGE(0.0f, 360.0f), 1, 1);
		APPLY_FORCE_TO_ENTITY(tempPed, 1, 5.0f, 5.0f, 5.0f, 5.0f, 13.0f, 6.5f, 1, 1, 1, 1, 0, 1);
		EXPLODE_PED_HEAD(tempPed, 324506233);
		ADD_EXPLOSION(tempCoords1[0], tempCoords1[1], tempCoords1[2], 26, 4.0f, 1, 0, 3.0f);

		// Water hydrants
		offset_from_entity(tempPed, GET_RANDOM_FLOAT_IN_RANGE(5.0f, 25.0f), GET_RANDOM_FLOAT_IN_RANGE(5.0f, 25.0f), GET_RANDOM_FLOAT_IN_RANGE(0.4f, 20.0f), tempCoords1);
		ADD_EXPLOSION(tempCoords1[0], tempCoords1[1], tempCoords1[2], 13, 8.0f, 1, 0, 3.0f);

		// Zombies
		offset_from_entity(tempPed, GET_RANDOM_FLOAT_IN_RANGE(5.0f, 25.0f), GET_RANDOM_FLOAT_IN_RANGE(5.0f, 25.0f), GET_RANDOM_FLOAT_IN_RANGE(0.4f, 20.0f), tempCoords1);
		tempPed = CREATE_PED(22, -1404353274, tempCoords1[0], tempCoords1[1], tempCoords1[2], GET_RANDOM_FLOAT_IN_RANGE(0.0f, 360.0f), 1, 1);
		PED_TO_NET(tempPed);
		SET_PED_COMBAT_ABILITY(tempPed, 100);
		TASK_COMBAT_HATED_TARGETS_AROUND_PED(tempPed, 400.0f, 0);
	}
}

namespace sub {
	// Define submenus here.

	void MainMenu()
	{
		AddTitle("Menya Baes");
		AddOption("Sample Self", null, nullFunc, SUB::SAMPLE);
		AddOption("Sample Teleport", null, nullFunc, SUB::SAMPLETELEPORT);
		AddOption("Sample World", null, nullFunc, SUB::SAMPLEWORLD);
		AddOption("Settings", null, nullFunc, SUB::SETTINGS);

		if (menujustopened)
		{
			Game::Print::PrintBottomLeft(AddStrings("Menya Base by ", "MAFINS.")); // Your opening message goes here.
			menujustopened = false;
		}
	}

	void SampleSelf()
	{
		bool sample_invisible = 0, player_invincibility_off = 0, player_wanted_plus = 0, player_wanted_minus = 0;
		int player_wanted_level = GET_PLAYER_WANTED_LEVEL(PLAYER_ID());

		AddTitle("Sample");
		AddToggle("Invincibility", loop_player_invincibility, null, player_invincibility_off);
		AddLocal("Invisibility", !IS_ENTITY_VISIBLE(PLAYER_PED_ID()), sample_invisible, sample_invisible);
		AddNumber("Wanted Level", player_wanted_level, 0, null, player_wanted_plus, player_wanted_minus);
		AddToggle("Never Wanted", loop_player_neverwanted, null, null);

		if (player_invincibility_off) {
			SET_PLAYER_INVINCIBLE(PLAYER_ID(), 0);
			return;
		}

		if (sample_invisible) {
			if (IS_ENTITY_VISIBLE(PLAYER_PED_ID())) SET_ENTITY_VISIBLE(PLAYER_PED_ID(), 0, 0);
			else SET_ENTITY_VISIBLE(PLAYER_PED_ID(), 1, 0);
			return;
		}

		if (player_wanted_plus) {
			if (player_wanted_level < 6)
			{
				player_wanted_level += 1;
				SET_MAX_WANTED_LEVEL(6);
				SET_PLAYER_WANTED_LEVEL(PLAYER_ID(), player_wanted_level, 0);
				SET_PLAYER_WANTED_LEVEL_NOW(PLAYER_ID(), 0);
			}
		}

		if (player_wanted_minus) {
			if (player_wanted_level > 0)
			{
				player_wanted_level -= 1;
				SET_PLAYER_WANTED_LEVEL(PLAYER_ID(), player_wanted_level, 0);
				SET_PLAYER_WANTED_LEVEL_NOW(PLAYER_ID(), 0);
			}
		}
	}

	void SampleTeleport()
	{
		AddTitle("Teleport");
		AddTele("Airport Entrance", -1034.6f, -2733.6f, 13.8f);
		AddTele("Airport Runway", -1336.0f, -3044.0f, 13.9f);
		AddTele("Michael's House", -813.603f, 179.474f, 72.1548f);
		AddTele("Franklin's House", -14.3803f, -1438.51f, 31.1073f);
		AddTele("Trevor's House", 1972.61f, 3817.04f, 33.4278f);
		AddTele("Trevor's House 2", -1151.77f, -1518.14f, 10.6327f);
		AddTele("Trevor's Office", 97.2707f, -1290.9940f, 29.2688f);
	}

	void SampleWorld()
	{
		bool hour_plus = 0, hour_minus = 0, timescale_plus = 0, timescale_minus = 0;
		int sample_hour = GET_CLOCK_HOURS();

		AddTitle("World");
		AddNumber("Hour", GET_CLOCK_HOURS(), 0, null, hour_plus, hour_minus);
		AddNumber("Time Scale", current_timescale, 2, null, timescale_plus, timescale_minus);
		AddToggle("Massacre Mode", loop_massacre_mode);

		if (hour_plus) {
			if (sample_hour + 1 == 24) NETWORK_OVERRIDE_CLOCK_TIME(0, 0, 0);
			else NETWORK_OVERRIDE_CLOCK_TIME((sample_hour + 1), 0, 0);
			return;
		}
		else if (hour_minus) {
			if ((sample_hour - 1) == -1) NETWORK_OVERRIDE_CLOCK_TIME(23, 0, 0);
			else NETWORK_OVERRIDE_CLOCK_TIME((sample_hour - 1), 0, 0);
			return;
		}

		if (timescale_plus) {
			if (current_timescale < 2.0f) current_timescale += 0.1f;
			SET_TIME_SCALE(current_timescale);
			return;
		}
		else if (timescale_minus) {
			if (current_timescale > 0.0f) current_timescale -= 0.1f;
			SET_TIME_SCALE(current_timescale);
			return;
		}
	}

	void Settings()
	{
		bool settings_xpos_plus = 0, settings_xpos_minus = 0, settings_ypos_plus = 0, settings_ypos_minus = 0;

		AddTitle("Settings");
		AddOption("Menu Colours", null, nullFunc, SUB::SETTINGS_COLOURS);
		AddOption("Menu Fonts", null, nullFunc, SUB::SETTINGS_FONTS);
		AddToggle("Centre Title", menu::bit_centre_title);
		AddToggle("Centre Options", menu::bit_centre_options);
		AddToggle("Centre Breaks", menu::bit_centre_breaks);
		AddNumber("Menu X", menuPos.x * 100 + 6.0, 2, null, settings_xpos_plus, settings_xpos_minus);
		AddNumber("Menu Y", menuPos.y * 100 + 7.4, 2, null, settings_ypos_plus, settings_ypos_minus);

		if (settings_xpos_plus) {
			if (menuPos.x < 0.7397f) menuPos.x += 0.002f;
			return;
		}
		else if (settings_xpos_minus) {
			if (menuPos.x > -0.0598f) menuPos.x -= 0.002f;
			if (menuPos.x < -0.0598f) menuPos.x = -0.0598f;
			return;
		}

		if (settings_ypos_plus) {
			if (menuPos.y < 0.85f) menuPos.y += 0.002f;
			return;
		}
		else if (settings_ypos_minus) {
			if (menuPos.y > -0.074f) menuPos.y -= 0.002f;
			if (menuPos.y < -0.074f) menuPos.y = -0.074f;
			return;
		}
	}

	void AddsettingscolOption(char* text, RGBA& feature)
	{
		AddOption(text, null, nullFunc, SUB::SETTINGS_COLOURS2);

		if (menu::printingop == menu::currentop) settings_rgba = &feature;
	}

	void SettingsColours()
	{
		AddTitle("Menu Colours");
		AddsettingscolOption("Title Box", titlebox);
		AddsettingscolOption("Background", BG);
		AddsettingscolOption("Title Text", titletext);
		AddsettingscolOption("Option Text", optiontext);
		AddsettingscolOption("Selected Text", selectedtext);
		AddsettingscolOption("Option Breaks", optionbreaks);
		AddsettingscolOption("Option Count", optioncount);
		AddsettingscolOption("Selection Box", selectionhi);
		AddToggle("Rainbow", loop_RainbowBoxes);
	}

	void SettingsColours2()
	{
		bool settings_r_input = 0, settings_r_plus = 0, settings_r_minus = 0;
		int* settings_rgba2;

		AddTitle("Set Colour");
		AddNumber("Red", settings_rgba->R, 0, settings_r_input, settings_r_plus, settings_r_minus);
		AddNumber("Green", settings_rgba->G, 0, settings_r_input, settings_r_plus, settings_r_minus);
		AddNumber("Blue", settings_rgba->B, 0, settings_r_input, settings_r_plus, settings_r_minus);
		AddNumber("Opacity", settings_rgba->A, 0, settings_r_input, settings_r_plus, settings_r_minus);

		switch (menu::currentop)
		{
		case 1: settings_rgba2 = &settings_rgba->R; break;
		case 2: settings_rgba2 = &settings_rgba->G; break;
		case 3: settings_rgba2 = &settings_rgba->B; break;
		case 4: settings_rgba2 = &settings_rgba->A; break;
		}

		if (settings_r_input) {
			int tempHash = NumberKeyboard();
			if (!(tempHash >= 0 && tempHash <= 255)) PrintError_InvalidInput();
			else *settings_rgba2 = tempHash;
			return;
		}

		if (settings_r_plus) {
			if (*settings_rgba2 < 255) (*settings_rgba2)++;
			else *settings_rgba2 = 0;
			return;
		}
		else if (settings_r_minus) {
			if (*settings_rgba2 > 0) (*settings_rgba2)--;
			else *settings_rgba2 = 255;
			return;
		}
	}

	void AddsettingsfonOption(char* text, int font_index = -1, int& feature = inull)
	{
		bool bit_changefont = 0, bit_setfeature = 0;
		if (font_index == -1) AddOption(text, bit_setfeature, nullFunc, SUB::SETTINGS_FONTS2);
		else AddOption(text, bit_changefont);

		if (bit_setfeature) settings_font = &feature;
		else if (bit_changefont) * settings_font = font_index;
	}

	void SettingsFonts()
	{
		AddTitle("Menu Fonts");
		AddsettingsfonOption("Title", -1, font_title);
		AddsettingsfonOption("Options", -1, font_options);
		AddsettingsfonOption("Selected Option", -1, font_selection);
		AddsettingsfonOption("Option Breaks", -1, font_breaks);
	}

	void SettingsFonts2()
	{
		bool fonts2_input = 0;

		AddTitle("Set Font");
		AddsettingsfonOption("Normalish", 0);
		AddsettingsfonOption("Impactish", 4);
		AddsettingsfonOption("Italic", 1);
		AddsettingsfonOption("Pricedown", 7);
		AddsettingsfonOption("Caps", 2);
		AddOption("Input Index", fonts2_input);

		if (fonts2_input) {
			int tempInt = NumberKeyboard();
			*settings_font = tempInt;
			return;
		}
	}
}


void menu::loops()
{ 
	/*	Make calls to functions that you want looped over here, e.g. ambient lights, whale guns, explosions, checks, flying deers, etc.
		Can also be used for (bool) options that are to be executed from many parts of the script. */

	if (loop_massacre_mode) set_massacre_mode(); // Massacre mode

	if (loop_RainbowBoxes && GET_GAME_TIMER() >= livetimer)
	{	titlebox.R = RandomRGB(); titlebox.G = RandomRGB(); titlebox.B = RandomRGB();
		BG.R = RandomRGB(); BG.G = RandomRGB(); BG.B = RandomRGB();
		selectedtext.R = RandomRGB(); selectedtext.G = RandomRGB(); selectedtext.B = RandomRGB();
	}

	if (loop_player_invincibility)
	{
		if (!GET_PLAYER_INVINCIBLE(PLAYER_ID()))
			SET_PLAYER_INVINCIBLE(PLAYER_ID(), 1);
	}

	if (loop_player_neverwanted)
	{
		CLEAR_PLAYER_WANTED_LEVEL(PLAYER_ID());
	}

}

void menu::submenu_switch()
{ // Make calls to submenus over here.

	switch (currentsub)
	{
	case SUB::MAINMENU:					sub::MainMenu(); break;
	case SUB::SETTINGS:					sub::Settings(); break;
	case SUB::SETTINGS_COLOURS:			sub::SettingsColours(); break;
	case SUB::SETTINGS_COLOURS2:		sub::SettingsColours2(); break;
	case SUB::SETTINGS_FONTS:			sub::SettingsFonts(); break;
	case SUB::SETTINGS_FONTS2:			sub::SettingsFonts2(); break;
	case SUB::SAMPLE:					sub::SampleSelf(); break;
	case SUB::SAMPLEWORLD:				sub::SampleWorld(); break;
	case SUB::SAMPLETELEPORT:			sub::SampleTeleport(); break;
//	case SUB::NAME						sub::name(); break;
	}
}

void main()
{
	srand(GetTickCount64());
	for(;;)
	{
		menu::base();
		menu::loops();
		menu::sub_handler();
		scriptWait(0);
	}
}



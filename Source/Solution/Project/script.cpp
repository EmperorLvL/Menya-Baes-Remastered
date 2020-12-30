#include "script.h"

namespace
{
	// Declare/Initialise global variables here.
	int sampleHour = 0;
	float currentTimescale = 1.0f;
	int testInt = 5;

	// Booleans for loops go here:
	bool playerInvincibility = 0, playerInvisible = 0;
}

namespace sub {
	// Define submenus here.

	void MainMenu()
	{
		AddTitle("MAIN MENU");
		AddOption("Sample Self", null, nullFunc, SUB::SAMPLE);
		AddOption("Sample Teleport", null, nullFunc, SUB::SAMPLETELEPORT);
		AddOption("Sample World", null, nullFunc, SUB::SAMPLEWORLD);
		AddOption("Settings", null, nullFunc, SUB::SETTINGS);

		if (menuOpened)
		{
			Game::Print::PrintStringBottomCentre("Menya Base by MAFINS."); // Your opening message goes here.
			menuOpened = false;
		}
	}

	void SampleSelf()
	{
		AddTitle("SAMPLE");
		AddToggle("Invincibility", playerInvincibility, [] { PLAYER::SET_PLAYER_INVINCIBLE(PLAYER::PLAYER_ID(), playerInvincibility); });
		AddToggle("Invisibility", playerInvisible, [] { ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), !playerInvisible, 0); });
		AddNumber("Options", testInt, 0, 255);
		AddBreak("Options");
		for (int i = 0; i <= testInt; i++)
		{
			AddOption("Option " + std::to_string(i));
		}
	}

	void SampleTeleport()
	{
		AddTitle("TELEPORT");
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
		sampleHour = CLOCK::GET_CLOCK_HOURS();
		AddTitle("WORLD");
		AddNumber("Hour", sampleHour, 0, 23, 1, [] { CLOCK::SET_CLOCK_TIME(sampleHour, 0, 0); });
		AddNumber("Time Scale", currentTimescale, 0.0f, 1.0f, 0.1f, [] { MISC::SET_TIME_SCALE(currentTimescale); });
	}

	void Settings()
	{
		AddTitle("MENU SETTINGS");
		AddOption("Menu Colours", null, nullFunc, SUB::SETTINGS_COLOURS);
		AddNumber("Menu X", menuPos.x, 0.0f, 0.8f, 0.01f);
		AddNumber("Menu Y", menuPos.y, 0.0f, 0.9f, 0.01f);
	}

	void AddsettingscolOption(char* text, RGBA& feature)
	{
		AddOption(text, null, nullFunc, SUB::SETTINGS_COLOURS2);
		if (menu::printingOp == menu::currentOp) settings_rgba = &feature;
	}

	void SettingsColours()
	{
		AddTitle("COLORS");
		AddsettingscolOption("Title Box", titlebox);
	}

	void SettingsColours2()
	{
		AddTitle("TITLE BOX");
		AddNumber("Red", settings_rgba->R, 0, 255);
		AddNumber("Green", settings_rgba->G, 0, 255);
		AddNumber("Blue", settings_rgba->B, 0, 255);
		AddNumber("Opacity", settings_rgba->A, 0, 255);
	}
}


void menu::loops()
{ 
	/*	Make calls to functions that you want looped over here, e.g. ambient lights, whale guns, explosions, checks, flying deers, etc.
		Can also be used for (bool) options that are to be executed from many parts of the script. */
	if (playerInvincibility)
	{
		if (!PLAYER::GET_PLAYER_INVINCIBLE(PLAYER::PLAYER_ID()))
			PLAYER::SET_PLAYER_INVINCIBLE(PLAYER::PLAYER_ID(), playerInvincibility);
	}
}

void menu::submenu_switch()
{ // Make calls to submenus over here.

	switch (currentSub)
	{
	case SUB::MAINMENU:					sub::MainMenu(); break;
	case SUB::SETTINGS:					sub::Settings(); break;
	case SUB::SETTINGS_COLOURS:			sub::SettingsColours(); break;
	case SUB::SETTINGS_COLOURS2:		sub::SettingsColours2(); break;
	case SUB::SAMPLE:					sub::SampleSelf(); break;
	case SUB::SAMPLEWORLD:				sub::SampleWorld(); break;
	case SUB::SAMPLETELEPORT:			sub::SampleTeleport(); break;
	}
}

void main()
{
	srand(static_cast<unsigned int>(GetTickCount64()));
	for(;;)
	{
		menu::base();
		menu::loops();
		menu::sub_handler();
		scriptWait(0);
	}
}



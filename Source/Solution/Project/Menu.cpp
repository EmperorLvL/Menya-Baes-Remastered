#include "script.h"

RGBA* settings_rgba;
RGBA titlebox = { 102, 0, 204, 255 };
RGBA BG = { 20, 20, 20, 200 };
RGBA titletext = { 255, 255, 255, 255 };
RGBA optiontext = { 255, 255, 255, 255 };
RGBA optioncount = { 255, 255, 255, 255 };
RGBA selectedtext = { 255, 255, 255, 255 };
RGBA optionbreaks = { 255, 255, 255, 240 };
RGBA selectionhi = { 255, 255, 255, 140 };

float OptionY;
Vector2 menuPos;

int* settings_font;
int font_title = 7, font_options = 4, font_selection = 4, font_breaks = 1;

int screen_res_x, screen_res_y;

bool controllerinput_bool = 1;
bool menujustopened = 1;

unsigned __int16 menu::currentsub = 0; 
unsigned __int16 menu::currentop = 0; 
unsigned __int16 menu::currentop_w_breaks = 0; 
unsigned __int16 menu::totalop = 0; 
unsigned __int16 menu::printingop = 0; 
unsigned __int16 menu::breakcount = 0; 
unsigned __int16 menu::totalbreaks = 0; 
unsigned __int8 menu::breakscroll = 0; 
__int16 menu::currentsub_ar_index = 0; 

int menu::currentsub_ar[100] = {}; 
int menu::currentop_ar[100] = {}; 
int menu::SetSub_delayed = 0; 

int menu::livetimer = 0;
bool menu::bit_centre_title = 1, 
menu::bit_centre_options = 0, 
menu::bit_centre_breaks = 1;

void menu::DisableControls()
{
	HIDE_HELP_TEXT_THIS_FRAME();
	SET_CINEMATIC_BUTTON_ACTIVE(1);
	DISABLE_CONTROL_ACTION(0, INPUT_NEXT_CAMERA, controllerinput_bool);
	DISABLE_CONTROL_ACTION(0, INPUT_VEH_SELECT_NEXT_WEAPON, controllerinput_bool);
	DISABLE_CONTROL_ACTION(0, INPUT_VEH_CIN_CAM, controllerinput_bool);
	SET_INPUT_EXCLUSIVE(2, INPUT_FRONTEND_X);
	SET_INPUT_EXCLUSIVE(2, INPUT_FRONTEND_ACCEPT);
	SET_INPUT_EXCLUSIVE(2, INPUT_FRONTEND_CANCEL);
	DISABLE_CONTROL_ACTION(0, INPUT_HUD_SPECIAL, controllerinput_bool);
	SET_INPUT_EXCLUSIVE(2, INPUT_FRONTEND_DOWN);
	SET_INPUT_EXCLUSIVE(2, INPUT_FRONTEND_UP);
	DISABLE_CONTROL_ACTION(2, INPUT_FRONTEND_ACCEPT, controllerinput_bool);
	DISABLE_CONTROL_ACTION(2, INPUT_FRONTEND_CANCEL, controllerinput_bool);
	DISABLE_CONTROL_ACTION(2, INPUT_FRONTEND_LEFT, controllerinput_bool);
	DISABLE_CONTROL_ACTION(2, INPUT_FRONTEND_RIGHT, controllerinput_bool);
	DISABLE_CONTROL_ACTION(2, INPUT_FRONTEND_DOWN, controllerinput_bool);
	DISABLE_CONTROL_ACTION(2, INPUT_FRONTEND_UP, controllerinput_bool);
	DISABLE_CONTROL_ACTION(2, INPUT_FRONTEND_RDOWN, controllerinput_bool);
	DISABLE_CONTROL_ACTION(2, INPUT_FRONTEND_ACCEPT, controllerinput_bool);
	HIDE_HUD_COMPONENT_THIS_FRAME(10);
	HIDE_HUD_COMPONENT_THIS_FRAME(6);
	HIDE_HUD_COMPONENT_THIS_FRAME(7);
	HIDE_HUD_COMPONENT_THIS_FRAME(9);
	HIDE_HUD_COMPONENT_THIS_FRAME(8);
	SET_INPUT_EXCLUSIVE(2, INPUT_FRONTEND_LEFT);
	SET_INPUT_EXCLUSIVE(2, INPUT_FRONTEND_RIGHT);
	DISABLE_CONTROL_ACTION(0, INPUT_SELECT_WEAPON, controllerinput_bool);
	DISABLE_CONTROL_ACTION(0, INPUT_SELECT_WEAPON_UNARMED, controllerinput_bool);
	DISABLE_CONTROL_ACTION(0, INPUT_SELECT_WEAPON_MELEE, controllerinput_bool);
	DISABLE_CONTROL_ACTION(0, INPUT_SELECT_WEAPON_HANDGUN, controllerinput_bool);
	DISABLE_CONTROL_ACTION(0, INPUT_SELECT_WEAPON_SHOTGUN, controllerinput_bool);
	DISABLE_CONTROL_ACTION(0, INPUT_SELECT_WEAPON_SMG, controllerinput_bool);
	DISABLE_CONTROL_ACTION(0, INPUT_SELECT_WEAPON_AUTO_RIFLE, controllerinput_bool);
	DISABLE_CONTROL_ACTION(0, INPUT_SELECT_WEAPON_SNIPER, controllerinput_bool);
	DISABLE_CONTROL_ACTION(0, INPUT_SELECT_WEAPON_HEAVY, controllerinput_bool);
	DISABLE_CONTROL_ACTION(0, INPUT_SELECT_WEAPON_SPECIAL, controllerinput_bool);
	DISABLE_CONTROL_ACTION(0, INPUT_WEAPON_WHEEL_NEXT, controllerinput_bool);
	DISABLE_CONTROL_ACTION(0, INPUT_WEAPON_WHEEL_PREV, controllerinput_bool);
	DISABLE_CONTROL_ACTION(0, INPUT_WEAPON_SPECIAL_TWO, controllerinput_bool);
	DISABLE_CONTROL_ACTION(0, INPUT_DIVE, controllerinput_bool);
	DISABLE_CONTROL_ACTION(0, INPUT_MELEE_ATTACK_LIGHT, controllerinput_bool);
	DISABLE_CONTROL_ACTION(0, INPUT_MELEE_ATTACK_HEAVY, controllerinput_bool);
	DISABLE_CONTROL_ACTION(0, INPUT_MELEE_BLOCK, controllerinput_bool);
	DISABLE_CONTROL_ACTION(0, INPUT_ARREST, controllerinput_bool);
	DISABLE_CONTROL_ACTION(0, INPUT_VEH_HEADLIGHT, controllerinput_bool);
	DISABLE_CONTROL_ACTION(0, INPUT_VEH_RADIO_WHEEL, controllerinput_bool);
	DISABLE_CONTROL_ACTION(0, INPUT_CONTEXT, controllerinput_bool);
	DISABLE_CONTROL_ACTION(0, INPUT_RELOAD, controllerinput_bool);
	DISABLE_CONTROL_ACTION(0, INPUT_DIVE, controllerinput_bool);
	DISABLE_CONTROL_ACTION(0, INPUT_VEH_CIN_CAM, controllerinput_bool);
	DISABLE_CONTROL_ACTION(0, INPUT_JUMP, controllerinput_bool);
	DISABLE_CONTROL_ACTION(0, INPUT_VEH_SELECT_NEXT_WEAPON, controllerinput_bool);
	DISABLE_CONTROL_ACTION(0, INPUT_VEH_FLY_SELECT_NEXT_WEAPON, controllerinput_bool);
	DISABLE_CONTROL_ACTION(0, INPUT_SELECT_CHARACTER_FRANKLIN, controllerinput_bool);
	DISABLE_CONTROL_ACTION(0, INPUT_SELECT_CHARACTER_MICHAEL, controllerinput_bool);
	DISABLE_CONTROL_ACTION(0, INPUT_SELECT_CHARACTER_TREVOR, controllerinput_bool);
	DISABLE_CONTROL_ACTION(0, INPUT_SELECT_CHARACTER_MULTIPLAYER, controllerinput_bool);
	DISABLE_CONTROL_ACTION(0, INPUT_CHARACTER_WHEEL, controllerinput_bool);
}

void menu::base()
{
	GET_SCREEN_RESOLUTION(&screen_res_x, &screen_res_y); // Get screen res
	if (menu::currentsub != SUB::CLOSED)
	{
		if (!HAS_STREAMED_TEXTURE_DICT_LOADED("CommonMenu")) { REQUEST_STREAMED_TEXTURE_DICT("CommonMenu", 0); }
		background();
		optionhi();
		MenuPressTimer::Update();
	}
}

void menu::background()
{
	float temp;
	if (totalop > 14) temp = 14; else temp = (float)totalop; // Calculate last option number to draw rect

	// Calculate Y Coord
	float bg_Y = ((temp * 0.035f) / 2.0f) + 0.159f;
	float bg_length = temp * 0.035f;

	// Draw titlebox
	DRAW_RECT(0.16f + menuPos.x, 0.1175f + menuPos.y, 0.20f, 0.083f, titlebox.R, titlebox.G, titlebox.B, titlebox.A);

	// Draw background
	DRAW_RECT(0.16f + menuPos.x, bg_Y + menuPos.y, 0.20f, bg_length, BG.R, BG.G, BG.B, BG.A);

	// Draw scroller indicator rect
	if (totalop > 14) temp = 14.0f; else temp = (float)totalop;
	float scr_rect_Y = ((temp + 1.0f) * 0.035f) + 0.1415f;
	DRAW_RECT(0.16f + menuPos.x, scr_rect_Y + menuPos.y, 0.20f, 0.0345f, titlebox.R, titlebox.G, titlebox.B, titlebox.A);

	// Draw thin line over scroller indicator rect
	if (totalop < 14) DRAW_RECT(0.16f + menuPos.x, (float)(totalop) * 0.035f + 0.16f + menuPos.y, 0.20f, 0.0022f, 255, 255, 255, 255);
	else DRAW_RECT(0.16f + menuPos.x, 14.0f * 0.035f + 0.16f + menuPos.y, 0.20f, 0.0011f, 255, 255, 255, 255);

	// Draw scroller indicator
	if ((totalop > 14))
	{
		Vector3 texture_res = GET_TEXTURE_RESOLUTION("CommonMenu", "shop_arrows_upANDdown");
		texture_res.x /= (1280 * 2);
		texture_res.y /= (720 * 2);

		temp = ((14 + 1.0f) * 0.035f) + 0.1413f; //0.1259f;
		DRAW_SPRITE("CommonMenu", "shop_arrows_upANDdown", 0.16f + menuPos.x, temp + menuPos.y, texture_res.x, texture_res.y, 0.0f, optioncount.R, optioncount.G, optioncount.B, 255);
	}

	// Draw option count
	temp = scr_rect_Y - 0.0124f;
	Game::Print::setupdraw();
	SET_TEXT_FONT(0);
	SET_TEXT_SCALE(0.0f, 0.26f);
	SET_TEXT_COLOUR(optioncount.R, optioncount.G, optioncount.B, optioncount.A);

	BEGIN_TEXT_COMMAND_DISPLAY_TEXT("CM_ITEM_COUNT");
	ADD_TEXT_COMPONENT_INTEGER(currentop); // ! currentop_w_breaks
	ADD_TEXT_COMPONENT_INTEGER(totalop); // ! totalop - totalbreaks
	END_TEXT_COMMAND_DISPLAY_TEXT(0.2205f + menuPos.x, temp + menuPos.y);
}

void menu::optionhi()
{
	float Y_coord;
	if (currentop > 14) Y_coord = 14.0f; else Y_coord = (float)currentop;

	Y_coord = (Y_coord * 0.035f) + 0.1415f;
	DRAW_RECT(0.16f + menuPos.x, Y_coord + menuPos.y, 0.20f, 0.035f, selectionhi.R, selectionhi.G, selectionhi.B, selectionhi.A);
}

bool menu::isBinds()
{
	// Open menu - RB + DPAD Right / F8
	return ((IS_DISABLED_CONTROL_JUST_PRESSED(2, INPUT_FRONTEND_RB) && IS_DISABLED_CONTROL_JUST_PRESSED(2, INPUT_CELLPHONE_RIGHT)) || IsKeyJustUp(VK_F8));
}

void menu::while_closed()
{
	if (isBinds())
	{
		Game::Sound::PlaySoundFrontend_default("SELECT");
		currentsub = 1;
		currentsub_ar_index = 0;
		currentop = 1;
	}
}

void menu::while_opened()
{
	totalop = printingop; printingop = 0;
	totalbreaks = breakcount; breakcount = 0; breakscroll = 0;

	if (IS_PAUSE_MENU_ACTIVE()) SetSub_closed();

	DISPLAY_AMMO_THIS_FRAME(0);
	DISPLAY_CASH(0);
	SET_RADAR_ZOOM(0);
	SET_MOBILE_PHONE_POSITION(0, 0, 0);

	DisableControls();

	// Scroll up
	if (MenuPressTimer::IsButtonHeldOrTapped(MenuPressTimer::Button::Up))
	{
		if (currentop <= 1)
			Bottom();
		else
			Up();
	}

	// Scroll down
	if (MenuPressTimer::IsButtonHeldOrTapped(MenuPressTimer::Button::Down))
	{
		if (currentop >= totalop)
			Top();
		else
			Down();
	}

	// B press
	if (MenuPressTimer::IsButtonTapped(MenuPressTimer::Button::Back))
	{
		if (currentsub == SUB::MAINMENU)
			SetSub_closed();
		else
			SetSub_previous();
	}

	// Binds press
	if (isBinds())
	{
		SetSub_closed();
	}
}

void menu::Up()
{
	currentop--; currentop_w_breaks--;
	Game::Sound::PlaySoundFrontend_default("NAV_UP_DOWN");
	breakscroll = 1;
}

void menu::Down()
{
	currentop++; currentop_w_breaks++;
	Game::Sound::PlaySoundFrontend_default("NAV_UP_DOWN");
	breakscroll = 2;
}

void menu::Bottom()
{
	currentop = totalop; currentop_w_breaks = totalop;
	Game::Sound::PlaySoundFrontend_default("NAV_UP_DOWN");
	breakscroll = 3;
}

void menu::Top()
{
	currentop = 1; currentop_w_breaks = 1;
	Game::Sound::PlaySoundFrontend_default("NAV_UP_DOWN");
	breakscroll = 4;
}

void menu::SetSub_previous()
{
	currentsub = currentsub_ar[currentsub_ar_index]; // Get previous submenu from array and set as current submenu
	currentop = currentop_ar[currentsub_ar_index]; // Get last selected option from array and set as current selected option
	currentsub_ar_index--; // Decrement array index by 1
	printingop = 0; // Reset option print variable
	Game::Sound::PlaySoundFrontend_default("BACK"); // Play sound
}

void menu::SetSub_new(int sub_index)
{
	currentsub_ar_index++; // Increment array index
	currentsub_ar[currentsub_ar_index] = currentsub; // Store current submenu index in array
	currentsub = sub_index; // Set new submenu as current submenu (Static_1)

	currentop_ar[currentsub_ar_index] = currentop; // Store currently selected option in array
	currentop = 1; currentop_w_breaks = 1; // Set new selected option as first option in submenu

	printingop = 0; // Reset currently printing option var
}

void menu::SetSub_closed()
{
	ENABLE_ALL_CONTROL_ACTIONS(2);
	Game::Sound::PlaySoundFrontend_default("BACK");
	currentsub = SUB::CLOSED;
}

void menu::sub_handler()
{
	if (currentsub == SUB::CLOSED) {
		while_closed();
	}

	else {
		submenu_switch();
		if (SetSub_delayed != NULL)
		{
			SetSub_new(SetSub_delayed);
			SetSub_delayed = NULL;
		}

		while_opened();

		if (GET_GAME_TIMER() >= livetimer) livetimer = GET_GAME_TIMER() + 1800; // 1.8s delay for rainbow related loops
	}
}

bool IsOptionPressed()
{
	if (MenuPressTimer::IsButtonTapped(MenuPressTimer::Button::Accept))
	{
		Game::Sound::PlaySoundFrontend_default("SELECT");
		return true;
	}
	return false;
}

bool IsOptionRPressed()
{
	if (MenuPressTimer::IsButtonHeldOrTapped(MenuPressTimer::Button::Right))
	{
		Game::Sound::PlaySoundFrontend_default("NAV_LEFT_RIGHT");
		return true;
	}
	else return false;
}

bool IsOptionLPressed()
{
	if (MenuPressTimer::IsButtonHeldOrTapped(MenuPressTimer::Button::Left))
	{
		Game::Sound::PlaySoundFrontend_default("NAV_LEFT_RIGHT");
		return true;
	}
	else return false;
}

int inull;
bool null;
void nullFunc() { return; }

void AddTitle(std::string title)
{
	Game::Print::setupdraw();
	SET_TEXT_FONT(font_title);
	SET_TEXT_COLOUR(titletext.R, titletext.G, titletext.B, titletext.A);

	if (menu::bit_centre_title)
	{
		SET_TEXT_CENTRE(1);
		OptionY = 0.16f + menuPos.x; // X coord
	}
	else
		OptionY = 0.066f + menuPos.x; // X coord

	if (title.length() < 14)
	{
		SET_TEXT_SCALE(0.75f, 0.75f);
		Game::Print::drawstring(title, OptionY, 0.1f + menuPos.y);
	}
	else
		Game::Print::drawstring(title, OptionY, 0.13f + menuPos.y);
}

void AddOption(std::string option, bool& option_code_bool, void(&Func)(), int submenu_index, bool show_arrow)
{
	std::string tempStr;
	if (font_options == 2 || font_options == 7) tempStr = "  ------"; // Font unsafe
	else tempStr = "  ~b~>"; // Font safe

	if (menu::printingop + 1 == menu::currentop && (font_selection == 2 || font_selection == 7)) tempStr = "  ------"; // Font unsafe
	else tempStr = "  ~b~>"; // Font safe

	menu::printingop++;

	OptionY = 0.0f;
	if (menu::currentop <= 14)
	{
		if (menu::printingop > 14) return;
		else OptionY = ((float)(menu::printingop) * 0.035f) + 0.125f;
	}
	else
	{
		if (menu::printingop < (menu::currentop - 13) || menu::printingop > menu::currentop) return;
		else OptionY = ((float)(menu::printingop - (menu::currentop - 14)) * 0.035f) + 0.125f;
	}

	Game::Print::setupdraw();
	SET_TEXT_FONT(font_options);
	SET_TEXT_COLOUR(optiontext.R, optiontext.G, optiontext.B, optiontext.A);
	if (menu::printingop == menu::currentop)
	{
		SET_TEXT_FONT(font_selection);
		SET_TEXT_COLOUR(selectedtext.R, selectedtext.G, selectedtext.B, selectedtext.A);
		if (IsOptionPressed())
		{
			/*if (&option_code_bool != &null)*/ option_code_bool = true;
			Func();
			if (submenu_index != -1) menu::SetSub_delayed = submenu_index;
		}
	}

	if (show_arrow || submenu_index != -1) option = option + tempStr;
	if (menu::bit_centre_options)
	{
		SET_TEXT_CENTRE(1);
		Game::Print::drawstring(option, 0.16f + menuPos.x, OptionY + menuPos.y);
	}
	else Game::Print::drawstring(option, 0.066f + menuPos.x, OptionY + menuPos.y);
}

void OptionStatus(int status)
{
	if (OptionY < 0.6325f && OptionY > 0.1425f)
	{
		std::string tempStr;
		SET_TEXT_FONT(4);
		SET_TEXT_SCALE(0.34f, 0.34f);
		SET_TEXT_CENTRE(1);

		if (status == 0) {
			SET_TEXT_COLOUR(255, 102, 102, 250); //RED
			tempStr = "OFF";
		}
		else if (status == 1) {
			SET_TEXT_COLOUR(102, 255, 102, 250); //GREEN
			tempStr = "ON";
		}
		else {
			SET_TEXT_COLOUR(255, 255, 102, 250); //YELLOW
			tempStr = "??";
		}

		Game::Print::drawstring(tempStr, 0.233f + menuPos.x, OptionY + menuPos.y);
	}
}

void AddToggle(std::string option, bool& loop_variable, bool& extra_option_code_ON, bool& extra_option_code_OFF)
{
	null = 0;
	AddOption(option, null);

	if (null) {
		loop_variable = !loop_variable;
		if (loop_variable != 0) extra_option_code_ON = true;
		else extra_option_code_OFF = true;
	}

	OptionStatus((int)loop_variable); // Display ON/OFF
}

void AddLocal(std::string option, Void condition, bool& option_code_ON, bool& option_code_OFF)
{
	null = 0;
	AddOption(option, null);
	if (null)
	{
		if (condition == 0) option_code_ON = true; else option_code_OFF = true;
	}

	if (condition == 0) OptionStatus(0); // Display OFF
	else				OptionStatus(1); // Display ON
}

void AddBreak(std::string text)
{
	menu::printingop++; menu::breakcount++;

	OptionY = 0;

	if (menu::currentop <= 14)
	{
		if (menu::printingop > 14) return;
		else OptionY = ((float)(menu::printingop) * 0.035f) + 0.125f;
	}
	else
	{
		if (menu::printingop < (menu::currentop - 13) || menu::printingop > menu::currentop) return;
		else OptionY = ((float)(menu::printingop - (menu::currentop - 14)) * 0.035f) + 0.125f;
	}

	Game::Print::setupdraw();
	SET_TEXT_FONT(font_breaks);
	SET_TEXT_COLOUR(optionbreaks.R, optionbreaks.G, optionbreaks.B, optionbreaks.A);
	if (menu::printingop == menu::currentop)
	{
		switch (menu::breakscroll)
		{
		case 1: // Up
			if (menu::currentop <= 1) menu::Bottom();
			else menu::Up();
			break;
		case 2: default: // Down
			if (menu::currentop >= menu::totalop) menu::Top();
			else menu::Down();
			break;
		}
	}
	if (menu::bit_centre_breaks)
	{
		SET_TEXT_CENTRE(1);
		Game::Print::drawstring(text, 0.16f + menuPos.x, OptionY + menuPos.y);
	}
	else
	{
		Game::Print::drawstring(text, 0.066f + menuPos.x, OptionY + menuPos.y);
	}

}

void AddNumber(std::string option, float value, __int8 decimal_places, bool& A_PRESS, bool& RIGHT_PRESS, bool& LEFT_PRESS)
{
	null = 0;
	AddOption(option, null);

	if (OptionY < 0.6325 && OptionY > 0.1425)
	{
		SET_TEXT_FONT(0);
		SET_TEXT_SCALE(0.26f, 0.26f);
		SET_TEXT_CENTRE(1);

		Game::Print::drawfloat(value, (DWORD)decimal_places, 0.233f + menuPos.x, OptionY + menuPos.y);
	}

	if (menu::printingop == menu::currentop)
	{
		if (null) A_PRESS = true;
		else if (IsOptionRPressed()) RIGHT_PRESS = true;
		else if (IsOptionLPressed()) LEFT_PRESS = true;
	}
}

void AddTele(std::string option, float X, float Y, float Z, bool& extra_option_code)
{
	null = 0;
	AddOption(option, null);
	if (menu::printingop == menu::currentop)
	{
		if (null)
		{
			if (!IS_PED_IN_ANY_VEHICLE(PLAYER_PED_ID(), true))
			{
				SET_ENTITY_COORDS(PLAYER_PED_ID(), X, Y, Z, 0, 0, 0, 1);
			}
			else
			{
				SET_ENTITY_COORDS(GET_VEHICLE_PED_IS_USING(PLAYER_PED_ID()), X, Y, Z, 0, 0, 0, 1);
			}
			LOAD_ALL_OBJECTS_NOW();
			extra_option_code = true;
		}
	}
}
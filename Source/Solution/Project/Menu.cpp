#include "script.h"

RGBA* settings_rgba;
RGBA titlebox = { 0, 50, 190, 255 };
RGBA BG = { 0, 0, 0, 255 };
RGBA optiontext = { 255, 255, 255, 255 };
RGBA selectedtext = { 0, 0, 0, 255 };
RGBA optionbreaks = { 255, 255, 255, 240 };
RGBA selectionhi = { 255, 255, 255, 255 };

float OptionY;
Vector2 menuPos = { 0.03f, 0.04f };
bool menuOpened = true;

int menu::currentSub = 0; 
int menu::currentOp = 0;
int menu::currentOpwBreaks = 0;
int menu::totalOp = 0;
int menu::printingOp = 0;
int menu::breakCount = 0;
int menu::totalBreaks = 0;
int menu::breakScroll = 0;
int menu::currentSubArIndex = 0;

int menu::currentSubAr[100] = {}; 
int menu::currentOpAr[100] = {}; 
int menu::setSubDelayed = 0; 

int menu::liveTimer = 0;

void menu::DisableControls()
{
	if (CAM::IS_GAMEPLAY_HINT_ACTIVE()) CAM::STOP_GAMEPLAY_HINT(false);
	HUD::HIDE_HELP_TEXT_THIS_FRAME();
	CAM::SET_CINEMATIC_BUTTON_ACTIVE(1);
	PAD::DISABLE_CONTROL_ACTION(0, INPUT_NEXT_CAMERA, false);
	PAD::DISABLE_CONTROL_ACTION(0, INPUT_VEH_SELECT_NEXT_WEAPON, false);
	PAD::DISABLE_CONTROL_ACTION(0, INPUT_VEH_CIN_CAM, false);
	PAD::SET_INPUT_EXCLUSIVE(2, INPUT_FRONTEND_X);
	PAD::SET_INPUT_EXCLUSIVE(2, INPUT_FRONTEND_ACCEPT);
	PAD::SET_INPUT_EXCLUSIVE(2, INPUT_FRONTEND_CANCEL);
	PAD::DISABLE_CONTROL_ACTION(0, INPUT_HUD_SPECIAL, false);
	PAD::SET_INPUT_EXCLUSIVE(2, INPUT_FRONTEND_DOWN);
	PAD::SET_INPUT_EXCLUSIVE(2, INPUT_FRONTEND_UP);
	PAD::DISABLE_CONTROL_ACTION(2, INPUT_FRONTEND_ACCEPT, false);
	PAD::DISABLE_CONTROL_ACTION(2, INPUT_FRONTEND_CANCEL, false);
	PAD::DISABLE_CONTROL_ACTION(2, INPUT_FRONTEND_LEFT, false);
	PAD::DISABLE_CONTROL_ACTION(2, INPUT_FRONTEND_RIGHT, false);
	PAD::DISABLE_CONTROL_ACTION(2, INPUT_FRONTEND_DOWN, false);
	PAD::DISABLE_CONTROL_ACTION(2, INPUT_FRONTEND_UP, false);
	PAD::DISABLE_CONTROL_ACTION(2, INPUT_FRONTEND_RDOWN, false);
	PAD::DISABLE_CONTROL_ACTION(2, INPUT_FRONTEND_ACCEPT, false);
	HUD::HIDE_HUD_COMPONENT_THIS_FRAME(10);
	HUD::HIDE_HUD_COMPONENT_THIS_FRAME(6);
	HUD::HIDE_HUD_COMPONENT_THIS_FRAME(7);
	HUD::HIDE_HUD_COMPONENT_THIS_FRAME(9);
	HUD::HIDE_HUD_COMPONENT_THIS_FRAME(8);
	PAD::SET_INPUT_EXCLUSIVE(2, INPUT_FRONTEND_LEFT);
	PAD::SET_INPUT_EXCLUSIVE(2, INPUT_FRONTEND_RIGHT);
	PAD::DISABLE_CONTROL_ACTION(0, INPUT_SELECT_WEAPON, false);
	PAD::DISABLE_CONTROL_ACTION(0, INPUT_SELECT_WEAPON_UNARMED, false);
	PAD::DISABLE_CONTROL_ACTION(0, INPUT_SELECT_WEAPON_MELEE, false);
	PAD::DISABLE_CONTROL_ACTION(0, INPUT_SELECT_WEAPON_HANDGUN, false);
	PAD::DISABLE_CONTROL_ACTION(0, INPUT_SELECT_WEAPON_SHOTGUN, false);
	PAD::DISABLE_CONTROL_ACTION(0, INPUT_SELECT_WEAPON_SMG, false);
	PAD::DISABLE_CONTROL_ACTION(0, INPUT_SELECT_WEAPON_AUTO_RIFLE, false);
	PAD::DISABLE_CONTROL_ACTION(0, INPUT_SELECT_WEAPON_SNIPER, false);
	PAD::DISABLE_CONTROL_ACTION(0, INPUT_SELECT_WEAPON_HEAVY, false);
	PAD::DISABLE_CONTROL_ACTION(0, INPUT_SELECT_WEAPON_SPECIAL, false);
	PAD::DISABLE_CONTROL_ACTION(0, INPUT_WEAPON_WHEEL_NEXT, false);
	PAD::DISABLE_CONTROL_ACTION(0, INPUT_WEAPON_WHEEL_PREV, false);
	PAD::DISABLE_CONTROL_ACTION(0, INPUT_WEAPON_SPECIAL_TWO, false);
	PAD::DISABLE_CONTROL_ACTION(0, INPUT_DIVE, false);
	PAD::DISABLE_CONTROL_ACTION(0, INPUT_MELEE_ATTACK_LIGHT, false);
	PAD::DISABLE_CONTROL_ACTION(0, INPUT_MELEE_ATTACK_HEAVY, false);
	PAD::DISABLE_CONTROL_ACTION(0, INPUT_MELEE_BLOCK, false);
	PAD::DISABLE_CONTROL_ACTION(0, INPUT_ARREST, false);
	PAD::DISABLE_CONTROL_ACTION(0, INPUT_VEH_HEADLIGHT, false);
	PAD::DISABLE_CONTROL_ACTION(0, INPUT_VEH_RADIO_WHEEL, false);
	PAD::DISABLE_CONTROL_ACTION(0, INPUT_CONTEXT, false);
	PAD::DISABLE_CONTROL_ACTION(0, INPUT_RELOAD, false);
	PAD::DISABLE_CONTROL_ACTION(0, INPUT_DIVE, false);
	PAD::DISABLE_CONTROL_ACTION(0, INPUT_VEH_CIN_CAM, false);
	PAD::DISABLE_CONTROL_ACTION(0, INPUT_JUMP, false);
	PAD::DISABLE_CONTROL_ACTION(0, INPUT_VEH_SELECT_NEXT_WEAPON, false);
	PAD::DISABLE_CONTROL_ACTION(0, INPUT_VEH_FLY_SELECT_NEXT_WEAPON, false);
	PAD::DISABLE_CONTROL_ACTION(0, INPUT_SELECT_CHARACTER_FRANKLIN, false);
	PAD::DISABLE_CONTROL_ACTION(0, INPUT_SELECT_CHARACTER_MICHAEL, false);
	PAD::DISABLE_CONTROL_ACTION(0, INPUT_SELECT_CHARACTER_TREVOR, false);
	PAD::DISABLE_CONTROL_ACTION(0, INPUT_SELECT_CHARACTER_MULTIPLAYER, false);
	PAD::DISABLE_CONTROL_ACTION(0, INPUT_CHARACTER_WHEEL, false);
}

void menu::base()
{
	if (menu::currentSub != SUB::CLOSED)
	{
		if (!GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED("commonmenu")) { GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT("commonmenu", 0); }
		if (!GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED("timerbar_sr")) { GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT("timerbar_sr", 0); }
		background();
		optionhi();
		MenuPressTimer::Update();
	}
}

void menu::background()
{
	float temp;
	if (totalOp > 14) temp = 14; else temp = static_cast<float>(totalOp); // Calculate last option number to draw rect

	// Calculate Y Coord
	float bgY = ((temp * 0.035f) / 2.0f) + 0.104f;
	float bgLength = temp * 0.035f;

	// Draw titlebox
	GRAPHICS::DRAW_RECT(0.1f + menuPos.x, 0.0375f + menuPos.y, 0.205f, 0.083f, titlebox.R, titlebox.G, titlebox.B, titlebox.A, 0);
	Game::Print::setupdraw();
	HUD::SET_TEXT_CENTRE(1);
	HUD::SET_TEXT_FONT(7);
	HUD::SET_TEXT_SCALE(0.75f, 0.75f);
	HUD::SET_TEXT_DROPSHADOW(1, 0, 0, 0, 255);
	Game::Print::drawstring("Menya Baes", menuPos.x + 0.1f, 0.015f + menuPos.y);

	// Draw subtitlebox
	GRAPHICS::DRAW_RECT(0.1f + menuPos.x, 0.0915f + menuPos.y, 0.205f, 0.025f, 0, 0, 0, 255, 0);

	// Draw background
	GRAPHICS::DRAW_SPRITE("commonmenu", "gradient_bgd", 0.1f + menuPos.x, bgY + menuPos.y, 0.205f, bgLength, 0.0f, BG.R, BG.G, BG.B, BG.A, 0);

	// Draw scroller indicator rect
	if (totalOp > 14) temp = 14.0f; else temp = static_cast<float>(totalOp);
	float footerY = ((temp + 1.0f) * 0.035f) + 0.086f;
	GRAPHICS::DRAW_RECT(0.1f + menuPos.x, footerY + menuPos.y, 0.205f, 0.0345f, 0, 0, 0, 255, 0);

	// Draw scroller indicator
	if(currentOp == 1)
		GRAPHICS::DRAW_SPRITE("commonmenu", "arrowright", 0.1f + menuPos.x, footerY + menuPos.y + 0.001f, 0.016f, 0.026f, 90.0f, optiontext.R, optiontext.G, optiontext.B, 255, 0);
	else if (currentOp == totalOp)
		GRAPHICS::DRAW_SPRITE("commonmenu", "arrowright", 0.1f + menuPos.x, footerY + menuPos.y - 0.002f, 0.016f, 0.026f, 270.0f, optiontext.R, optiontext.G, optiontext.B, 255, 0);
	else
		GRAPHICS::DRAW_SPRITE("commonmenu", "shop_arrows_upanddown", 0.1f + menuPos.x, footerY + menuPos.y, 0.023f, 0.038f, 0.0f, optiontext.R, optiontext.G, optiontext.B, 255, 0);

	// Draw option count
	temp = footerY - 0.0124f;
	Game::Print::setupdraw();
	HUD::SET_TEXT_SCALE(0.0f, 0.26f);
	HUD::SET_TEXT_COLOUR(optiontext.R, optiontext.G, optiontext.B, 255);
	Game::Print::drawstring(std::to_string(currentOp) + " / " + std::to_string(totalOp), 0.0015f + menuPos.x, temp + menuPos.y);
}

void menu::optionhi()
{
	float scrollerY;
	if (currentOp > 14) scrollerY = 14.0f; else scrollerY = static_cast<float>(currentOp);

	scrollerY = (scrollerY * 0.035f) + 0.0865f;
	GRAPHICS::DRAW_SPRITE("commonmenu", "gradient_nav", 0.1f + menuPos.x, scrollerY + menuPos.y, 0.205f, 0.035f, 0.0f, selectionhi.R, selectionhi.G, selectionhi.B, selectionhi.A, 0);
}

bool menu::isBinds()
{
	// Open menu - RB + DPAD Right / F8
	return ((PAD::IS_DISABLED_CONTROL_JUST_PRESSED(2, INPUT_FRONTEND_RB) && PAD::IS_DISABLED_CONTROL_JUST_PRESSED(2, INPUT_CELLPHONE_RIGHT)) || IsKeyJustUp(VK_F8));
}

void menu::while_closed()
{
	if (isBinds())
	{
		Game::Sound::PlaySoundFrontend_default("SELECT");
		currentSub = 1;
		currentSubArIndex = 0;
		currentOp = 1;
	}
}

void menu::while_opened()
{
	totalOp = printingOp; printingOp = 0;
	totalBreaks = breakCount; breakCount = 0; breakScroll = 0;

	if (HUD::IS_PAUSE_MENU_ACTIVE()) SetSub_closed();

	DisableControls();

	// Scroll up
	if (MenuPressTimer::IsButtonHeldOrTapped(MenuPressTimer::Button::Up))
	{
		if (currentOp <= 1)
			Bottom();
		else
			Up();
	}

	// Scroll down
	if (MenuPressTimer::IsButtonHeldOrTapped(MenuPressTimer::Button::Down))
	{
		if (currentOp >= totalOp)
			Top();
		else
			Down();
	}

	// B press
	if (MenuPressTimer::IsButtonTapped(MenuPressTimer::Button::Back))
	{
		if (currentSub == SUB::MAINMENU)
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
	currentOp--; currentOpwBreaks--;
	Game::Sound::PlaySoundFrontend_default("NAV_UP_DOWN");
	breakScroll = 1;
}

void menu::Down()
{
	currentOp++; currentOpwBreaks++;
	Game::Sound::PlaySoundFrontend_default("NAV_UP_DOWN");
	breakScroll = 2;
}

void menu::Bottom()
{
	currentOp = totalOp; currentOpwBreaks = totalOp;
	Game::Sound::PlaySoundFrontend_default("NAV_UP_DOWN");
	breakScroll = 3;
}

void menu::Top()
{
	currentOp = 1; currentOpwBreaks = 1;
	Game::Sound::PlaySoundFrontend_default("NAV_UP_DOWN");
	breakScroll = 4;
}

void menu::SetSub_previous()
{
	currentSub = currentSubAr[currentSubArIndex]; // Get previous submenu from array and set as current submenu
	currentOp = currentOpAr[currentSubArIndex]; // Get last selected option from array and set as current selected option
	currentSubArIndex--; // Decrement array index by 1
	printingOp = 0; // Reset option print variable
	Game::Sound::PlaySoundFrontend_default("BACK");
}

void menu::SetSub_new(int sub_index)
{
	currentSubArIndex++; // Increment array index
	currentSubAr[currentSubArIndex] = currentSub; // Store current submenu index in array
	currentSub = sub_index; // Set new submenu as current submenu (Static_1)

	currentOpAr[currentSubArIndex] = currentOp; // Store currently selected option in array
	currentOp = 1; currentOpwBreaks = 1; // Set new selected option as first option in submenu

	printingOp = 0; // Reset currently printing option var
}

void menu::SetSub_closed()
{
	Game::Sound::PlaySoundFrontend_default("BACK");
	currentSub = SUB::CLOSED;
}

void menu::sub_handler()
{
	if (currentSub == SUB::CLOSED) {
		while_closed();
	}

	else {
		submenu_switch();
		if (setSubDelayed != NULL)
		{
			SetSub_new(setSubDelayed);
			setSubDelayed = NULL;
		}

		while_opened();

		if (MISC::GET_GAME_TIMER() >= liveTimer) liveTimer = MISC::GET_GAME_TIMER() + 1800;
	}
}

const char* TextKeyboard()
{
	MISC::DISPLAY_ONSCREEN_KEYBOARD(1, "", "", "", "", "", "", 30);
	while (MISC::UPDATE_ONSCREEN_KEYBOARD() == 0) scriptWait(0);
	if (!MISC::GET_ONSCREEN_KEYBOARD_RESULT())
		return "";
	return MISC::GET_ONSCREEN_KEYBOARD_RESULT();
}

float NumberKeyboard()
{
	MISC::DISPLAY_ONSCREEN_KEYBOARD(1, "", "", "", "", "", "", 20);
	while (MISC::UPDATE_ONSCREEN_KEYBOARD() == 0) scriptWait(0);
	if (!MISC::GET_ONSCREEN_KEYBOARD_RESULT())
		return 0;
	return static_cast<float>(std::atof(MISC::GET_ONSCREEN_KEYBOARD_RESULT()));
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

bool null;
void nullFunc() { return; }

void AddTitle(const std::string& title)
{
	Game::Print::setupdraw();
	Game::Print::drawstring(title, 0.0015f + menuPos.x, 0.08f + menuPos.y);
}

void AddOption(const std::string& option, bool& option_code_bool, std::function<void()> func, int submenu_index, bool show_arrow)
{
	menu::printingOp++;

	OptionY = 0.0f;
	if (menu::currentOp <= 14)
	{
		if (menu::printingOp > 14) return;
		else OptionY = (static_cast<float>(menu::printingOp) * 0.035f) + 0.075f;
	}
	else
	{
		if (menu::printingOp < (menu::currentOp - 13) || menu::printingOp > menu::currentOp) return;
		else OptionY = (static_cast<float>(menu::printingOp - (menu::currentOp - 14)) * 0.035f) + 0.075f;
	}

	Game::Print::setupdraw();
	HUD::SET_TEXT_COLOUR(optiontext.R, optiontext.G, optiontext.B, optiontext.A);
	if (menu::printingOp == menu::currentOp)
	{
		HUD::SET_TEXT_COLOUR(selectedtext.R, selectedtext.G, selectedtext.B, selectedtext.A);
		if (IsOptionPressed())
		{
			option_code_bool = true;
			func();
			if (submenu_index != -1) menu::setSubDelayed = submenu_index;
		}
	}

	if (show_arrow || submenu_index != -1)
	{
		if (menu::printingOp == menu::currentOp) {
			GRAPHICS::DRAW_SPRITE("commonmenu", "arrowright", menuPos.x + 0.192f, OptionY + menuPos.y + 0.01f, 0.016f, 0.026f, 0.0f, selectedtext.R, selectedtext.G, selectedtext.B, 255, 0);
		}
		else {
			GRAPHICS::DRAW_SPRITE("commonmenu", "arrowright", menuPos.x + 0.192f, OptionY + menuPos.y + 0.01f, 0.016f, 0.026f, 0.0f, optiontext.R, optiontext.G, optiontext.B, 255, 0);
		}
	}
	
	Game::Print::drawstring(option, 0.001f + menuPos.x, OptionY + menuPos.y);
}

void OptionStatus(int status)
{
	OptionY = 0.0f;
	if (menu::currentOp <= 14)
	{
		if (menu::printingOp > 14) return;
		else OptionY = (static_cast<float>(menu::printingOp) * 0.035f) + 0.075f;
	}
	else
	{
		if (menu::printingOp < (menu::currentOp - 13) || menu::printingOp > menu::currentOp) return;
		else OptionY = (static_cast<float>(menu::printingOp - (menu::currentOp - 14)) * 0.035f) + 0.075f;
	}

	switch (status)
	{
	case 0:
		if (menu::printingOp == menu::currentOp) {
			GRAPHICS::DRAW_SPRITE("timerbar_sr", "timer_cross", 0.192f + menuPos.x, OptionY + menuPos.y + 0.01f, 0.013f, 0.023f, 0.0f, selectedtext.R, selectedtext.G, selectedtext.B, 255, 0);
		}
		else {
			GRAPHICS::DRAW_SPRITE("timerbar_sr", "timer_cross", 0.192f + menuPos.x, OptionY + menuPos.y + 0.01f, 0.013f, 0.023f, 0.0f, optiontext.R, optiontext.G, optiontext.B, 255, 0);
		}
		break;
	case 1:
		if (menu::printingOp == menu::currentOp) {
			GRAPHICS::DRAW_SPRITE("timerbar_sr", "timer_tick", 0.192f + menuPos.x, OptionY + menuPos.y + 0.01f, 0.013f, 0.023f, 0.0f, selectedtext.R, selectedtext.G, selectedtext.B, 255, 0);
		}
		else {
			GRAPHICS::DRAW_SPRITE("timerbar_sr", "timer_tick", 0.192f + menuPos.x, OptionY + menuPos.y + 0.01f, 0.013f, 0.023f, 0.0f, optiontext.R, optiontext.G, optiontext.B, 255, 0);
		}
		break;
	}
}

void AddToggle(const std::string& option, bool& loop_variable, std::function<void()> func)
{
	null = 0;
	AddOption(option, null);

	if (null) {
		loop_variable = !loop_variable;
		func();
	}

	OptionStatus((int)loop_variable); // Display Tick/Cross
}

void AddBreak(const std::string& text)
{
	menu::printingOp++; menu::breakCount++;

	OptionY = 0.0f;

	if (menu::currentOp <= 14)
	{
		if (menu::printingOp > 14) return;
		else OptionY = (static_cast<float>(menu::printingOp) * 0.035f) + 0.07f;
	}
	else
	{
		if (menu::printingOp < (menu::currentOp - 13) || menu::printingOp > menu::currentOp) return;
		else OptionY = (static_cast<float>(menu::printingOp - (menu::currentOp - 14)) * 0.035f) + 0.07f;
	}

	Game::Print::setupdraw();
	HUD::SET_TEXT_SCALE(0.33f, 0.33f);
	HUD::SET_TEXT_CENTRE(1);
	HUD::SET_TEXT_COLOUR(optionbreaks.R, optionbreaks.G, optionbreaks.B, optionbreaks.A);
	if (menu::printingOp == menu::currentOp)
	{
		switch (menu::breakScroll)
		{
		case 1: // Up
			if (menu::currentOp <= 1) menu::Bottom();
			else menu::Up();
			break;
		case 2: default: // Down
			if (menu::currentOp >= menu::totalOp) menu::Top();
			else menu::Down();
			break;
		}
	}

	HUD::SET_TEXT_FONT(1);
	Game::Print::drawstring("~c~~italic~" + text, 0.1f + menuPos.x, OptionY + menuPos.y + 0.005f);
}

void AddNumber(const std::string& option, int& value, int min, int max, int step, std::function<void()> func)
{
	null = 0;
	AddOption(option, null);

	OptionY = 0.0f;
	if (menu::currentOp <= 14)
	{
		if (menu::printingOp > 14) return;
		else OptionY = (static_cast<float>(menu::printingOp) * 0.035f) + 0.075f;
	}
	else
	{
		if (menu::printingOp < (menu::currentOp - 13) || menu::printingOp > menu::currentOp) return;
		else OptionY = (static_cast<float>(menu::printingOp - (menu::currentOp - 14)) * 0.035f) + 0.075f;
	}

	Game::Print::setupdraw();
	HUD::SET_TEXT_COLOUR(optiontext.R, optiontext.G, optiontext.B, optiontext.A);
	HUD::SET_TEXT_CENTRE(1);
	HUD::SET_TEXT_JUSTIFICATION(2);
	HUD::SET_TEXT_WRAP(menuPos.x, 0.198f + menuPos.x);
	if (menu::printingOp == menu::currentOp)
	{
		HUD::SET_TEXT_COLOUR(selectedtext.R, selectedtext.G, selectedtext.B, selectedtext.A);
		if (null)
		{
			value = static_cast<int>(NumberKeyboard());
			func();
		}
		else if (IsOptionRPressed())
		{
			value < max ? value += step : value = max;
			func();
		}
		else if (IsOptionLPressed())
		{
			value > min ? value -= step : value = min;
			func();
		}
	}
	
	Game::Print::drawinteger(value, 0.198f + menuPos.x, OptionY + menuPos.y);
}

void AddNumber(const std::string& option, float& value, float min, float max, float step, std::function<void()> func)
{
	null = 0;
	AddOption(option, null);

	OptionY = 0.0f;
	if (menu::currentOp <= 14)
	{
		if (menu::printingOp > 14) return;
		else OptionY = (static_cast<float>(menu::printingOp) * 0.035f) + 0.075f;
	}
	else
	{
		if (menu::printingOp < (menu::currentOp - 13) || menu::printingOp > menu::currentOp) return;
		else OptionY = (static_cast<float>(menu::printingOp - (menu::currentOp - 14)) * 0.035f) + 0.075f;
	}


	Game::Print::setupdraw();
	HUD::SET_TEXT_COLOUR(optiontext.R, optiontext.G, optiontext.B, optiontext.A);
	HUD::SET_TEXT_CENTRE(1);
	HUD::SET_TEXT_JUSTIFICATION(2);
	HUD::SET_TEXT_WRAP(menuPos.x, 0.198f + menuPos.x);
	if (menu::printingOp == menu::currentOp)
	{
		HUD::SET_TEXT_COLOUR(selectedtext.R, selectedtext.G, selectedtext.B, selectedtext.A);
		if (null)
		{
			value = static_cast<float>(NumberKeyboard());
			func();
		}
		else if (IsOptionRPressed())
		{
			value < max ? value += step : value = max;
			func();
		}
		else if (IsOptionLPressed())
		{
			value > min ? value -= step : value = min;
			func();
		}
	}
	
	Game::Print::drawfloat(value, 2, 0.198f + menuPos.x, OptionY + menuPos.y);
}

void AddTele(const std::string& option, float X, float Y, float Z)
{
	null = 0;
	AddOption(option, null);
	if (menu::printingOp == menu::currentOp)
	{
		if (null)
		{
			if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), true)) {
				ENTITY::SET_ENTITY_COORDS_NO_OFFSET(PLAYER::PLAYER_PED_ID(), X, Y, Z, 1, 1, 1);
			}
			else {
				ENTITY::SET_ENTITY_COORDS_NO_OFFSET(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), X, Y, Z, 1, 1, 1);
			}
		}
	}
}

/*
		THIS FILE IS A PART OF GTA V SCRIPT HOOK SDK
					http://dev-c.com
				(C) Alexander Blade 2015
*/

#include "script.h"

const int KEYS_SIZE = 255;

struct {
	DWORD time;
	BOOL isWithAlt;
	BOOL wasDownBefore;
	BOOL isUpNow;
} keyStates[KEYS_SIZE];

void OnKeyboardMessage(DWORD key, WORD repeats, BYTE scanCode, BOOL isExtended, BOOL isWithAlt, BOOL wasDownBefore, BOOL isUpNow)
{
	if (key < KEYS_SIZE)
	{
		keyStates[key].time = GetTickCount();
		keyStates[key].isWithAlt = isWithAlt;
		keyStates[key].wasDownBefore = wasDownBefore;
		keyStates[key].isUpNow = isUpNow;
	}
}

const int NOW_PERIOD = 100, MAX_DOWN = 5000; // ms

bool IsKeyDown(DWORD key)
{
	return (key < KEYS_SIZE) ? ((GetTickCount() < keyStates[key].time + MAX_DOWN) && !keyStates[key].isUpNow) : false;
}

bool IsKeyJustUp(DWORD key, bool exclusive)
{
	bool b = (key < KEYS_SIZE) ? (GetTickCount() < keyStates[key].time + NOW_PERIOD && keyStates[key].isUpNow) : false;
	if (b && exclusive)
		ResetKeyState(key);
	return b;
}

void ResetKeyState(DWORD key)
{
	if (key < KEYS_SIZE)
		memset(&keyStates[key], 0, sizeof(keyStates[0]));
}

namespace MenuPressTimer
{
	MenuPressTimer::Button currentButton = { MenuPressTimer::Button::None };
	DWORD offsettedTime = 0;

	void Update()
	{
		if (currentButton == Button::None)
		{
			offsettedTime = GetTickCount() + 630;
		}

		if (IS_DISABLED_CONTROL_PRESSED(2, INPUT_FRONTEND_RIGHT) || IsKeyDown(VirtualKey::Numpad6))
		{
			currentButton = Button::Right;
		}
		else if (IS_DISABLED_CONTROL_PRESSED(2, INPUT_FRONTEND_LEFT) || IsKeyDown(VirtualKey::Numpad4))
		{
			currentButton = Button::Left;
		}
		else if (IS_DISABLED_CONTROL_PRESSED(2, INPUT_FRONTEND_DOWN) || IsKeyDown(VirtualKey::Numpad2))
		{
			currentButton = Button::Down;
		}
		else if (IS_DISABLED_CONTROL_PRESSED(2, INPUT_FRONTEND_UP) || IsKeyDown(VirtualKey::Numpad8))
		{
			currentButton = Button::Up;
		}
		else
		{
			currentButton = Button::None;
			offsettedTime = 0;
		}
	}

	bool IsButtonHeld(const MenuPressTimer::Button& button)
	{
		DWORD tickCount = GetTickCount();
		return (currentButton == button && offsettedTime < tickCount);
	}

	bool IsButtonTapped(const MenuPressTimer::Button & button)
	{
		bool isTapped = true;
		switch (button)
		{
		case Button::Right: isTapped = IS_DISABLED_CONTROL_JUST_PRESSED(2, INPUT_FRONTEND_RIGHT) || IsKeyJustUp(VirtualKey::Numpad6); break;
		case Button::Left: isTapped = IS_DISABLED_CONTROL_JUST_PRESSED(2, INPUT_FRONTEND_LEFT) || IsKeyJustUp(VirtualKey::Numpad4); break;
		case Button::Down: isTapped = IS_DISABLED_CONTROL_JUST_PRESSED(2, INPUT_FRONTEND_DOWN) || IsKeyJustUp(VirtualKey::Numpad2); break;
		case Button::Up: isTapped = IS_DISABLED_CONTROL_JUST_PRESSED(2, INPUT_FRONTEND_UP) || IsKeyJustUp(VirtualKey::Numpad8); break;
		case Button::Back: isTapped = IS_DISABLED_CONTROL_JUST_PRESSED(2, INPUT_FRONTEND_RRIGHT) || IsKeyJustUp(VirtualKey::Numpad0); break;
		case Button::Accept: isTapped = IS_DISABLED_CONTROL_JUST_PRESSED(2, INPUT_FRONTEND_ACCEPT) || IsKeyJustUp(VirtualKey::Numpad5); break;
		}
		return isTapped;
	}

	bool IsButtonHeldOrTapped(const MenuPressTimer::Button & button)
	{
		return IsButtonHeld(button) || IsButtonTapped(button);
	}
}
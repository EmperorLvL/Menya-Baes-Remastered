#pragma once

extern Vector2 menuPos;
extern float OptionY;

extern int font_title;
extern int font_options;
extern int font_selection;
extern int font_breaks;
extern int* settings_font;

extern RGBA* settings_rgba;
extern RGBA titlebox;
extern RGBA BG;
extern RGBA titletext;
extern RGBA optiontext;
extern RGBA selectedtext;
extern RGBA optionbreaks;
extern RGBA optioncount;
extern RGBA selectionhi;

extern bool menujustopened;

class menu
{
public:

	static unsigned __int16 currentsub;
	static unsigned __int16 currentop;
	static unsigned __int16 currentop_w_breaks;
	static unsigned __int16 totalop;
	static unsigned __int16 printingop;
	static unsigned __int16 breakcount;
	static unsigned __int16 totalbreaks;
	static unsigned __int8 breakscroll;
	static __int16 currentsub_ar_index;
	static int currentsub_ar[100];
	static int currentop_ar[100];
	static int SetSub_delayed;
	static int livetimer;
	static bool bit_controller, bit_mouse, bit_centre_title, bit_centre_options, bit_centre_breaks, gradients, thin_line_over_screct, bit_glare_test;

	static void loops();
	static void sub_handler();
	static void submenu_switch();

	static void DisableControls();
	static void base();
	static void background();
	static void optionhi();
	static bool isBinds();
	static void while_closed();
	static void while_opened();
	static void Up();
	static void Down();
	static void Bottom();
	static void Top();
	static void SetSub_previous();
	static void SetSub_new(int sub_index);
	static void SetSub_closed();
};

extern int inull;
extern bool null;
void nullFunc();

void AddTitle(std::string title);
void AddOption(std::string option, bool& option_code_bool = null, void(&Func)() = nullFunc, int submenu_index = -1, bool show_arrow = 0);
void AddToggle(std::string option, bool& loop_variable, bool& extra_option_code_ON = null, bool& extra_option_code_OFF = null);
void AddLocal(std::string option, Void condition, bool& option_code_ON, bool& option_code_OFF);
void AddBreak(std::string text);
void AddNumber(std::string option, float value, __int8 decimal_places, bool& A_PRESS = null, bool& RIGHT_PRESS = null, bool& LEFT_PRESS = null);
void AddTele(std::string option, float X, float Y, float Z, bool& extra_option_code = null);

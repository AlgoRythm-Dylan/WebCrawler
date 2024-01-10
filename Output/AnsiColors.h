#pragma once

#include <Windows.h>
#include <string>

using std::string;

namespace ansicolor
{
#ifdef USE_ANSI_COLORS
	inline const string reset = "\x1B[0;0m";
	inline const string black = "\x1B[30m";
	inline const string red = "\x1B[31m";
	inline const string green = "\x1B[32m";
	inline const string yellow = "\x1B[33m";
	inline const string blue = "\x1B[34m";
	inline const string magenta = "\x1B[35m";
	inline const string cyan = "\x1B[36m";
	inline const string white = "\x1B[37m";
	inline const string def = "\x1B[39m";
	inline const string bg_black = "\x1B[40m";
	inline const string bg_red = "\x1B[41m";
	inline const string bg_green = "\x1B[42m";
	inline const string bg_yellow = "\x1B[43m";
	inline const string bg_blue = "\x1B[44m";
	inline const string bg_magenta = "\x1B[45m";
	inline const string bg_cyan = "\x1B[46m";
	inline const string bg_white = "\x1B[47m";
	inline const string bg_def = "\x1B[49m";
	inline const string bold = "\33[1m";
	inline const string dim = "\33[2m";
	inline const string italic = "\33[3m";
	inline const string underline = "\33[4m";
	inline const string blink = "\33[5m";
	inline const string reverse = "\33[7m";
	inline const string strikethrough = "\33[9m";
#else
	inline const string reset = "";
	inline const string black = "";
	inline const string red = "";
	inline const string green = "";
	inline const string yellow = "";
	inline const string blue = "";
	inline const string magenta = "";
	inline const string cyan = "";
	inline const string white = "";
	inline const string def = "";
	inline const string bg_black = "";
	inline const string bg_red = "";
	inline const string bg_green = "";
	inline const string bg_yellow = "";
	inline const string bg_blue = "";
	inline const string bg_magenta = "";
	inline const string bg_cyan = "";
	inline const string bg_white = "";
	inline const string bg_def = "";
	inline const string bold = "";
	inline const string dim = "";
	inline const string underline = "";
	inline const string italic = "";
	inline const string blink = "";
	inline const string reverse = "";
	inline const string strikethrough = "";
#endif
	inline const string screen_test = "Foreground colors test\n" +
		string("\t") + red + "RED\n" + reset +
		string("\t") + green + "GREEN\n" + reset +
		string("\t") + yellow + "YELLOW\n" + reset +
		string("\t") + blue + "BLUE\n" + reset +
		string("\t") + magenta + "MAGENTA\n" + reset +
		string("\t") + cyan + "CYAN\n" + reset +
		"Background colors test\n" +
		string("\t") + bg_red + "RED\n" + reset +
		string("\t") + bg_green + "GREEN\n" + reset +
		string("\t") + bg_yellow + "YELLOW\n" + reset +
		string("\t") + bg_blue + "BLUE\n" + reset +
		string("\t") + bg_magenta + "MAGENTA\n" + reset +
		string("\t") + bg_cyan + "CYAN\n" + reset +
		"Formatting test\n" +
		string("\t") + bold + "BOLD\n" + reset +
		string("\t") + dim + "DIM\n" + reset +
		string("\t") + underline + "UNDERLINE\n" + reset +
		string("\t") + italic + "ITALIC\n" + reset +
		string("\t") + blink + "BLINK\n" + reset +
		string("\t") + reverse + "REVERSE\n" + reset +
		string("\t") + strikethrough + "STRIKETHROUGH\n" + reset;
	// By default, cmd.exe on win 10 doesn't recognize ANSI sequences,
	// even though it has the ability. Need to enable it.
	void inline setup_ansi_mode()
	{
		// Get current console mode
		HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
		DWORD mode = 0;
		GetConsoleMode(out, &mode);
		// Add ansi sequence processing
		mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
		SetConsoleMode(out, mode);
	}
}
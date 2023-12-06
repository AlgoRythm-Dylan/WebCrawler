#pragma once

#include <Windows.h>
#include <string>

#define EXP __declspec(dllexport)

using std::string;

namespace ansicolor
{
#ifdef USE_ANSI_COLORS
	EXP inline const string reset = "\x1B[0;0m";
	EXP inline const string black = "\x1B[30m";
	EXP inline const string red = "\x1B[31m";
	EXP inline const string green = "\x1B[32m";
	EXP inline const string yellow = "\x1B[33m";
	EXP inline const string blue = "\x1B[34m";
	EXP inline const string magenta = "\x1B[35m";
	EXP inline const string cyan = "\x1B[36m";
	EXP inline const string white = "\x1B[37m";
	EXP inline const string def = "\x1B[39m";
	EXP inline const string bg_black = "\x1B[40m";
	EXP inline const string bg_red = "\x1B[41m";
	EXP inline const string bg_green = "\x1B[42m";
	EXP inline const string bg_yellow = "\x1B[43m";
	EXP inline const string bg_blue = "\x1B[44m";
	EXP inline const string bg_magenta = "\x1B[45m";
	EXP inline const string bg_cyan = "\x1B[46m";
	EXP inline const string bg_white = "\x1B[47m";
	EXP inline const string bg_def = "\x1B[49m";
	EXP inline const string bold = "\33[1m";
	EXP inline const string dim = "\33[2m";
	EXP inline const string italic = "\33[3m";
	EXP inline const string underline = "\33[4m";
	EXP inline const string blink = "\33[5m";
	EXP inline const string reverse = "\33[7m";
	EXP inline const string strikethrough = "\33[9m";
#else
	EXP inline const string reset = "";
	EXP inline const string black = "";
	EXP inline const string red = "";
	EXP inline const string green = "";
	EXP inline const string yellow = "";
	EXP inline const string blue = "";
	EXP inline const string magenta = "";
	EXP inline const string cyan = "";
	EXP inline const string white = "";
	EXP inline const string def = "";
	EXP inline const string bg_black = "";
	EXP inline const string bg_red = "";
	EXP inline const string bg_green = "";
	EXP inline const string bg_yellow = "";
	EXP inline const string bg_blue = "";
	EXP inline const string bg_magenta = "";
	EXP inline const string bg_cyan = "";
	EXP inline const string bg_white = "";
	EXP inline const string bg_def = "";
	EXP inline const string bold = "";
	EXP inline const string dim = "";
	EXP inline const string underline = "";
	EXP inline const string italic = "";
	EXP inline const string blink = "";
	EXP inline const string reverse = "";
	EXP inline const string strikethrough = "";
#endif
	EXP inline const string screen_test = "Foreground colors test\n" +
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
	EXP void inline setup_ansi_mode()
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
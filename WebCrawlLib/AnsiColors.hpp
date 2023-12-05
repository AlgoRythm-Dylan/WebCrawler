#pragma once

#include <Windows.h>
#include <string>

#define EXP __declspec(dllexport)

using std::string;

namespace ansicolor
{
#ifdef USE_ANSI_COLORS
	EXP const string reset = "\x1B[0;0m";
	EXP const string black = "\x1B[30m";
	EXP const string red = "\x1B[31m";
	EXP const string green = "\x1B[32m";
	EXP const string yellow = "\x1B[33m";
	EXP const string blue = "\x1B[34m";
	EXP const string magenta = "\x1B[35m";
	EXP const string cyan = "\x1B[36m";
	EXP const string white = "\x1B[37m";
	EXP const string def = "\x1B[39m";
	EXP const string bg_black = "\x1B[40m";
	EXP const string bg_red = "\x1B[41m";
	EXP const string bg_green = "\x1B[42m";
	EXP const string bg_yellow = "\x1B[43m";
	EXP const string bg_blue = "\x1B[44m";
	EXP const string bg_magenta = "\x1B[45m";
	EXP const string bg_cyan = "\x1B[46m";
	EXP const string bg_white = "\x1B[47m";
	EXP const string bg_def = "\x1B[49m";
	EXP const string bold = "\33[1m";
	EXP const string dim = "\33[2m";
	EXP const string italic = "\33[3m";
	EXP const string underline = "\33[4m";
	EXP const string blink = "\33[5m";
	EXP const string reverse = "\33[7m";
	EXP const string strikethrough = "\33[9m";
#else
	EXP const string reset = "";
	EXP const string black = "";
	EXP const string red = "";
	EXP const string green = "";
	EXP const string yellow = "";
	EXP const string blue = "";
	EXP const string magenta = "";
	EXP const string cyan = "";
	EXP const string white = "";
	EXP const string def = "";
	EXP const string bg_black = "";
	EXP const string bg_red = "";
	EXP const string bg_green = "";
	EXP const string bg_yellow = "";
	EXP const string bg_blue = "";
	EXP const string bg_magenta = "";
	EXP const string bg_cyan = "";
	EXP const string bg_white = "";
	EXP const string bg_def = "";
	EXP const string bold = "";
	EXP const string dim = "";
	EXP const string underline = "";
	EXP const string italic = "";
	EXP const string blink = "";
	EXP const string reverse = "";
	EXP const string strikethrough = "";
#endif
	EXP const string screen_test = "Foreground colors test\n" +
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
	EXP void setup_ansi_mode()
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
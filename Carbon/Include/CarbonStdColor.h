/**
 * Created by cy on 2018/4/30.
 */

#ifndef PRINTF_H
#define PRINTF_H

#include "stddef.h"

typedef enum
{
	BLACK = 0b0000,
	DARKGRAY = BLACK + 0b1000,

	RED = 0b0100,
	LIGHTRED = RED + 0b1000,
	TOMATO = LIGHTRED,

	GREEN = 0b0010,
	LIGHTGREEN = GREEN + 0b1000,
	LAWNGREEN = LIGHTGREEN,

	BLUE = 0b0001,
	SKYBLUE = BLUE + 0b1000,
	LIGHTBLUE = SKYBLUE,

	ORANGE = 0b0110,
	YELLOW = ORANGE + 0b1000,

	PURPLE = 0b0101,
	PINK = PURPLE + 0b1000,

	CYAN = 0b0011,
	LIGHTCYAN = CYAN + 0b1000,

	WHITE = 0b0111,
	LIGHTGRAY = WHITE,
	LIGHTWHITE = WHITE + 0b1000
} TextColor;

typedef enum
{
	bgBLACK = 0b0000 << 4,
	bgRED = 0b0100 << 4,
	bgGREEN = 0b0010 << 4,
	bgBLUE = 0b0001 << 4,
	bgORANGE = 0b0110 << 4,
	bgPURPLE = 0b0101 << 4,
	bgCYAN = 0b0011 << 4,
	bgWHITE = 0b0111 << 4
} BgColor;

#define makeColor(textcolor, bgcolor) ((textcolor) + (bgcolor))

#define defaultTextColor (WHITE)
#define defaultBgColor (bgBLACK)

#define defaultColor makeColor(defaultTextColor, defaultBgColor)

#endif //PRINTF_H


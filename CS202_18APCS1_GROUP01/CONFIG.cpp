#include "CONFIG.h"
#pragma once

void autoConfig(){
	HWND consoleWindow = GetConsoleWindow();
	RECT ConsoleRect;
	GetWindowRect(consoleWindow, &ConsoleRect);
	MoveWindow(consoleWindow, ConsoleRect.left, ConsoleRect.top, 1600, 900, TRUE);
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}

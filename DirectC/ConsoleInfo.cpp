#include "pch.h"
#include "ConsoleInfo.h"

namespace DirectC {
	DIRECTC_API ConsoleSizeData ConsoleInfo::GetConsoleSize(void) {
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

		return ConsoleSizeData{ csbi.srWindow.Right - csbi.srWindow.Left + 1, csbi.srWindow.Bottom - csbi.srWindow.Top + 1 };
	}
}

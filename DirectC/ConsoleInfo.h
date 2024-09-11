#pragma once

#include <iostream>
#include <Windows.h>

#include "ConsoleSizeData.h"

#ifdef DIRECTC_EXPORTS
#define DIRECTC_API __declspec(dllexport)
#else
#define DIRECTC_API __declspec(dllimport)
#endif

namespace DirectC {
	class ConsoleInfo {
	public:
		static DIRECTC_API ConsoleSizeData GetConsoleSize(void);
	};
}


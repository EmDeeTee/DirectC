#pragma once

#include <iostream>
#include <format>

#include "Position.h"
#include "ConsoleSizeData.h"
#include "DirectC.h"
//#include "Key.h"

#ifdef DIRECTC_EXPORTS
#define DIRECTC_API __declspec(dllexport)
#else
#define DIRECTC_API __declspec(dllimport)
#endif

namespace DirectC {
	class Screen {
	public:
		DIRECTC_API Screen(size_t w, size_t h, const std::string& title = "");
		DIRECTC_API ~Screen(void);
		DIRECTC_API size_t GetScreenSize(void) const;
		DIRECTC_API DWORD RenderNextFrame(void) const;
		DIRECTC_API void Write(const std::string& text, const Position& p = {0, 0}, bool centerText = false, const WORD attrs = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		DIRECTC_API Position GetCenter(void) const;
		DIRECTC_API const wchar_t* GetCharAt(const Position& p) const;
		DIRECTC_API void ClearBuffer(void);
		DIRECTC_API void DisplayConsoleInfo();
		DIRECTC_API bool WasKeyPressed(const Key key);
		DIRECTC_API bool IsWithinBounds(const Position& p) const;
		DIRECTC_API ConsoleSizeData GetConsoleSizeData(void) const;
	private:
		size_t m_Width = 0;
		size_t m_Height = 0;
		wchar_t* m_Screen;
		HANDLE m_Console;
		ConsoleSizeData m_SizeData = {0};
		static constexpr uint16_t m_CONSOLE_BUFFER_SIZE = 255;
		wchar_t* m_OldConsoleTitle = new wchar_t[m_CONSOLE_BUFFER_SIZE];

		const WORD m_RainbowColours[5] = { 
			FOREGROUND_RED | FOREGROUND_GREEN,
			FOREGROUND_GREEN,
			FOREGROUND_BLUE | FOREGROUND_GREEN,
			FOREGROUND_RED | FOREGROUND_BLUE,
			FOREGROUND_RED | FOREGROUND_INTENSITY
		};
	};
}



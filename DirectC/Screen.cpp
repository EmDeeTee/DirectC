#include "pch.h"
#include "Screen.h"
#include "Util.h"

namespace DirectC {
	/// <summary>
	/// Init the screen and fill it with empty chars. Passing 0 for width or height will automatically determine them 
	/// </summary>
	/// <param name="w">Width</param>
	/// <param name="h">Height</param>
	Screen::Screen(size_t w, size_t h, const std::string& title) {
		m_SizeData = ConsoleInfo::GetConsoleSize();
		if (w <= 0 || h <= 0) { // auto
			m_Width = m_SizeData.rows;
			m_Height = m_SizeData.cols;
		} else {
			m_Width = w;
			m_Height = h;
		}

		m_Screen = new wchar_t[m_Width * m_Height];
		m_Console = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
		GetConsoleTitle(m_OldConsoleTitle, m_CONSOLE_BUFFER_SIZE);
		SetConsoleActiveScreenBuffer(m_Console);
		const CONSOLE_CURSOR_INFO i = { 1, false };
		SetConsoleCursorInfo(m_Console, &i);

		if (title != "") {
			SetConsoleTitle(Util::StringToLPCWSTR(title).c_str());
		}

		for (size_t i = 0; i < GetScreenSize(); i++) {
			m_Screen[i] = ' ';
		}
	}

	Screen::~Screen(void) {
		SetConsoleTitle(m_OldConsoleTitle);
		delete[] m_Screen;
		delete[] m_OldConsoleTitle;
		if (m_Console != INVALID_HANDLE_VALUE) {
			CloseHandle(m_Console);
			m_Console = INVALID_HANDLE_VALUE;
		}
	}

	DIRECTC_API size_t Screen::GetScreenSize(void) const {
		return m_Width * m_Height;
	}

	DIRECTC_API DWORD Screen::RenderNextFrame(void) const {
		DWORD bytesWritten = 0;

		WriteConsoleOutputCharacter(m_Console, m_Screen, GetScreenSize(), { 0,0 }, &bytesWritten);
		return bytesWritten;
	}

	// ReSharper disable once CppMemberFunctionMayBeConst
	DIRECTC_API void Screen::Write(const std::string& text, const Position& p, bool centerText, const WORD attrs) {
		if (IsWithinBounds(p)) {
			DWORD o;

			int currentAttrIndex = 0;
			for (size_t i = 0; i < text.length(); i++) {
				if (attrs == Colour::RAINBOW) {
					if (currentAttrIndex >= 5) // Length of the array
						currentAttrIndex = 0;
					WORD currentAttr = m_RainbowColours[currentAttrIndex];
					WriteConsoleOutputAttribute(m_Console, &currentAttr, 1, { static_cast<short>(p.x + i - (centerText ? text.length() / 2 : 0)), static_cast<short>(p.y) }, &o);
					currentAttrIndex++;
				}
				else {
					WriteConsoleOutputAttribute(m_Console, &attrs, 1, {static_cast<short>(p.x+i - (centerText ? text.length() / 2 : 0)), static_cast<short>(p.y) }, &o);
				}
			}
			wsprintf(&m_Screen[(p.y * m_Width + p.x) - (centerText ? text.length() / 2 : 0)], Util::StringToLPCWSTR(text).c_str(), nullptr);
		}
		else
			throw std::out_of_range("Position was outside of the buffer");
	}

	DIRECTC_API Position Screen::GetCenter(void) const {
		return { m_Width / 2, m_Height / 2 };
	}

	DIRECTC_API const wchar_t* Screen::GetCharAt(const Position& p) const {
		if (IsWithinBounds(p))
			return &m_Screen[p.y * m_Width + p.x];
		else
			throw std::out_of_range("Position was outside of the buffer");
	}

	DIRECTC_API void Screen::ClearBuffer(void) {
		for (size_t i = 0; i < GetScreenSize(); i++) {
			m_Screen[i] = ' ';
		} 
		DWORD o;
		WORD attrs = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;

		/*for (size_t x = 0; x < m_Width; x++) {
			for (size_t y = 0; y < m_Height; y++) {
				if (m_Screen[y * m_Width + x] == L' ')
					WriteConsoleOutputAttribute(m_Console, &attrs, 1, { static_cast<short>(x), static_cast<short>(y) }, &o);
			}
		}*/
	}
	/// <summary>
	/// Displays basic information about the console
	///	This method triggers RenderNextFrame()
	/// </summary>
	/// <returns></returns>
	DIRECTC_API void Screen::DisplayConsoleInfo() {
		Write(std::format("DirectC Version {}", DIRECTC_VERSION), GetCenter(), true, FOREGROUND_BLUE | FOREGROUND_GREEN);
		Write(std::format("Cols: {}", m_SizeData.cols), GetCenter().AddY(1), true, FOREGROUND_RED | FOREGROUND_GREEN);
		Write(std::format("Rows: {}", m_SizeData.rows), GetCenter().AddY(2), true, FOREGROUND_RED | FOREGROUND_GREEN);
		RenderNextFrame();
	}

	DIRECTC_API bool Screen::WasKeyPressed(const Key key) {
		return GetAsyncKeyState(key);
	}

	DIRECTC_API bool Screen::IsWithinBounds(const Position& p) const {
		return (p.x >= 0 && p.x <= m_Width - 1) && (p.y >= 0 && p.y <= m_Height - 1);
	}

	DIRECTC_API ConsoleSizeData Screen::GetConsoleSizeData(void) const {
		return m_SizeData;
	}
}


#pragma once

namespace Console
{
	///Color type enumlation
	enum Color
	{
		Black = 0,
		DarkBlue = 1,
		DarkGreen = 2,
		DarkCyan = 3,
		DarkRed = 4,
		DarkMagenta = 5,
		DarkYellow = 6,
		Gray = 7,
		DarkGray = 8,
		Blue = 9,
		Green = 10,
		Cyan = 11,
		Red = 12,
		Magenta = 13,
		Yellow = 14,
		White = 15,
		Length,
	};
	void Init();
	void Write(const char* str);
	void Write(const char* str, unsigned int forgraund);
	void Write(const char* str, unsigned int forgraund, unsigned int background);

	void WriteLine(const char* str);
	void WriteLine(const char* str, unsigned int forgraund);
	void WriteLine(const char* str, unsigned int forgraund, unsigned int background);

	void SetColor(unsigned int forgraund);
	void SetColor(unsigned int forgraund, unsigned int background);
	void ResetColor();

	void ShowColorSample();
};// namespace ndk_build_ex
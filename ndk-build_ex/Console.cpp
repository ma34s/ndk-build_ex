#include "stdafx.h"
#include <stdio.h>
#include <windows.h>
#include <iostream>

#include "Console.h"

static int initialColor;
static int initialBackground;
static FILE* fpLog = nullptr;

void Console::Init()
{
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleInfo);
	initialColor = consoleInfo.wAttributes;
	initialBackground = (initialColor & 0xF0) >> 4;
	fpLog = nullptr;
}

int Console::SetLogfile(const char* path)
{
	return fopen_s(&fpLog, path, "wt");
}

void Console::CloseLogfile()
{
	if (fpLog){
		fclose(fpLog);
		fpLog = nullptr;
	}
}

void Console::SetColor(unsigned int forgraund)
{
	SetColor((forgraund & 0x0F), initialBackground);
}
void Console::SetColor(unsigned int forgraund, unsigned int background)
{
	int style;
	style = (forgraund & 0x0F);
	style |= (background & 0x0F) << 4;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), style);
}

void Console::Write(const char* str)
{
	std::cout << str;
	if (fpLog){
		fprintf_s(fpLog, "%s", str);
	}
}

void Console::Write(const char* str, unsigned int forgraund)
{
	SetColor(forgraund);
	Write(str);
	ResetColor();
}
void Console::Write(const char* str, unsigned int forgraund, unsigned int background)
{
	SetColor(forgraund, background);
	Write(str);
	ResetColor();
}
void Console::WriteLine(const char* str)
{
	Write(str);
	Write("\n");
}

void Console::WriteLine(const char* str, unsigned int forgraund)
{
	SetColor(forgraund);
	WriteLine(str);
	ResetColor();
}
void Console::WriteLine(const char* str, unsigned int forgraund, unsigned int background)
{
	SetColor(forgraund, background);
	WriteLine(str);
	ResetColor();
}

void Console::ResetColor()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), initialColor);
}

void Console::ShowColorSample()
{
	const char* ColorName[Color::Length] =
	{
		"Black","DarkBlue",	"DarkGreen","DarkCyan","DarkRed",
		"DarkMagenta","DarkYellow","Gray","DarkGray","Blue",
		"Green","Cyan","Red","Magenta","Yellow","White",
	};
	for (int background = 0; background < Color::Length; background++)
	{
		for (int forgraund = 0; forgraund < Color::Length; forgraund++)
		{
			SetColor(forgraund, background);
			Write("forgraund=");
			Write(ColorName[forgraund]);
			Write(",background=");
			WriteLine(ColorName[background]);
		}
	}
	ResetColor();
}

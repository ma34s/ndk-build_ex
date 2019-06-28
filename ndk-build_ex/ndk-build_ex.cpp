// ndk-build_ex.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Console.h"

int main(int argc, char **argv)
{
	Console::Init();

	//Show ConsoleColor Sample
	Console::ShowColorSample();

	Console::ResetColor();
	return 0;
}


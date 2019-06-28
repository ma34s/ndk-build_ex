// ndk-build_ex.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "ndk-build_ex.h"
#include "Console.h"
using namespace ndk_build_ex;

void NdkBuild::MakeCommand(int argc, char **argv)
{
	sprintf_s(commandLine, sizeof(commandLine), "ndk-build");

	for (int i = 1; i < argc; i++)
	{
		strcat_s(commandLine, sizeof(commandLine), " ");
		strcat_s(commandLine, sizeof(commandLine), argv[i]);
	}
	strcat_s(commandLine, sizeof(commandLine), " 2>&1");
}

int NdkBuild::Build()
{
	FILE *fp;
	int result;
	if (fp = _popen(commandLine, "r")) {
		while (fgets(output, sizeof(output), fp)) {
			Console::Write(output);
		}
		result = _pclose(fp);
		Console::WriteLine("");
		if (result) {
			OnBuildFaild();
		} else {
			OnBuildSuccsess();
		}
	}
	return result;
}
void NdkBuild::OnBuildFaild()
{
	Console::WriteLine("Build is faild!", Console::Color::Red);
}
void NdkBuild::OnBuildSuccsess()
{
	Console::WriteLine("Build is succsessful Complete", Console::Color::Green);
}

int main(int argc, char **argv)
{
	Console::Init();
	//Show ConsoleColor Sample for test
	//Console::ShowColorSample();

	NdkBuild* ndkBuild = new NdkBuild();
	ndkBuild->MakeCommand(argc, argv);
	int result = ndkBuild->Build();
	delete ndkBuild;

	Console::ResetColor();
	return result;
}



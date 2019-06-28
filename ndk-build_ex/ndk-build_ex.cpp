// ndk-build_ex.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <regex>

#include "ndk-build_ex.h"
#include "Console.h"
using namespace ndk_build_ex;

static const std::regex rLog("^log:");

NdkBuild::NdkBuild()
{
	errCount = 0;
	wrnCount = 0;
}

void NdkBuild::MakeCommand(int argc, char **argv)
{
	sprintf_s(commandLine, sizeof(commandLine), "ndk-build");
	std::match_results<const char *> results;

	char logPath[1000];
	for (int i = 1; i < argc; i++)
	{
		if (std::regex_search(argv[i], results, rLog, std::regex_constants::match_default)) {
			sprintf_s(logPath, sizeof(logPath), "%s", &argv[i][strlen("log:")]);
			Console::Write("[ndk_build_ex] Info : build log: ", Console::Color::Magenta);
			if (Console::SetLogfile(logPath)) {
				Console::WriteLine("[ndk_build_ex] Error : build log open error", Console::Color::Magenta);
			}
		}
		else {
			strcat_s(commandLine, sizeof(commandLine), " ");
			strcat_s(commandLine, sizeof(commandLine), argv[i]);
		}
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
	Console::CloseLogfile();
	return result;
}



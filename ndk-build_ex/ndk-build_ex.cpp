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
			Console::Write("[ndk_build_ex] Info : build log: ", Console::Color::DarkMagenta);
			Console::WriteLine(logPath, Console::Color::DarkMagenta);
			if (Console::SetLogfile(logPath)) {
				Console::WriteLine("[ndk_build_ex] Error : build log open error", Console::Color::DarkMagenta);
			}
		}
		else {
			strcat_s(commandLine, sizeof(commandLine), " ");
			strcat_s(commandLine, sizeof(commandLine), argv[i]);
		}
	}
	strcat_s(commandLine, sizeof(commandLine), " 2>&1");
}

static const std::regex patternError(":[0-9]*:[0-9]*:.*error:");
static const std::regex patternWrings(":[0-9]*:[0-9]*:.*warning:");
static const std::regex patternInstall("\\[*.\\] Install *:");
static const std::regex patternStatic("\\[*.\\] StaticLibrary *:");
static const std::regex patternShared("\\[*.\\] SharedLibrary *:");
static const std::regex patternExecute("\\[*.\\] Executable *:");
static const std::regex patternCursol("\\s+\\^+\\s*");

void NdkBuild::ParseNdkOutput(char* output)
{
	std::match_results<const char *> results;

	if (std::regex_search(output, results, patternCursol, std::regex_constants::match_default)) {
		Console::Write(output, Console::Color::DarkMagenta);
	}
	else if (std::regex_search(output, results, patternError, std::regex_constants::match_default)) {
		errCount++;
		Console::Write(output, Console::Color::Red);
	}
	else if (std::regex_search(output, results, patternWrings, std::regex_constants::match_default)) {
		wrnCount++;
		Console::Write(output, Console::Color::Yellow);
	}
	else if (std::regex_search(output, results, patternInstall, std::regex_constants::match_default)) {
		Console::Write(output, Console::Color::Green);
	}
	else if (std::regex_search(output, results, patternStatic, std::regex_constants::match_default)) {
		Console::Write(output, Console::Color::DarkCyan);
	}
	else if (std::regex_search(output, results, patternShared, std::regex_constants::match_default)) {
		Console::Write(output, Console::Color::Blue);
	}
	else if (std::regex_search(output, results, patternExecute, std::regex_constants::match_default)) {
		Console::Write(output, Console::Color::Blue);
	}
	else
	{
		Console::ResetColor();
		Console::Write(output);
	}
}

void NdkBuild::ShowErrorCount()
{
	char buf[30];
	sprintf_s(buf, sizeof(buf), "Errors: %d", errCount);
	if (errCount) {
		Console::WriteLine(buf, Console::Color::Red);
	}
	else {
		Console::WriteLine(buf);
	}
	
	sprintf_s(buf, sizeof(buf), "Warnings: %d", wrnCount);
	if (wrnCount){
		Console::WriteLine(buf, Console::Color::Yellow);
	} else {
		Console::WriteLine(buf);
	}
}

int NdkBuild::Build()
{
	FILE *fp;
	int result;
	if (fp = _popen(commandLine, "r")) {
		while (fgets(output, sizeof(output), fp)) {
			ParseNdkOutput(output);
		}
		result = _pclose(fp);
		Console::WriteLine("");
		if (result) {
			OnBuildFaild();
		} else {
			OnBuildSuccsess();
		}
		ShowErrorCount();
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



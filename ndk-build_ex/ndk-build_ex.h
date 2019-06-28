#pragma once

namespace ndk_build_ex
{
	class NdkBuild
	{
	private:
		char commandLine[1000];
		char output[100000];
	protected:
		int errCount;
		int wrnCount;
		void OnBuildFaild();
		void OnBuildSuccsess();
		void ParseNdkOutput(char* output);
		void ShowErrorCount();
	public:
		NdkBuild();
		void MakeCommand(int argc, char **argv);
		int Build();
	};
};

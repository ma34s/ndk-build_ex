#pragma once

namespace ndk_build_ex
{
	class NdkBuild
	{
	private:
		char commandLine[1000];
		char output[100000];
	protected:
		void OnBuildFaild();
		void OnBuildSuccsess();
	public:
		void MakeCommand(int argc, char **argv);
		int Build();
	};
};

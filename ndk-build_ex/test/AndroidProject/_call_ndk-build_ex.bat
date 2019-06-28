@echo off
setlocal
set path=..\..\..\Debug;%path%

cd %~dp0
ndk-build_ex NDK_PROJECT_PATH=. APP_BUILD_SCRIPT=./Android.mk -j4 -B log:buildlog.txt
endlocal
pause

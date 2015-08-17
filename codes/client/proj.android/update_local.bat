ECHO OFF
SET cur_path=%~dp0
cmd /C android update project -p . -t android-20
cd ..\cocos2d\cocos\platform\android\java
cmd /C android update project -p . -t android-20
cd %cur_path%
pause

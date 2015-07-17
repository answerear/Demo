@ECHO OFF
SET PROTO_PATH=..\..\..\..\..\common\protocol\proto
SET OUT_PATH=.\source
SET PROTOC=..\..\..\dependencies\win32\protobuf\lib\x64\protoc.exe
SET CURRENT_PATH=%~dp0

CD %PROTO_PATH%


FOR /f "delims=\" %%a IN ('dir /b /a-d /o-d ".\*.proto"') DO (
	ECHO %PROTOC% -I=.\ --cpp_out=..\source  .\%%a
	%PROTOC% -I=.\ --cpp_out=..\source  .\%%a
)

CD %CURRENT_PATH%

PAUSE
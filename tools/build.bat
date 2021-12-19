@ECHO off
SetLocal EnableDelayedExpansion

IF DEFINED VSDEV ; ELSE (
	PUSHD "C:\Program Files (x86)\Microsoft Visual Studio\Installer\"
	SET CMD=vswhere -latest -property installationPath
	FOR /F "tokens=* USEBACKQ" %%F IN (`%CMD%`) DO (SET vsdir=%%F)
	POPD
	CALL "%vsdir%\VC\Auxiliary\Build\vcvars64.bat" > nul
)

ECHO Building...

PUSHD %1
FOR /R %%f in (*.cpp) do (
    SET filenames=!filenames! %%f
)
@REM echo Files: %filenames%
POPD

SET nova_args=/std:c++20 /MP /Ycpc.h /Yupc.h /Isrc
SET nova_link=/LIBPATH:..\..\bin

SET cwd=%cd%
SET clfile=%cwd%\build\msvc.build
MKDIR ..\bin\ 2>nul
MKDIR ..\build\%3 2>nul
PUSHD ..\build\%3
call cl.exe @%clfile% %nova_args% /Fe: %cwd%\..\bin\%2 %filenames% /link %nova_link%
POPD

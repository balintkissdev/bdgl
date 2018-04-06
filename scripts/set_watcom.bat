@ECHO OFF

SETLOCAL
SET SCRIPTS_DIR=%~dp0
FOR %%D in ("%SCRIPTS_DIR:~0,-1%") DO SET PROJECT_DIR=%%~dpD
SET DEPS_DIR=%PROJECT_DIR%deps\

:: Modify Open Watcom installation path here
SET WATCOM_DIR=%DEPS_DIR%open-watcom-v2\

ENDLOCAL && SET WATCOM_DIR=%WATCOM_DIR%

IF "%WATCOM%"=="%WATCOM_DIR%" GOTO :watcomisalreadyset
IF NOT "%WATCOM%"=="%WATCOM_DIR%" GOTO :setwatcomvariable

:setwatcomvariable
SET WATCOM=%WATCOM_DIR%

IF "%PROCESSOR_ARCHITECTURE%"=="AMD64" GOTO :setwin64watcom
IF NOT "%PROCESSOR_ARCHITECTURE%"=="AMD64" GOTO :setwin32watcom

:setallvariables
SET PATH=%WATCOM_BINDIRS%;%PATH%
SET EDPATH=%WATCOM%eddat
SET WIPFC=%WATCOM%wipfc
SET INCLUDE=%WATCOM%h

ECHO Watcom root: %WATCOM%
ECHO System: %OS_TEXT%
ECHO Watcom binaries: %WATCOM_BINDIRS%
ECHO.
ECHO Open Watcom build environment is set! Use "wmake" to build the library.
EXIT /B 0

:setwin64watcom
SET OS_TEXT=Windows 64-bit
SET WATCOM_BINDIRS=%WATCOM%binnt64;%WATCOM%binnt
GOTO :setallvariables

:setwin32watcom
SET OS_TEXT=Windows 32-bit
SET WATCOM_BINDIRS=%WATCOM%binnt;%WATCOM%binw
GOTO :setallvariables

:watcomisalreadyset
ECHO Open Watcom build environment was already set. Use "wmake" to build the library.
EXIT /B 0

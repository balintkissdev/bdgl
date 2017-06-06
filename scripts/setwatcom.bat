@ECHO OFF

:: Modify Open Watcom installation path here
SET WATCOM=C:\Watcom

:: Do not touch these!
IF "%WATCOM_P%=="" (
  SET WATCOM_P=%WATCOM%

  SET PATH=%WATCOM_P%\binnt;%WATCOM%\binw;%PATH%
  SET EDPATH=%WATCOM_P%\eddat
  SET WIPFC=%WATCOM_P%\wipfc
  SET INCLUDE=%WATCOM_P%\h

  ECHO "Open Watcom build environment is set! Use \"wmake all\" to build the library."
) ELSE (
  ECHO "Open Watcom build environment was already set. Use \"wmake all\" to build the library."
)
  

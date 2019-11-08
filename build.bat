@echo off
setlocal enableextensions
setlocal disabledelayedexpansion
for /l %%i in (100,-1,16) do (
	call :find_icl "%%i"
	if not errorlevel 1 goto found_icl
)
echo *** WARNING: ICL not found
goto no_icl
:found_icl
echo ICL: "%__intel__%"
setlocal
call "%__intel__%" ia32 >nul
call :exec icl.exe -O3t -Qm32 -QxHost -nologo -W3 -Qwd1786 -Qstd=c99 bitscan.c -obitscan-32.exe -Fabitscan-32.lst -FAcs
endlocal
setlocal
call "%__intel__%" intel64 >nul
call :exec icl.exe -O3t -Qm64 -QxHost -nologo -W3 -Qwd1786 -Qstd=c99 bitscan.c -Fabitscan.lst -FAcs
call :exec icl.exe -Qmic -O3 -m64 -mmic -nologo -masm=intel -w3 -wd1786 -std=c99 -DINTEL_SYNTAX bitscan.c -obitscan.mic -Fabitscan-mic.lst
endlocal
:no_icl
for /l %%i in (100,-1,10) do (
	call :find_msc "%%i"
	if not errorlevel 1 goto found_msc
)
echo *** WARNING: MSC not found
goto stop
:found_msc
echo MSC: "%__msc__%"
setlocal
call "%__msc__%" x86 >nul
call :exec cl.exe /Oxt /nologo /W3 /wd4996 bitscan.c /Febitscan-ms32.exe /FAcs /Fabitscan-ms32.lst
endlocal
setlocal
call "%__msc__%" amd64 >nul
set TARGET_VS_ARCH=x86_amd64
call :exec cl.exe /Oxt /nologo /W3 /wd4996 bitscan.c /Febitscan-ms64.exe /FAcs /Fabitscan-ms64.lst
endlocal
:stop
endlocal & endlocal & goto end
:find_icl
call set "__intel__=%%ICPP_COMPILER%~1%%bin\compilervars.bat"
if exist "%__intel__%" verify >nul & goto end
verify shit 2>nul & goto end
:find_msc
call set "__msc__=%%VS%~10COMNTOOLS%%..\..\VC\vcvarsall.bat"
if exist "%__msc__%" verify >nul & goto end
verify shit 2>nul & goto end
:exec
echo %*
%* & goto end
:end
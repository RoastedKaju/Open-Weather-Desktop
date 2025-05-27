@echo off
setlocal

REM Set path to vcpkg executeable
set VCPKG_EXE=Vendor\VCPKG\vcpkg.exe

REM Check if vcpkg.exe exists
if not exist %VCPKG_EXE% (
	echo [ERROR] vcpkg.exe not found, please run "Vendor/VCPKG/bootstrap-vcpkg.bat"
	pause
	exit /b 1
)

REM install GLFW
echo Installing dependencies...
%VCPKG_EXE% install glfw3 glad curl jsoncpp

if %errorlevel% neq 0 (
	echo [ERROR] Installation failed
	pause
	exit /b 1
)

echo [SUCCESS] Dependencies installed successfully.
endlocal
pause
@echo off
setlocal

REM Set path to vcpkg executeable
set VCPKG_EXE=Vendor\VCPKG\vcpkg.exe

REM Check if vcpkg.exe exists
if not exist %VCPKG_EXE% (
	echo [ERROR] vcpkg.exe not found, please run "Vendor/VCPKG/bootstrap-vcpkg.bat"
	exit /b 1
)

REM install GLFW
echo Installing glfw3, glad and opengl...
%VCPKG_EXE% install glfw3 glad

if %errorlevel% neq 0 (
	echo [ERROR] glfw3 installation failed
	exit /b 1
)

echo [SUCCESS] glfw3, glad and opengl installed successfully.
endlocal
pause
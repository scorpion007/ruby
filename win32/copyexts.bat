@echo off
REM Run from base Ruby dir, not win32.
REM
if "%1" == "" (
    echo Copies built extension static libs to destination of choice.
    echo usage: %0 ^<dest^>
    exit /b
)

for /f %%f in ('dir /s /b ext\*.lib enc\*.lib ^| findstr /v /c:"-test-"') ^
do copy /y %%f %1\

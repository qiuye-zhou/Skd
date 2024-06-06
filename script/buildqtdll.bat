@echo off
chcp 65001 > nul

cd ..\x64\Release
windeployqt.exe Skd.exe
if errorlevel 1 goto 0
if errorlevel 0 goto 1
:0
echo "未配置qt相关的环境变量"
goto exit

:1
echo "项目需要的qt相关dll打包完成"
goto exit

:exit
pause
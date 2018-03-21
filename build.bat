@echo off

cmake src -Bbuild
cmake --build build

pause #don't close the console
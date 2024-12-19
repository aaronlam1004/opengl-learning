@echo off

set SRC_DIR=../src
set SRCS=%SRC_DIR%/main.cpp %SRC_DIR%/glad.c

set INCLUDE_DIR=../include

set LIB_DIR=../lib
set LIBS=opengl32.lib %LIB_DIR%/glfw3dll.lib

mkdir build
pushd build
cl -Zi /EHsc %SRCS% /I %INCLUDE_DIR% /link %LIBS%
xcopy ..\lib\glfw3.dll . /d
popd

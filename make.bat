@echo off

rem sources
set SRC_DIR=../src
set SRCS=%SRC_DIR%/main.cpp
set SRCS=%SRCS% %SRC_DIR%/glad.c
set SRCS=%SRCS% %SRC_DIR%/Buffers.cpp
set SRCS=%SRCS% %SRC_DIR%/Shader.cpp
set SRCS=%SRCS% %SRC_DIR%/Texture.cpp

rem includes
set INCLUDE_DIR=../include

rem libs
set LIB_DIR=../lib
set LIBS=opengl32.lib %LIB_DIR%/glfw3dll.lib

mkdir build
pushd build
cl -Zi /EHsc %SRCS% /I %INCLUDE_DIR% /link %LIBS%
xcopy ..\lib\glfw3.dll . /d
popd

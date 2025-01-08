@echo off

rem sources
set SRC_DIR=../src
set SRCS=%SRC_DIR%/main.cpp
set SRCS=%SRCS% %SRC_DIR%/glad.c
set SRCS=%SRCS% %SRC_DIR%/Buffers.cpp
set SRCS=%SRCS% %SRC_DIR%/Shader.cpp
set SRCS=%SRCS% %SRC_DIR%/Texture.cpp
set SRCS=%SRCS% %SRC_DIR%/Camera.cpp

rem includes
set INCLUDE_DIR=../include

rem libs
set LIB_DIR=../lib
set LIBS=opengl32.lib %LIB_DIR%/glfw3dll.lib

rem debug
if "%1%"=="nonabstract" (
   echo == NON ABSTRACTION ENABLED ==
   set CPP_NONABSTRACT_FLAGS=/DNONABSTRACT
)

mkdir build
pushd build
cl -Zi %CPP_NONABSTRACT_FLAGS% /EHsc %SRCS% /I %INCLUDE_DIR% /link %LIBS%
xcopy ..\lib\glfw3.dll . /d
popd

@echo off

rem sources
set SRC_DIR=../src

if "%1%"=="lighting" (
    echo == BUILDING [%1%] ==
    set SRCS=%SRC_DIR%/lighting/main.cpp
) else (
    echo == BUILDING [intro] ==
    set SRCS=%SRC_DIR%/intro/main.cpp
)

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
set NON_ABSTRACT=F
if "%1%"=="--nonabstract" set NON_ABSTRACT=T
if "%2%"=="--nonabstract" set NON_ABSTRACT=T
if "%NON_ABSTRACT%"=="T" (
    echo == NON ABSTRACTION ENABLED ==
    set CPP_NONABSTRACT_FLAGS=/DNONABSTRACT
)

mkdir build
pushd build
cl -Zi %CPP_NONABSTRACT_FLAGS% /EHsc %SRCS% /I %INCLUDE_DIR% /link %LIBS%
xcopy ..\lib\glfw3.dll . /d
popd

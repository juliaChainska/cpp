cmake_minimum_required(VERSION 3.21)
project(projektc4)

set(CMAKE_CXX_STANDARD 23)

add_executable(projektc4 main.cpp Password.cpp Password.h PasswordCoder.cpp PasswordCoder.h Timestamp.cpp Timestamp.h)

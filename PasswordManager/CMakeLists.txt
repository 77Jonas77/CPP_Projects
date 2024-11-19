cmake_minimum_required(VERSION 3.25)
project(PasswordManager)

set(CMAKE_CXX_STANDARD 17)

add_executable(PasswordManager main.cpp PasswordManager.h PasswordManager.cpp Password.cpp Password.h UserInterface.cpp UserInterface.h FileManager.cpp FileManager.h Encryptor.cpp Encryptor.h Program.cpp Program.h Utilities.cpp Utilities.h)

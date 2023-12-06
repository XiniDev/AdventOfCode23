# Bundle & App stuff
APP_NAME = Advent Of Code 2023
APP_VERSION = 1.0
APP_INFO = © 2023 by Xini

# Check for the presence of MinGW or MSVC
ifeq ($(OS),Windows_NT)
    # assume 64 bit mingw
    COMPILER = MINGW64
else
    $(error This Makefile is intended for Windows 64bit MINGW systems only)
endif

# lib and include
LIB = -L lib
INCLUDE = -I include

# Compiler and flags
ifeq ($(COMPILER),MINGW64)
    CC = x86_64-w64-mingw32-g++
    RM_CMD = rm -Force
else
    $(error Unsupported compiler: $(COMPILER))
endif

# Compile flags
CFLAGS = -std=c++20 -Wall $(INCLUDE)
LDFLAGS = $(LIB)

# Source and object file
SRCS := $(wildcard *.cpp ./lib/*.cpp)
OBJS := $(patsubst %.cpp,%.o,$(SRCS))
# Target executable
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
    ifeq ($(COMPILER),MINGW64)
		powershell "echo $(TARGET).exe $(OBJS) | $(RM_CMD)"
    else
        $(error Unsupported compiler: $(COMPILER))
    endif

.PHONY: all clean

# g++ -I src/mingw/x86_64/include -L src/mingw/x86_64/lib -o main main.cpp -lmingw32 -lSDL2main -lSDL2
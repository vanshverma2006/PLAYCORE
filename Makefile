# Makefile for Raylib project

# Compiler
CXX = clang++

# Compiler flags
CXXFLAGS = -std=c++17 -I/opt/homebrew/include -I/opt/homebrew/include/raylib

# Linker flags
LDFLAGS = -L/opt/homebrew/lib -lraylib -framework OpenGL -framework Cocoa -framework IOKit

# Source and output
SRC =prac.cpp
OUT = prac

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT) $(LDFLAGS)

clean:
	rm -f prac
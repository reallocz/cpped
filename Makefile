CC=g++
CFLAGS=-std=c++14 -Wall

TARGET=bin/debug

SRCDIR=src
BINDIR=bin
OBJ=bin/obj
INCLUDE=-Iinclude

LINKS=-lSDL2 -lSDL2main -lSDL2_ttf

#GUI=$(wildcard src/gui/*.cpp)
#CORE=$(wildcard src/core/*.cpp)
ALL=$(wildcard src/**/*.cpp)
MAIN=$(wildcard src/*.cpp)

SRC=$(MAIN) $(ALL)

OBJECTS=$(addprefix $(OBJ)/, $(patsubst %.cpp, %.o, $(SRC)))

$(OBJ)/%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<

dirs:
	@mkdir -p $(OBJ)/src $(OBJ)/src/gui $(OBJ)/src/core

clean:
	@rm -rf $(BINDIR)
	make dirs

all: ctags dirs $(OBJECTS)
	@$(CC) $(CFLAGS) $(INCLUDE) -o $(TARGET) $(OBJECTS) $(LINKS)

r:
	@./$(TARGET)

ctags:
	@ctags -R -f

.PHONY: all clean

.DEFAULT_GOAL := all

CC=g++
CFLAGS=-std=c++14 -Wall

TARGET=bin/debug

SRCDIR=src
BINDIR=bin
OBJ=bin/obj
INCLUDE=-Iinclude -I/usr/include/freetype2

LINKS=-lSDL2 -lSDL2main -lfreetype

##### SRC
GUI=$(wildcard src/gui/*.cpp)
CORE=$(wildcard src/core/*.cpp)
MAIN=$(wildcard src/*.cpp)

SRC=$(MAIN) $(GUI) $(CORE)
OBJECTS=$(addprefix $(OBJ)/, $(patsubst %.cpp, %.o, $(SRC)))
##### / SRC

##### TESTS
# NOTE: Add individual files to $(TESTSRC)
TEST=$(wildcard src/tests/*.cpp)
TESTSRC=$(TEST) src/core/string.cpp 
TESTOBJECTS=$(addprefix $(OBJ)/, $(patsubst %.cpp, %.o, $(TESTSRC)))
TESTINCLUDE=-I/usr/src/googletest/googletest
##### / TESTS


$(OBJ)/%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<

dirs:
	@mkdir -p $(OBJ)/src $(OBJ)/src/gui $(OBJ)/src/core $(OBJ)/src/tests

clean:
	@rm -rf $(BINDIR)
	make dirs

all: ctags dirs $(OBJECTS)
	@$(CC) $(CFLAGS) $(INCLUDE) -o $(TARGET) $(OBJECTS) $(LINKS)

#Run
r:
	@./$(TARGET)


ctags:
	@ctags -R -f

#Test
test: $(TESTOBJECTS)
	@$(CC) $(CFLAGS) $(INCLUDE) -o bin/test $(TESTOBJECTS) $(TESTINCLUDE) -pthread /usr/src/googletest/googletest/src/gtest-all.cc


#Run tests
rt:
	@./bin/test


.PHONY: all clean test

.DEFAULT_GOAL := all

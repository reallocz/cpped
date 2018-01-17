### Instructions
# Adding files to nested dirs
# 	- Create a new VAR in ###SRC->Vars
# 	- Add new VAR to ###SRC->Aggregate->SRC list
# 	- Create add dir to the `dirs` recipie
#

CC=g++
CFLAGS=-std=c++14 -Wall

TARGET=bin/debug

SRCDIR=src
BINDIR=bin
OBJ=bin/obj
INCLUDE=-Iinclude -I/usr/include/freetype2

LINKS=-lSDL2 -lSDL2main -lfreetype
EXLINKS = -lGL -lX11 -lpthread -lXrandr -lXi -ldl

##### SRC
# Vars
GUI=$(wildcard src/gui/*.cpp)
GL=$(wildcard src/gui/gl/*.cpp)
CORE=$(wildcard src/core/*.cpp)
MAIN=$(wildcard src/*.cpp)

# Aggregate
SRC=$(MAIN) $(GUI) $(CORE) $(GL)
OBJECTS=$(addprefix $(OBJ)/, $(patsubst %.cpp, %.o, $(SRC)))
##### / SRC

##### TESTS
# NOTE: Add individual files to $(TESTSRC)
TEST=$(wildcard src/tests/*.cpp)
TESTSRC=$(TEST) src/core/string.cpp 
TESTOBJECTS=$(addprefix $(OBJ)/, $(patsubst %.cpp, %.o, $(TESTSRC)))
TESTINCLUDE=-I/usr/src/googletest/googletest
##### / TESTS

### EXTERNAL
EXOBJECTS=bin/obj/src/glad.o
### / External


external:
	gcc -g $(INCLUDE) -c -o bin/obj/src/glad.o src/glad.c $(EXLINKS)

$(OBJ)/%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<

dirs:
	@mkdir -p $(OBJ)/src $(OBJ)/src/gui $(OBJ)/src/gui/gl $(OBJ)/src/core $(OBJ)/src/tests

clean:
	@rm -rf $(BINDIR)
	make dirs

all: ctags dirs external $(OBJECTS)
	@$(CC) $(CFLAGS) $(INCLUDE) -o $(TARGET) $(EXOBJECTS) $(OBJECTS) $(LINKS) $(EXLINKS)

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


.PHONY: all clean test external

.DEFAULT_GOAL := all

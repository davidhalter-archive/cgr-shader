# -------------------------------------------------------
# Makefile to build scene
# -------------------------------------------------------

CC=g++
CFLAGS=-c -O2 -Wall
SRC_DIR = src/
BUILD_DIR = build/
LDFLAGS=-lGL -lGLU -lSDL -lGLEW
SOURCES=$(wildcard $(SRC_DIR)*.cpp)
HEADER_FILES=$(patsubst %.cpp, %.h, $(SOURCES))
#OBJECTS=$(SOURCES:.cpp=.o)
OBJECTS=$(patsubst $(SRC_DIR)%.cpp,$(BUILD_DIR)%.o,$(SOURCES))
EXECUTABLE=main.bin

DEPENDENCIES=$(patsubst %.o, %.d, $(OBJECTS))

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $(BUILD_DIR)$@

# The -MP adds a 'phony' target for all prerequisite headers
# to stop 'make' complaining if you remove a header
# MMD generate dependency files
# The odd-looking 'sed' line makes the .d file itself 
# depend on relevant source and headers
$(BUILD_DIR)%.o: $(SRC_DIR)%.cpp
	$(CC) -MMD -MP $(CFLAGS) $< -o $@
	@sed -i -e '1s,\($*\)\.o[ :]*,\1.o $(BUILD_DIR)$*.d: ,' $(BUILD_DIR)$*.d


# The include stops 'make' complaining if any .d files 
# are not found (eg. on initial build).
-include $(DEPENDENCIES)

clean:
	rm build/*

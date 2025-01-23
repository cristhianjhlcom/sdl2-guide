DEBUG = 1

INCLUDE_DIR = include
SOURCE_DIR = src
BUILD_DIR = build

CC_STD = c11
CC = gcc
CC_WARNINGS = -Wall -Wextra -Wpedantic
CC_FLAGS = $(CC_WARNINGS) -std=$(CC_STD) -I $(INCLUDE_DIR)
CL_FLAGS = -lSDL2 -lSDL2_image -lSDL2_mixer

ifeq ($(DEBUG), 1)
    CC_FLAGS += -g -DDEBUG
    OUTPUT = output
else
    CC_FLAGS += -O2
    OUTPUT = app
endif

CC_COMPILER = $(CC) $(CC_FLAGS)

CC_SOURCES = $(wildcard $(SOURCE_DIR)/*.c)
CC_OBJECTS = $(patsubst $(SOURCE_DIR)/%.c, $(BUILD_DIR)/%.o, $(CC_SOURCES))

all: create build

create:
	@mkdir -p build

build: $(CC_OBJECTS)
	$(CC_COMPILER) $(CC_OBJECTS) $(CL_FLAGS) -o $(BUILD_DIR)/$(OUTPUT)
	@echo "\n🎮 Game compilation completed..."

run:
	./$(BUILD_DIR)/$(OUTPUT)

install:
	sudo apt-get update
	sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev
	sudo apt-get install bear

clean:
	@echo "\n🗑️  Cleaning build directory...\n"
	rm -rf $(BUILD_DIR)/*

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c
	$(CC_COMPILER) -c $< -o $@

.PHONY: create build execute clean


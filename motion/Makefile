DEBUG = 1

# cp D:/SDL2-2.30.11/bin/*.dll build/

INCLUDE_DIR = include
SOURCE_DIR = src
BUILD_DIR = build
SDL_DIR = D:/SDL2-2.30.11

CC_STD = c2x
CC = gcc
CC_WARNINGS = -Wall -Werror -Wpedantic
CC_FLAGS = $(CC_WARNINGS) -std=$(CC_STD) -I $(INCLUDE_DIR) -I$(SDL_DIR)/include/SDL2
CL_FLAGS = -L$(SDL_DIR)/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

ifeq ($(DEBUG), 1)
    CC_FLAGS += -g -DDEBUG
    OUTPUT = output.exe
else
    CC_FLAGS += -O2
    OUTPUT = app.exe
endif

CC_COMPILER = $(CC) $(CC_FLAGS)

CC_SOURCES = $(wildcard $(SOURCE_DIR)/*.c)
CC_OBJECTS = $(patsubst $(SOURCE_DIR)/%.c, $(BUILD_DIR)/%.o, $(CC_SOURCES))

all: create build run

create:
	@echo "Create build folder"
	@mkdir -p build
	@echo "SUCCESS!"

build: $(CC_OBJECTS)
	@echo "Copy SDL2 binaries files into build folder"
	@cp $(SDL_DIR)/bin/*.dll $(BUILD_DIR)/
	@echo "SUCCESS!"
	$(CC_COMPILER) $(CC_OBJECTS) $(CL_FLAGS) -o $(BUILD_DIR)/$(OUTPUT)

run:
	@echo "Run executable 'output.exe' file"
	@echo "SUCCESS!"
	@./$(BUILD_DIR)/$(OUTPUT)

clean:
	@echo "Clean the build folder"
	@rm -rf $(BUILD_DIR)/*
	@echo "SUCCESS!"

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c
	$(CC_COMPILER) -c $< -o $@

.PHONY: create build execute clean

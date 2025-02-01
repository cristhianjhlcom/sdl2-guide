DEBUG = 1

INCLUDE_DIR = include
SOURCE_DIR = src
BUILD_DIR = build

CC_STD = c2x
CC = gcc
CC_WARNINGS = -Wall -Werror -Wpedantic
CC_FLAGS = $(CC_WARNINGS) -std=$(CC_STD) -I $(INCLUDE_DIR) -I$(INCLUDE_DIR)/SDL2
CL_FLAGS = -L$(INCLUDE_DIR)/lib -lmingw32 -lSDL2main -lSDL2

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
	@mkdir -p build

build: $(CC_OBJECTS)
	$(CC_COMPILER) $(CC_OBJECTS) $(CL_FLAGS) -o $(BUILD_DIR)/$(OUTPUT)

run:
	./$(BUILD_DIR)/$(OUTPUT)

clean:
	rm -rf $(BUILD_DIR)/*

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c
	$(CC_COMPILER) -c $< -o $@

.PHONY: create build execute clean

SRC_DIR = src
BIN_DIR = bin

ENTRY_FILE = main.cpp
BIN_FILE = gng

CC = g++

CC_FLAGS = -w -lSDL2 -lSDL2_image -lSDL2_ttf
WATCH_FLAGS = -w src/**/* -w assets/**/* -e cpp,c,h,hpp -x "make run || exit 0"

NODE_PACKAGE_MANAGER = pnpm # For Watch Mode

build:
	$(CC) $(SRC_DIR)/$(ENTRY_FILE) -o $(BIN_DIR)/$(BIN_FILE) $(CC_FLAGS)

run: build
	exec $(BIN_DIR)/$(BIN_FILE)

watch:
	$(NODE_PACKAGE_MANAGER) nodemon $(WATCH_FLAGS)
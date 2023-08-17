SRC_DIR = src
BIN_DIR = bin

ENTRY_FILE = main.cpp
BIN_FILE = gng

CC = g++

CC_FLAGS = -w -lSDL2 -lSDL2_image -lSDL2_ttf

build:
	$(CC) $(SRC_DIR)/$(ENTRY_FILE) -o $(BIN_DIR)/$(BIN_FILE) $(CC_FLAGS)

zip:
	cp -r bin/ zip-build/
	cp -r ../assets/ zip-build/
	zip -r zip-build.zip zip-build/

run: build
	exec $(BIN_DIR)/$(BIN_FILE)
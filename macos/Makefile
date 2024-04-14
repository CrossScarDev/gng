SRC_DIR = src
BIN_DIR = bin

ENTRY_FILE = main.cpp
TARGET = gng

TARGET_MACOS_VERSION=10.13

CC = o64-clang++

CC_FLAGS = -w -std=gnu++14 `x86_64-apple-darwin23-pkg-config --cflags --libs SDL2_image SDL2_ttf sdl2` -D__MACOS__ -mmacosx-version-min=$(TARGET_MACOS_VERSION)

all: assets build

build:
	$(CC) $(SRC_DIR)/$(ENTRY_FILE) -o $(BIN_DIR)/$(TARGET) $(CC_FLAGS)

dev: assets build
	@echo Dev not implemented yet!

clean: clean-assets
	@echo clean ...
	@rm -rf bin/*

include ../assets.mk

SRC_DIR = src
BIN_DIR = bin

ENTRY_FILE = main.cpp
TARGET = gng.exe

CC = win-clang++

CC_FLAGS = -w -std=gnu++14 `pkg-config --cflags --libs SDL2_image SDL2_ttf sdl2` -D__WINDOWS__

all: assets build zip

build:
	$(CC) $(SRC_DIR)/$(ENTRY_FILE) -o $(BIN_DIR)/$(TARGET) $(CC_FLAGS)

dev: assets build
	wine bin/gng.exe

zip:
	@mkdir /tmp/gng-windows/
	@echo Copying Libs...
	@cp libs/* /tmp/gng-windows/
	@echo Copying $(TARGET)...
	@cp $(BIN_DIR)/$(TARGET) /tmp/gng-windows/
	@echo Zipping Files...
	@zip -r -j gng-windows.zip /tmp/gng-windows/
	@echo Cleaning...
	@rm -rf /tmp/gng-windows/

clean: clean-assets
	@echo clean ...
	@rm -rf bin/* gng-windows.zip

include ../assets.mk
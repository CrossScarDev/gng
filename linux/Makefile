SRC_DIR = src
BIN_DIR = bin

ENTRY_FILE = main.cpp
TARGET = gng

CC = g++

CC_FLAGS = -w -std=gnu++14 `pkg-config --cflags --libs SDL2_image SDL2_ttf sdl2`

all: assets build deb-pkg

build:
	$(CC) $(SRC_DIR)/$(ENTRY_FILE) -o $(BIN_DIR)/$(TARGET) $(CC_FLAGS)

deb-pkg:
	cp bin/$(TARGET) deb/usr/bin/
	mkdir -p deb/usr/share/icons/hicolor/128x128/apps/
	cp ../assets/logo.png deb/usr/share/icons/hicolor/128x128/apps/$(TARGET).png
	dpkg-deb --build deb
	@mv deb.deb $(TARGET).deb

dev: assets build
	exec $(BIN_DIR)/$(TARGET)

clean: clean-assets
	@echo clean ...
	@rm -fr bin/* deb/usr/bin/* *.deb deb/usr/share/icons/hicolor/128x128/apps/$(TARGET).png

include ../assets.mk

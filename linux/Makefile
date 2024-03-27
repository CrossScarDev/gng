SRC_DIR = src
BIN_DIR = bin

ENTRY_FILE = main.cpp
TARGET = gng

CC = g++

CC_FLAGS = -w -std=gnu++14 `pkg-config --cflags --libs SDL2_image SDL2_ttf sdl2` -D__LINUX__

PKG_DIR = pkg

all: assets build deb-pkg

include ../assets.mk

build:
	$(CC) $(SRC_DIR)/$(ENTRY_FILE) -o $(BIN_DIR)/$(TARGET) $(CC_FLAGS)

install:
	cp $(BIN_DIR)/$(TARGET) /usr/bin/$(TARGET)
	cp $(PKG_DIR)/$(TARGET).desktop /usr/share/applications/$(TARGET).desktop
	cp $(ASSETS_DIR)/logo.png /usr/share/icons/hicolor/128x128/apps/gng.png

deb-pkg:
	fpm \
		--force \
		-s dir -t deb \
		--name gng \
		--version 0.0.0 \
		--architecture native \
		--depends libsdl2-dev --depends libsdl2-image-dev --depends libsdl2-ttf-dev \
		--url "https://crossscardev.itch.io/gng" \
		--maintainer "CrossScar <crossscarcs@gmail.com>" \
		$(BIN_DIR)/$(TARGET)=/usr/bin/$(TARGET) \
		$(PKG_DIR)/$(TARGET).desktop=/usr/share/applications/$(TARGET).desktop \
		$(ASSETS_DIR)/logo.png=/usr/share/icons/hicolor/128x128/apps/gng.png

dev: assets build
	exec $(BIN_DIR)/$(TARGET)

clean: clean-assets
	@echo clean ...
	@rm -rf bin/* *.deb

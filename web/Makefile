SRC_DIR = src
BIN_DIR = bin

ENTRY_FILE = main.cpp
BIN_FILE = index.html

CC = em++

SHELL_FILE = shell.html

CC_FLAGS = --shell-file $(SHELL_FILE) -w -g -lm --bind -s ALLOW_MEMORY_GROWTH -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s USE_SDL_TTF=2 -s SDL2_IMAGE_FORMATS='["png"]' --preload-file ../assets/ --use-preload-plugins

all: build zip

build:
	$(CC) $(SRC_DIR)/$(ENTRY_FILE) -o $(BIN_DIR)/$(BIN_FILE) $(CC_FLAGS)

zip:
	zip -r gng-web.zip bin/

clean:
	@echo clean ...
	@rm -fr gng-web.zip bin/*
include config.mk

APP_NAME = pong
BUILD_DIR = ./bin
C_FILES = ./src/*.c

APP_INCLUDES:= -I$(SDL_INCLUDE_PATH)
APP_LINKERS:= -L$(SDL_LIB_PATH) -lSDL2

all: build run

build:
	mkdir -p $(BUILD_DIR)
	clang -o $(BUILD_DIR)/$(APP_NAME) $(C_FILES) $(APP_INCLUDES) $(APP_LINKERS)

run:
	./$(BUILD_DIR)/$(APP_NAME)
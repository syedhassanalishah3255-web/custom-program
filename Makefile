# Makefile for Sunset Rangers Game

# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -D_DEFAULT_SOURCE
LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Directories
SRC_DIR = .
BUILD_DIR = build

# Targets
MENU = menu
GAMEPLAY = gameplay
MAIN_GAME = sunset_rangers

# Source files
MENU_SRC = $(SRC_DIR)/menu.c
GAMEPLAY_SRC = $(SRC_DIR)/gameplay.c
MAIN_SRC = $(SRC_DIR)/main.c

# Object files
MENU_OBJ = $(BUILD_DIR)/menu.o
GAMEPLAY_OBJ = $(BUILD_DIR)/gameplay.o
MAIN_OBJ = $(BUILD_DIR)/main.o

# Default target
all: $(BUILD_DIR) $(MENU) $(GAMEPLAY) $(MAIN_GAME)

# Create build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Build menu
$(MENU): $(MENU_OBJ)
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

# Build gameplay
$(GAMEPLAY): $(GAMEPLAY_OBJ)
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

# Compile menu
$(MENU_OBJ): $(MENU_SRC)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile gameplay
$(GAMEPLAY_OBJ): $(GAMEPLAY_SRC)
	$(CC) $(CFLAGS) -c $< -o $@

# Build main launcher
$(MAIN_GAME): $(MAIN_OBJ)
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

# Compile main launcher
$(MAIN_OBJ): $(MAIN_SRC)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)
	rm -f $(MENU) $(GAMEPLAY) $(MAIN_GAME)

# Run menu
run-menu: $(MENU)
	./$(MENU)

# Run gameplay
run-gameplay: $(GAMEPLAY)
	./$(GAMEPLAY)

# Run main game launcher
run: $(MAIN_GAME) $(MENU) $(GAMEPLAY)
	./$(MAIN_GAME)

# Help
help:
	@echo "Sunset Rangers Game - Build System"
	@echo "==================================="
	@echo "Available targets:"
	@echo "  all          - Build all components (default)"
	@echo "  menu         - Build menu only"
	@echo "  gameplay     - Build gameplay only"
	@echo "  clean        - Remove build artifacts"
	@echo "  run          - Build and run main game launcher"
	@echo "  run-menu     - Build and run menu"
	@echo "  run-gameplay - Build and run gameplay"
	@echo "  help         - Show this help message"

.PHONY: all clean run run-menu run-gameplay help

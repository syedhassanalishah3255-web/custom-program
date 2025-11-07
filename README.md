# Sunset Rangers - Western Action Game

A thrilling western-themed action game built with Raylib in C.

## Features

- **Cinematic Menu System**: Animated background with western-themed UI
- **Action Gameplay**: Run, jump, crouch, and shoot your way through the desert
- **Smooth Animations**: Character sprite animations for all actions
- **Scrolling Background**: Dynamic parallax scrolling desert scenery

## Prerequisites

To build and run this game, you need:
- GCC compiler
- Raylib library installed
- Linux/Unix environment (for current build system)

**Quick Start**: If you're new to Raylib, see [QUICKSTART.md](QUICKSTART.md) for detailed installation instructions.

### Installing Raylib

On Ubuntu/Debian:
```bash
sudo apt-get install libraylib-dev
```

Or build from source: [Raylib Installation Guide](https://github.com/raysan5/raylib#build-and-installation)

## Building the Game

The project includes a Makefile for easy building:

```bash
# Build all components
make all

# Build specific components
make menu
make gameplay

# Clean build artifacts
make clean
```

## Running the Game

```bash
# Run the main game launcher
make run

# Or run components individually
make run-menu
make run-gameplay

# Or run the executables directly
./sunset_rangers  # Main launcher
./menu            # Menu only
./gameplay        # Gameplay only
```

## Controls

**Gameplay:**
- ← / → : Move left/right
- SPACE : Jump
- ↓ : Crouch
- F : Shoot

**Menu:**
- ↑ / ↓ : Navigate menu
- ENTER : Select option
- Mouse : Click to select

## Project Structure

```
custom-program/
├── assets/          # Background images
├── character/       # Character sprite sheets
├── fonts/          # Western-themed fonts
├── images/         # UI elements (logo, icons, etc.)
├── menu.c          # Menu system
├── gameplay.c      # Main gameplay
├── main.c          # Game launcher
├── Makefile        # Build system
└── README.md       # This file
```

## Development

This is an ongoing game project. Future enhancements may include:
- Enemy AI
- Multiple levels
- Sound effects and music
- Save/load system
- Settings menu

## License

This project is open source and available for educational purposes.


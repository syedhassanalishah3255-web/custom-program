# Quick Start Guide - Sunset Rangers

## For Users Without Raylib

If you don't have Raylib installed, follow these steps:

### Option 1: Install Raylib from Package Manager (Ubuntu/Debian)

Unfortunately, Raylib is not available in default Ubuntu repositories. You'll need to use Option 2.

### Option 2: Build Raylib from Source (Recommended)

```bash
# Install build dependencies
sudo apt-get update
sudo apt-get install -y build-essential git cmake libasound2-dev mesa-common-dev libx11-dev libxrandr-dev libxi-dev xorg-dev libgl1-mesa-dev libglu1-mesa-dev

# Clone and build Raylib
git clone https://github.com/raysan5/raylib.git
cd raylib/src
make PLATFORM=PLATFORM_DESKTOP

# Install Raylib
sudo make install

# Go back to game directory
cd ../..
```

### Option 3: Using Pre-built Binaries

If someone has already compiled the game on a similar system, you can use the pre-built executables:
```bash
./menu      # Run menu
./gameplay  # Run gameplay
```

## Building the Game

Once Raylib is installed:

```bash
# Run the setup script
./setup.sh

# Or manually:
make all
```

## Running the Game

```bash
# Main launcher (recommended)
make run

# Or individual components:
./menu
./gameplay
```

## Troubleshooting

### Error: "raylib.h: No such file or directory"
- Raylib is not installed. Follow the installation steps above.

### Error: "cannot find -lraylib"
- Raylib library is not in the system library path.
- Try running: `sudo ldconfig` after installing Raylib.

### Error: "undefined reference to 'glXxx'"
- Missing OpenGL libraries.
- Install with: `sudo apt-get install libgl1-mesa-dev libglu1-mesa-dev`

## System Requirements

- **OS**: Linux (tested on Ubuntu 20.04+)
- **Compiler**: GCC 7.5+
- **Graphics**: OpenGL 3.3+ compatible GPU
- **RAM**: 512MB minimum
- **Disk**: 50MB for game + 100MB for Raylib

## Controls Reference

### Menu
- **Up/Down Arrow**: Navigate options
- **Enter**: Select
- **Mouse**: Click to select
- **ESC**: Close game

### Gameplay
- **Left/Right Arrow**: Move
- **Space**: Jump
- **Down Arrow**: Crouch
- **F**: Shoot
- **ESC**: Return to menu

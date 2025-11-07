#!/bin/bash
# Setup script for Sunset Rangers game
# This script installs dependencies and builds the game

set -e

echo "=========================================="
echo "  Sunset Rangers - Setup Script"
echo "=========================================="
echo ""

# Check for required tools
echo "[1/4] Checking for required tools..."
if ! command -v gcc &> /dev/null; then
    echo "Error: GCC compiler not found. Please install build-essential."
    exit 1
fi
echo "  ✓ GCC found"

# Check for raylib
echo ""
echo "[2/4] Checking for Raylib..."
if ! pkg-config --exists raylib 2>/dev/null; then
    echo "  Raylib not found in system packages."
    echo "  You need to install Raylib manually:"
    echo "  - Visit: https://github.com/raysan5/raylib"
    echo "  - Or run: git clone https://github.com/raysan5/raylib.git && cd raylib/src && make && sudo make install"
    echo ""
    echo "  Note: This game requires Raylib to compile and run."
    exit 1
else
    echo "  ✓ Raylib found"
fi

# Build the game
echo ""
echo "[3/4] Building the game..."
make clean
make all

# Verify build
echo ""
echo "[4/4] Verifying build..."
if [ -f "./menu" ] && [ -f "./gameplay" ] && [ -f "./sunset_rangers" ]; then
    echo "  ✓ All components built successfully!"
    echo ""
    echo "=========================================="
    echo "  Setup Complete!"
    echo "=========================================="
    echo ""
    echo "You can now run the game with:"
    echo "  make run        # Main launcher"
    echo "  make run-menu   # Menu only"
    echo "  make run-gameplay # Gameplay only"
    echo ""
else
    echo "  ✗ Build verification failed"
    exit 1
fi

#!/bin/bash
# Verification script for Sunset Rangers game structure
# This script verifies the project structure without requiring Raylib

echo "=========================================="
echo "  Sunset Rangers - Project Verification"
echo "=========================================="
echo ""

ERRORS=0

# Function to check file exists
check_file() {
    if [ -f "$1" ]; then
        echo "  ✓ $1"
    else
        echo "  ✗ $1 - MISSING"
        ERRORS=$((ERRORS+1))
    fi
}

# Function to check directory exists
check_dir() {
    if [ -d "$1" ]; then
        echo "  ✓ $1/"
        return 0
    else
        echo "  ✗ $1/ - MISSING"
        ERRORS=$((ERRORS+1))
        return 1
    fi
}

# Check source files
echo "[1/5] Checking source files..."
check_file "menu.c"
check_file "gameplay.c"
check_file "main.c"
check_file "Makefile"

# Check asset directories
echo ""
echo "[2/5] Checking asset directories..."
check_dir "assets"
check_dir "character"
check_dir "fonts"
check_dir "images"

# Check key assets
echo ""
echo "[3/5] Checking key assets..."
if check_dir "assets"; then
    check_file "assets/idea.png"
fi

if check_dir "character"; then
    check_file "character/Idle.png"
    check_file "character/Run.png"
    check_file "character/Jump.png"
    check_file "character/Shot.png"
fi

if check_dir "fonts"; then
    check_file "fonts/western.ttf"
fi

if check_dir "images"; then
    check_file "images/logo.png"
    check_file "images/revolver.png"
fi

# Check documentation
echo ""
echo "[4/5] Checking documentation..."
check_file "README.md"
check_file "QUICKSTART.md"
check_file ".gitignore"

# Check for build artifacts that should be ignored
echo ""
echo "[5/5] Checking for unwanted build artifacts..."
BUILD_CLEAN=true
if [ -f "menu.exe" ] || [ -f "gameplay.exe" ] || [ -f "sunset_rangers.exe" ]; then
    echo "  ✗ .exe files found (should be in .gitignore)"
    BUILD_CLEAN=false
    ERRORS=$((ERRORS+1))
else
    echo "  ✓ No .exe files in repository"
fi

if [ -d "build" ]; then
    echo "  ✗ build/ directory exists (should be in .gitignore)"
    BUILD_CLEAN=false
    ERRORS=$((ERRORS+1))
else
    echo "  ✓ No build/ directory"
fi

# Summary
echo ""
echo "=========================================="
if [ $ERRORS -eq 0 ]; then
    echo "  ✓ Verification PASSED!"
    echo "  All required files are present."
    echo ""
    echo "  Next steps:"
    echo "  1. Install Raylib (see QUICKSTART.md)"
    echo "  2. Run ./setup.sh to build the game"
    echo "  3. Run 'make run' to play!"
else
    echo "  ✗ Verification FAILED!"
    echo "  Found $ERRORS error(s)"
    echo ""
    echo "  Please ensure all required files are present."
fi
echo "=========================================="

exit $ERRORS

#!/bin/bash
# Simple test script to verify the game framework
# This runs basic checks without requiring graphical output

set -e

echo "Running Sunset Rangers Test Suite..."
echo ""

# Test 1: Verify project structure
echo "Test 1: Project Structure"
./verify.sh
echo ""

# Test 2: Check Makefile syntax
echo "Test 2: Makefile Syntax"
if make -n all > /dev/null 2>&1; then
    echo "  ✓ Makefile syntax is valid"
else
    echo "  ✗ Makefile has syntax errors"
    exit 1
fi
echo ""

# Test 3: Check that source files have basic structure
echo "Test 3: Source Code Structure"

# Check for main function in files
if grep -q "int main(void)" menu.c; then
    echo "  ✓ menu.c has main function"
else
    echo "  ✗ menu.c missing main function"
    exit 1
fi

if grep -q "int main(void)" gameplay.c; then
    echo "  ✓ gameplay.c has main function"
else
    echo "  ✗ gameplay.c missing main function"
    exit 1
fi

if grep -q "int main(void)" main.c; then
    echo "  ✓ main.c has main function"
else
    echo "  ✗ main.c missing main function"
    exit 1
fi

# Check for required includes
if grep -q '#include "raylib.h"' gameplay.c; then
    echo "  ✓ gameplay.c includes raylib.h"
else
    echo "  ✗ gameplay.c missing raylib.h"
    exit 1
fi

echo ""
echo "Test 4: Asset Path Correctness"

# Check that gameplay.c uses correct paths for character sprites
if grep -q 'character/Idle.png' gameplay.c; then
    echo "  ✓ gameplay.c uses correct character sprite paths"
else
    echo "  ✗ gameplay.c has incorrect character sprite paths"
    exit 1
fi

echo ""
echo "=========================================="
echo "  ✓ All Tests PASSED!"
echo "=========================================="
echo ""
echo "Note: Full compilation test requires Raylib installation."
echo "Run ./setup.sh to install dependencies and build the game."

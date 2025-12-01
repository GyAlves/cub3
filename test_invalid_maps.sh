#!/bin/bash

# Colors
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

MAPS_DIR="./maps/maps_invalid"
PROGRAM="./cub3D"

success_count=0
fail_count=0

echo "Testing all invalid maps (should all return errors)..."
echo "======================================================"
echo ""

success_maps=()
fail_maps=()

# Check if directory exists
if [ ! -d "$MAPS_DIR" ]; then
    echo "Directory $MAPS_DIR not found!"
    exit 1
fi

for map_file in "$MAPS_DIR"/*; do
    # Skip if not a file
    if [ ! -f "$map_file" ]; then
        continue
    fi

    map_name=$(basename "$map_file")

    # Run the program - invalid maps should exit with error code 1
    timeout 1s "$PROGRAM" "$map_file" > /dev/null 2>&1
    exit_code=$?

    # For invalid maps, we expect exit code 1 (error)
    # Exit code 124 means timeout (BAD - program should reject immediately)
    # Exit code 0 means success (BAD - should have rejected the map)
    if [ $exit_code -eq 1 ]; then
        echo -e "${GREEN}✓${NC} $map_name (correctly rejected)"
        success_maps+=("$map_name")
        ((success_count++))
    else
        echo -e "${RED}✗${NC} $map_name (exit code: $exit_code - should be 1)"
        fail_maps+=("$map_name")
        ((fail_count++))
    fi
done

echo ""
echo "======================================================"
echo "Results: $success_count correctly rejected, $fail_count incorrectly accepted"
echo ""

if [ $fail_count -gt 0 ]; then
    echo "Maps that should have been rejected but weren't:"
    for map in "${fail_maps[@]}"; do
        echo "  - $map"
    done
fi

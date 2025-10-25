#!/bin/bash

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
MAGENTA='\033[0;35m'
NC='\033[0m' # No Color

# Counters
TOTAL=0
PASSED=0
FAILED=0

# Executable
CUB3D="./cub3D"
MAPS_DIR="./maps"

# Check if executable exists
if [ ! -f "$CUB3D" ]; then
    echo -e "${RED}Error: $CUB3D not found!${NC}"
    echo "Compile your project first with 'make'"
    exit 1
fi

# Check if maps directory exists
if [ ! -d "$MAPS_DIR" ]; then
    echo -e "${RED}Error: $MAPS_DIR directory not found!${NC}"
    exit 1
fi

# Function to print header
print_header() {
    echo -e "\n${BLUE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
    echo -e "${BLUE}  $1${NC}"
    echo -e "${BLUE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
}

# Function to test a map
test_map() {
    local map_file=$1
    local expected=$2  # "valid" or "invalid"
    
    TOTAL=$((TOTAL + 1))
    
    local filename=$(basename "$map_file")
    echo -e "\n${YELLOW}[$TOTAL]${NC} Testing: ${BLUE}$filename${NC}"
    
    # Run the program and capture output
    output=$($CUB3D "$map_file" 2>&1)
    exit_code=$?
    
    # Check result
    if [ "$expected" == "valid" ]; then
        # For valid maps, program should NOT print "Error"
        if echo "$output" | grep -iq "error"; then
            echo -e "  ${RED}✗ FAILED${NC} - Map should be valid but got error:"
            echo -e "  ${MAGENTA}$output${NC}"
            FAILED=$((FAILED + 1))
        else
            echo -e "  ${GREEN}✓ PASSED${NC}"
            PASSED=$((PASSED + 1))
        fi
    else
        # For invalid maps, program SHOULD print "Error"
        if echo "$output" | grep -iq "error"; then
            echo -e "  ${GREEN}✓ PASSED${NC} - Correctly detected error"
            # Show only first line of error
            first_error=$(echo "$output" | grep -i "error" | head -1)
            echo -e "  ${MAGENTA}→ $first_error${NC}"
            PASSED=$((PASSED + 1))
        else
            echo -e "  ${RED}✗ FAILED${NC} - Should have detected error but didn't"
            FAILED=$((FAILED + 1))
        fi
    fi
}

# Function to print summary
print_summary() {
    echo -e "\n${BLUE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
    echo -e "${BLUE}  SUMMARY${NC}"
    echo -e "${BLUE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
    
    local percentage=0
    if [ $TOTAL -gt 0 ]; then
        percentage=$((PASSED * 100 / TOTAL))
    fi
    
    echo -e "Total tests:  ${YELLOW}$TOTAL${NC}"
    echo -e "Passed:       ${GREEN}$PASSED${NC}"
    echo -e "Failed:       ${RED}$FAILED${NC}"
    echo -e "Success rate: ${YELLOW}$percentage%${NC}"
    
    if [ $FAILED -eq 0 ]; then
        echo -e "\n${GREEN}╔═══════════════════════════════════════════════════╗${NC}"
        echo -e "${GREEN}║   🎉  ALL TESTS PASSED! CONGRATULATIONS! 🎉      ║${NC}"
        echo -e "${GREEN}╚═══════════════════════════════════════════════════╝${NC}"
    else
        echo -e "\n${RED}╔═══════════════════════════════════════════════════╗${NC}"
        echo -e "${RED}║      ❌  SOME TESTS FAILED - CHECK ABOVE  ❌       ║${NC}"
        echo -e "${RED}╚═══════════════════════════════════════════════════╝${NC}"
    fi
    echo ""
}

# Start testing
clear
echo -e "${GREEN}╔═══════════════════════════════════════════════════╗${NC}"
echo -e "${GREEN}║              CUB3D MAP TESTER                     ║${NC}"
echo -e "${GREEN}╚═══════════════════════════════════════════════════╝${NC}"

# ============================================
# VALID MAPS
# ============================================
print_header "TESTING VALID MAPS"

if [ -d "$MAPS_DIR/maps_valid" ]; then
    for map in "$MAPS_DIR/maps_valid"/*.cub; do
        if [ -f "$map" ]; then
            test_map "$map" "valid"
        fi
    done
else
    # Test individual valid maps
    [ -f "$MAPS_DIR/13_map.cub" ] && test_map "$MAPS_DIR/13_map.cub" "valid"
    [ -f "$MAPS_DIR/14_map.cub" ] && test_map "$MAPS_DIR/14_map.cub" "valid"
    [ -f "$MAPS_DIR/31_map.cub" ] && test_map "$MAPS_DIR/31_map.cub" "valid"
    [ -f "$MAPS_DIR/52_map.cub" ] && test_map "$MAPS_DIR/52_map.cub" "valid"
fi

# ============================================
# INVALID MAPS - FILE ERRORS
# ============================================
print_header "FILE & EXTENSION ERRORS"

[ -f "$MAPS_DIR/0_map_error_extension.ber" ] && \
    test_map "$MAPS_DIR/0_map_error_extension.ber" "invalid"

[ -f "$MAPS_DIR/[X]1.3_map_error_empty_file.cub" ] && \
    test_map "$MAPS_DIR/[X]1.3_map_error_empty_file.cub" "invalid"

# ============================================
# INVALID MAPS - MAP CONTENT
# ============================================
print_header "MAP CONTENT ERRORS"

[ -f "$MAPS_DIR/1_map_error_invalidchar.cub" ] && \
    test_map "$MAPS_DIR/1_map_error_invalidchar.cub" "invalid"

[ -f "$MAPS_DIR/1.2_map_error_wrong_map_content.cub" ] && \
    test_map "$MAPS_DIR/1.2_map_error_wrong_map_content.cub" "invalid"

[ -f "$MAPS_DIR/1.4_map_error_unidentified_content.cub" ] && \
    test_map "$MAPS_DIR/1.4_map_error_unidentified_content.cub" "invalid"

[ -f "$MAPS_DIR/1.5_map_error_unidentified_content.cub" ] && \
    test_map "$MAPS_DIR/1.5_map_error_unidentified_content.cub" "invalid"

[ -f "$MAPS_DIR/1.5_map_error_invalidmap.cub" ] && \
    test_map "$MAPS_DIR/1.5_map_error_invalidmap.cub" "invalid"

[ -f "$MAPS_DIR/4_map_error_element_after_map.cub" ] && \
    test_map "$MAPS_DIR/4_map_error_element_after_map.cub" "invalid"

# ============================================
# INVALID MAPS - WALL ERRORS
# ============================================
print_header "WALL & ENCLOSURE ERRORS"

for map in "$MAPS_DIR"/2*_map_error*.cub "$MAPS_DIR"/2.*_map_error*.cub; do
    [ -f "$map" ] && test_map "$map" "invalid"
done

# ============================================
# INVALID MAPS - PLAYER ERRORS
# ============================================
print_header "PLAYER ERRORS"

[ -f "$MAPS_DIR/3_map_error_2players.cub" ] && \
    test_map "$MAPS_DIR/3_map_error_2players.cub" "invalid"

[ -f "$MAPS_DIR/[X]3.2_map_error_2players.cub" ] && \
    test_map "$MAPS_DIR/[X]3.2_map_error_2players.cub" "invalid"

[ -f "$MAPS_DIR/3.1_map_error_missing_player.cub" ] && \
    test_map "$MAPS_DIR/3.1_map_error_missing_player.cub" "invalid"

# ============================================
# INVALID MAPS - TEXTURE ERRORS
# ============================================
print_header "TEXTURE ERRORS"

for map in "$MAPS_DIR"/5*_map_error*.cub "$MAPS_DIR"/5.*_map_error*.cub; do
    [ -f "$map" ] && test_map "$map" "invalid"
done

[ -f "$MAPS_DIR/[X]5.4_map_error_extra_tex.cub" ] && \
    test_map "$MAPS_DIR/[X]5.4_map_error_extra_tex.cub" "invalid"

[ -f "$MAPS_DIR/[X]7_map_error_opentexture.cub" ] && \
    test_map "$MAPS_DIR/[X]7_map_error_opentexture.cub" "invalid"

[ -f "$MAPS_DIR/[X]7.2_map_error_opentexture.cub" ] && \
    test_map "$MAPS_DIR/[X]7.2_map_error_opentexture.cub" "invalid"

[ -f "$MAPS_DIR/[X]82_map_error_opentexture.cub" ] && \
    test_map "$MAPS_DIR/[X]82_map_error_opentexture.cub" "invalid"

[ -f "$MAPS_DIR/[X]9_map_error_texture.cub" ] && \
    test_map "$MAPS_DIR/[X]9_map_error_texture.cub" "invalid"

# ============================================
# INVALID MAPS - COLOR ERRORS
# ============================================
print_header "COLOR ERRORS"

for map in "$MAPS_DIR"/6*_map_error*.cub "$MAPS_DIR"/6.*_map_error*.cub; do
    [ -f "$map" ] && test_map "$map" "invalid"
done

# ============================================
# OTHER ERROR MAPS
# ============================================
print_header "OTHER ERRORS"

[ -f "$MAPS_DIR/32_map_error.cub" ] && \
    test_map "$MAPS_DIR/32_map_error.cub" "invalid"

[ -f "$MAPS_DIR/30_map_error copy.cub" ] && \
    test_map "$MAPS_DIR/30_map_error copy.cub" "invalid"

# Print final summary
print_summary

# Exit with appropriate code
if [ $FAILED -eq 0 ]; then
    exit 0
else
    exit 1
fi
#!/bin/bash

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Counters
PASSED=0
FAILED=0
TOTAL=0

# Print header
echo -e "${BLUE}================================${NC}"
echo -e "${BLUE}   SO_LONG MEMORY LEAK TESTER   ${NC}"
echo -e "${BLUE}================================${NC}\n"

# Check if valgrind is installed
if ! command -v valgrind &> /dev/null; then
    echo -e "${RED}Error: valgrind is not installed${NC}"
    echo "Install with: sudo apt-get install valgrind"
    exit 1
fi

# Check if executables exist
if [ ! -f "./so_long" ]; then
    echo -e "${RED}Error: so_long executable not found${NC}"
    echo "Run 'make' first"
    exit 1
fi

echo -e "${YELLOW}Testing mandatory version (so_long)...${NC}\n"

# Function to run test
run_test() {
    local test_name=$1
    local map_file=$2
    local should_fail=$3
    local program=$4
    
    TOTAL=$((TOTAL + 1))
    
    echo -e "${BLUE}Test $TOTAL: $test_name${NC}"
    
    # Run valgrind
    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
             --error-exitcode=42 --log-file=valgrind_output.txt \
             ./$program "$map_file" 2>&1 > /dev/null
    
    VALGRIND_EXIT=$?
    
    # Check for leaks in valgrind output
    LEAKS=$(grep "definitely lost" valgrind_output.txt | grep -o '[0-9,]* bytes' | head -1)
    STILL_REACHABLE=$(grep "still reachable" valgrind_output.txt | grep -o '[0-9,]* bytes' | head -1)
    
    if [ $VALGRIND_EXIT -eq 42 ]; then
        echo -e "${RED}  ✗ FAILED - Valgrind detected errors${NC}"
        cat valgrind_output.txt
        FAILED=$((FAILED + 1))
    elif [[ "$LEAKS" != "0 bytes" && ! -z "$LEAKS" ]]; then
        echo -e "${RED}  ✗ FAILED - Memory leaks detected: $LEAKS${NC}"
        grep "definitely lost" valgrind_output.txt
        FAILED=$((FAILED + 1))
    else
        echo -e "${GREEN}  ✓ PASSED - No memory leaks${NC}"
        PASSED=$((PASSED + 1))
    fi
    
    echo ""
    rm -f valgrind_output.txt
}

# Test: No arguments
echo -e "${BLUE}Test $((TOTAL + 1)): No arguments${NC}"
TOTAL=$((TOTAL + 1))
./so_long 2>&1 > /dev/null
if [ $? -eq 1 ]; then
    echo -e "${GREEN}  ✓ PASSED - Correctly rejected${NC}\n"
    PASSED=$((PASSED + 1))
else
    echo -e "${RED}  ✗ FAILED - Should reject no arguments${NC}\n"
    FAILED=$((FAILED + 1))
fi

# Test: Too many arguments
echo -e "${BLUE}Test $((TOTAL + 1)): Too many arguments${NC}"
TOTAL=$((TOTAL + 1))
./so_long map1 map2 2>&1 > /dev/null
if [ $? -eq 1 ]; then
    echo -e "${GREEN}  ✓ PASSED - Correctly rejected${NC}\n"
    PASSED=$((PASSED + 1))
else
    echo -e "${RED}  ✗ FAILED - Should reject multiple arguments${NC}\n"
    FAILED=$((FAILED + 1))
fi

# Test invalid maps
run_test "Invalid extension (.txt)" "test_maps/invalid_extension.txt" true "so_long"
run_test "Empty file" "test_maps/empty.ber" true "so_long"
run_test "No wall on top" "test_maps/no_wall_top.ber" true "so_long"
run_test "No wall on bottom" "test_maps/no_wall_bottom.ber" true "so_long"
run_test "No wall on left" "test_maps/no_wall_left.ber" true "so_long"
run_test "No wall on right" "test_maps/no_wall_right.ber" true "so_long"
run_test "Not rectangular" "test_maps/not_rectangular.ber" true "so_long"
run_test "No player" "test_maps/no_player.ber" true "so_long"
run_test "Two players" "test_maps/two_players.ber" true "so_long"
run_test "No exit" "test_maps/no_exit.ber" true "so_long"
run_test "Two exits" "test_maps/two_exits.ber" true "so_long"
run_test "No collectible" "test_maps/no_collectible.ber" true "so_long"
run_test "Invalid character" "test_maps/invalid_char.ber" true "so_long"
run_test "Exit not reachable" "test_maps/not_playable_exit.ber" true "so_long"
run_test "Collectible not reachable" "test_maps/not_playable_collectible.ber" true "so_long"

# Test valid maps (these will timeout on window, so we'll just check memory at init)
run_test "Valid simple map" "test_maps/valid_simple.ber" false "so_long"
run_test "Valid map with collectibles" "test_maps/valid_with_collectibles.ber" false "so_long"

# Test bonus if it exists
if [ -f "./so_long_bonus" ]; then
    echo -e "\n${YELLOW}Testing bonus version (so_long_bonus)...${NC}\n"
    
    run_test "Bonus: No arguments" "" true "so_long_bonus"
    run_test "Bonus: Invalid extension" "test_maps/invalid_extension.txt" true "so_long_bonus"
    run_test "Bonus: Empty file" "test_maps/empty.ber" true "so_long_bonus"
    run_test "Bonus: Not rectangular" "test_maps/not_rectangular.ber" true "so_long_bonus"
    run_test "Bonus: Invalid character (no X)" "test_maps/invalid_char.ber" true "so_long_bonus"
    run_test "Bonus: Valid with enemy" "test_maps/bonus_valid_with_enemy.ber" false "so_long_bonus"
    run_test "Bonus: Valid with multiple enemies" "test_maps/bonus_valid_multiple_enemies.ber" false "so_long_bonus"
fi

# Test non-existent file
echo -e "${BLUE}Test $((TOTAL + 1)): Non-existent file${NC}"
TOTAL=$((TOTAL + 1))
./so_long test_maps/non_existent.ber 2>&1 > /dev/null
if [ $? -eq 1 ]; then
    echo -e "${GREEN}  ✓ PASSED - Correctly rejected${NC}\n"
    PASSED=$((PASSED + 1))
else
    echo -e "${RED}  ✗ FAILED - Should reject non-existent file${NC}\n"
    FAILED=$((FAILED + 1))
fi

# Print summary
echo -e "${BLUE}================================${NC}"
echo -e "${BLUE}          TEST SUMMARY          ${NC}"
echo -e "${BLUE}================================${NC}"
echo -e "Total tests: $TOTAL"
echo -e "${GREEN}Passed: $PASSED${NC}"
echo -e "${RED}Failed: $FAILED${NC}"

if [ $FAILED -eq 0 ]; then
    echo -e "\n${GREEN}🎉 ALL TESTS PASSED! No memory leaks detected!${NC}\n"
    exit 0
else
    echo -e "\n${RED}❌ Some tests failed. Please fix the issues.${NC}\n"
    exit 1
fi

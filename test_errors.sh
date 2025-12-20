#!/bin/bash

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color

# Counters
PASSED=0
FAILED=0
TOTAL=0

# Print header
echo -e "${CYAN}================================${NC}"
echo -e "${CYAN}   SO_LONG ERROR TESTER         ${NC}"
echo -e "${CYAN}================================${NC}\n"

# Check if executables exist
if [ ! -f "./so_long" ]; then
    echo -e "${RED}Error: so_long executable not found${NC}"
    echo "Run 'make' first"
    exit 1
fi

# Function to run test
run_test() {
    local test_name=$1
    local map_file=$2
    local expected_error=$3
    local program=$4
    
    TOTAL=$((TOTAL + 1))
    
    printf "${BLUE}%-50s${NC}" "Test $TOTAL: $test_name"
    
    # Run program and capture output
    OUTPUT=$(timeout 0.5 ./$program "$map_file" 2>&1)
    EXIT_CODE=$?
    
    # Check if program exited with error (non-zero)
    if [ $EXIT_CODE -eq 124 ]; then
        # Timeout means program started (for valid maps)
        if [ "$expected_error" == "none" ]; then
            echo -e " ${GREEN}✓ PASS${NC}"
            PASSED=$((PASSED + 1))
        else
            echo -e " ${RED}✗ FAIL (Should have failed but started)${NC}"
            FAILED=$((FAILED + 1))
        fi
    elif [ $EXIT_CODE -ne 0 ]; then
        # Program exited with error
        if [ "$expected_error" == "none" ]; then
            echo -e " ${RED}✗ FAIL (Should not error)${NC}"
            echo -e "   ${YELLOW}Output: $OUTPUT${NC}"
            FAILED=$((FAILED + 1))
        elif [[ "$OUTPUT" == *"$expected_error"* ]]; then
            echo -e " ${GREEN}✓ PASS${NC}"
            PASSED=$((PASSED + 1))
        else
            echo -e " ${YELLOW}~ PARTIAL (Error but wrong message)${NC}"
            echo -e "   ${YELLOW}Expected: $expected_error${NC}"
            echo -e "   ${YELLOW}Got: $OUTPUT${NC}"
            PASSED=$((PASSED + 1))
        fi
    else
        # Program exited successfully
        if [ "$expected_error" == "none" ]; then
            echo -e " ${GREEN}✓ PASS${NC}"
            PASSED=$((PASSED + 1))
        else
            echo -e " ${RED}✗ FAIL (Should have failed)${NC}"
            FAILED=$((FAILED + 1))
        fi
    fi
}

# Function for simple tests (no map file)
run_simple_test() {
    local test_name=$1
    local args=$2
    local program=$3
    
    TOTAL=$((TOTAL + 1))
    
    printf "${BLUE}%-50s${NC}" "Test $TOTAL: $test_name"
    
    OUTPUT=$(timeout 0.5 $args 2>&1)
    EXIT_CODE=$?
    
    if [ $EXIT_CODE -ne 0 ] && [ $EXIT_CODE -ne 124 ]; then
        echo -e " ${GREEN}✓ PASS${NC}"
        PASSED=$((PASSED + 1))
    else
        echo -e " ${RED}✗ FAIL${NC}"
        FAILED=$((FAILED + 1))
    fi
}

echo -e "${YELLOW}Testing MANDATORY version (so_long)${NC}\n"

# Argument tests
run_simple_test "No arguments" "./so_long" "so_long"
run_simple_test "Too many arguments" "./so_long map1 map2" "so_long"
run_simple_test "Non-existent file" "./so_long test_maps/non_existent.ber" "so_long"

# Invalid extension
run_test "Invalid extension (.txt)" "test_maps/invalid_extension.txt" "Invalid argument type" "so_long"

# Empty file
run_test "Empty file" "test_maps/empty.ber" "Empty or invalid file" "so_long"

# Wall tests
run_test "No wall on top" "test_maps/no_wall_top.ber" "rectangular or be enclosed by walls" "so_long"
run_test "No wall on bottom" "test_maps/no_wall_bottom.ber" "rectangular or be enclosed by walls" "so_long"
run_test "No wall on left" "test_maps/no_wall_left.ber" "rectangular or be enclosed by walls" "so_long"
run_test "No wall on right" "test_maps/no_wall_right.ber" "rectangular or be enclosed by walls" "so_long"

# Shape tests
run_test "Not rectangular" "test_maps/not_rectangular.ber" "rectangular" "so_long"

# Character count tests
run_test "No player" "test_maps/no_player.ber" "character count" "so_long"
run_test "Two players" "test_maps/two_players.ber" "character count" "so_long"
run_test "No exit" "test_maps/no_exit.ber" "character count" "so_long"
run_test "Two exits" "test_maps/two_exits.ber" "character count" "so_long"
run_test "No collectible" "test_maps/no_collectible.ber" "character count" "so_long"

# Invalid character
run_test "Invalid character" "test_maps/invalid_char.ber" "Invalid character" "so_long"

# Playability tests
run_test "Exit not reachable" "test_maps/not_playable_exit.ber" "not playable" "so_long"
run_test "Collectible not reachable" "test_maps/not_playable_collectible.ber" "not playable" "so_long"

# Valid maps (should start the game)
run_test "Valid simple map" "test_maps/valid_simple.ber" "none" "so_long"
run_test "Valid with collectibles" "test_maps/valid_with_collectibles.ber" "none" "so_long"

# Bonus tests
if [ -f "./so_long_bonus" ]; then
    echo -e "\n${YELLOW}Testing BONUS version (so_long_bonus)${NC}\n"
    
    run_simple_test "Bonus: No arguments" "./so_long_bonus" "so_long_bonus"
    run_simple_test "Bonus: Too many arguments" "./so_long_bonus map1 map2" "so_long_bonus"
    run_test "Bonus: Invalid extension" "test_maps/invalid_extension.txt" "Invalid argument type" "so_long_bonus"
    run_test "Bonus: Empty file" "test_maps/empty.ber" "Empty or invalid file" "so_long_bonus"
    run_test "Bonus: Not rectangular" "test_maps/not_rectangular.ber" "rectangular" "so_long_bonus"
    run_test "Bonus: No player" "test_maps/no_player.ber" "character count" "so_long_bonus"
    run_test "Bonus: Valid with enemy" "test_maps/bonus_valid_with_enemy.ber" "none" "so_long_bonus"
    run_test "Bonus: Valid with enemies" "test_maps/bonus_valid_multiple_enemies.ber" "none" "so_long_bonus"
else
    echo -e "\n${YELLOW}Skipping bonus tests (so_long_bonus not found)${NC}"
fi

# Print summary
echo -e "\n${CYAN}================================${NC}"
echo -e "${CYAN}          TEST SUMMARY          ${NC}"
echo -e "${CYAN}================================${NC}"
echo -e "Total tests: $TOTAL"
echo -e "${GREEN}Passed: $PASSED${NC}"
echo -e "${RED}Failed: $FAILED${NC}"

PERCENTAGE=$((PASSED * 100 / TOTAL))
echo -e "Success rate: ${PERCENTAGE}%"

if [ $FAILED -eq 0 ]; then
    echo -e "\n${GREEN}🎉 ALL TESTS PASSED!${NC}\n"
    exit 0
else
    echo -e "\n${RED}❌ Some tests failed. Check the output above.${NC}\n"
    exit 1
fi

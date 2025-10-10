#!/bin/bash

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color

TIMEOUT=60
PHILO="./philo"
LOG_DIR="stress_test_logs"
TEST_DELAY=2  # Delay between tests in seconds

# Test counter
TOTAL_TESTS=0
PASSED_TESTS=0
FAILED_TESTS=0

# Create log directory
mkdir -p "$LOG_DIR"
rm -f "$LOG_DIR"/*  # Clean old logs

print_header() {
    echo -e "\n${BLUE}╔════════════════════════════════════════════════════════════╗${NC}"
    printf "${BLUE}║${NC} %-58s ${BLUE}║${NC}\n" "$1"
    echo -e "${BLUE}╚════════════════════════════════════════════════════════════╝${NC}"
}

print_test() {
    echo -e "\n${CYAN}┌────────────────────────────────────────────────────────────┐${NC}"
    printf "${CYAN}│${NC} ${YELLOW}Test %2d:${NC} %-48s ${CYAN}│${NC}\n" "$TOTAL_TESTS" "$1"
    printf "${CYAN}│${NC} ${YELLOW}Command:${NC} %-48s ${CYAN}│${NC}\n" "$2"
    echo -e "${CYAN}└────────────────────────────────────────────────────────────┘${NC}"
}

save_log() {
    local test_num="$1"
    local test_name="$2"
    local cmd="$3"
    local output="$4"
    local result="$5"
    
    local log_file="$LOG_DIR/test_${test_num}.log"
    
    {
        echo "TEST #$test_num - $result"
        echo "Test Name: $test_name"
        echo "Command: $cmd"
        echo "Date: $(date)"
        echo "----------------------------------------"
        echo "$output"
    } > "$log_file"
}

run_test() {
    local test_name="$1"
    local cmd="$2"
    local expected="$3"
    local check_func="$4"
    
    ((TOTAL_TESTS++))
    print_test "$test_name" "$cmd"
    
    # Run with timeout and capture output
    output=$(timeout $TIMEOUT $cmd 2>&1)
    exit_code=$?
    
    # Check if timeout occurred
    if [ $exit_code -eq 124 ]; then
        if [ "$expected" = "timeout" ]; then
            echo -e "${GREEN}✓ OK${NC} - Program ran for full timeout (no deaths detected)"
            ((PASSED_TESTS++))
        else
            echo -e "${RED}✗ KO${NC} - Program timed out unexpectedly"
            save_log "$TOTAL_TESTS" "$test_name" "$cmd" "$output" "FAILED"
            ((FAILED_TESTS++))
        fi
        sleep $TEST_DELAY
        return
    fi
    
    # Call custom check function if provided
    if [ -n "$check_func" ]; then
        # Capture the result before calling check function
        local temp_passed=$PASSED_TESTS
        $check_func "$output" "$expected"
        
        # If test failed (PASSED_TESTS didn't increase), save log
        if [ $PASSED_TESTS -eq $temp_passed ]; then
            save_log "$TOTAL_TESTS" "$test_name" "$cmd" "$output" "FAILED"
        fi
    fi
    
    sleep $TEST_DELAY
}

check_invalid_args() {
    local output="$1"
    # Should exit immediately with error (no output or error message)
    if [ -z "$output" ] || echo "$output" | grep -qiE "(error|invalid|usage)"; then
        echo -e "${GREEN}✓ OK${NC} - Invalid arguments rejected"
        ((PASSED_TESTS++))
    else
        echo -e "${RED}✗ KO${NC} - Should reject invalid arguments"
        ((FAILED_TESTS++))
    fi
}

check_single_philo() {
    local output="$1"
    # Single philosopher should take one fork and die
    if echo "$output" | grep -q "has taken a fork" && echo "$output" | grep -q "died"; then
        echo -e "${GREEN}✓ OK${NC} - Single philosopher took fork and died"
        ((PASSED_TESTS++))
    else
        echo -e "${RED}✗ KO${NC} - Single philosopher behavior incorrect"
        ((FAILED_TESTS++))
    fi
}

check_all_ate() {
    local output="$1"
    if echo "$output" | grep -q "ate enough"; then
        if echo "$output" | grep -q "died"; then
            echo -e "${RED}✗ KO${NC} - Philosopher died before all ate enough"
            ((FAILED_TESTS++))
        else
            echo -e "${GREEN}✓ OK${NC} - All philosophers ate enough, no deaths"
            ((PASSED_TESTS++))
        fi
    else
        echo -e "${RED}✗ KO${NC} - All philosophers should have eaten enough"
        ((FAILED_TESTS++))
    fi
}

check_should_die() {
    local output="$1"
    if echo "$output" | grep -q "died"; then
        echo -e "${GREEN}✓ OK${NC} - Philosopher died as expected"
        ((PASSED_TESTS++))
    else
        echo -e "${RED}✗ KO${NC} - Philosopher should die (insufficient time_die)"
        ((FAILED_TESTS++))
    fi
}

check_no_death() {
    local output="$1"
    if echo "$output" | grep -q "died"; then
        echo -e "${RED}✗ KO${NC} - Philosopher died unexpectedly"
        ((FAILED_TESTS++))
    else
        echo -e "${GREEN}✓ OK${NC} - No deaths during timeout period"
        ((PASSED_TESTS++))
    fi
}

# Check if philo executable exists
if [ ! -f "$PHILO" ]; then
    echo -e "${RED}Error: $PHILO not found. Please compile first.${NC}"
    exit 1
fi

print_header "PHILOSOPHERS STRESS TESTS"
echo -e "${CYAN}Focus: Critical edge cases and boundary conditions${NC}"
echo -e "${CYAN}Failed test logs: ${YELLOW}$LOG_DIR/${NC}\n"

# ============================================================================
print_header "INVALID ARGUMENTS"
# ============================================================================

run_test "No arguments" \
    "$PHILO" \
    "invalid" \
    "check_invalid_args"

run_test "Negative philosophers" \
    "$PHILO -5 800 200 200" \
    "invalid" \
    "check_invalid_args"

run_test "Zero philosophers" \
    "$PHILO 0 800 200 200" \
    "invalid" \
    "check_invalid_args"

run_test "Non-numeric argument" \
    "$PHILO abc 800 200 200" \
    "invalid" \
    "check_invalid_args"

run_test "More than 200 philosophers" \
    "$PHILO 201 800 200 200" \
    "invalid" \
    "check_invalid_args"

# ============================================================================
print_header "SINGLE PHILOSOPHER"
# ============================================================================

run_test "1 philosopher must die" \
    "$PHILO 1 800 200 200" \
    "death" \
    "check_single_philo"

# ============================================================================
print_header "200 PHILOSOPHERS (EVEN) - CRITICAL"
# ============================================================================

run_test "200 philos - CRITICAL: 130ms (60+60+10)" \
    "$PHILO 200 130 60 60" \
    "timeout" \
    "check_no_death"

run_test "200 philos - SHOULD DIE: 119ms" \
    "$PHILO 200 119 60 60" \
    "death" \
    "check_should_die"

run_test "200 philos - 10 meals at critical timing" \
    "$PHILO 200 130 60 60 10" \
    "all_ate" \
    "check_all_ate"

# ============================================================================
print_header "199 PHILOSOPHERS (ODD) - CRITICAL"
# ============================================================================

run_test "199 philos - CRITICAL: 190ms (60+60+10+60)" \
    "$PHILO 199 190 60 60" \
    "timeout" \
    "check_no_death"

run_test "199 philos - SHOULD DIE: 179ms" \
    "$PHILO 199 179 60 60" \
    "death" \
    "check_should_die"

run_test "199 philos - 10 meals at critical timing" \
    "$PHILO 199 190 60 60 10" \
    "all_ate" \
    "check_all_ate"

# ============================================================================
print_header "OTHER CRITICAL ODD NUMBERS"
# ============================================================================

run_test "5 philos - CRITICAL: 190ms minimum" \
    "$PHILO 5 190 60 60" \
    "timeout" \
    "check_no_death"

run_test "5 philos - SHOULD DIE: 179ms" \
    "$PHILO 5 179 60 60" \
    "death" \
    "check_should_die"

run_test "101 philos - CRITICAL: 190ms" \
    "$PHILO 101 190 60 60" \
    "timeout" \
    "check_no_death"

# ============================================================================
# SUMMARY
# ============================================================================

print_header "TEST SUMMARY"
echo -e "${CYAN}┌────────────────────────────────────────────────────────────┐${NC}"
printf "${CYAN}│${NC} Total Tests: %-46s ${CYAN}│${NC}\n" "${BLUE}$TOTAL_TESTS${NC}"
printf "${CYAN}│${NC} Passed:      %-46s ${CYAN}│${NC}\n" "${GREEN}$PASSED_TESTS${NC}"
printf "${CYAN}│${NC} Failed:      %-46s ${CYAN}│${NC}\n" "${RED}$FAILED_TESTS${NC}"
echo -e "${CYAN}└────────────────────────────────────────────────────────────┘${NC}"

if [ $FAILED_TESTS -eq 0 ]; then
    echo -e "\n${GREEN}╔════════════════════════════════════════════════════════════╗${NC}"
    echo -e "${GREEN}║              🎉 ALL TESTS PASSED! 🎉                      ║${NC}"
    echo -e "${GREEN}║    Your philosophers are dining without incidents!        ║${NC}"
    echo -e "${GREEN}╚════════════════════════════════════════════════════════════╝${NC}\n"
    rm -rf "$LOG_DIR"  # Clean up if all passed
    exit 0
else
    percentage=$((PASSED_TESTS * 100 / TOTAL_TESTS))
    echo -e "\n${RED}╔════════════════════════════════════════════════════════════╗${NC}"
    echo -e "${RED}║              ❌ SOME TESTS FAILED ❌                       ║${NC}"
    printf "${RED}║${NC}           Success Rate: ${YELLOW}%d%%${NC} (%d/%d)                    ${RED}║${NC}\n" "$percentage" "$PASSED_TESTS" "$TOTAL_TESTS"
    echo -e "${RED}║                                                            ║${NC}"
    echo -e "${RED}║${NC}  Check logs in: ${YELLOW}$LOG_DIR/${NC}                           ${RED}║${NC}"
    echo -e "${RED}╚════════════════════════════════════════════════════════════╝${NC}\n"
    exit 1
fi

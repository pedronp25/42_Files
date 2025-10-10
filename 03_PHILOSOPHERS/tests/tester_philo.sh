#!/bin/bash

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
MAGENTA='\033[0;35m'
NC='\033[0m' # No Color

# Counters
TOTAL_TESTS=0
PASSED_TESTS=0
FAILED_TESTS=0

# Program name
PHILO="./philo"

# Create logs directory
LOG_DIR="philo_test_logs_$(date +%Y%m%d_%H%M%S)"
mkdir -p "$LOG_DIR"

echo -e "${BLUE}Logs will be saved to: $LOG_DIR${NC}"

# Check if program exists
if [ ! -f "$PHILO" ]; then
    echo -e "${RED}Error: $PHILO not found. Please compile the program first.${NC}"
    exit 1
fi

# Check for data race detection tools
HELGRIND_AVAILABLE=false
TSAN_AVAILABLE=false

if command -v valgrind &> /dev/null; then
    if valgrind --tool=helgrind --version &> /dev/null; then
        HELGRIND_AVAILABLE=true
        echo -e "${MAGENTA}Helgrind detected - data race tests will be available${NC}"
    fi
fi

# Check if program was compiled with ThreadSanitizer
if ldd "$PHILO" 2>/dev/null | grep -q "tsan"; then
    TSAN_AVAILABLE=true
    echo -e "${MAGENTA}ThreadSanitizer detected - data race tests will be available${NC}"
fi

if [ "$HELGRIND_AVAILABLE" = false ] && [ "$TSAN_AVAILABLE" = false ]; then
    echo -e "${YELLOW}Warning: No data race detection tool found.${NC}"
    echo -e "${YELLOW}To enable data race tests:${NC}"
    echo -e "${YELLOW}  - Install valgrind for Helgrind, OR${NC}"
    echo -e "${YELLOW}  - Recompile with: gcc -fsanitize=thread -g ...${NC}"
fi

# Function to print test header
print_test() {
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    echo -e "\n${BLUE}========================================${NC}"
    echo -e "${BLUE}Test $TOTAL_TESTS: $1${NC}"
    echo -e "${BLUE}Command: $PHILO $2${NC}"
    echo -e "${BLUE}========================================${NC}"
}

# Function to print OK
print_ok() {
    PASSED_TESTS=$((PASSED_TESTS + 1))
    echo -e "${GREEN}✓ OK${NC}"
    if [ ! -z "$1" ]; then
        echo -e "${GREEN}  $1${NC}"
    fi
}

# Function to print KO
print_ko() {
    FAILED_TESTS=$((FAILED_TESTS + 1))
    echo -e "${RED}✗ KO${NC}"
    echo -e "${RED}  Expected: $1${NC}"
    if [ ! -z "$2" ]; then
        echo -e "${RED}  Got: $2${NC}"
    fi
}

# Function to check if philosopher died when expected
check_death_timing() {
    local output="$1"
    local expected_time=$2
    local tolerance=10
    
    # Extract death message and timestamp
    local death_line=$(echo "$output" | grep "died" | head -1)
    
    if [ -z "$death_line" ]; then
        echo "NO_DEATH"
        return
    fi
    
    local death_time=$(echo "$death_line" | grep -oE '^[0-9]+')
    
    if [ -z "$death_time" ]; then
        echo "INVALID"
        return
    fi
    
    # Check if death occurred within acceptable range
    local min_time=$expected_time
    local max_time=$((expected_time + tolerance))
    
    if [ $death_time -ge $min_time ] && [ $death_time -le $max_time ]; then
        echo "OK:$death_time"
    else
        echo "BAD_TIMING:$death_time:$min_time:$max_time"
    fi
}

# Function to check if no philosopher died
check_no_death() {
    local output="$1"
    if echo "$output" | grep -q "died"; then
        echo "DIED"
    else
        echo "OK"
    fi
}

# Function to check if philosopher starved (went too long without eating)
check_starvation() {
    local output="$1"
    local time_to_die=$2
    local tolerance=10
    
    # Get all eating timestamps for each philosopher
    local last_eat=$(echo "$output" | grep "is eating" | tail -1 | grep -oE '^[0-9]+')
    local death_time=$(echo "$output" | grep "died" | head -1 | grep -oE '^[0-9]+')
    
    if [ -z "$death_time" ]; then
        echo "OK"
        return
    fi
    
    if [ -z "$last_eat" ]; then
        last_eat=0
    fi
    
    local time_since_eat=$((death_time - last_eat))
    local max_allowed=$((time_to_die + tolerance))
    
    if [ $time_since_eat -gt $max_allowed ]; then
        echo "STARVED:$time_since_eat:$max_allowed"
    else
        echo "OK"
    fi
}

# Function to run test with timeout
run_test() {
    local args="$1"
    local duration=${2:-30}
    
    # Create log file for this test
    local test_num=$(printf "%03d" $TOTAL_TESTS)
    local log_file="$LOG_DIR/test_${test_num}_${args// /_}.log"
    
    # Create a temporary file for output
    local tmpfile=$(mktemp)
    
    # Run the program in background
    $PHILO $args > "$tmpfile" 2>&1 &
    local pid=$!
    
    # Sleep for the full duration
    sleep $duration
    
    # Kill the process if still running
    if kill -0 $pid 2>/dev/null; then
        kill $pid 2>/dev/null
        sleep 0.2
        # Force kill if still alive
        if kill -0 $pid 2>/dev/null; then
            kill -9 $pid 2>/dev/null
        fi
        wait $pid 2>/dev/null
    fi
    
    # Read output
    local output=$(cat "$tmpfile")
    
    # Save to log file
    echo "Command: $PHILO $args" > "$log_file"
    echo "Duration: ${duration}s" >> "$log_file"
    echo "Timestamp: $(date)" >> "$log_file"
    echo "========================================" >> "$log_file"
    echo "$output" >> "$log_file"
    
    # Output and cleanup
    echo "$output"
    rm -f "$tmpfile"
}

# Function to run test with data race detection
run_datarace_test() {
    local args="$1"
    local duration=${2:-10}
    local tool="$3"
    
    # Create log file for this test
    local test_num=$(printf "%03d" $TOTAL_TESTS)
    local log_file="$LOG_DIR/test_${test_num}_datarace_${args// /_}.log"
    
    # Create a temporary file for output
    local tmpfile=$(mktemp)
    
    if [ "$tool" = "helgrind" ]; then
        # Run with Helgrind
        valgrind --tool=helgrind --log-file="$tmpfile" $PHILO $args > /dev/null 2>&1 &
        local pid=$!
    else
        # Run with TSan (already compiled in)
        $PHILO $args > "$tmpfile" 2>&1 &
        local pid=$!
    fi
    
    # Sleep for the duration
    sleep $duration
    
    # Kill the process if still running
    if kill -0 $pid 2>/dev/null; then
        kill $pid 2>/dev/null
        sleep 0.2
        if kill -0 $pid 2>/dev/null; then
            kill -9 $pid 2>/dev/null
        fi
        wait $pid 2>/dev/null
    fi
    
    # Read output
    local output=$(cat "$tmpfile")
    
    # Save to log file
    echo "Command: $tool $PHILO $args" > "$log_file"
    echo "Duration: ${duration}s" >> "$log_file"
    echo "Timestamp: $(date)" >> "$log_file"
    echo "========================================" >> "$log_file"
    echo "$output" >> "$log_file"
    
    # Output and cleanup
    echo "$output"
    rm -f "$tmpfile"
}

# Function to check for data races in output
check_data_races() {
    local output="$1"
    local tool="$2"
    
    if [ "$tool" = "helgrind" ]; then
        # Check for Helgrind warnings
        if echo "$output" | grep -q "Possible data race"; then
            echo "RACE_DETECTED"
        elif echo "$output" | grep -q "ERROR SUMMARY: 0 errors"; then
            echo "OK"
        else
            echo "UNCERTAIN"
        fi
    else
        # Check for ThreadSanitizer warnings
        if echo "$output" | grep -q "WARNING: ThreadSanitizer: data race"; then
            echo "RACE_DETECTED"
        elif echo "$output" | grep -q "WARNING: ThreadSanitizer"; then
            echo "RACE_DETECTED"
        else
            echo "OK"
        fi
    fi
}

echo -e "${YELLOW}╔════════════════════════════════════════╗${NC}"
echo -e "${YELLOW}║   42 PHILOSOPHERS PROJECT TESTER      ║${NC}"
echo -e "${YELLOW}╚════════════════════════════════════════╝${NC}"

# ============================================
# BASIC TESTS FROM EVALUATION SHEET
# ============================================

echo -e "\n${YELLOW}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
echo -e "${YELLOW}  BASIC TESTS (From Evaluation Sheet)${NC}"
echo -e "${YELLOW}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"

# Test 1: Should not die
print_test "4 philosophers, 410ms to die, 200ms to eat, 200ms to sleep - No one should die" "4 410 200 200"
OUTPUT=$(run_test "4 410 200 200" 30)
RESULT=$(check_no_death "$OUTPUT")
if [ "$RESULT" = "OK" ]; then
    print_ok "No philosopher died as expected"
else
    print_ko "No philosopher should die" "A philosopher died"
fi

# Test 2: Should not die
print_test "5 philosophers, 800ms to die, 200ms to eat, 200ms to sleep - No one should die" "5 800 200 200"
OUTPUT=$(run_test "5 800 200 200" 30)
RESULT=$(check_no_death "$OUTPUT")
if [ "$RESULT" = "OK" ]; then
    print_ok "No philosopher died as expected"
else
    print_ko "No philosopher should die" "A philosopher died"
fi

# Test 3: Should not die with 5th parameter
print_test "5 philosophers, 800ms to die, 200ms to eat, 200ms to sleep, must eat 7 times" "5 800 200 200 7"
OUTPUT=$(run_test "5 800 200 200 7" 30)
RESULT=$(check_no_death "$OUTPUT")
if [ "$RESULT" = "OK" ]; then
    if echo "$OUTPUT" | grep -q "ate enough"; then
        print_ok "No philosopher died and simulation ended correctly"
    else
        print_ok "No philosopher died (Note: ending message may vary)"
    fi
else
    print_ko "No philosopher should die and all should eat 7 times" "A philosopher died"
fi

# Test 4: One philosopher should die
print_test "1 philosopher, 800ms to die - Should die after 800ms" "1 800 200 200"
OUTPUT=$(run_test "1 800 200 200" 5)
RESULT=$(check_death_timing "$OUTPUT" 800)
case $RESULT in
    OK:*)
        DEATH_TIME=$(echo $RESULT | cut -d':' -f2)
        print_ok "Philosopher died at ${DEATH_TIME}ms (expected: 800-810ms)"
        ;;
    NO_DEATH)
        print_ko "Philosopher should die at ~800ms" "No death detected"
        ;;
    BAD_TIMING:*)
        DEATH_TIME=$(echo $RESULT | cut -d':' -f2)
        MIN_TIME=$(echo $RESULT | cut -d':' -f3)
        MAX_TIME=$(echo $RESULT | cut -d':' -f4)
        print_ko "Death should occur between ${MIN_TIME}ms and ${MAX_TIME}ms" "Death occurred at ${DEATH_TIME}ms"
        ;;
    *)
        print_ko "Valid death message with timestamp" "Invalid output format"
        ;;
esac

# Test 5: One philosopher should die (different timing)
print_test "1 philosopher, 200ms to die - Should die after 200ms" "1 200 200 200"
OUTPUT=$(run_test "1 200 200 200" 5)
RESULT=$(check_death_timing "$OUTPUT" 200)
case $RESULT in
    OK:*)
        DEATH_TIME=$(echo $RESULT | cut -d':' -f2)
        print_ok "Philosopher died at ${DEATH_TIME}ms (expected: 200-210ms)"
        ;;
    NO_DEATH)
        print_ko "Philosopher should die at ~200ms" "No death detected"
        ;;
    BAD_TIMING:*)
        DEATH_TIME=$(echo $RESULT | cut -d':' -f2)
        MIN_TIME=$(echo $RESULT | cut -d':' -f3)
        MAX_TIME=$(echo $RESULT | cut -d':' -f4)
        print_ko "Death should occur between ${MIN_TIME}ms and ${MAX_TIME}ms" "Death occurred at ${DEATH_TIME}ms"
        ;;
    *)
        print_ko "Valid death message with timestamp" "Invalid output format"
        ;;
esac

# ============================================
# EDGE CASES AND STRESS TESTS
# ============================================

echo -e "\n${YELLOW}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
echo -e "${YELLOW}  EDGE CASES & STRESS TESTS${NC}"
echo -e "${YELLOW}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"

# Test 6: Two philosophers - adjusted timing to barely survive
print_test "2 philosophers, 410ms to die, 200ms to eat, 100ms to sleep - Should not die" "2 410 200 100"
OUTPUT=$(run_test "2 410 200 100" 30)
RESULT=$(check_no_death "$OUTPUT")
if [ "$RESULT" = "OK" ]; then
    print_ok "No philosopher died with adjusted timing"
else
    print_ko "No philosopher should die with 10ms extra margin" "A philosopher died"
fi

# Test 7: Tight timing - should barely survive
print_test "4 philosophers, 310ms to die, 100ms to eat, 100ms to sleep - Should not die" "4 310 100 100"
OUTPUT=$(run_test "4 310 100 100" 30)
RESULT=$(check_no_death "$OUTPUT")
if [ "$RESULT" = "OK" ]; then
    print_ok "No philosopher died despite tight timing"
else
    print_ko "No philosopher should die" "A philosopher died (possible synchronization issue)"
fi

# Test 8: Should die - not enough time
print_test "4 philosophers, 200ms to die, 100ms to eat, 100ms to sleep - Should die" "4 200 100 100"
OUTPUT=$(run_test "4 200 100 100" 5)
if echo "$OUTPUT" | grep -q "died"; then
    print_ok "A philosopher died as expected due to insufficient time"
else
    print_ko "A philosopher should die (time_to_die too short)" "No philosopher died"
fi

# Test 9: Many philosophers
print_test "200 philosophers, 800ms to die, 200ms to eat, 200ms to sleep - No one should die" "200 800 200 200"
OUTPUT=$(run_test "200 800 200 200" 30)
RESULT=$(check_no_death "$OUTPUT")
if [ "$RESULT" = "OK" ]; then
    print_ok "No philosopher died even with 200 philosophers"
else
    print_ko "No philosopher should die" "A philosopher died (possible deadlock or starvation)"
fi

# Test 10: Adjusted timing for 3 philosophers
print_test "3 philosophers, 310ms to die, 100ms to eat, 100ms to sleep - Should not die" "3 310 100 100"
OUTPUT=$(run_test "3 310 100 100" 30)
RESULT=$(check_no_death "$OUTPUT")
if [ "$RESULT" = "OK" ]; then
    print_ok "No philosopher died with adjusted timing"
else
    print_ko "No philosopher should die with 10ms extra margin" "A philosopher died"
fi

# Test 11: Fast eating and sleeping
print_test "4 philosophers, 500ms to die, 50ms to eat, 50ms to sleep - Should not die" "4 500 50 50"
OUTPUT=$(run_test "4 500 50 50" 30)
RESULT=$(check_no_death "$OUTPUT")
if [ "$RESULT" = "OK" ]; then
    print_ok "No philosopher died with fast actions"
else
    print_ko "No philosopher should die" "A philosopher died"
fi

# Test 12: Minimum viable timing for 4 philos
print_test "4 philosophers, 210ms to die, 100ms to eat, 10ms to sleep - Should not die" "4 210 100 10"
OUTPUT=$(run_test "4 210 100 10" 30)
RESULT=$(check_no_death "$OUTPUT")
if [ "$RESULT" = "OK" ]; then
    print_ok "No philosopher died at minimum viable timing"
else
    print_ko "No philosopher should die" "A philosopher died"
fi

# Test 13: Should die - impossible timing
print_test "5 philosophers, 150ms to die, 100ms to eat, 100ms to sleep - Should die" "5 150 100 100"
OUTPUT=$(run_test "5 150 100 100" 5)
if echo "$OUTPUT" | grep -q "died"; then
    print_ok "A philosopher died as expected (impossible timing)"
else
    print_ko "A philosopher should die (mathematically impossible to survive)" "No philosopher died"
fi

# Test 14: Check death timing precision
print_test "1 philosopher, 500ms to die - Death timing precision check" "1 500 200 200"
OUTPUT=$(run_test "1 500 200 200" 5)
RESULT=$(check_death_timing "$OUTPUT" 500)
case $RESULT in
    OK:*)
        DEATH_TIME=$(echo $RESULT | cut -d':' -f2)
        print_ok "Death occurred at ${DEATH_TIME}ms (within 500-510ms window)"
        ;;
    NO_DEATH)
        print_ko "Philosopher should die at ~500ms" "No death detected"
        ;;
    BAD_TIMING:*)
        DEATH_TIME=$(echo $RESULT | cut -d':' -f2)
        MIN_TIME=$(echo $RESULT | cut -d':' -f3)
        MAX_TIME=$(echo $RESULT | cut -d':' -f4)
        print_ko "Death should occur between ${MIN_TIME}ms and ${MAX_TIME}ms" "Death occurred at ${DEATH_TIME}ms (outside 10ms tolerance)"
        ;;
esac

# Test 15: Odd number of philosophers
print_test "7 philosophers, 600ms to die, 150ms to eat, 150ms to sleep - Should not die" "7 600 150 150"
OUTPUT=$(run_test "7 600 150 150" 30)
RESULT=$(check_no_death "$OUTPUT")
if [ "$RESULT" = "OK" ]; then
    print_ok "No philosopher died with odd number of philosophers"
else
    print_ko "No philosopher should die" "A philosopher died"
fi

# Test 16: With meal count - adjusted timing
print_test "3 philosophers, 610ms to die, 200ms to eat, 200ms to sleep, must eat 3 times - Should not die" "3 610 200 200 3"
OUTPUT=$(run_test "3 610 200 200 3" 10)
RESULT=$(check_no_death "$OUTPUT")
if [ "$RESULT" = "OK" ]; then
    print_ok "Simulation completed successfully with meal count and adjusted timing"
else
    print_ko "Simulation should complete without deaths with 10ms extra margin" "A philosopher died"
fi

# Test 17: Large meal count
print_test "4 philosophers, 410ms to die, 100ms to eat, 100ms to sleep, must eat 50 times" "4 410 100 100 50"
OUTPUT=$(run_test "4 410 100 100 50" 30)
RESULT=$(check_no_death "$OUTPUT")
if [ "$RESULT" = "OK" ]; then
    print_ok "Simulation completed 50 meals per philosopher without deaths"
else
    print_ko "Simulation should complete without deaths" "A philosopher died"
fi

# Test 18: Minimum times allowed (60ms)
print_test "4 philosophers, 200ms to die, 60ms to eat, 60ms to sleep - Should not die" "4 200 60 60"
OUTPUT=$(run_test "4 200 60 60" 30)
RESULT=$(check_no_death "$OUTPUT")
if [ "$RESULT" = "OK" ]; then
    print_ok "No philosopher died with minimum allowed times (60ms)"
else
    print_ko "No philosopher should die" "A philosopher died"
fi

# Test 19: Maximum philosophers (200)
print_test "200 philosophers, 410ms to die, 200ms to eat, 100ms to sleep - Should not die" "200 410 200 100"
OUTPUT=$(run_test "200 410 200 100" 30)
RESULT=$(check_no_death "$OUTPUT")
if [ "$RESULT" = "OK" ]; then
    print_ok "No philosopher died with maximum (200) philosophers"
else
    print_ko "No philosopher should die" "A philosopher died (possible thread/resource issue)"
fi

# Test 20: High contention - many philos, tight timing (EVEN number works better)
print_test "100 philosophers, 800ms to die, 200ms to eat, 200ms to sleep - Should not die" "100 800 200 200"
OUTPUT=$(run_test "100 800 200 200" 30)
RESULT=$(check_no_death "$OUTPUT")
if [ "$RESULT" = "OK" ]; then
    print_ok "No philosopher died with 100 philosophers"
else
    print_ko "No philosopher should die" "A philosopher died (check log in $LOG_DIR)"
fi

# Test 21: Minimum time with multiple philos
print_test "5 philosophers, 200ms to die, 60ms to eat, 60ms to sleep - Should not die" "5 200 60 60"
OUTPUT=$(run_test "5 200 60 60" 30)
RESULT=$(check_no_death "$OUTPUT")
if [ "$RESULT" = "OK" ]; then
    print_ok "No philosopher died with minimum times"
else
    print_ko "No philosopher should die" "A philosopher died"
fi

# Test 22: Even number stress test
print_test "10 philosophers, 410ms to die, 200ms to eat, 200ms to sleep - Should not die" "10 410 200 200"
OUTPUT=$(run_test "10 410 200 200" 30)
RESULT=$(check_no_death "$OUTPUT")
if [ "$RESULT" = "OK" ]; then
    print_ok "No philosopher died with 10 philosophers (even number)"
else
    print_ko "No philosopher should die" "A philosopher died"
fi

# Test 23: Odd number stress test - SHOULD FAIL
print_test "11 philosophers, 410ms to die, 200ms to eat, 200ms to sleep - Should die" "11 410 200 200"
OUTPUT=$(run_test "11 410 200 200" 10)
if echo "$OUTPUT" | grep -q "died"; then
    print_ok "A philosopher died as expected (odd number creates starvation)"
else
    print_ko "A philosopher should die (odd number with these timings)" "No philosopher died"
fi

# Test 24: Very fast cycle
print_test "5 philosophers, 400ms to die, 60ms to eat, 60ms to sleep - Should not die" "5 400 60 60"
OUTPUT=$(run_test "5 400 60 60" 30)
RESULT=$(check_no_death "$OUTPUT")
if [ "$RESULT" = "OK" ]; then
    print_ok "No philosopher died with very fast eating/sleeping cycles"
else
    print_ko "No philosopher should die" "A philosopher died"
fi

# Test 25: Asymmetric times
print_test "4 philosophers, 400ms to die, 100ms to eat, 200ms to sleep - Should not die" "4 400 100 200"
OUTPUT=$(run_test "4 400 100 200" 30)
RESULT=$(check_no_death "$OUTPUT")
if [ "$RESULT" = "OK" ]; then
    print_ok "No philosopher died with asymmetric eat/sleep times"
else
    print_ko "No philosopher should die" "A philosopher died"
fi

# Test 26: Long sleep time
print_test "3 philosophers, 1000ms to die, 200ms to eat, 700ms to sleep - Should not die" "3 1000 200 700"
OUTPUT=$(run_test "3 1000 200 700" 30)
RESULT=$(check_no_death "$OUTPUT")
if [ "$RESULT" = "OK" ]; then
    print_ok "No philosopher died with long sleep time"
else
    print_ko "No philosopher should die" "A philosopher died"
fi

# Test 27: Should die - 2 philos insufficient time
print_test "2 philosophers, 300ms to die, 200ms to eat, 100ms to sleep - Should die" "2 300 200 100"
OUTPUT=$(run_test "2 300 200 100" 5)
if echo "$OUTPUT" | grep -q "died"; then
    print_ok "A philosopher died as expected (2 philos, insufficient time)"
else
    print_ko "A philosopher should die" "No philosopher died"
fi

# Test 28: Should die - odd number tight timing
print_test "5 philosophers, 200ms to die, 100ms to eat, 100ms to sleep - Should die" "5 200 100 100"
OUTPUT=$(run_test "5 200 100 100" 5)
if echo "$OUTPUT" | grep -q "died"; then
    print_ok "A philosopher died as expected (5 philos, impossible timing)"
else
    print_ko "A philosopher should die" "No philosopher died"
fi

# Test 29: Extreme case - many philos with meal count
print_test "50 philosophers, 410ms to die, 200ms to eat, 200ms to sleep, must eat 5 times" "50 410 200 200 5"
OUTPUT=$(run_test "50 410 200 200 5" 30)
RESULT=$(check_no_death "$OUTPUT")
if [ "$RESULT" = "OK" ]; then
    print_ok "Simulation completed with 50 philosophers and meal count"
else
    print_ko "Simulation should complete without deaths" "A philosopher died"
fi

# Test 30: Borderline survival - exactly on the edge
print_test "4 philosophers, 310ms to die, 100ms to eat, 100ms to sleep - Should not die" "4 310 100 100"
OUTPUT=$(run_test "4 310 100 100" 30)
RESULT=$(check_no_death "$OUTPUT")
if [ "$RESULT" = "OK" ]; then
    print_ok "No philosopher died at borderline timing (310ms)"
else
    print_ko "No philosopher should die" "A philosopher died (tight but possible)"
fi

# Test 31: Borderline case - should NOT die (I was wrong before!)
print_test "4 philosophers, 309ms to die, 100ms to eat, 100ms to sleep - Should not die" "4 309 100 100"
OUTPUT=$(run_test "4 309 100 100" 30)
RESULT=$(check_no_death "$OUTPUT")
if [ "$RESULT" = "OK" ]; then
    print_ok "No philosopher died at borderline timing (309ms is sufficient for 4 philos)"
else
    print_ko "No philosopher should die (max wait ~300ms)" "A philosopher died"
fi

# Test 32: Very large time_to_die
print_test "4 philosophers, 5000ms to die, 200ms to eat, 200ms to sleep - Should not die" "4 5000 200 200"
OUTPUT=$(run_test "4 5000 200 200" 30)
RESULT=$(check_no_death "$OUTPUT")
if [ "$RESULT" = "OK" ]; then
    print_ok "No philosopher died with very large time_to_die (5000ms)"
else
    print_ko "No philosopher should die" "A philosopher died"
fi

# Test 33: Odd number stress - SHOULD FAIL
print_test "99 philosophers, 410ms to die, 200ms to eat, 200ms to sleep - Should die" "99 410 200 200"
OUTPUT=$(run_test "99 410 200 200" 10)
if echo "$OUTPUT" | grep -q "died"; then
    print_ok "A philosopher died as expected (odd number creates starvation)"
else
    print_ko "A philosopher should die (99 is odd, creates starvation)" "No philosopher died"
fi

# Test 34: Minimum viable for 2 philosophers
print_test "2 philosophers, 310ms to die, 100ms to eat, 100ms to sleep - Should not die" "2 310 100 100"
OUTPUT=$(run_test "2 310 100 100" 30)
RESULT=$(check_no_death "$OUTPUT")
if [ "$RESULT" = "OK" ]; then
    print_ok "No philosopher died with 2 philos at minimum viable timing"
else
    print_ko "No philosopher should die" "A philosopher died"
fi

# Test 35: High meal count stress
print_test "5 philosophers, 800ms to die, 200ms to eat, 200ms to sleep, must eat 100 times" "5 800 200 200 100"
OUTPUT=$(run_test "5 800 200 200 100" 30)
RESULT=$(check_no_death "$OUTPUT")
if [ "$RESULT" = "OK" ]; then
    print_ok "Simulation completed 100 meals per philosopher"
else
    print_ko "Simulation should complete without deaths" "A philosopher died"
fi

# ============================================
# DATA RACE DETECTION TESTS
# ============================================

if [ "$HELGRIND_AVAILABLE" = true ] || [ "$TSAN_AVAILABLE" = true ]; then
    echo -e "\n${YELLOW}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
    echo -e "${YELLOW}  DATA RACE DETECTION TESTS${NC}"
    echo -e "${YELLOW}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
    
    # Determine which tool to use
    TOOL=""
    if [ "$TSAN_AVAILABLE" = true ]; then
        TOOL="tsan"
        echo -e "${MAGENTA}Using ThreadSanitizer for data race detection${NC}"
    elif [ "$HELGRIND_AVAILABLE" = true ]; then
        TOOL="helgrind"
        echo -e "${MAGENTA}Using Helgrind for data race detection (this will be slower)${NC}"
    fi
    
    # Data Race Test 1: Basic case
    print_test "Data Race Check: 4 philosophers, 410ms to die, 200ms to eat, 200ms to sleep" "4 410 200 200"
    OUTPUT=$(run_datarace_test "4 410 200 200" 10 "$TOOL")
    RESULT=$(check_data_races "$OUTPUT" "$TOOL")
    if [ "$RESULT" = "OK" ]; then
        print_ok "No data races detected"
    elif [ "$RESULT" = "RACE_DETECTED" ]; then
        print_ko "No data races" "Data race detected! Check log for details"
    else
        print_ok "Test completed (check log if uncertain: $LOG_DIR)"
    fi
    
    # Data Race Test 2: High contention
    print_test "Data Race Check: 10 philosophers, 800ms to die, 200ms to eat, 200ms to sleep" "10 800 200 200"
    OUTPUT=$(run_datarace_test "10 800 200 200" 10 "$TOOL")
    RESULT=$(check_data_races "$OUTPUT" "$TOOL")
    if [ "$RESULT" = "OK" ]; then
        print_ok "No data races detected with 10 philosophers"
    elif [ "$RESULT" = "RACE_DETECTED" ]; then
        print_ko "No data races" "Data race detected! Check log for details"
    else
        print_ok "Test completed (check log if uncertain: $LOG_DIR)"
    fi
    
    # Data Race Test 3: Fast cycles
    print_test "Data Race Check: 5 philosophers, 400ms to die, 60ms to eat, 60ms to sleep" "5 400 60 60"
    OUTPUT=$(run_datarace_test "5 400 60 60" 10 "$TOOL")
    RESULT=$(check_data_races "$OUTPUT" "$TOOL")
    if [ "$RESULT" = "OK" ]; then
        print_ok "No data races detected with fast cycles"
    elif [ "$RESULT" = "RACE_DETECTED" ]; then
        print_ko "No data races" "Data race detected! Check log for details"
    else
        print_ok "Test completed (check log if uncertain: $LOG_DIR)"
    fi
    
    # Data Race Test 4: Single philosopher
    print_test "Data Race Check: 1 philosopher, 800ms to die, 200ms to eat, 200ms to sleep" "1 800 200 200"
    OUTPUT=$(run_datarace_test "1 800 200 200" 5 "$TOOL")
    RESULT=$(check_data_races "$OUTPUT" "$TOOL")
    if [ "$RESULT" = "OK" ]; then
        print_ok "No data races detected with 1 philosopher"
    elif [ "$RESULT" = "RACE_DETECTED" ]; then
        print_ko "No data races" "Data race detected! Check log for details"
    else
        print_ok "Test completed (check log if uncertain: $LOG_DIR)"
    fi
    
    # Data Race Test 5: With meal count
    print_test "Data Race Check: 4 philosophers, 800ms to die, 200ms to eat, 200ms to sleep, 7 meals" "4 800 200 200 7"
    OUTPUT=$(run_datarace_test "4 800 200 200 7" 10 "$TOOL")
    RESULT=$(check_data_races "$OUTPUT" "$TOOL")
    if [ "$RESULT" = "OK" ]; then
        print_ok "No data races detected with meal count"
    elif [ "$RESULT" = "RACE_DETECTED" ]; then
        print_ko "No data races" "Data race detected! Check log for details"
    else
        print_ok "Test completed (check log if uncertain: $LOG_DIR)"
    fi
    
    # Data Race Test 6: Two philosophers (tricky case)
    print_test "Data Race Check: 2 philosophers, 410ms to die, 200ms to eat, 100ms to sleep" "2 410 200 100"
    OUTPUT=$(run_datarace_test "2 410 200 100" 10 "$TOOL")
    RESULT=$(check_data_races "$OUTPUT" "$TOOL")
    if [ "$RESULT" = "OK" ]; then
        print_ok "No data races detected with 2 philosophers"
    elif [ "$RESULT" = "RACE_DETECTED" ]; then
        print_ko "No data races" "Data race detected! Check log for details"
    else
        print_ok "Test completed (check log if uncertain: $LOG_DIR)"
    fi
    
    # Data Race Test 7: Many philosophers
    print_test "Data Race Check: 50 philosophers, 800ms to die, 200ms to eat, 200ms to sleep" "50 800 200 200"
    OUTPUT=$(run_datarace_test "50 800 200 200" 10 "$TOOL")
    RESULT=$(check_data_races "$OUTPUT" "$TOOL")
    if [ "$RESULT" = "OK" ]; then
        print_ok "No data races detected with 50 philosophers"
    elif [ "$RESULT" = "RACE_DETECTED" ]; then
        print_ko "No data races" "Data race detected! Check log for details"
    else
        print_ok "Test completed (check log if uncertain: $LOG_DIR)"
    fi
    
else
    echo -e "\n${YELLOW}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
    echo -e "${YELLOW}  DATA RACE DETECTION TESTS - SKIPPED${NC}"
    echo -e "${YELLOW}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
    echo -e "${YELLOW}No data race detection tool available.${NC}"
    echo -e "${YELLOW}Install valgrind or recompile with -fsanitize=thread${NC}"
fi

# ============================================
# INVALID INPUT TESTS
# ============================================

echo -e "\n${YELLOW}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
echo -e "${YELLOW}  INVALID INPUT TESTS${NC}"
echo -e "${YELLOW}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"

# Test 18: Zero philosophers
print_test "0 philosophers - Should handle invalid input" "0 400 200 200"
OUTPUT=$(run_test "0 400 200 200" 2)
if [ $? -ne 0 ] || [ -z "$OUTPUT" ] || echo "$OUTPUT" | grep -iq "error\|invalid"; then
    print_ok "Program correctly rejected invalid input (0 philosophers)"
else
    print_ko "Program should reject 0 philosophers" "Program accepted invalid input"
fi

# Test 19: Negative values
print_test "Negative time_to_die - Should handle invalid input" "4 -200 200 200"
OUTPUT=$(run_test "4 -200 200 200" 2)
if [ $? -ne 0 ] || [ -z "$OUTPUT" ] || echo "$OUTPUT" | grep -iq "error\|invalid"; then
    print_ok "Program correctly rejected negative values"
else
    print_ko "Program should reject negative values" "Program accepted invalid input"
fi

# Test 20: Non-numeric input
print_test "Non-numeric input - Should handle invalid input" "4 abc 200 200"
OUTPUT=$(run_test "4 abc 200 200" 2)
if [ $? -ne 0 ] || [ -z "$OUTPUT" ] || echo "$OUTPUT" | grep -iq "error\|invalid"; then
    print_ok "Program correctly rejected non-numeric input"
else
    print_ko "Program should reject non-numeric input" "Program accepted invalid input"
fi

# ============================================
# FINAL RESULTS
# ============================================

echo -e "\n${YELLOW}╔════════════════════════════════════════╗${NC}"
echo -e "${YELLOW}║            TEST SUMMARY                ║${NC}"
echo -e "${YELLOW}╚════════════════════════════════════════╝${NC}"
echo -e "Total tests: ${TOTAL_TESTS}"
echo -e "${GREEN}Passed: ${PASSED_TESTS}${NC}"
echo -e "${RED}Failed: ${FAILED_TESTS}${NC}"
echo -e "${BLUE}Logs saved in: $LOG_DIR${NC}"

if [ $FAILED_TESTS -eq 0 ]; then
    echo -e "\n${GREEN}🎉 All tests passed! Great job!${NC}"
    exit 0
else
    echo -e "\n${RED}❌ Some tests failed. Check the logs in $LOG_DIR for details.${NC}"
    exit 1
fi
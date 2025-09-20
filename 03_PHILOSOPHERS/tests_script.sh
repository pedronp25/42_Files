#!/bin/bash

PHILO_EXEC=./philo
LOGDIR=logs
TIMEOUT=5

mkdir -p $LOGDIR

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

# Helper: returns 0 if this is a 1 philosopher with n_meals set case
is_one_philo_meals_case() {
    local np=$1
    local nmeals=$2
    if [[ "$np" == "1" && -n "$nmeals" ]]; then
        return 0
    fi
    return 1
}

# Helper: returns 0 if the test should run forever (no one should die)
should_be_infinite() {
    local np=$1
    local td=$2
    local te=$3
    local ts=$4
    local nmeals=$5

    # If n_meals is set, it must terminate after all eat enough
    if [ -n "$nmeals" ]; then
        return 1
    fi
    # single philosopher can never eat forever
    if [ "$np" == "1" ]; then
        return 1
    fi
    # For 2+ philosophers, if time_die > (time_eat + time_sleep)*[(n-1)/n] + time_eat, then no one should die (approx)
    # We'll just use a reasonable approximation:
    # Even: time_die > time_eat + time_sleep + 10
    # Odd: time_die > 2*time_eat + time_sleep + 10
    local slack=10
    if (( np % 2 == 0 )); then
        local critical_time=$((te + ts + slack))
    else
        local critical_time=$((2*te + ts + slack))
    fi
    if (( td > critical_time )); then
        return 0
    fi
    return 1
}

run_test() {
    local np=$1
    local td=$2
    local te=$3
    local ts=$4
    local nmeals=$5
    local logfile="$LOGDIR/philo_n${np}_die${td}_eat${te}_sleep${ts}_meals${nmeals}.log"

    local args="$np $td $te $ts"
    [[ -n "$nmeals" ]] && args="$args $nmeals"

    printf "Test: $PHILO_EXEC $args ... "

    timeout $TIMEOUT $PHILO_EXEC $args > "$logfile" 2>&1
    local exit_code=$?

    # Special case: 1 philosopher with n_meals set, should never reach n_meals (should die)
    is_one_philo_meals_case $np "$nmeals"
    if [[ $? -eq 0 ]]; then
        # Check if last line is a death message
        last_line=$(grep -a "has died" "$logfile" | tail -n 1)
        last_line_full=$(tail -n 1 "$logfile")
        if echo "$last_line_full" | grep -q "has died"; then
            if [ $exit_code -eq 124 ]; then
                echo -e "${RED}KO${NC} (Philosopher died but simulation got stuck and didn't exit)"
            else
                echo -e "${GREEN}OK${NC} (Philosopher died as expected before eating enough meals)"
            fi
        else
            echo -e "${RED}KO${NC} (Should not be able to reach n_meals with only 1 philosopher, should die)"
        fi
        return
    fi

    should_be_infinite $np $td $te $ts $nmeals
    local infinite_expected=$?

    if [ $infinite_expected -eq 0 ]; then
        # Simulation should run forever (no one should die).
        if [ $exit_code -eq 124 ]; then
            # Timed out (still running): OK
            echo -e "${GREEN}OK${NC}"
        else
            # Terminated: KO
            echo -e "${RED}KO${NC} (Simulation should run forever, but it terminated)"
        fi
    else
        # Simulation is expected to end (philosopher dies or all eat n_meals)
        last_line=$(grep -a "has died" "$logfile" | tail -n 1)
        last_line_full=$(tail -n 1 "$logfile")
        if echo "$last_line_full" | grep -q "has died"; then
            if [ $exit_code -eq 124 ]; then
                echo -e "${RED}KO${NC} (Philosopher died but simulation got stuck and didn't exit)"
            else
                echo -e "${GREEN}OK${NC} (Philosopher died and simulation exited)"
            fi
            return
        fi

        if [ $exit_code -eq 0 ]; then
            # Correctly terminated: OK
            echo -e "${GREEN}OK${NC}"
        else
            # Did not terminate (timeout): KO
            if [[ -n "$nmeals" ]]; then
                echo -e "${RED}KO${NC} (Simulation should terminate after all philosophers eat required meals)"
            else
                echo -e "${RED}KO${NC} (Simulation should terminate because a philosopher must die)"
            fi
        fi
    fi
}

# Test matrix
for np in 1 2 3 4 5 10 50 100 200; do
    for td in 130 170 190 230 270 310 330 410 470 510 610; do
        for te in 60 100 200; do
            for ts in 60 100 200; do
                # Without n_meals
                run_test $np $td $te $ts
                # With n_meals (2, 3, 5)
                for nmeals in 2 3 5; do
                    run_test $np $td $te $ts $nmeals
                done
            done
        done
    done
done

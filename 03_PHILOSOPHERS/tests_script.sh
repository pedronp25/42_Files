#!/bin/bash

PHILO_EXEC=./philo   # Change to ./philosophers if needed
TIMEOUT=10           # seconds, timeout for each test

N_PHILOS=(1 2 3 4 5 10 50 100 200)
TIMES=(60 100 200)
N_MEALS=(2 3 5)

LOGDIR="philo_test_logs"
mkdir -p "$LOGDIR"

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

# Determine if simulation is expected to be infinite or not
# Returns 0 if simulation should run forever (no philosopher dies), 1 if simulation should terminate (a philosopher must die)
should_be_infinite() {
    local np=$1
    local td=$2
    local te=$3
    local ts=$4
    local nmeals=$5

    # If n_meals is set, simulation should always terminate
    if [[ -n "$nmeals" ]]; then
        return 1
    fi
    # If only one philosopher, always dies, simulation must terminate
    if [[ $np -eq 1 ]]; then
        return 1
    fi
    # For even n_philos: max starvation = te + ts (+10 slack)
    if (( np % 2 == 0 )); then
        local min_die=$((te + ts + 10))
        [[ $td -ge $min_die ]] && return 0 || return 1
    else
        # For odd n_philos: max starvation = 2*te + ts (+10 slack)
        local min_die=$((2 * te + ts + 10))
        [[ $td -ge $min_die ]] && return 0 || return 1
    fi
}

# For 1 philosopher with n_meals set, reaching n_meals is a KO (cannot eat), should die before reaching n_meals
is_one_philo_meals_case() {
    local np=$1
    local nmeals=$2
    [[ $np -eq 1 && -n "$nmeals" ]] && return 0 || return 1
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
        if [ $exit_code -eq 0 ]; then
            # Terminated successfully (probably reached n_meals): KO
            echo -e "${RED}KO (Should not be able to reach n_meals with only 1 philosopher, should die)${NC}"
        else
            # Did not terminate cleanly (timeout or exit on death): OK
            echo -e "${GREEN}OK${NC}"
        fi
        return
    fi

    # Should it run forever?
    should_be_infinite $np $td $te $ts $nmeals
    local infinite_expected=$?

    if [ $infinite_expected -eq 0 ]; then
        # Simulation should run forever (no one should die).
        if [ $exit_code -eq 124 ]; then
            # Timed out (still running): OK
            echo -e "${GREEN}OK${NC}"
        else
            # Terminated: KO
            echo -e "${RED}KO (Simulation should run forever, but it terminated)${NC}"
        fi
    else
        # Simulation is expected to end (philosopher dies or all eat n_meals)
        if [ $exit_code -eq 0 ]; then
            # Correctly terminated: OK
            echo -e "${GREEN}OK${NC}"
        else
            # Did not terminate (timeout): KO
            if [[ -n "$nmeals" ]]; then
                echo -e "${RED}KO (Simulation should terminate after all philosophers eat required meals)${NC}"
            else
                echo -e "${RED}KO (Simulation should terminate because a philosopher must die)${NC}"
            fi
        fi
    fi
}

# Main test loop
for np in "${N_PHILOS[@]}"; do
    for te in "${TIMES[@]}"; do
        for ts in "${TIMES[@]}"; do
            # For the "minimum working" time_die for each case
            if (( np % 2 == 0 )); then
                min_td=$((te + ts + 10))
            else
                min_td=$((2 * te + ts + 10))
            fi

            # Special known valid test for 3 philosophers, 610 200 200
            if [[ $np -eq 3 ]]; then
                run_test 3 610 200 200
                for nmeals in "${N_MEALS[@]}"; do
                    run_test 3 610 200 200 $nmeals
                done
            fi

            # Test with minimum time_die (should always be the boundary)
            run_test $np $min_td $te $ts

            # Test with n_meals set
            for nmeals in "${N_MEALS[@]}"; do
                run_test $np $min_td $te $ts $nmeals
            done

            # Avoid too many tests for high n_philos
            if (( np >= 50 )); then break; fi
        done
        if (( np >= 50 )); then break; fi
    done
done

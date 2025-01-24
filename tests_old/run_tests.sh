#!/bin/bash

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

# Counter for tests
TOTAL=0
PASSED=0

# Path to minishell executable
MINISHELL="../minishell"

# Check if minishell exists and is executable
if [ ! -x "$MINISHELL" ]; then
    echo "Error: minishell executable not found or not executable at $MINISHELL"
    exit 1
fi

run_test() {
    local test_name=$1
    local command=$2
    
    TOTAL=$((TOTAL + 1))
    
    # Create temp files
    echo "$command" > test_input
    
    # Run commands
    $MINISHELL < test_input > test_output 2> test_error
    actual_exit_code=$?
    
    bash < test_input > bash_output 2> bash_error
    bash_exit_code=$?

    # Compare outputs
    if diff test_output bash_output > /dev/null && \
       diff test_error bash_error > /dev/null; then
        echo -e "${GREEN}✓ $test_name${NC}"
        PASSED=$((PASSED + 1))
    else
        echo -e "${RED}✗ $test_name${NC}"
        echo "Command: $command"
        echo "Expected exit code: $bash_exit_code, Got: $actual_exit_code"
        echo "Differences in output:"
        diff test_output bash_output || true
        echo "Differences in error output:"
        diff test_error bash_error || true
    fi
}

# Basic command tests
run_test "Echo Test" "echo hello world"
run_test "Echo with quotes" "echo \"hello world\""
run_test "PWD Test" "pwd"
run_test "Export Test" "export TEST=123 && echo \$TEST"
run_test "Env Test" "env | grep PATH"

# Print summary
echo -e "\nTests completed: $PASSED/$TOTAL passed"

exit $(($TOTAL - $PASSED))
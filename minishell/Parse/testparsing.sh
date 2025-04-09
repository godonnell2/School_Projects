#!/bin/bash

# Color codes for output
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

# Test counter
TESTS_PASSED=0
TOTAL_TESTS=0

# Function to run a test case
run_test() {
    local description=$1
    local command=$2
    local expected=$3
    local should_fail=${4:-0} # Default to 0 (success expected)

    ((TOTAL_TESTS++))
    
    echo -e "\n${GREEN}TEST #$TOTAL_TESTS:${NC} $description"
    echo -e "Command: ${GREEN}$command${NC}"
    
    # Run in minishell and capture output
    actual=$(./minishell -c "$command" 2>&1)
    exit_status=$?
    
    # Check for expected failure
    if [ $should_fail -eq 1 ]; then
        if [ $exit_status -eq 0 ]; then
            echo -e "${RED}FAIL: Expected failure but command succeeded${NC}"
            return
        fi
        echo -e "${GREEN}PASS: Failed as expected${NC} (Exit status: $exit_status)"
        ((TESTS_PASSED++))
        return
    fi
    
    # Compare actual vs expected
    if [ "$actual" = "$expected" ]; then
        echo -e "${GREEN}PASS:${NC} Output matches"
        echo "Expected and got: '$expected'"
        ((TESTS_PASSED++))
    else
        echo -e "${RED}FAIL:${NC} Output mismatch"
        echo "Expected: '$expected'"
        echo "Got:      '$actual'"
    fi
}

# ---------------------------
# Test Cases
# ---------------------------
# ---------------------------
# Empty Input Tests
# ---------------------------

# Pure empty input
run_test "Empty input (no characters)" \
    "" \
    "" \
    0

# Whitespace-only input
run_test "Whitespace-only input" \
    "   " \
    "" \
    0

# Single quote tests
run_test "Single quotes - literal interpretation" \
    "echo '\$USER * \`date\`'" \
    '$USER * `date`'

run_test "Single quotes - with double quotes inside" \
    "echo '\"hello\"'" \
    '"hello"'

# Double quote tests
run_test "Double quotes - variable expansion" \
    "echo \"\$USER\"" \
    "$USER"  # Your shell should expand this

run_test "Double quotes - preserve other metacharacters" \
    "echo \"file*.txt\"" \
    'file*.txt'

# Mixed quotes
run_test "Adjacent quotes" \
    "echo 'hello'\"world\"" \
    'helloworld'

run_test "Nested quotes" \
    "echo \"'\$(echo \"foo\")'\"" \
    "'foo'"

# Special character handling
run_test "Backslashes - should be literal" \
    "echo \\hello" \
    '\hello'

run_test "Semicolons - should be literal" \
    "echo hello;world" \
    'hello;world'

# Error cases
run_test "Unclosed single quote" \
    "echo 'hello" \
    "" \
    1  # Should fail

run_test "Unclosed double quote" \
    "echo \"hello" \
    "" \
    1  # Should fail

run_test "Empty between quotes" \
    "echo hello\"\"world" \
    'helloworld'

# Whitespace preservation
run_test "Preserve whitespace in quotes" \
    "echo \"  hello  \"" \
    '  hello  '

# ---------------------------
# Results
# ---------------------------
echo -e "\n${GREEN}RESULTS:${NC}"
echo "$TESTS_PASSED/$TOTAL_TESTS tests passed"

if [ $TESTS_PASSED -eq $TOTAL_TESTS ]; then
    echo -e "${GREEN}All tests passed!${NC}"
else
    echo -e "${RED}$((TOTAL_TESTS-TESTS_PASSED)) tests failed${NC}"
fi

exit $((TOTAL_TESTS - TESTS_PASSED))
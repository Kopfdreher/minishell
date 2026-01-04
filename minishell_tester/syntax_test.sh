#!/bin/bash

# ==============================================================================
#                               MINISHELL TESTER
# ==============================================================================
# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
RESET='\033[0m'

# Path to your minishell
MINISHELL="./minishell"

# Cleanup from previous runs
rm -f out_bash out_mini test_file test_file2 file file1 file2

print_header() {
    echo -e "${BLUE}======================================================${RESET}"
    echo -e "${BLUE}   TESTING: $1 ${RESET}"
    echo -e "${BLUE}======================================================${RESET}"
}

run_test() {
    local cmd="$1"
    local description="$2"

    echo -n "Test: [$cmd] ... "

    # 1. Run in BASH
    # We use ( ) to run in a subshell so syntax errors don't kill the tester
    echo "$cmd" | bash > out_bash 2>&1
    local exit_bash=$?

    # 2. Run in MINISHELL
    echo "$cmd" | $MINISHELL > out_mini 2>&1
    local exit_mini=$?

    # NOTE: Minishell prints prompts/exit messages in non-interactive mode if not handled 
    # perfectly. We mostly care about EXIT CODES for syntax errors.
    
    # Filter out "minishell: " prefix or specific error wording differences if needed
    # For this basic test, we compare Exit Codes primarily.

    if [ $exit_bash -eq $exit_mini ]; then
        echo -e "${GREEN}[OK]${RESET} (Exit: $exit_bash)"
    else
        echo -e "${RED}[FAIL]${RESET}"
        echo "  Input: $cmd"
        echo "  Bash Exit: $exit_bash | Mini Exit: $exit_mini"
        echo "  Bash Output: $(cat out_bash)"
        echo "  Mini Output: $(cat out_mini)"
    fi
}

# ==============================================================================
# 1. SYNTAX ERRORS (Should Exit 2 or 258 depending on bash version)
# ==============================================================================
print_header "SYNTAX ERRORS (MUST FAIL)"

# Pipe Errors
run_test "|"            "Start with pipe"
run_test "| ls"         "Start with pipe 2"
run_test "ls |"         "End with pipe"
run_test "ls | | wc"    "Empty pipe"

# Redirection Errors
run_test ">"            "Empty redir"
run_test "ls >"         "Redir no target"
run_test "ls > |"       "Redir into pipe"
run_test "ls < |"       "Input redir from pipe"
run_test "ls > > file"  "Redir to redir"
run_test "ls >>> file"  "Triple redir"
run_test "ls << <"      "Heredoc to redir"

# Quote Errors (Unclosed)
# Note: Bash usually waits for input. Minishell should error.
# We skip comparison here because Bash behavior (interactive wait) differs from 
# Minishell (error immediately) unless you implemented multiline.
echo -e "${BLUE}--- Manual Check Required for Unclosed Quotes ---${RESET}"
echo "Run: echo \"hello   -> Should print error"
echo "Run: echo 'hello    -> Should print error"

# ==============================================================================
# 2. WEIRD BUT VALID (MUST WORK)
# ==============================================================================
print_header "TRICKY VALID CASES (MUST WORK)"

# Weird Positioning
run_test "> test_file"          "Create empty file"
run_test "> test_file ls"       "Command after redir"
run_test "ls > test_file -l"    "Args separated by redir"

# Sticky Syntax
run_test "ls>test_file"         "No spaces >"
run_test "ls|wc"                "No spaces |"
run_test "echo 'hello'>test_file" "Quotes and redir"

# Cleanup
rm -f out_bash out_mini test_file test_file2 file file1 file2

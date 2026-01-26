<!-- *********************************************************************** -->
<!--                                                                         -->
<!--                                                      :::      ::::::::  -->
<!-- README.md                                          :+:      :+:    :+:  -->
<!--                                                  +:+ +:+         +:+    -->
<!-- By: alago-ga <alago-ga@student.42berlin.d>     +#+  +:+       +#+       -->
<!--                                              +#+#+#+#+#+   +#+          -->
<!-- Created: 2026/01/22 18:07:56 by alago-ga          #+#    #+#            -->
<!-- Updated: 2026/01/26 22:42:08 by alago-ga         ###   ########.fr      -->
<!--                                                                         -->
<!-- *********************************************************************** -->

*This project has been created as part of the 42 curriculum by Ariel Lago Garcia
and Sergej Gavrilov.*

# Minishell

## Description
Minishell is a project that aims to create a simple shell, inspired by bash. It is a major milestone in the 42 curriculum, serving as an introduction to processes, file descriptors, and intricate memory management in C.

The goal is to build a functional command-line interface that can parse commands, handle environment variables, manage executable paths, and execute external commands. It also replicates standard shell behaviors like piping, redirections, and signal handling.

### Key Features
* **Prompt:** Displays a clean prompt waiting for user input.
* **History:** Functional command history using the readline library.
* **Parsing:** Handles single quotes `'`, double quotes `"`, and environment variable expansion `$VAR`.
* **Redirections:** Implementation of `<`, `>`, `<<` (heredoc), and `>>` input/output redirections.
* **Pipes:** Handling of infinite pipelines (`|`).
* **Builtins:** Custom implementation of `echo`, `cd`, `pwd`, `export`, `unset`, `env`, and `exit`.
* **Signals:** Mimics bash signal behavior in interactive, non-interactive, and heredoc modes.

## Instructions

### Requirements
* **OS:** Linux (or macOS with adjustments)
* **Compiler:** `cc` or `gcc`
* **Dependencies:** `libreadline`
    * On Linux (Debian/Ubuntu): `sudo apt-get install libreadline-dev`

### Installation
1.  Clone the repository:
    ```bash
    git clone [Link to your repo] minishell
    cd minishell
    ```

2.  Compile the project:
    ```bash
    make
    ```

### Execution
Start the shell by running:
```bash
./minishell
```

You can now type commands just like in bash (e.g., `ls -l | grep .c`, `cat << EOF`).

## Resources

### References

* [GNU Bash Reference Manual](https://www.gnu.org/software/bash/manual/) - The gold standard for expected behavior.
* **Man Pages:** `fork(2)`, `execve(2)`, `waitpid(2)`, `pipe(2)`, `dup2(2)`, `sigaction(2)`.
* [Architecture of a Shell](https://aosabook.org/en/v1/bash.html) - Helpful for understanding the parsing/execution loop.
* [CodeVault](www.youtube.com/@CodeVault) - Course on unix processes used for understanding execution.
* [hhp3](https://www.youtube.com/@hhp3) - Videos on Shell helped as an introduction to the project.

### AI Usage

AI tools (specifically ChatGPT/Gemini/Claude) were used in this project for the following tasks:

1. **Conceptual Understanding:**
* Clarifying the difference between "Heap" and "Stack" memory in the context of string literals vs. allocated strings.
* Understanding the specific behavior of Process Groups and how signals propagate to children vs. parents.
* Comparing ways in which bash, zsh and other shells handle heredocs.
* Helping with understanding why built in functions needed to be handled differently.

2. **Debugging & Logic:**
* Designing the `wait_for_children` loop to correctly handle pipeline exit codes (`128 + Signal`).
* Troubleshooting the "Interrupted System Call" (`EINTR`) error when using `waitpid` alongside signal handlers.
* Refining the `ft_strjoin_multi` variadic function to ensure memory safety.
* Handeling more than one heredoc and improving exit codes.
* Creating minishell tests and finding edge cases to check.

3. **Code Structure:**
* Suggestions for organizing enums and structs to avoid global scope pollution (e.g., separating `enum` definitions from `struct` definitions).

*Note: All code provided by AI was reviewed, tested, and adapted to fit the project's specific coding standard (Norminette) and architecture.*

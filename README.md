<!-- *********************************************************************** -->
<!--                                                                         -->
<!--                                                      :::      ::::::::  -->
<!-- README.md                                          :+:      :+:    :+:  -->
<!--                                                  +:+ +:+         +:+    -->
<!-- By: alago-ga <alago-ga@student.42berlin.d>     +#+  +:+       +#+       -->
<!--                                              +#+#+#+#+#+   +#+          -->
<!-- Created: 2026/01/22 18:07:56 by alago-ga          #+#    #+#            -->
<!-- Updated: 2026/01/22 18:08:27 by alago-ga         ###   ########.fr      -->
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

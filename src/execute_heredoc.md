# 🐛 Heredoc Implementation Issues

### 1. Multiple Heredocs Failure

Currently, chaining multiple heredocs does not work as expected. The shell fails to process the second delimiter correctly or loses context.

**Reproduction:**

```bash
minishell$ <<EOF <<EOF
> hi
> EOF
> hi
> warning: here-document delimited by end-of-file (wanted: `EOF')

```

### 2. Broken Piping Logic

When piping a heredoc into another command, the input processing breaks. It appears the child process (running the heredoc) conflicts with the pipe execution, causing command-not-found errors on the input text itself.

**Reproduction:**

```bash
minishell$ cat <<EOF | ls
[ls output]
ello: command not found
hleo: command not found
minishell$ 

```

### 3. Execution Order (Priority Issue)

Bash processes heredoc input **before** attempting to open other redirections or execute commands. Our shell currently processes them in strict linear order or too late in the execution chain.

**Current Behavior:**

```bash
minishell$ cat <missing <<EOF <missing | ls
missing: No such file or directory

```

*(The shell errors out immediately on the file open, preventing the user from inputting the heredoc.)*

**Expected Behavior (Bash):**

1. User is prompted for Heredoc input (`<<EOF`).
2. *Then* the shell attempts to open `<missing`.
3. *Then* the error is displayed.

---

### 💡 Proposed Solution

**Architecture Change:** Heredoc processing must be the **very first action** taken during the execution phase.

**Plan:**

1. Scan the entire command chain for heredocs **before** forking or piping.
2. Collect all user input and save to temporary files.
3. Replace `<<` tokens with simple `<` redirections pointing to these temp files.
4. Proceed with normal execution (pipes, file opens, etc.).

---

Here is the breakdown of why your current approach fails and how the "Pre-Process" architecture fixes it.

### The Problem: Timing and Process Ownership

1. **The Piping Bug:**
* **Current Behavior:** You execute redirections *inside* the child process (after `fork`).
* **The Issue:** When you run `cat << EOF | ls`, the `cat` process is a child. It tries to run `readline()`. However, in a pipeline, the terminal control is complex. Often the child does not have the right permissions to read from the TTY, or `readline` gets confused because `stdin` is being messed with by the pipe setup.
* **The Fix:** You must read the Heredoc in the **Parent** process, *before* any forking happens.


2. **Multiple Heredocs (`<< A << B`):**
* **Current Behavior:** You write to a hardcoded filename `/tmp/.heredoc`.
* **The Issue:** The second heredoc overwrites the first one because they use the same filename.
* **The Fix:** Every heredoc needs a **unique filename** (e.g., `.heredoc_0`, `.heredoc_1`).


3. **Order of Operations (`< missing << EOF`):**
* **Current Behavior:** Your `redirs()` loop stops at the first error (`missing`).
* **The Issue:** The user never gets to type the heredoc input because the code crashed on the missing file first.
* **The Fix:** Bash scans the *entire* command line for heredocs and collects them **all** first. Only *then* does it try to open files like `missing`.



---

### The Solution: The "Pre-Execution Scan"

You need to split your logic into two phases:

1. **Phase 1 (Parent):** Scan all commands, find all heredocs, read user input, save to unique temp files.
2. **Phase 2 (Child/Execution):** When execution happens, the heredoc is treated just like a normal input file (because we already saved it).

#### Step 1: Generate Unique Filenames

We need a way to ensure every heredoc gets a different name so they don't overwrite each other.

```c
// Helper to generate names like "/tmp/.heredoc_1", "/tmp/.heredoc_2"
static char *generate_heredoc_filename(void)
{
    static int i = 0;
    char *num;
    char *name;

    num = ft_itoa(i++);
    name = ft_strjoin("/tmp/.heredoc_", num);
    free(num);
    return (name);
}

```

#### Step 2: The Heredoc Collector (Phase 1)

Create a function that runs **before** your execution loop (before `execute_cmds` or pipes).

#### Step 3: Modify `open_heredoc` logic

Your `open_heredoc` (or `process_heredoc` in the new plan) should no longer unlink the file immediately. The file must exist until the child process reads it.

```c
/*
** Modified version of your open_heredoc
** It takes the unique filename as an argument
*/
int process_heredoc(t_redir *heredoc, char *filename, t_shell *shell)
{
    int     fd;
    t_token *eof;
    char    *eof_str;
    int     expand;

    eof = heredoc->file_tokens; // This is currently the delimiter tokens
    
    // Open the UNIQUE filename
    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd == ERROR)
        return (put_error(OPEN, "heredoc", shell), ERROR);

    // ... (Your expansion and readline logic remains the same) ...
    
    set_signals(SIG_HEREDOC);
    if (read_heredoc(fd, expand, eof_str, shell) == FAILURE)
    {
        close(fd);
        // If interrupted, unlink immediately to clean up
        unlink(filename); 
        return (FAILURE);
    }
    set_signals(SIG_INTERACTIVE);
    
    close(fd); 
    // DO NOT UNLINK HERE! The child needs to read it later.
    return (SUCCESS);
}

```

#### Step 4: Integration in Main Loop

Call this **before** you start forking or piping.

```c
// In your execute_cmds or main execution logic
int execute_cmds(t_shell *shell)
{
    // 1. PRE-PROCESS HEREDOCS
    // This happens in the parent, sequentially.
    // It handles the "order" issue and the "piping" issue.
    if (handle_heredoc_execution(shell) == FAILURE)
        return (130); // Stop if Ctrl+C was pressed during heredoc

    // 2. NOW EXECUTE PIPELINE
    // The heredoc nodes have been converted to simple REDIR_IN nodes
    // pointing to files like /tmp/.heredoc_0.
    // Your existing redirs() function will just open them naturally!
    
    // ... your forking loop ...
    
    // 3. CLEANUP
    // After all children are dead, delete the temp files.
    cleanup_heredocs(shell); 
}

```

### Cleanup Strategy

Since we aren't unlinking immediately, we need a cleanup function at the end of execution to delete `/tmp/.heredoc_0`, `/tmp/.heredoc_1`, etc.

You can iterate through your command list again at the end:

### Summary of fixes

1. **Buggy Piping:** Solved because input is read in the Parent before `fork`.
2. **Multiple Heredocs:** Solved because we generate unique filenames (`index++`).
3. **Order of Ops:** Solved because we scan/read heredocs before we try to open any files (`< missing`)

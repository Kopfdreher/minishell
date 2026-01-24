# 🐛 Heredoc Refactor: The "Pre-Process" Strategy

### ❌ Current Issues

1. **Multiple Heredocs:** Overwriting occurs because filenames aren't unique.
2. **Broken Piping:** Reading input inside a child process conflicts with TTY/Pipes.
3. **Priority:** Bash reads heredocs *before* checking other file errors; we currently check too late.

---

### 💡 The Solution: `t_list *heredocs`

To solve this efficiently, we will utilize the `t_list *heredocs` in the `t_shell` struct. This generic linked list should store a pointer to **every** heredoc redirection node found during parsing.

**Why this makes it easier:**
Instead of traversing complex command trees to find heredocs, we simply iterate this linear list to process, execute, and clean up everything in one go.

#### 1. Unique Filename Generator

We need a static counter to ensure every heredoc gets a unique path (e.g., `/tmp/.heredoc_0`, `/tmp/.heredoc_1`) so they don't overwrite each other.

```c
static char *get_unique_filename(void)
{
    static int i = 0;
    char *num = ft_itoa(i++);
    char *name = ft_strjoin("/tmp/.heredoc_", num);
    return (free(num), name);
}

```

#### 2. The Execution Loop (Phase 1: Parent)

Before any forking or piping, iterate through `shell->heredocs`. For each node, generate a filename, read the input, and then **convert** the node type.

```c
int handle_heredocs(t_shell *shell)
{
    t_list  *current = shell->heredocs;
    t_redir *redir;
    char    *filename;

    while (current)
    {
        redir = (t_redir *)current->content; // Access the redir node directly
        filename = get_unique_filename();

        // 1. Read input and save to 'filename'
        if (process_heredoc(redir, filename, shell) == FAILURE)
            return (free(filename), FAILURE); // Handle Ctrl+C

        // 2. Mutate the node: It is now a normal input file
        free(redir->file);
        redir->file = filename;
        redir->type = REDIR_IN; // Executor will treat it like "< /tmp/.heredoc_0"

        current = current->next;
    }
    return (SUCCESS);
}

```

#### 3. Cleanup Strategy

Since we stored all references in `shell->heredocs`, cleanup is trivial. We don't need to search the command tree; we just walk the list and unlink the files we created.

```c
void cleanup_heredocs(t_shell *shell)
{
    t_list  *current = shell->heredocs;
    t_redir *redir;

    while (current)
    {
        redir = (t_redir *)current->content;
        // Unlink the unique temp file we generated earlier
        unlink(redir->file);
        current = current->next;
    }
}

```

### ✅ Summary of Flow

1. **Parse:** Add every `<<` token to `shell->heredocs`.
2. **Pre-Exec:** Call `handle_heredocs(shell)` (Parent process).
* Generates unique `/tmp/.heredoc_N`.
* Reads user input.
* Updates token to `REDIR_IN`.


3. **Exec:** Run pipes/forks. The executor sees normal input files.
4. **Post-Exec:** Call `cleanup_heredocs(shell)` to unlink files.

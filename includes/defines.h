/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 18:58:19 by sgavrilo          #+#    #+#             */
/*   Updated: 2025/12/31 18:58:21 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include <signal.h> // Needed for sig_atomic_t

// --- MACROS ---
# define SUCCESS 0
# define FAILURE 1
# define FALSE 0
# define TRUE 1

// --- ENUMS ---
typedef enum e_token_type {
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC
}	t_token_type;

typedef enum e_quote_type {
	NO_QUOTE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE
}	t_quote_type;

typedef enum e_error_type {
	SYNTAX,
	MALLOC
}	t_error_type;

typedef enum e_sig_mode {
	SIG_INTERACTIVE,
	SIG_EXEC,
	SIG_HEREDOC
}	t_sig_mode;

// --- STRUCTS ---
typedef struct s_shell	t_shell;
typedef struct s_cmd	t_cmd;
typedef struct s_token	t_token;

typedef struct s_env {
	char			*name;
	char			*value;
	t_token			*tokens;
	int				word_count;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef struct s_token {
	char			*value;
	t_token_type	type;
	t_quote_type	quote;
	int				merge;
	struct s_token	*expand_tokens;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_arg {
	char			*arg;
	t_token			*arg_tokens;
	t_token			*expand_arg_tokens;
	t_cmd			*cmd;
	struct s_arg	*next;
}	t_arg;

typedef struct s_redir {
	t_token_type	type;
	char			*file;
	t_token			*file_tokens;
	t_token			*expand_redir_tokens;
	int				heredoc_fd;
	int				is_ambiguous;
	t_cmd			*cmd;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd {
	char			**args;
	char			*path;
	int				is_builtin;
	t_arg			*args_list;
	t_token			*expand_arg_tokens;
	t_redir			*redir_list;
	struct s_cmd	*next;
	struct s_cmd	*prev;
	pid_t			pid;
	int				fd_in;
	int				fd_out;
	t_shell			*shell;
}	t_cmd;

typedef struct s_shell {
	t_cmd	*cmd_list;
	t_env	*env_list;
	t_token	*tokens;
	char	*input;
	char	**env_array;
	int		exit_status;
	int		running;
	int		original_stdin;
	int		original_stdout;
}	t_shell;

// --- Global ---
//extern volatile sig_atomic_t	g_signal_status;

#endif

# |--- Variables --------------------------------|

NAME		= minishell
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -g3 -fsanitize=address

# Colors
GREEN		= \033[0;32m
BLUE		= \033[0;36m
RESET		= \033[0m

# Directories
SRC_DIR		= src
OBJ_DIR		= obj
INC_DIR		= includes

# Includes 
INC_FILES	= $(addsuffix .h, minishell builtins defines execute parse \
			  initialize tokenize error)
INCS		= $(addprefix $(INC_DIR)/, $(INC_FILES))

# Source files
ERROR_FILES	= error
INIT_FILES	= init_env init_shell
TOKEN_FILES	= tokenize_shell tokenize_helper tokenize_print tokenize_word\
			  tokenize_syntax
PARSE_FILES	= parse_shell parse_helper parse_token_to_cmd parse_print\
			  parse_args_list_to_strarr parse_tokens_to_str\
			  parse_file_tokens_to_file
EXPAND_FILES= expand_env_handling expand_env_print expand_get_env_value\
			  expand_token expand_token_list expand_exit_code
SRC_FILES	= $(addsuffix .c, main\
			  $(ERROR_FILES)\
			  $(INIT_FILES)\
			  $(TOKEN_FILES)\
			  $(PARSE_FILES)\
			  $(EXPAND_FILES))
SRCS		= $(addprefix $(SRC_DIR)/, $(SRC_FILES))

# Object files
OBJS		= $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))


# Paths
LIBFT_DIR	= ./libft
LIBFT		= $(LIBFT_DIR)/libft.a

# |--- Rules ------------------------------------|

all: $(NAME)

# Main Traget
$(NAME): $(OBJS) $(LIBFT) 
		@echo "$(BLUE)|--Linking $(NAME)----------------|$(RESET)"
		@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -lreadline -lncurses -o $(NAME)
		@echo "$(GREEN)|--$(NAME) created successfully!--|$(RESET)"

# Libft
$(LIBFT):
		@echo "$(BLUE)|--Building Libft-------------------|$(RESET)"
		@make -C $(LIBFT_DIR) > /dev/null

# Compiling .c to .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCS)
		@mkdir -p $(OBJ_DIR)
		@$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

# |--- Clean up ---------------------------------|

# Remove all Object-Files
clean:
		@echo "$(BLUE)|--Cleaning Objects-----------------|$(RESET)"
		@rm -rf $(OBJ_DIR)
		@make clean -C $(LIBFT_DIR) > /dev/null
		@echo "$(GREEN)|--Cleaned successfully!------------|$(RESET)"

# Remove all Object- and Archive-Files
fclean: clean
		@echo "$(BLUE)|--Cleaning Executables-------------|$(RESET)"
		@rm -f $(NAME) > /dev/null
		@make fclean -C $(LIBFT_DIR) > /dev/null
		@echo "$(GREEN)|--Cleaned successfully!------------|$(RESET)"

# Rebuild
re: fclean all

.PHONY: clean all re fclean

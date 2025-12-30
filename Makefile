# |--- Variables --------------------------------|

NAME		= minishell
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g

# Colors
GREEN		= \033[0;32m
BLUE		= \033[0;36m
RESET		= \033[0m

# Directories
SRC_DIR		= src
OBJ_DIR		= obj
INC_DIR		= includes

# Includes 
INC_FILES	= $(addsuffix .h, minishell)
INCS		= $(addprefix $(INC_DIR)/, $(INC_FILES))

# Source files
SRC_FILES	= $(addsuffix .c, main)
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
		@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -lreadline -o $(NAME)
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

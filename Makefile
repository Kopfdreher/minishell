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

# Includes & Linking
INCLUDES	= -I $(INC_DIR) -I$(LIBFT_DIR)

# Source files
SRCS 		= $(addsuffix .c, main my_mlx draw_helper key_press free_exit \
				map_is_valid map_parsing map_valid_positions \
				map_chars_not_reachable key_movement)

# Object files
OBJS		= $(SRCS:.c=.o)

# |--- Rules ------------------------------------|

all: $(NAME)

# Main Traget
$(NAME): $(OBJS) $(LIBFT) $(MLX_LIB)
		@echo "$(BLUE)|--Linking $(NAME)------------------|$(RESET)"
		@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)
		@echo "$(GREEN)|--$(NAME) created successfully!----|$(RESET)"

# Libft
$(LIBFT):
		@echo "$(BLUE)|--Building Libft-------------------|$(RESET)"
		@make -C $(LIBFT_DIR) > /dev/null

# MLX
$(MLX_LIB):
		@echo "$(BLUE)|--Building MiniLibX ---------------|$(RESET)"
		@make -C $(MLX_DIR) > /dev/null 2>&1

# Compiling .c to .o
%.o: %.c $(HEADERS)
		@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# |--- Clean up ---------------------------------|

# Remove all Object-Files
clean:
		@echo "$(BLUE)|--Cleaning Objects-----------------|$(RESET)"
		@rm -f $(OBJS)
		@make clean -C $(LIBFT_DIR) > /dev/null
		@make clean -C $(MLX_DIR) > /dev/null
		@echo "$(GREEN)|--Cleaned successfully!------------|$(RESET)"

# Remove all Object- and Archive-Files
fclean: clean
		@echo "$(BLUE)|--Cleaning Executables-------------|$(RESET)"
		@rm -f $(NAME)
		@rm -f $(MLX_LIB)
		@make fclean -C $(LIBFT_DIR) > /dev/null
		@echo "$(GREEN)|--Cleaned successfully!------------|$(RESET)"

# Rebuild
re: fclean all

flush: re
		@make clean > /dev/null

.PHONY: clean all re fclean flush

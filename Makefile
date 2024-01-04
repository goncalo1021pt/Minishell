NAME = Minishell
BONUS_NAME = Minishell_bonus

BONUS = $(addprefix bonus/,$(addsuffix .c, $(B)))
B = 

SRCS = $(addprefix srcs/,$(addsuffix .c, $(S)))
S = main 

COMPRESS = ar rcs
RM = rm -f
CFLAGS = -Wall -Wextra -Werror
CC = cc

OBJS = $(addprefix $(OBJS_DIR)/,$(SRCS:srcs/%.c=%.o))
BONUS_OBJS = $(addprefix $(OBJS_DIR_BONUS)/,$(BONUS:bonus/%.c=%.o))
OBJS_DIR = objs
OBJS_DIR_BONUS = objs_bonus

LIBFT_DIR = ./includes/libft
LIBFT = $(LIBFT_DIR)/libft.a

# Color codes
GREEN = \033[0;32m
RED = \033[0;31m
BLUE = \033[0;34m 
ORANGE = \033[0;33m
NC = \033[0m 

all: $(NAME) 
bonus: $(BONUS_NAME)

$(OBJS_DIR)/%.o: srcs/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR_BONUS)/%.o: bonus/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT)
	@echo "$(GREEN)$(NAME)$(NC) compiling..."
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)
	@echo "$(GREEN)$(NAME)$(NC) ready!"

$(BONUS_NAME): $(BONUS_OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) -o $(BONUS_NAME) $(BONUS_OBJS) $(LIBFT)
	@echo $(BONUS_NAME)ready!

$(LIBFT):
	@echo "$(ORANGE)libft$(NC)compiling..."
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory
	@echo "$(ORANGE)libft$(NC)ready!"

clean:
	@$(RM) -r $(OBJS_DIR)
	@$(RM) -r $(OBJS_DIR_BONUS)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(BONUS_NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory

fcount:
	@echo "you wrote $(RED)$(shell cat $(SRCS) | wc -l)$(NC)lines of code"
#	@echo "you wrote quite some lines of code"
#	@cat $(SRCS) | wc -l | 

run: all
	./$(NAME) 

re: fclean all

.PHONY: all fclean clean re

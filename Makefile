# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lserrao- <lserrao-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/11 11:28:54 by lserrao-          #+#    #+#              #
#    Updated: 2024/12/14 15:22:55 by lserrao-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	pipex
CC			=	cc
CFLAGS		=	-g3 -Wall -Wextra -Werror -I $(H_DIR) -I $(LIBFT_DIR)
RM      	=	rm -rf

H_SRCS		=	pipex.h
H_DIR		=	includes/
HEADER		=	$(addprefix $(H_DIR), $(H_SRCS))

PIPEX		=	$(addprefix $(PIPEX_DIR), $(PIPEX_SRCS))
PIPEX_SRCS	=	main.c utils.c
PIPEX_DIR	=	src/
OBJ_DIR		=	build/
OBJ_M		=	$(addprefix $(OBJ_DIR), $(notdir $(PIPEX_SRCS:.c=.o)))

LIBFT_DIR	=	lib/libft/
LIBFT		=	$(LIBFT_DIR)libft.a

$(OBJ_DIR)%.o: $(PIPEX_DIR)%.c $(HEADER)
			@mkdir -p $(OBJ_DIR)
			@echo "Compilando" $<
			$(CC) $(CFLAGS) -c $< -o $@
			

$(NAME): $(OBJ_M) $(LIBFT)
			$(CC) $(CFLAGS) $(OBJ_M) $(LIBFT) -o $(NAME)
			@echo "\n$(GREEN)Execution completed, $(NAME) created!$(DEFAULT)"

$(LIBFT):
			@make -C $(LIBFT_DIR) all bonus new_fun
			@touch $(LIBFT)

all:		$(NAME)

clean:
			@$(RM) $(OBJ_M)
			@make clean -C $(LIBFT_DIR)
			@rm -rf $(LIBFT_DIR)/*.o
			@rm -rf $(LIBFT_DIR)/get_next_line/*.o
			@echo -e "\n$(GREEN)Cleaning completed!$(DEFAULT)"

fclean: clean
			@$(RM) $(NAME)
			@make fclean -C $(LIBFT_DIR)
			@rm -rf $(LIBFT_DIR)/*.a
			@rm -rf $(LIBFT_DIR)/get_next_line/*.a
			@echo -e "\n\e$(GREEN)Complete cleaning completed!$(DEFAULT)"

re:	fclean all

.PHONY:		all clean fclean re

#/********| Shell Collors |********/#

RED	   := \033[1;31m
GREEN	:= \033[1;32m
YELLOW	 := \033[1;33m
PURPLE	  := \033[1;35m
CYAN	   := \033[1;36m
DEFAULT		:= \033[0m

#/*********************************/#
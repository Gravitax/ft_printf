# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maboye <maboye@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/06 14:36:31 by maboye            #+#    #+#              #
#    Updated: 2019/08/06 15:16:01 by maboye           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BLACK	=	\033[30m
RED		=	\033[31m
GREEN	=	\033[32m
YELLOW	=	\033[33m
BLUE	=	\033[34m
PURPLE	=	\033[35m
TUR		=	\033[36m
WHITE	=	\033[37m
END		=	\033[0m

UP 		=	\033[A
CUT 	=	\033[K

# project
NAME	=	ft_printf
OS		=	$(shell uname)

# src / obj files
SRC		=	main.c

OBJ		=	$(SRC:.c=.o)

# compiler
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -g

# ft library
FT		=	./libft/
FT_LIB	=	$(addprefix $(FT),libft.a)
FT_INC	=	-I ./libft

# printf library
PF		=	./lib_printf/
PF_LIB	=	$(addprefix $(PF),ft_printf.a)
PF_INC	=	-I ./lib_printf/includes

all: 		$(FT_LIB) $(PF_LIB) $(NAME)

obj:
			mkdir -p $(OBJDIR)

%.o:		%.c
			@echo "${BLUE}compiling [$@] ...${END}"
			@$(CC) $(CFLAGS) $(FT_INC) $(PF_INC) -c -o $@ $<
			@printf "$(UP)$(CUT)"

$(FT_LIB):
			@$(MAKE) -C $(FT)
			@echo "${GREEN}[LIBRARY COMPILED]${END}"

$(PF_LIB):	$(FT_LIB)
			@$(MAKE) -C $(PF)
			@echo "${GREEN}[PF_LIBRARY COMPILED]${END}"

$(NAME):	$(OBJ) $(FT_LIB) $(PF_LIB)
			@$(CC) $(CFLAGS) $(OBJ) $(FT_LIB) $(PF_LIB) -o $@
			@echo "${GREEN}[$@ COMPILED]${END}"

clean:
			@/bin/rm -rf $(OBJ)
			@$(MAKE) -C $(FT) clean
			@$(MAKE) -C $(PF) clean
			@echo "${PURPLE}[.o deleted]${END}"

fclean:		clean
			@/bin/rm -rf $(NAME)
			@$(MAKE) -C $(FT) fclean
			@$(MAKE) -C $(PF) fclean
			@echo "${RED}[$(NAME) deleted]${END}"
			@echo "${RED}[libft.a deleted]${END}"
			@echo "${RED}[ft_printf.a deleted]${END}"

re:			fclean all

.PHONY:		all clean fclean re

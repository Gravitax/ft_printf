# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maboye <maboye@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/31 12:01:33 by maboye            #+#    #+#              #
#    Updated: 2019/08/06 14:56:06 by maboye           ###   ########.fr        #
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
NAME	=	ft_printf.a
OS		=	$(shell uname)

# directories
SRCDIR	=	./srcs
INCDIR	=	./includes
OBJDIR	=	./obj

# src / obj files
SRC		=	ft_printf.c
INC		=	ft_printf.h

OBJ		=	$(addprefix $(OBJDIR)/,$(SRC:.c=.o))
HEADER	=	$(addprefix $(INCDIR)/,$(INC))

# compiler
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -g

# ft library
FT		=	../libft/
FT_LIB	=	$(addprefix $(FT),libft.a)
FT_INC	=	-I ./libft
FT_LNK	=	-L ./libft -lft

all: 		obj $(FT_LIB) $(NAME)

obj:
			mkdir -p $(OBJDIR)

$(OBJDIR)/%.o:$(SRCDIR)/%.c $(HEADER)
			@echo "${TUR}compiling [$@] ...${END}"
			@$(CC) $(CFLAGS) $(FT_INC) -I $(INCDIR) -c -o $@ $<
			@printf "$(UP)$(CUT)"

$(FT_LIB):
			@$(MAKE) -C $(FT)

$(NAME):	$(OBJ) $(FT_LIB)
			@ar rcs $(NAME) $(OBJ)

clean:
			@/bin/rm -rf $(OBJDIR)

fclean:		clean
			@/bin/rm -rf $(NAME)

re:			fclean all

.PHONY:		all clean fclean re

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/15 16:57:29 by cdarrell          #+#    #+#              #
#    Updated: 2021/10/15 17:01:04 by cdarrell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libftprintf.a

HEADER		=	ft_printf.h
LIBFT_DIR	=	libft
LIBFT_LIB	=	libft.a

CC			=	gcc
FLAGS		=	-Wall -Wextra -Werror

SRC			=	ft_printf.c \
				ft_printf_pars.c \
				ft_printf_utils.c \
				ft_libft_utils.c \
				ft_printf_type_c_s_pers.c \
				ft_printf_type_d_i_u.c \
				ft_printf_type_p_x_X.c
				
OBJ_DIR		=	obj

OBJ 		=	$(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

RM_DIR		=	rm -rf
RM_FILE		=	rm -f

LIBC		=	ar -rcs

INCLUDES	= 	-I .

${NAME}:	${OBJ}
			@make -C ${LIBFT_DIR}/ all
			@cp $(LIBFT_DIR)/$(LIBFT_LIB) $(NAME)
			@${LIBC} $(NAME) $(OBJ)
			@echo "\tCompiling..." [ $(NAME) ] $(SUCCESS)

$(OBJ)		:	| $(OBJ_DIR)

$(OBJ_DIR):
			@mkdir -p $(OBJ_DIR)
			
$(OBJ_DIR)/%.o :	%.c $(HEADER) Makefile
					@${CC} $(CFLAGS) $(INCLUDES) -o $@ -c $<
#COLORS
C_NO="\033[00m"
C_OK="\033[32m"
C_GOOD="\033[32m"

#DEBUG
SUCCESS		=	$(C_GOOD)SUCCESS$(C_NO)
OK			=	$(C_OK)OK$(C_NO)
			
all:	$(NAME)

bonus:	${NAME}	
			
clean:
		@make -C ${LIBFT_DIR}/ clean
		@${RM_DIR} ${OBJ_DIR}
		@echo "\tCleaning..." [ $(NAME) ] $(OK)
		
fclean:	clean
		@${RM_FILE} libft/$(LIBFT_LIB) > /dev/null
		@echo "\tDeleting..." [ $(LIBFT_LIB) ] $(OK)
		@${RM_FILE} $(NAME)
		@echo "\tDeleting..." [ $(NAME) ] $(OK)
		
re:		fclean all

.PHONY: all clean fclean re


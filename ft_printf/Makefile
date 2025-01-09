# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hpehliva <hpehliva@student.42heilbronn.de  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/06 10:42:11 by hpehliva          #+#    #+#              #
#    Updated: 2024/11/06 13:02:59 by hpehliva         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

CC = cc

CFLAGS = -Wall -Werror -Wextra

AR = ar rcs

RM = rm -rf

OBJDIR = Objects

SRCS = 	ft_printf.c \
		ft_printf_utils.c \
		ft_printf_utils2.c 

OBJS = ${SRCS:.c=.o}

OBJSPATH = $(addprefix $(OBJDIR)/, $(OBJS))

all: ${NAME}

${NAME}: ${OBJSPATH}
	${AR} ${NAME} ${OBJSPATH}

${OBJDIR}/%.o: %.c
	@mkdir -p ${OBJDIR}
	${CC} ${CFLAGS} -o $@ -c $<

clean:  
	${RM} ${OBJDIR}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re

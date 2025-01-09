# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hpehliva <hpehliva@student.42heilbronn.de  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/23 15:30:31 by hpehliva          #+#    #+#              #
#    Updated: 2024/12/23 15:30:33 by hpehliva         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:


NAME        = so_long
RM          = rm -f
RM_DIR      = rm -rf

LIBFTDIR    = libft
LIBFT       = $(LIBFTDIR)/libft.a

FT_PRINTF_DIR   = ft_printf
FT_PRINTF       = $(FT_PRINTF_DIR)/libftprintf.a

MLX42_DIR   = MLX42
MLX42_URL	= https://github.com/codam-coding-college/MLX42.git
MLX42_LIB   = $(MLX42_DIR)/build/libmlx42.a

INCLUDE     = -I$(MLX42_DIR)/include -I header -I libft
LDINCLUDE   = -L$(MLX42_DIR)/build -lmlx42 -L$(LIBFTDIR) -lft -L$(FT_PRINTF_DIR) -lftprintf -lglfw -framework Cocoa -framework OpenGL -framework IOKit
CFLAGS      = -Wextra -Wall -Werror -g $(INCLUDE)

SRCS = \
    srcs/main.c \
    srcs/check_maps.c \
    srcs/init_maps.c \
    srcs/init_png.c \
    srcs/key_up.c \
    srcs/key_down.c \
    srcs/key_left.c \
    srcs/key_right.c \
    srcs/utils.c \
    srcs/utils_png.c \
    get_next_line/get_next_line.c \
    get_next_line/get_next_line_utils.c

OBJS = $(SRCS:.c=.o)

all:    $(NAME)

$(LIBFT):
	make -C $(LIBFTDIR) && make clean -C $(LIBFTDIR)

$(FT_PRINTF):
	make -C $(FT_PRINTF_DIR) && make clean -C $(FT_PRINTF_DIR)

$(MLX42_DIR):
	git clone $(MLX42_URL) $(MLX42_DIR)

$(MLX42_LIB): $(MLX42_DIR)
		 cd $(MLX42_DIR) && cmake -B build && cmake --build build

$(NAME):    $(MLX42_LIB) $(LIBFT) $(FT_PRINTF) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDINCLUDE) -o $(NAME)
	echo "So_long and MLX compiled successfully!"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM_DIR) $(OBJS)
	rm -rf $(MLX42_DIR) clean
	echo "Object files cleaned successfully!"

fclean: clean
	$(RM) $(NAME)
	make fclean -C $(LIBFTDIR)
	make fclean -C $(FT_PRINTF_DIR)
	echo "All files cleaned successfully!"

re: fclean all

.PHONY: all clean fclean re

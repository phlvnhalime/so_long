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
    srcs/position_of_player.c \
    srcs/utils.c \
    srcs/init_png2.c \
    srcs/free_malloc.c \
    srcs/rules_map.c \
    get_next_line/get_next_line.c \
    get_next_line/get_next_line_utils.c

OBJS = $(SRCS:.c=.o)

all:    $(NAME)
	@echo "\033[1;33m" # Yellow color for Star Wars style
	@echo "	██████╗ ██████╗  ██████╗  ██████╗ ██╗   ██╗     ██████╗ ███████╗    ██╗    ██╗ █████╗ ██╗   ██╗ "
	@echo "	██╔════╝ ██╔══██╗██╔═══██╗██╔════╝ ██║   ██║    ██╔═══██╗██╔════╝    ██║    ██║██╔══██╗╚██╗ ██╔╝"
	@echo "	██║  ███╗██████╔╝██║   ██║██║  ███╗██║   ██║    ██║   ██║█████╗      ██║ █╗ ██║███████║ ╚████╔╝ "
	@echo "	██║   ██║██╔══██╗██║   ██║██║   ██║██║   ██║    ██║   ██║██╔══╝      ██║███╗██║██╔══██║  ╚██╔╝  "
	@echo "	╚██████╔╝██║  ██║╚██████╔╝╚██████╔╝╚██████╔╝    ╚██████╔╝██║         ╚███╔███╔╝██║  ██║   ██║   "
	@echo "	╚═════╝ ╚═╝  ╚═╝ ╚═════╝  ╚═════╝  ╚═════╝      ╚═════╝ ╚═╝          ╚══╝╚══╝ ╚═╝  ╚═╝   ╚═╝    "
	@echo "\033[0m" # Reset color
	@echo "\033[1;3m	Five years after the fall of the Empire, a Mandalorian bounty hunter collects a fugitive (and saves the fugitive's life)\033[0m"
	@echo "\033[1;3m	After a scuffle in a bar on the ice planet Pagodon. Returning to the planet Nevarro in his ship, the Razor Crest,\033[0m"
	@echo "\033[1;3m	he unknowingly embarks on a journey that will intertwine with the fates of many. At the heart of this journey is the mysterious child\033[0m"
	@echo "\033[1;3m	"Grogu". The Mandalorian's mission to deliver the child to an enigmatic Imperial client sets the stage for an adventure that challenges\033[0m"
	@echo "\033[1;3m	His loyalties and reveals the lingering presence of the Empire in the galaxy.\033[0m"
# Compile libft
$(LIBFT):
	make -C $(LIBFTDIR) && make clean -C $(LIBFTDIR)

# Compile ft_printf
$(FT_PRINTF):
	make -C $(FT_PRINTF_DIR) && make clean -C $(FT_PRINTF_DIR)

# Final target to build the executable
$(NAME):    $(MLX42_LIB) $(LIBFT) $(FT_PRINTF) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDINCLUDE) -o $(NAME)
	echo "\033[1;32m So_long and MLX compiled successfully!\033[0m"

# Compile each source file to an object
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean object files
clean:
	$(RM_DIR) $(OBJS)
	@echo "\033[1;31m"
	@echo "	████████╗██╗  ██╗███████╗    ███████╗███╗   ██╗██████╗ 	"
	@echo "	╚══██╔══╝██║  ██║██╔════╝    ██╔════╝████╗  ██║██╔══██╗	"
	@echo "	   ██║   ███████║█████╗      █████╗  ██╔██╗ ██║██║  ██║	"
	@echo "	   ██║   ██╔══██║██╔══╝      ██╔══╝  ██║╚██╗██║██║  ██║	"
	@echo "	   ██║   ██║  ██║███████╗    ███████╗██║ ╚████║██████╔╝	"
	@echo "	   ╚═╝   ╚═╝  ╚═╝╚══════╝    ╚══════╝╚═╝  ╚═══╝╚═════╝ 	"
	@echo "\033[0m"                                                   

# Full clean (also remove MLX42 build directory)
fclean: clean
	$(RM) $(NAME)
	make fclean -C $(LIBFTDIR)
	make fclean -C $(FT_PRINTF_DIR)
	echo "\033[1;32m All files cleaned successfully!\033[0m"

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re
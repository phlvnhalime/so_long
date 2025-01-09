/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 16:27:20 by hpehliva          #+#    #+#             */
/*   Updated: 2024/12/23 16:27:21 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "MLX42/MLX42.h"
#include "../libft/libft.h"
#include "../get_next_line/get_next_line.h"
#include "../ft_printf/ft_printf.h"

#define WIDTH 2200
#define HEIGHT 1200

typedef struct  s_player
{
    mlx_image_t *player_image;
    char *png_path;
    int x_vector;
    int y_vector;
    int moves;
    
} t_player;


typedef struct s_game
{
    mlx_t   *mlx;
    char    **map;
    char    *map_line;
    int     last_column;
    int     last_row;
    int     collactable;
    t_player  *player;
    
} t_game;

enum e_keycode
{
	KEY_UP = 87,
	KEY_DOWN = 83,
	KEY_LEFT = 65,
	KEY_RIGHT = 68,
	RESET = 15,
	ESC = 256
};


void    read_arg(char *av);

void    read_map(t_game *masters_of_war);
void    check_map(t_game *mow, char   **map);
bool is_surrounded(t_game *mow);
bool    is_rectangular(char **map);
bool door_player(t_game *mow);
bool minimal_map(t_game *mow);
bool    valid_path(t_game *mow);

//free 
void	error_free(t_game *mow);
void    matrix_free(char **str);
void    free_visited(char **visited, int row);

// Images
void    player(t_game *yoda, int x, int y);
void    outside_wall(t_game *game, int column, int row);
void    inner_wall(t_game *game, int column, int row);
void    background(t_game *game, int column, int row);
void    collactable(t_game *game, int column, int row);
void    darth_vader(t_game *game, int column, int row);
void    door(t_game *game, int column, int row);

// Position of player!
void    current_position(t_game *game);
bool    end_rule(t_game *game, char **pixel, int row, int col);
char    **before_of_visited(t_game *game);
void    dfs(t_game *game, char **visited, int row, int col);
bool    end_rule(t_game *game, char **pixel, int row, int col);

// initialized map

void    initialized_map(t_game *darth_vader, char **map);
void    put_png(char symbol, t_game *mow, int x, int y);

//Movements

bool key_up(t_game *mow);
bool move_up_map(t_game *mow, int x, int y);
void    mission_completed(t_game *mow);
bool key_down(t_game *mow);
bool move_down_map(t_game *mow, int x, int y);
bool key_left(t_game *mow);
bool move_left_map(t_game *mow, int x, int y);
bool key_right(t_game *mow);
bool move_right_map(t_game *mow, int x, int y);
bool key_right(t_game *mow);
bool move_right_map(t_game *mow, int x, int y);


#endif
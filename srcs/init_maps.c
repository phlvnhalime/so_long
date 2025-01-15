/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_maps.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 18:24:06 by hpehliva          #+#    #+#             */
/*   Updated: 2024/12/29 18:24:08 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

/*
	To Do List:
	-found the images which you can use for this game.
	-initialized your photos.
	-Create a maps.
	-Put your player
	- Create a exit place
	<character> = 0 -> it is mean this is background.
	<character> = 1 -> this is wall(Add millennium falcon picture)
	<character> = E -> Exit
	<character> = C -> Collactable
	<character> = N -> Darth Vather!
	<character> = P -> player’s starting position.

*/
void	initialized_map(t_game *mow, char **map)
{
	int	i;
	int	column;

	column = 0;
	i = 0;
	while (map[column])
	{
		i = 0;
		while (map[column][i] != 0)
		{
			put_png(map[column][i], mow, i, column);
			i++;
		}
		column++;
	}
	player(mow, mow->player->x_vector, mow->player->y_vector);
}

/*
	Check the codes for image:
		-mlx_image_to_window;
		-mlx_texture_to_image;
		-mlx_load_png;
		-mlx_delete_texture;
*/
void	put_png(char symbol, t_game *mow, int x, int y)
{
	if (symbol == '0')
		background(mow, x, y);
	else if (symbol == '1' && (x == 0 || y == 0 || y == mow->last_row
			|| x == mow->last_column - 1))
		outside_wall(mow, x, y);
	else if (symbol == '1')
		inner_wall(mow, x, y);
	else if (symbol == 'E')
		door(mow, x, y);
	else if (symbol == 'C')
	{
		background(mow, x, y);
		collactable(mow, x, y);
	}
	else if (symbol == 'P')
	{
		mow->player->x_vector = x;
		mow->player->y_vector = y;
		background(mow, x, y);
	}
}

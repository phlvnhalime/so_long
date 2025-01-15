/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_down.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 17:07:28 by hpehliva          #+#    #+#             */
/*   Updated: 2025/01/02 17:07:29 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

bool	key_down(t_game *mow)
{
	int	x;
	int	y;

	x = mow->player->x_vector;
	y = mow->player->y_vector;
	if (move_down_map(mow, x, y + 1) == true)
	{
		mow->player->player_image->instances[0].y += 32;
		moves(mow, x, y);
		mow->player->y_vector += 1;
		mow->player->moves++;
		ft_printf("Player is moving = %d\n", mow->player->moves);
		mlx_delete_image(mow->mlx, mow->player->player_image);
		player(mow, x, y + 1);
	}
	return (true);
}

bool	move_down_map(t_game *mow, int x, int y)
{
	ft_printf("Move DOWN: x=%d, y=%d, map[%d][%d]=%c\n", x, y, y, x,
		mow->map[y][x]);
	if (mow->last_row == y)
	{
		ft_printf("You can't go down!\n");
		return (false);
	}
	if (mow->map[y][x] == '1')
	{
		ft_printf("Be CAREFULL!! Does this look like a path to you?\n");
		return (false);
	}
	if (mow->map[y][x] == 'C')
	{
		ft_printf("The great reunion has happened! Eternity is near: %d\n",
			mow->collactable);
		background(mow, x, y);
	}
	return (true);
}

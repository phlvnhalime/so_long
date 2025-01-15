/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 17:11:03 by hpehliva          #+#    #+#             */
/*   Updated: 2025/01/11 17:11:04 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

bool	is_rectangular(char **map)
{
	size_t	length;
	int		i;

	i = 1;
	if (!map || !map[0])
		return (false);
	length = ft_strlen(map[0]);
	while (map[i])
	{
		if (ft_strlen(map[i]) != length)
			return (false);
		i++;
	}
	return (true);
}

bool	is_surrounded(t_game *mow)
{
	int	i;
	int	col;

	i = 0;
	col = 0;
	if (!mow || !mow->map)
		return (false);
	while (mow->map[i])
	{
		if (mow->map[i][0] != '1' || mow->map[i][mow->last_column - 1] != '1')
			return (false);
		i++;
	}
	while (col < mow->last_column)
	{
		if (mow->map[0][col] != '1' || mow->map[mow->last_row][col] != '1')
			return (false);
		col++;
	}
	return (true);
}

bool	valid_path(t_game *mow)
{
	int	cur_x;
	int	cur_y;

	if (!mow || !mow->map)
		return (false);
	current_position(mow);
	cur_x = mow->player->x_vector;
	cur_y = mow->player->y_vector;
	if (end_rule(mow, mow->map, cur_y, cur_x) == false)
		return (false);
	return (true);
}

bool	minimal_map(t_game *mow)
{
	int		x;
	int		collactable_index;
	char	*str;

	x = -1;
	collactable_index = 0;
	if (!mow || !mow->map)
		return (false);
	while (mow->map[++x])
	{
		str = mow->map[x];
		while (*str != '\0')
		{
			if (!ft_strchr("EP01C", *str))
				return (false);
			collactable_index += (*str == 'C');
			str++;
		}
	}
	if (collactable_index == 0)
		return (false);
	mow->collactable = collactable_index;
	return (true);
}

bool	door_player(t_game *mow)
{
	int	p;
	int	e;
	int	x;
	int	y;

	p = 0;
	e = 0;
	y = 0;
	while (mow->map[y])
	{
		x = 0;
		while (mow->map[y][x])
		{
			if (mow->map[y][x] == 'P')
				p++;
			if (mow->map[y][x] == 'E')
				e++;
			x++;
		}
		y++;
	}
	if (e != 1 || p != 1)
		return (false);
	return (true);
}

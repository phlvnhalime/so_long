/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 15:42:49 by hpehliva          #+#    #+#             */
/*   Updated: 2024/12/29 15:42:51 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	current_position(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (game->map[y] != NULL)
	{
		x = 0;
		while (game->map[y][x + 1])
		{
			if (game->map[y][x] == 'P')
			{
				game->player->x_vector = x;
				game->player->y_vector = y;
				return ;
			}
			x++;
		}
		y++;
	}
}

/*
	When i completed all collactable i have to quit
	otherwise that game must not be end.
*/

bool	end_rule(t_game *game, char **pixel, int row, int col)
{
	char	**visited;
	int		j;
	int		i;

	visited = before_of_visited(game);
	dfs(game, visited, row, col);
	i = 0;
	while (pixel[i])
	{
		j = 0;
		while (pixel[i][j])
		{
			if ((pixel[i][j] == 'C' && visited[i][j] == 'h')
				|| (pixel[i][j] == 'E' && visited[i][j] == 'h'))
				return (free_visited(visited, game->last_row + 1), false);
			j++;
		}
		i++;
	}
	matrix_free(visited);
	return (true);
}

char	**before_of_visited(t_game *game)
{
	char	**visited;
	int		i;
	int		j;

	i = 0;
	visited = malloc(sizeof(char **) * (game->last_row + 2));
	while (game->map[i])
	{
		j = 0;
		visited[i] = malloc(sizeof(char) * (game->last_column + 1));
		while (game->map[i][j])
		{
			visited[i][j] = 'h';
			j++;
		}
		visited[i][j] = '\0';
		i++;
	}
	visited[i] = NULL;
	return (visited);
}

void	get_directions(int directions[4][2])
{
	int	values[8];
	int	i;

	i = 0;
	values[0] = -1;
	values[1] = 0;
	values[2] = 1;
	values[3] = 0;
	values[4] = 0;
	values[5] = -1;
	values[6] = 0;
	values[7] = 1;
	while (i < 4)
	{
		directions[i][0] = values[i * 2];
		directions[i][1] = values[i * 2 + 1];
		i++;
	}
}

void	dfs(t_game *game, char **visited, int row, int col)
{
	int	directions[4][2];
	int	i;
	int	newrow;
	int	newcol;

	i = 0;
	visited[row][col] = 'b';
	get_directions(directions);
	while (i < 4)
	{
		newrow = row + directions[i][0];
		newcol = col + directions[i][1];
		i++;
		if (newrow >= 0 && newcol >= 0 && newrow < game->last_row
			&& newcol < game->last_column && visited[newrow][newcol] == 'h'
			&& game->map[newrow][newcol] != '1')
		{
			dfs(game, visited, newrow, newcol);
		}
	}
}

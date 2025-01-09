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


/*
    -Open the file descriptor
        -Check it.
    -Read the file line by line with using get_next_line
    -Close fd.
*/
void    read_arg(char *file_name)
{
	int	len;
	int	fd;

	len = ft_strlen(file_name);
	if (len > 4 && (ft_strncmp(file_name + len - 4, ".ber", 4) == 0))
	{
		fd = open(file_name, O_RDONLY);
		if (fd < 0)
		{
			perror("Open");
			exit (EXIT_FAILURE);
		}
	}
	else
	{
		ft_putstr_fd("Error. Map should be '.ber' file", 2);
		exit (EXIT_FAILURE);
	}
	close(fd);
}

void    current_position(t_game *game)
{
    int x;
    int y;

    y = 0;
    while(game->map[y] != NULL)
    {
        x = 0;
        while(game->map[y][x])
        {
            if(game->map[y][x] == 'P')
            {
                game->player->x_vector = x;
                game->player->y_vector = y;
                return ;
            }
            x++;
        }
        y++;
    }
    ft_putendl_fd("Error. Player position not found!", 2);
    exit(EXIT_FAILURE);
}

void    free_visited(char **visited, int row)
{
    int k = 0;
    while(k < row)
    {
       free(visited[k]);
       k++;
    }
    free(visited);
}
/*
    When i completed all collactable i have to quit
    otherwise that game must not be end.
*/

bool    end_rule(t_game *game, char **pixel, int row, int col)
{
    char    **visited;
    int j;
    int i;

    visited = before_of_visited(game);
    dfs(game, visited, row, col);
    i = 0;
    while(visited[i])
    {
        ft_printf("%s\n", visited[i]);
        i++;
    }
    i = 0;
    while(pixel[i])
    {
        j = 0;
        while(pixel[i][j])
        {
            if((pixel[i][j] == 'C' && visited[i][j] == 'h') || (pixel[i][j] == 'E' && visited[i][j] == 'h'))
            {
                free_visited(visited,game->last_row + 1);
                return false;
            }
            j++;
        }
        i++;
    }
    int x = 0;
    while(visited[x] != NULL)
    {
        free(visited[x]);
        x++;
    }
    free(visited);
    return true;
}

char    **before_of_visited(t_game *game)
{
    char **visited;
    int i;
    int j;
    i = 0;
    visited = malloc(sizeof(char **) * (game->last_row + 2));
    while(game->map[i])
    {
        j=0;
        visited[i] = malloc (sizeof(char) * (game->last_column + 1));
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


void    dfs(t_game *game, char **visited, int row, int col)
{
    int	directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};;
	int	i;
	int	newrow;
	int	newcol;

	visited[row][col] = 'h';
	i = 0;
	while (i < 4)
	{
		newrow = row + directions[i][0];
		newcol = col + directions[i][1];
		i++;
		if (newrow >= 0 && newcol >= 0 && newrow <= game->last_row && newcol <= game->last_column && visited[newrow][newcol] == 'h' && game->map[newrow][newcol] != '1')
		{
			dfs(game, visited, newrow, newcol);
		}
	}
}

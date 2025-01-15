/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_maps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 18:23:41 by hpehliva          #+#    #+#             */
/*   Updated: 2024/12/29 18:23:45 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static char	**read_map_file(t_game *masters_of_war)
{
	char	**tmp;
	int		fd;
	int		i;

	i = 0;
	tmp = (char **)malloc(sizeof(char **) * get_size(masters_of_war));
	if (!tmp)
		return (ft_putendl_fd("Error: Memory allocation failed for tmp", 2),
			exit(1), NULL);
	fd = open(masters_of_war->map_line, O_RDONLY);
	if (fd < 0)
		return (ft_putendl_fd("Error: Failed to open map file", 2), exit(1),
			NULL);
	tmp[i] = get_next_line(fd);
	while (tmp[i])
	{
		if (tmp[i][ft_strlen(tmp[i]) - 1] == '\n')
			tmp[i][ft_strlen(tmp[i]) - 1] = '\0';
		i++;
		tmp[i] = get_next_line(fd);
	}
	close(fd);
	if (!tmp[0])
		return (ft_putendl_fd("Error: Map file is empty", 2), exit(1), NULL);
	return (tmp);
}

static void	allocate_map(t_game *masters_of_war, char **tmp)
{
	int	i;

	i = -1;
	masters_of_war->last_column = ft_strlen(tmp[0]);
	masters_of_war->map = malloc(sizeof(char **) * get_size(masters_of_war));
	if (!masters_of_war->map)
		return (ft_putendl_fd("Error: Memory allocation failed for map", 2),
			exit(1));
	while (tmp[++i])
	{
		masters_of_war->map[i] = malloc(sizeof(char)
				* (masters_of_war->last_column + 1));
		if (!masters_of_war->map[i])
		{
			ft_putendl_fd("Error: Memory allocation failed for map row", 2);
			exit(1);
		}
		ft_strncpy(masters_of_war->map[i], tmp[i], masters_of_war->last_column);
		masters_of_war->map[i][masters_of_war->last_column] = '\0';
	}
	masters_of_war->map[i] = NULL;
	masters_of_war->last_row = i - 1;
}

void	read_map(t_game *masters_of_war)
{
	char	**tmp;

	tmp = read_map_file(masters_of_war);
	if (!tmp)
		return ;
	allocate_map(masters_of_war, tmp);
	check_map(masters_of_war, tmp);
}

void	return_maps(t_game *mow, char *str, char **map)
{
	ft_putendl_fd(str, 2);
	matrix_free(mow->map);
	matrix_free(map);
	exit(EXIT_FAILURE);
}

void	check_map(t_game *mow, char **map)
{
	if (is_rectangular(map) == false)
		return_maps(mow, "Error: Map is not rectangular.", map);
	if (is_surrounded(mow) == false)
		return_maps(mow, "Error: Map is not surrounded by walls.", map);
	if (valid_path(mow) == false)
		return_maps(mow, "Error: No valid path to exit.", map);
	if (minimal_map(mow) == false)
		return_maps(mow, "Error: Map does not contain enough characters.", map);
	if (door_player(mow) == false)
		return_maps(mow,
			"Error: The player or door is missing or dublicated on the map.",
			map);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 17:14:31 by hpehliva          #+#    #+#             */
/*   Updated: 2025/01/11 17:14:37 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0' && i < len)
	{
		dst[i] = src[i];
		i++;
	}
	while (i < len)
	{
		dst[i] = '\0';
		i++;
	}
	return (dst);
}

int	get_size(t_game *mow)
{
	int		size;
	int		fd;
	char	*line;

	size = 0;
	fd = open(mow->map_line, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		size++;
	}
	free(line);
	close(fd);
	return (size + 1);
}

void	moves(t_game *mow, int x, int y)
{
	if (mow->map[y][x] == 'E' && mow->collactable == 0)
		mission_completed(mow);
	if (mow->map[y][x] == 'C')
	{
		mow->collactable--;
		mow->map[y][x] = '0';
	}
}

void	mission_completed(t_game *mow)
{
	mow->player->player_image->instances[0].y += 32;
	usleep(50000);
	ft_printf("MAY THE FORCE BE WITH YOU!\n");
	error_free(mow);
	exit(EXIT_SUCCESS);
}

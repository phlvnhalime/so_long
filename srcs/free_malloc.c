/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 16:57:46 by hpehliva          #+#    #+#             */
/*   Updated: 2025/01/11 16:57:47 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	error_free(t_game *mow)
{
	if (mow->player)
	{
		free(mow->player);
		mow->player = NULL;
	}
	if (mow->map)
	{
		matrix_free(mow->map);
	}
	free(mow);
}

void	matrix_free(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_visited(char **visited, int row)
{
	int	k;

	k = 0;
	while (k < row)
	{
		free(visited[k]);
		k++;
	}
	free(visited);
}

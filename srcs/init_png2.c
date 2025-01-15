/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_png.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 13:19:26 by hpehliva          #+#    #+#             */
/*   Updated: 2024/12/30 13:19:27 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	door(t_game *game, int column, int row)
{
	mlx_texture_t	*png;
	mlx_image_t		*img;
	int				x;
	int				y;

	x = column * 32;
	y = row * 32;
	png = mlx_load_png("textures/portal.png");
	if (!png)
	{
		ft_putendl_fd("the file of .png has an error!", 2);
		exit(1);
	}
	img = mlx_texture_to_image(game->mlx, png);
	if (!game->mlx)
	{
		ft_putendl_fd("Image Error", 2);
		exit(1);
	}
	if (mlx_image_to_window(game->mlx, img, x, y))
	{
		ft_putendl_fd("Image Error", 2);
		exit(1);
	}
	mlx_delete_texture(png);
}

void	background(t_game *game, int column, int row)
{
	mlx_texture_t	*png;
	mlx_image_t		*img;
	int				x;
	int				y;

	x = column * 32;
	y = row * 32;
	png = mlx_load_png("textures/background.png");
	if (!png)
	{
		ft_putendl_fd("the file of .png has an error!", 2);
		exit(1);
	}
	img = mlx_texture_to_image(game->mlx, png);
	if (!game->mlx)
	{
		ft_putendl_fd("Image Error", 2);
		exit(1);
	}
	if (mlx_image_to_window(game->mlx, img, x, y))
	{
		ft_putendl_fd("Image Error", 2);
		exit(1);
	}
	mlx_delete_texture(png);
}

void	collactable(t_game *game, int column, int row)
{
	mlx_texture_t	*png;
	mlx_image_t		*img;
	int				x;
	int				y;

	x = column * 32;
	y = row * 32;
	png = mlx_load_png("textures/mandalorian.png");
	if (!png)
	{
		return (ft_putendl_fd("the file of .png has an error!", 2), exit(1));
		exit(1);
	}
	img = mlx_texture_to_image(game->mlx, png);
	if (!game->mlx)
	{
		ft_putendl_fd("Image Error", 2);
		exit(1);
	}
	if (mlx_image_to_window(game->mlx, img, x, y))
	{
		ft_putendl_fd("Image Error", 2);
		exit(1);
	}
	mlx_delete_texture(png);
}

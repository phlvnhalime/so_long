/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_png.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 11:46:45 by hpehliva          #+#    #+#             */
/*   Updated: 2024/12/30 11:46:47 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	player(t_game *yoda, int column, int row)
{
	mlx_texture_t	*png;
	mlx_image_t		*img;
	int				x;
	int				y;

	x = column * 32;
	y = row * 32;
	png = mlx_load_png(yoda->player->png_path);
	if (!png)
		return (ft_putendl_fd("Png Error", 2), exit(1));
	img = mlx_texture_to_image(yoda->mlx, png);
	if (!img)
	{
		ft_putendl_fd("the image doesn't change as .png file!", 2);
		exit(1);
	}
	if (mlx_image_to_window(yoda->mlx, img, x, y))
	{
		ft_putendl_fd("Error!", 2);
		exit(1);
	}
	mlx_delete_texture(png);
	yoda->player->player_image = img;
}

void	outside_wall(t_game *game, int column, int row)
{
	mlx_texture_t	*png;
	mlx_image_t		*img;
	int				x;
	int				y;

	x = column * 32;
	y = row * 32;
	png = mlx_load_png("textures/outside_wall.png");
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

void	inner_wall(t_game *game, int column, int row)
{
	mlx_texture_t	*png;
	mlx_image_t		*img;
	int				x;
	int				y;

	x = column * 32;
	y = row * 32;
	png = mlx_load_png("textures/spaceship_wall.png");
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

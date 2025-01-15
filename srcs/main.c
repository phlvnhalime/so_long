/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 16:26:45 by hpehliva          #+#    #+#             */
/*   Updated: 2024/12/23 16:26:47 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	init_hook(mlx_key_data_t keys, void *game)
{
	t_game	*mow;
	int		keycode;

	mow = (t_game *)game;
	keycode = keys.key;
	if (keys.action == MLX_PRESS || keys.action == MLX_REPEAT)
	{
		if (keycode == ESC)
		{
			error_free(mow);
			mlx_close_window(mow->mlx);
			ft_putendl_fd("The END!", 1);
			exit(EXIT_SUCCESS);
		}
		else if (keycode == KEY_UP)
			key_up(mow);
		else if (keycode == KEY_DOWN)
			key_down(mow);
		else if (keycode == KEY_RIGHT)
			key_right(mow);
		else if (keycode == KEY_LEFT)
			key_left(mow);
	}
}

void	init_game(t_game *mow)
{
	mow->mlx = mlx_init(WIDTH, HEIGHT, "MASTERS_OF_WAR", true);
	if (!(mow->mlx))
	{
		puts(mlx_strerror(mlx_errno));
		exit(EXIT_FAILURE);
	}
	if (!mow->player)
	{
		perror("Player pointer is NULL");
		exit(EXIT_FAILURE);
	}
	mow->player->moves = 0;
	mow->player->png_path = "textures/yoda.png";
}

int	get_arguments(char *av[])
{
	t_game	*masters_of_war;

	masters_of_war = malloc(sizeof(t_game));
	if (!masters_of_war)
		exit(EXIT_FAILURE);
	masters_of_war->player = malloc(sizeof(t_player));
	if (!masters_of_war->player)
		return (free(masters_of_war), EXIT_FAILURE);
	masters_of_war->map_line = av[1];
	read_map(masters_of_war);
	if (!masters_of_war->map)
	{
		free(masters_of_war->player);
		free(masters_of_war);
		exit(EXIT_FAILURE);
	}
	init_game(masters_of_war);
	initialized_map(masters_of_war, masters_of_war->map);
	mlx_key_hook(masters_of_war->mlx, init_hook, masters_of_war);
	mlx_loop(masters_of_war->mlx);
	mlx_terminate(masters_of_war->mlx);
	error_free(masters_of_war);
	return (EXIT_SUCCESS);
}

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		ft_putendl_fd("Usage: <executable_name> <maps.ber>", 2);
		exit(EXIT_FAILURE);
	}
	if (!ft_strnstr(av[1], ".ber", ft_strlen(av[1])))
	{
		ft_putendl_fd("Error: Map file must have '.ber' extension", 2);
		exit(EXIT_FAILURE);
	}
	get_arguments(av);
	return (0);
}

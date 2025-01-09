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

/*
 * An image with an individual buffer that can be rendered.
 * Any value can be modified except the width/height and context.
 * 
 * @param width The width of the image.
 * @param height The height of the image.
 * @param pixels The literal pixel data.
 * @param instances An instance carrying the X, Y and Z location data.
 * @param count The element count of the instances array.
 * @param enabled If true the image is drawn onto the screen, else it's not.
 * @param context Abstracted OpenGL data.

typedef struct mlx_image
{
	const uint32_t	width;
	const uint32_t	height;
	uint8_t*		pixels;
	mlx_instance_t*	instances;
	size_t			count;
	bool			enabled;
	void*			context;
}	mlx_image_t;


 * Main MLX handle, carries important data in regards to the program.
 * @param window The window itself.
 * @param context Abstracted opengl data.
 * @param width The width of the window.
 * @param height The height of the window.
 * @param delta_time The time difference between the previous frame 
 * and the current frame.

typedef struct mlx
{
	void*		window;
	void*		context;
	int32_t		width;
	int32_t		height;
	double		delta_time;
}	mlx_t;

    create your visualizer in mlx_t link. 
    First create your game links
        -  mlx file.
        - map
        - map_path
        - player
    Create a player.
        - image
        - png file
    The game name masters_of_war
*/

/*
	for initialized game i have to add screen width and height
*/ 

void	error_free(t_game *mow)
{
	int i = 0;
	char **str = mow->map;
	while(str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
	free(mow->player);
	free(mow);
}

void	init_hook(mlx_key_data_t keys, void *game)
{
	t_game *mow;
	int keycode;

	mow = (t_game *)game;
	keycode = keys.key;
	if(keys.action == MLX_PRESS || keys.action == MLX_REPEAT)
	{
		if(keycode == ESC)
		{
			error_free(mow);
			mlx_close_window(mow->mlx);
			ft_putendl_fd("The END!", 1);
			exit(EXIT_SUCCESS);
		}
		else if(keycode == KEY_UP)
			key_up(mow);
		else if(keycode == KEY_DOWN)
			key_down(mow);
		else if(keycode == KEY_RIGHT)
			key_right(mow);
		else if(keycode == KEY_LEFT)
			key_left(mow);
	}
}

void	init_game(t_game *mow)
{
	mow->mlx = mlx_init(WIDTH, HEIGHT, "MASTERS_OF_WAR", true);
	if(!(mow->mlx))
	{
		puts(mlx_strerror(mlx_errno));
		exit(EXIT_FAILURE);
	}
	mow->player->moves = 0;
	mow->player->png_path = "images/yoda.png";
}


int main2(int ac, char *av[])
{
	t_game	*masters_of_war;

	if(ac != 2)
		return (perror("Usage: <executable_name> <maps.ber>\n"), 1);
	read_arg(av[1]);
	masters_of_war = malloc(sizeof(t_game));
	if(masters_of_war == NULL)
		exit(EXIT_FAILURE);
	masters_of_war->player = malloc(sizeof(t_player));
	if(masters_of_war->player == NULL)
		exit(EXIT_FAILURE);
	masters_of_war->map_line = av[1];
	read_map(masters_of_war);
	init_game(masters_of_war);
	initialized_map(masters_of_war, masters_of_war->map);
	mlx_key_hook(masters_of_war->mlx, init_hook, masters_of_war);// Add hooks and moves.
	mlx_loop(masters_of_war->mlx);
	mlx_terminate(masters_of_war->mlx);
	error_free(masters_of_war);
	ft_putendl_fd("Good Bye!", 1);
	return (EXIT_SUCCESS);
}

int main(int ac, char *av[])
{
	main2(ac,av);
	return 0;
}
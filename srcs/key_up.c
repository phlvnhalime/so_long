/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_up.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 16:43:42 by hpehliva          #+#    #+#             */
/*   Updated: 2025/01/02 16:43:43 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"



void    mission_completed(t_game *mow)
{
    mow->player->player_image->instances[0].y += 32;
    usleep(50000);
    ft_printf("Congrats!\n");
    error_free(mow);
    exit(EXIT_SUCCESS);

}

bool key_up(t_game *mow)
{
    int x;
    int y;

    x = mow->player->x_vector;
    y = mow->player->y_vector;
    if (move_up_map(mow, x, y - 1) == true)
    {
        mow->player->player_image->instances[0].y -= 32;
        if(mow->map[y][x] == 'E' && mow->collactable == 0)
            mission_completed(mow);
        if(mow->map[y][x] == 'C')
        {
            mow->collactable--;
            mow->map[y][x] = '0';
        }
        mow->player->y_vector -= 1;
        mow->player->moves++;
        ft_printf("Player is moving = %d\n", mow->player->moves);
        // Tum hareketlerde bu ikisini ekle!
        mlx_delete_image(mow->mlx, mow->player->player_image);
        player(mow, x, y - 1);
    }
    return true;
}

bool move_up_map(t_game *mow, int x, int y)
{
    if(y == 0)
        return false;
    if(mow->map[y][x] == '1')
        return false;
    if(mow->map[y][x] == 'C')
        background(mow, x, y);
    return true;
}

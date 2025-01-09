/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_right.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 17:25:22 by hpehliva          #+#    #+#             */
/*   Updated: 2025/01/02 17:25:23 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"


bool key_right(t_game *mow)
{
    int x;
    int y;

    x = mow->player->x_vector;
    y = mow->player->y_vector;
    if (move_up_map(mow, x + 1, y ) == true)
    {
        mow->player->player_image->instances[0].x += 32;
        if(mow->map[y][x] == 'E' && mow->collactable == 0)
            mission_completed(mow);
        if(mow->map[y][x] == 'C')
        {
            mow->collactable--;
            mow->map[y][x] = '0';
        }
        mow->player->x_vector += 1;
        mow->player->moves++;
        ft_printf("Player is moving = %d\n", mow->player->moves);
        // Tum hareketlerde bu ikisini ekle!
        mlx_delete_image(mow->mlx, mow->player->player_image);
        player(mow, x + 1, y );
    }
    return true;
}

bool move_right_map(t_game *mow, int x, int y)
{
    if(mow->last_column -1 == x)
        return false;
    if(mow->map[y][x] == '1')
        return false;
    if(mow->map[y][x] == 'C')
        background(mow, x, y);
    return true;
}
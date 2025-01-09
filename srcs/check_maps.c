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

int get_size(t_game *mow)
{
    int size;
    int fd;
    char *line;

    size = 0;
    fd = open(mow->map_line, O_RDONLY);
    if(fd < 0)
        return 0;
    
    while((line = get_next_line(fd)))
    {
        free(line);
        size++;
    }
    // free(line);
    close(fd);
    return (size);
}

void    read_map(t_game *masters_of_war)
{
    char **tmp;
    int fd;
    int i;
    int lines;

    lines = get_size(masters_of_war);
    if(lines <= 0)
    {
        ft_putendl_fd("Error. Empty map or cannot open file!", 2);
        exit(1);
    }

    tmp = malloc(sizeof(char *) * (lines + 1));
    if(!tmp)
        return (perror("malloc"), exit(1), (void)0);
    fd = open(masters_of_war->map_line, O_RDONLY);
    if(fd < 0)
    {
        free(tmp);
        ft_putendl_fd("Error. Cannot open file!", 2);
        exit(1);
    }
    i = 0;
    while (i < lines)
    {
        tmp[i] = get_next_line(fd);
        if (!tmp[i])
            break; // In case GNL returns NULL sooner
        // Optionally remove trailing '\n' if needed:
        // e.g. if (tmp[i][ft_strlen(tmp[i]) - 1] == '\n') tmp[i][ft_strlen(tmp[i]) - 1] = '\0';
        i++;
    }
    tmp[i] = NULL;
    close(fd);
    masters_of_war->last_column = ft_strlen(tmp[0]);
    masters_of_war->map = malloc(sizeof(char *) * (i + 1));
    if(!masters_of_war->map)
        return (perror("malloc"), exit(1), (void)0);
    int j = 0;
    while(j < i)
    {
        masters_of_war->map[j] = malloc (sizeof(char) * masters_of_war->last_column + 1);
        if (!masters_of_war->map[j])
            return (perror("malloc"), exit(1), (void)0);
        ft_strlcpy(masters_of_war->map[j], tmp[j], masters_of_war->last_column + 1);
        j++;
    }
    masters_of_war->map[i] = NULL;
    masters_of_war->last_row = i - 1;
    j = 0;
    while(j < i)
        free(tmp[j++]);
    free(tmp);

    printf("last_column: %d, last_row: %d\n", masters_of_war->last_column, masters_of_war->last_row);
    check_map(masters_of_war, masters_of_war->map);
}

/*
    NOTES: I need to create a maps way like map[x][y] for init.
    Add a check maps!
    Whe can check it!
    • The map must be rectangular.
    • The map must be closed/surrounded by walls. If it’s not, the program must return
        an error.
    • You have to check if there’s a valid path in the map.
    • You must be able to parse any kind of map, as long as it respects the above rules.
    • Another example of a minimal .ber map:
1111111111111111111111111111111111
1E0000000000000C00000C000000000001
1010010100100000101001000000010101
1010010010101010001001000000010101
1P0000000C00C0000000000000000000C1
1111111111111111111111111111111111
    • If any misconfiguration of any kind is encountered in the file, the program must
    exit in a clean way, and return "Error\n" followed by an explicit error message of
    your choice.
*/

void    matrix_free(char **str)
{
    int i = 0;
    while(str[i] != NULL)
    {
        free(str[i]);
        i++;
    }
    free(str);
}

void    return_maps(t_game  *mow, char *str, char **map)
{
    ft_putendl_fd(str, 2);
    matrix_free(mow->map);
    matrix_free(map);
    exit(EXIT_FAILURE);

}


void    check_map(t_game *mow, char   **map)
{
    if(is_rectangular(map) == false)
        return_maps(mow,"Map is not rectangular!", map);
    // Implement this code!
    if(is_surrounded(mow) == false)
    {

        return_maps(mow,"Map is not surrounded by walls!", map);
    }

    if(valid_path(mow) == false)
        return_maps(mow,"You don't have any way to exit!", map);
    if(minimal_map(mow) == false)
        return_maps(mow,"Map hasn't enough character!", map);
    if(door_player(mow) == false)
        return_maps(mow,"Map doesn't have any player and door!", map);
    matrix_free(mow->map);
    matrix_free(map);
    exit(EXIT_FAILURE);
}



bool is_surrounded(t_game *mow)
{
    int i;

    i = 0;
    while(i < mow->last_row)
    {
        if(mow->map[i][0] != '1' || mow->map[i][mow->last_column - 1] != '1')
            return (false);
        i++;
    }
    i = 0;
    while(i < mow->last_column)
    {
        if(mow->map[0][i] != '1' || mow->map[mow->last_row - 1][i] != '1')
            return (false);
        i++;
    }
    return (true);
}

bool    valid_path(t_game *mow)
{
    int cur_x;
    int cur_y;

    current_position(mow);
    cur_x = mow->player->x_vector;
    cur_y = mow->player->y_vector;
    if(end_rule(mow, mow->map, cur_y, cur_x) == false)
        return (false);
    return (true);
}

bool    is_rectangular(char **map)
{
    int i;
    size_t length;

    if (!map || !map[0])
        return (false);
    length = ft_strlen(map[0]);
    i = 1;
    while (map[i])
    {
        if (ft_strlen(map[i]) != length)
            return false;
        i++;
    }
    return true;
}

bool minimal_map(t_game *mow)
{
    int x;
    char *str;
    int collactable_index;

    collactable_index = 0;
    x = -1;
    while(mow->map[++x])
    {
        str = mow->map[x];
        while(*str != '\0')
        {
            if(!ft_strchr("EP01C", *str))
                return false;
            collactable_index += (*str == 'C');
            str++;
        }
    }
    if(collactable_index == 0)
        return false;
    mow->collactable = collactable_index;
    return true;
}

bool door_player(t_game *mow)
{
    int y;
    int x;
    int p;
    int e;

    p = 0;
    e = 0;
    y = 0;
    while(mow->map[y])
    {
        x = 0;
        while (mow->map[y][x])
        {
            if(mow->map[y][x] == 'P')
                p++;
            if(mow->map[y][x] == 'E')
                e++;
        }
        y++;
    }
    if(e != 1 || p != 1)
        return false;
    return true;
}


// int get_size(t_game *mow)
// {
//     int size;
//     int fd;
//     char *line;

//     size = 0;
//     fd = open(mow->map_line, O_RDONLY);
//     if (fd < 0)
//         return (0);
//     while ((line = get_next_line(fd)))
//     {
//         free(line);
//         size++;
//     }
//     close(fd);
//     return (size);
// }

// void free_partial_map(char **map, int rows_allocated)
// {
//     for (int i = 0; i < rows_allocated; i++)
//         free(map[i]);
//     free(map);
// }

// void read_map(t_game *masters_of_war)
// {
//     char **tmp;
//     int fd;
//     int i;
//     int lines;

//     // Get the number of lines in the map
//     lines = get_size(masters_of_war);
//     if (lines <= 0)
//     {
//         ft_putendl_fd("Error. Empty map or cannot open file!", 2);
//         exit(1);
//     }

//     // Allocate temporary storage for reading the map
//     tmp = malloc(sizeof(char *) * (lines + 1));
//     if (!tmp)
//         return (perror("malloc"), exit(1), (void)0);

//     // Open the map file
//     fd = open(masters_of_war->map_line, O_RDONLY);
//     if (fd < 0)
//     {
//         free(tmp);
//         ft_putendl_fd("Error. Cannot open file!", 2);
//         exit(1);
//     }

//     // Read each line from the file
//     i = 0;
//     while (i < lines && (tmp[i] = get_next_line(fd)))
//     {
//         // Remove trailing newline, if present
//         if (ft_strlen(tmp[i]) > 0 && tmp[i][ft_strlen(tmp[i]) - 1] == '\n')
//             tmp[i][ft_strlen(tmp[i]) - 1] = '\0';
//         i++;
//     }
//     tmp[i] = NULL; // Null-terminate the array
//     close(fd);

//     // Check for an empty or invalid map
//     if (!tmp[0])
//     {
//         free_partial_map(tmp, lines);
//         ft_putendl_fd("Error. Empty or invalid map!", 2);
//         exit(1);
//     }

//     // Set map dimensions
//     masters_of_war->last_column = ft_strlen(tmp[0]);
//     masters_of_war->map = malloc(sizeof(char *) * (i + 1));
//     if (!masters_of_war->map)
//         return (perror("malloc"), free_partial_map(tmp, i), exit(1), (void)0);

//     // Validate all rows have the same length
//     for (int j = 1; j < i; j++)
//     {
//         if ((int)ft_strlen(tmp[j]) != masters_of_war->last_column)
//         {
//             free_partial_map(tmp, i);
//             ft_putendl_fd("Error. Map rows are not of equal length!", 2);
//             exit(1);
//         }
//     }

//     // Copy the map to the game's map structure
//     for (int j = 0; j < i; j++)
//     {
//         masters_of_war->map[j] = malloc(sizeof(char) * (masters_of_war->last_column + 1));
//         if (!masters_of_war->map[j])
//             return (perror("malloc"), free_partial_map(masters_of_war->map, j), free_partial_map(tmp, i), exit(1), (void)0);
//         ft_strlcpy(masters_of_war->map[j], tmp[j], masters_of_war->last_column + 1);
//     }
//     masters_of_war->map[i] = NULL; // Null-terminate the map
//     masters_of_war->last_row = i - 1;

//     // Free temporary storage
//     for (int j = 0; j < i; j++)
//         free(tmp[j]);
//     free(tmp);

//     // Debug: Print map dimensions
//     printf("last_column: %d, last_row: %d\n", masters_of_war->last_column, masters_of_war->last_row);

//     // Validate the map
//     check_map(masters_of_war, masters_of_war->map);
// }

// void matrix_free(char **str)
// {
//     if (!str)
//         return;
//     for (int i = 0; str[i] != NULL; i++)
//         free(str[i]);
//     free(str);
// }

// void return_maps(t_game *mow, char *str)
// {
//     ft_putendl_fd(str, 2);
//     matrix_free(mow->map);
//     exit(EXIT_FAILURE);
// }

// void check_map(t_game *mow, char **map)
// {
//     if (!is_rectangular(map))
//         return_maps(mow, "Map is not rectangular!");

//     if (!is_surrounded(mow))
//         return_maps(mow, "Map is not surrounded by walls!");

//     if (!valid_path(mow))
//         return_maps(mow, "You don't have any way to exit!");

//     if (!minimal_map(mow))
//         return_maps(mow, "Map hasn't enough characters!");

//     if (!door_player(mow))
//         return_maps(mow, "Map doesn't have any player and door!");
// }

// bool is_surrounded(t_game *mow)
// {
//     for (int i = 0; i <= mow->last_row; i++)
//     {
//         if (!mow->map[i] || mow->map[i][0] != '1' || mow->map[i][mow->last_column - 1] != '1')
//             return false;
//     }

//     for (int i = 0; i < mow->last_column; i++)
//     {
//         if (!mow->map[0][i] || mow->map[mow->last_row][i] != '1')
//             return false;
//     }
//     return true;
// }

// bool valid_path(t_game *mow)
// {
//     int cur_x;
//     int cur_y;

//     current_position(mow);
//     cur_x = mow->player->x_vector;
//     cur_y = mow->player->y_vector;

//     if (cur_x < 0 || cur_y < 0 || cur_x >= mow->last_column || cur_y > mow->last_row)
//     {
//         printf("Invalid player position: x=%d, y=%d\n", cur_x, cur_y);
//         return false;
//     }

//     if (!end_rule(mow, mow->map, cur_y, cur_x))
//         return false;

//     return true;
// }

// bool is_rectangular(char **map)
// {
//     if (!map || !map[0])
//         return false;

//     size_t length = ft_strlen(map[0]);
//     for (int i = 1; map[i]; i++)
//     {
//         if (ft_strlen(map[i]) != length)
//             return false;
//     }
//     return true;
// }

// bool minimal_map(t_game *mow)
// {
//     int collactable_index = 0;

//     for (int x = 0; mow->map[x]; x++)
//     {
//         char *str = mow->map[x];
//         while (*str)
//         {
//             if (!ft_strchr("EP01C", *str))
//                 return false;
//             collactable_index += (*str == 'C');
//             str++;
//         }
//     }
//     if (collactable_index == 0)
//         return false;

//     mow->collactable = collactable_index;
//     return true;
// }

// bool door_player(t_game *mow)
// {
//     int p = 0;
//     int e = 0;

//     for (int y = 0; mow->map[y]; y++)
//     {
//         for (int x = 0; mow->map[y][x]; x++)
//         {
//             if (mow->map[y][x] == 'P')
//                 p++;
//             if (mow->map[y][x] == 'E')
//                 e++;
//         }
//     }
//     return (e == 1 && p == 1);
// }
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_available_test.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhypar <junhypar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 15:28:55 by junhypar          #+#    #+#             */
/*   Updated: 2020/11/06 17:39:25 by junhypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		check_available2(char **map, int i, int j)
{
	if (map[i - 1][j] != ' ' && map[i - 1][j] != '1')
		return(1);
	else if (map[i][j - 1] != ' ' && map[i][j - 1] != '1')
		return(1);
	else if (map[i + 1][j] != ' ' && map[i + 1][j] != '1')
		return(1);
	else if (map[i][j + 1] != ' ' && map[i][j + 1] != '1')
		return(1);
	return (0);
}

int		check_available(t_game *g, char **map, int i, int j)
{
	if (i == 0)
	{
		if (map[i][j] != ' ' && map[i][j] != '1')
			return (1);
	}
	else if (i == g->col - 1)
	{
		if (map[i][j] != ' ' && map[i][j] != '1')
			return (1);
	}
	else if (j == 0)
	{
		if (map[i][j] != ' ' && map[i][j] != '1')
			return (1);
	}
	else if (j == g->row - 1)
	{
		if (map[i][j] != ' ' && map[i][j] != '1')
			return (1);
	}
	else if (map[i][j] == ' ')
	{
		return (check_available2(map, i, j));
	}
	return (0);
}

void	find_location_of_player(t_game *g, int i, int j)
{
	g->x = j;
	g->y = i;
	g->player_cnt += 1;
	if (g->map[i][j] == 'S')
		rotate_vector(g, 180);
	else if (g->map[i][j] == 'W')
		rotate_vector(g, 90);
	else if (g->map[i][j] == 'E')
		rotate_vector(g, -90);
	else if (g->map[i][j] == 'N')
		rotate_vector(g, 0);
	g->map[i][j] = '0';
}

int		map_available_test(t_game *g)
{
	int i;
	int j;

	i = 0;
	while(i < g->col)
	{
		j = 0;
		while(j < g->row)
		{
			if (g->player_cnt > 1)
				return (2);
			if ((check_available(g, g->map, i, j)))
				return (1);
			if (g->map[i][j] == 'N' || g->map[i][j] == 'S' ||
					g->map[i][j] == 'E' || g->map[i][j] == 'W')
				find_location_of_player(g, i, j);
			j++;
		}
		i++;
	}
	return (0);
}

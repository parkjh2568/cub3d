/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secret_door.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhypar <junhypar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 18:47:16 by junhypar          #+#    #+#             */
/*   Updated: 2020/12/31 21:14:41 by junhypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "./bonus.h"

void	secret_door(t_game *g)
{
	double	k;

	k = 0;
	if (g->click == 1)
	{
		while (g->map[(int)(g->y + g->dir_y * k)][(int)(g->x +
					g->dir_x * k)] == '0')
		{
			k += 1;
			if (g->map[(int)(g->y + g->dir_y * k)][(int)(g->x +
					g->dir_x * k)] == '5')
			{
				g->map[(int)(g->y + g->dir_y * k)][(int)(g->x +
						g->dir_x * k)] = '0';
				break ;
			}
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_action.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhypar <junhypar@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 13:51:47 by junhypar          #+#    #+#             */
/*   Updated: 2020/12/31 16:45:14 by junhypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "./bonus.h"

void	trap_and_potion(t_game *g, int i)
{
	int x;
	int y;

	x = g->item[i].x;
	y = g->item[i].y;
	if (((x - 1 < g->x) && (g->x < (x + 1))) &&
			((y - 1 < g->y) && (g->y < (y + 1))))
	{
		if (g->item[i].tex_num == 8)
		{
			if (g->hp > 1)
				g->hp -= 1;
			g->item[i].tex_num = EMPTY;
		}
		else
		{
			if (g->hp < 10)
				g->hp += 1;
			g->item[i].tex_num = EMPTY;
		}
	}
}

void	moster_to_crop(t_game *g, int i)
{
	if (g->item[i].timer < 0)
		g->item[i].tex_num = EMPTY;
	else
		g->item[i].timer -= 1;
}

void	monster_action(t_game *g, int i)
{
	int x;
	int y;
	double k;

	k = 0;
	x = g->item[i].x;
	y = g->item[i].y;
	if (((x - 1 < g->x) && (g->x < (x + 1))) &&
			((y - 1 < g->y) && (g->y < (y + 1))))
	{
		if (g->hp > 1)
			g->hp -= 1;
		g->item[i].tex_num = EMPTY;
	}
	if (g->click == 1)
	{
		while(g->map[(int)(g->y + g->dir_y * k)][(int)(g->x +
					g->dir_x * k)] == '0')
		{
			if (x == (int)(g->x + g->dir_x * k) && y ==
					(int)(g->y + g->dir_y * k))
			{
				g->item[i].tex_num = 13;
				g->item[i].timer = 20;
			}
			k += 1;
		}
	}	
}

void	object_action(t_game *g)
{
	int i;

	i = 0;
	while(i < g->item_cnt)
	{
		if (g->item[i].tex_num == 8 || g->item[i].tex_num == 9)
			trap_and_potion(g, i);
		else if (g->item[i].tex_num == 12)
			monster_action(g, i);
		else if (g->item[i].tex_num == 13)
			moster_to_crop(g, i);
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhypar <junhypar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 21:10:01 by junhypar          #+#    #+#             */
/*   Updated: 2020/12/31 21:36:27 by junhypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "./bonus.h"

void	reset_struct2(t_game *g)
{
	int i;

	i = 0;
	while (i < 150)
	{
		g->key_trig[i] = 0;
		i++;
	}
	g->hp = 10;
	g->save_flag = 0;
	g->row = 0;
	g->col = 0;
	g->x = 0;
	g->y = 0;
	g->flag = 0;
	g->player_cnt = 0;
	g->dir_x = 0;
	g->dir_y = -1;
	g->plan_x = 0.66;
	g->plan_y = 0;
	g->mov_speed = 0.1;
	g->rot_speed = get_radian(5);
}

void	reset_struct(t_game *g)
{
	int i;

	g->map = 0;
	g->map_all = 0;
	i = NO;
	while (i <= S)
	{
		g->wall[i].name = 0;
		i++;
	}
	g->buf = 0;
	g->texture = 0;
	g->ex_texture = 0;
	g->item_cnt = 0;
	g->z_buf = 0;
	g->click = 0;
	g->lv = 1;
	g->exp = 0;
	i = 0;
	reset_struct2(g);
}

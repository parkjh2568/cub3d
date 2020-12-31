/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_lv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhypar <junhypar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 17:02:54 by junhypar          #+#    #+#             */
/*   Updated: 2020/12/31 21:14:08 by junhypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "./bonus.h"

void	draw_lv(t_game *g)
{
	g->item[g->item_cnt + 1].x = g->x + 0.1 * g->dir_x;
	g->item[g->item_cnt + 1].y = g->y + 0.1 * g->dir_y;
	g->item[g->item_cnt + 1].flag = 1;
	if (g->lv <= 1)
		g->item[g->item_cnt + 1].tex_num = 15;
	else if (g->lv == 2)
		g->item[g->item_cnt + 1].tex_num = 16;
	else if (g->lv == 3)
		g->item[g->item_cnt + 1].tex_num = 17;
	else if (g->lv == 4)
		g->item[g->item_cnt + 1].tex_num = 18;
	else
		g->item[g->item_cnt + 1].tex_num = 19;
}

void	check_lv_cops_div(t_game *g, t_painter *p)
{
	if (p->tex_num == 14)
	{
		p->u_div = 3;
		p->v_div = 3;
		p->v_move = g->height / 3;
	}
	else if (p->tex_num >= 15 && p->tex_num <= 19)
	{
		p->u_div = 90;
		p->v_div = 150;
		p->v_move = (g->height / 21) * -1;
	}
	else
	{
		p->u_div = 3;
		p->v_div = 3;
		p->v_move = 0;
	}
}

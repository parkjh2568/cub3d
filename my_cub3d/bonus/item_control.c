/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   item_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhypar <junhypar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 15:10:12 by junhypar          #+#    #+#             */
/*   Updated: 2020/12/31 16:20:07 by junhypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "./bonus.h"

static void			set_sprite_painter(t_game *g, t_painter *p, int i)
{
	p->spt_x = g->item[g->item_order[i]].x - g->x;
	p->spt_y = g->item[g->item_order[i]].y - g->y;
	p->inv = 1.0 / (g->plan_x * g->dir_y - g->dir_x * g->plan_y);
	p->trans_x = p->inv * (g->dir_y * p->spt_x - g->dir_x * p->spt_y);
	p->trans_y = p->inv * (-g->plan_y * p->spt_x + g->plan_x * p->spt_y);
	p->spt_screen_x = (int)((g->width / 2) * (1 + p->trans_x / p->trans_y));
	p->v_move_screen = (int)(p->v_move / p->trans_y);
	p->spt_height = (int)fabs((g->height / p->trans_y) / p->v_div);
	p->d_start = -p->spt_height / 2 + g->height / 2 + p->v_move_screen;
	if (p->d_start < 0)
		p->d_start = 0;
	p->d_end = p->spt_height / 2 + g->height / 2 + p->v_move_screen;
	if (p->d_end >= g->height)
		p->d_end = g->height - 1;
	p->spt_width = (int)fabs((g->height / p->trans_y) / p->u_div);
	p->d_start_x = -p->spt_width / 2 + p->spt_screen_x;
	if (p->d_start_x < 0)
		p->d_start_x = 0;
	p->d_end_x = p->spt_width / 2 + p->spt_screen_x;
	if (p->d_end_x >= g->width)
		p->d_end_x = g->width - 1;
}

static void			draw_sprite_to_buf(t_game *g, t_painter *p, int x)
{
	int y;
	int d;

	p->tex_width = g->wall[p->tex_num].width;
	p->tex_height = g->wall[p->tex_num].height;
	while (x < p->d_end_x)
	{
		p->tex_x = (int)((x - (p->spt_screen_x - p->spt_width / 2)) *
					p->tex_width / p->spt_width);
		y = p->d_start;
		if (p->trans_y > 0 && x > 0 && x < g->width && p->trans_y < g->z_buf[x])
			while (y < p->d_end)
			{
				d = (y - p->v_move_screen) * 256 - g->height * 128 +
					p->spt_height * 128;
				p->tex_y = ((d * p->tex_height) / p->spt_height) / 256;
				p->color = g->texture[p->tex_num][p->tex_width *
					p->tex_y + p->tex_x];
				if ((p->color & 0x00FFFFFF) != 0)
					g->buf[y][x] = set_bright(p->color, g, p->spt_height);
				y++;
			}
		x++;
	}
}

void			check_div_move(t_game *g, t_painter *p)
{
	if (p->tex_num == 7)
	{
		p->u_div = 1.3;
		p->v_div = 1.3;
		p->v_move = g->height / 4;
	}
	else if (p->tex_num == 8)
	{
		p->u_div = 2;
		p->v_div = 2;
		p->v_move = g->height / 3;;
	}
	else if (p->tex_num == 10)
	{
		p->u_div = 50;
		p->v_div = 30;
		p->v_move = (double)g->height / 28;
	}
	else if (p->tex_num == 11)
	{
		p->u_div = 20;
		p->v_div = 20;
		p->v_move = (double)g->height / 35;
	}
	else if (p->tex_num == 12)
	{
		p->u_div = 1.5;
		p->v_div = 1.3;
		p->v_move = (g->height / 4);
	}
	else if (p->tex_num == 13)
	{
		p->u_div = 1.5;
		p->v_div = 1.3;
		p->v_move = (g->height / 4);
	}
	else
	{
		p->u_div = 3;
		p->v_div = 3;
		p->v_move = 0;
	}
}

void			draw_sprite(t_game *g, t_painter *p, int i)
{
	p->u_div = 1.3;
	p->v_div = 1;
	p->v_move = 0;
	p->tex_num = g->item[g->item_order[i]].tex_num;
	set_sprite_painter(g, p, i);
	draw_sprite_to_buf(g, p, p->d_start_x);
}

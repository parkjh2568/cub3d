/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hp_mini_map_control.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhypar <junhypar@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 20:59:03 by junhypar          #+#    #+#             */
/*   Updated: 2020/12/30 22:42:57 by junhypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "./bonus.h"

void	color_control(t_b_painter *p, int flag, int color)
{
	int r;
	int g;
	int b;

	if (flag == 1)
	{
		p->color = (p->r * 256 * 256) + (p->g * 256) + p->b;
	}
	else if (flag == 2)
	{
		r = (p->alpha_ratio * (double)p->r + (1 - p->alpha_ratio) *
			(double)((color / (256 * 256)) % 256));
		g = (p->alpha_ratio * (double)p->g + (1 - p->alpha_ratio) *
			(double)((color / 256) % 256));
		b = (p->alpha_ratio * (double)p->b + (1 - p->alpha_ratio) *
				(double)((color % 256)));
		p->color = (r * 256 * 256) + (g * 256) + (b);
	}
	else
	{
		p->a = (p->wanted_color) / (256 * 256 * 256);
		p->r = (p->wanted_color / (256 * 256)) % 256;
		p->g = (p->wanted_color / 256) % 256;
		p->b = (p->wanted_color) % 256;
		p->alpha_ratio = (double)(255 - p->a) / 255;
	}
}

void	draw_somting(t_game *g, t_b_painter *p)
{
	int x_start;
	int x_end;
	int y_start;
	int y_end;

	x_end = p->d_end_x;
	y_start = p->d_start_y;
	y_end = p->d_end_y;
	while(y_start < y_end)
	{
		x_start = p->d_start_x;
		while(x_start < x_end)
		{
			color_control(p, MIX_ALPHA_RATIO_RGB, g->buf[y_start][x_start]);
			g->buf[y_start][x_start] = p->color;
			x_start += 1;
		}
		y_start += 1;
	}

}

void	draw_hp(t_game *g, t_b_painter *p)
{
	p->d_start_x = (g->width / 3);
	p->d_end_x = (g->width / 3) * 2;
	p->d_start_y = (g->height / 30) * 2;
	p->d_end_y = (g->height / 30) * 3;
	p->wanted_color = 0x7f000000;
	color_control(p, DIVIDE_RGB, 0);
	draw_somting(g, p);
	p->d_start_x = (g->width / 3) + 1;
	p->d_end_x = (g->width / 3) * 2 - 1;
	p->d_start_y = (g->height / 30) * 2 + 1;
	p->d_end_y = (g->height / 30) * 3 - 1;
	p->wanted_color = 0x10FF0000;
	color_control(p, DIVIDE_RGB, 0);
	draw_somting(g, p);
}

void	start_bonus(t_game *g)
{
	t_b_painter p;

	draw_hp(g, &p);

}

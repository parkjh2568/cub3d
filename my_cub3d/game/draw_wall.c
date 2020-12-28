/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhypar <junhypar@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 14:22:33 by junhypar          #+#    #+#             */
/*   Updated: 2020/12/28 15:38:55 by junhypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_bg(t_game *g)
{
	int x;
	int y;

	x = 0;
	while (x < g->width)
	{
		y = 0;
		while (y < g->height)
		{
			g->buf[y][x] = g->bgcolor[0];
			g->buf[g->height - y - 1][x] = g->bgcolor[1];
		   y++;	
		}
		x++;
	}
}
void	draw_wall(t_game *g, t_raycast *ray, t_painter *p, int j)
{
	int i;

	p->tex_width = g->wall[p->tex_num].width;
	p->tex_height = g->wall[p->tex_num].height;
	if (ray->side == 0)
		p->wall_x = g->y + ray->how_long * ray->dir_y;
	else
		p->wall_x = g->x + ray->how_long * ray->dir_x;
	p->wall_x -= floor(p->wall_x);
	p->tex_x = (int)(p->wall_x * (double)p->tex_width);
	if (ray->side == 0 && ray->dir_x > 0)
		p->tex_x = p->tex_width - p->tex_x - 1;
	if (ray->side == 1 && ray->dir_y < 0)
		p->tex_x = p->tex_width - p->tex_x - 1;
	p->step = 1.0 * p->tex_height / ray->wall_height;
	p->tex_pos = (p->d_start - g->height / 2 + ray->wall_height / 2) * p->step;
	i = p->d_start;
	while (i < p->d_end)
	{
		p->tex_y = p->tex_pos;
		p->tex_pos += p->step;
		g->buf[i][j] = g->texture[p->tex_num][p->tex_width *
			p->tex_y + p->tex_x];
		i++;
	}
}

void	set_painter(t_game *g, t_raycast *ray, t_painter *p)
{
	p->d_start = (ray->wall_height / 2 * -1) + (g->height / 2);
	if (p->d_start < 0)
		p->d_start = 0;
	p->d_end = (ray->wall_height / 2) + (g->height / 2);
	if (p->d_end >= g->height)
		p->d_end = g->height - 1;
	p->tex_num = g->map[ray->y][ray->x] - 1 - '0';
	if(ray->side == 0 && ray->dir_x > 0)
		p->tex_num += 3;
	else if (ray->side == 0 && ray->dir_x <= 0)
		p->tex_num += 2;
	else if (ray->side == 1 && ray->dir_y >= 0)
		p->tex_num += 1;
}

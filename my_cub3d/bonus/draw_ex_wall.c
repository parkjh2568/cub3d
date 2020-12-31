/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ex_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhypar <junhypar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 14:30:53 by junhypar          #+#    #+#             */
/*   Updated: 2020/12/31 21:21:53 by junhypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "./bonus.h"

void	draw_ex_wall(t_game *g, t_raycast *ray, t_painter *p, int j)
{
	int i;

	p->tex_width = g->info_tex[p->tex_num].width;
	p->tex_height = g->info_tex[p->tex_num].height;
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
		g->buf[i][j] = set_bright(g->ex_texture[p->tex_num][p->tex_width *
			p->tex_y + p->tex_x], g, ray->wall_height);
		i++;
	}
}

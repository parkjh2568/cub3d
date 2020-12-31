/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhypar <junhypar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 20:39:29 by junhypar          #+#    #+#             */
/*   Updated: 2020/12/31 22:13:13 by junhypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "./bonus.h"

void	set_ray2(t_game *g, t_raycast *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (g->x - ray->x) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->x + 1.0 - g->x) * ray->delta_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (g->y - ray->y) * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->y + 1.0 - g->y) * ray->delta_y;
	}
}

void	set_ray(t_game *g, t_raycast *ray, int i)
{
	ray->camera = (2 * i / (double)(g->width)) - 1;
	ray->dir_x = g->dir_x + g->plan_x * ray->camera;
	ray->dir_y = g->dir_y + g->plan_y * ray->camera;
	ray->x = (int)g->x;
	ray->y = (int)g->y;
	ray->delta_x = fabs(1 / ray->dir_x);
	ray->delta_y = fabs(1 / ray->dir_y);
	ray->hit = 0;
	set_ray2(g, ray);
}

void	draw_start(t_game *g, t_raycast *ray, int i)
{
	t_painter	p;

	set_painter(g, ray, &p);
	if (p.flag)
		draw_ex_wall(g, ray, &p, i);
	else
		draw_wall(g, ray, &p, i);
}

void	spread_ray(t_raycast *ray, t_game *g)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_x;
			ray->x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_y;
			ray->y += ray->step_y;
			ray->side = 1;
		}
		if (g->map[ray->y][ray->x] > '0')
		{
			if (g->map[ray->y][ray->x] == '1' || (g->map[ray->y][ray->x] >=
					'3' && g->map[ray->y][ray->x] <= '5'))
				ray->hit = 1;
		}
	}
}

void	ray_casting(t_game *g)
{
	t_raycast	ray;
	int			i;

	draw_bg(g);
	i = 0;
	while (i < g->width)
	{
		set_ray(g, &ray, i);
		spread_ray(&ray, g);
		if (ray.side == 0)
			ray.how_long = (ray.x - g->x + (1 - ray.step_x) / 2) / ray.dir_x;
		else
			ray.how_long = (ray.y - g->y + (1 - ray.step_y) / 2) / ray.dir_y;
		ray.wall_height = (int)(g->height / ray.how_long);
		draw_start(g, &ray, i);
		g->z_buf[i] = ray.how_long;
		i++;
	}
}

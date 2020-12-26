/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhypar <junhypar@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 20:39:29 by junhypar          #+#    #+#             */
/*   Updated: 2020/12/26 16:23:01 by junhypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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


//임시 색입히기//
void	draw_wall(t_game *g, t_raycast *ray, int i)
{
	int drawS = (ray->wall_height / 2 * -1) + (g->height / 2);
	if (drawS < 0)
		drawS = 0;
	int drawE = (ray->wall_height / 2) + (g->height / 2);
	if (drawE >= g->height)
		drawE = g->height - 1;
	int color;
	if (g->map[ray->y][ray->x] == '1')
		color = 0xFF0000;
	else if (g->map[ray->y][ray->x] == '2')
		color = 0x00ff00;
	else if (g->map[ray->y][ray->x] == '3')
		color = 0x0000ff;
	else
		color = 0x123456;

	if (ray->side == 1)
		color = color / 2;
		//draw_line(g, i, drawS, drawE, color);
	
	while(drawS <= drawE)
	{
		mlx_pixel_put(g->mlx, g->win, i, drawS, color);
		drawS++;
	}
}

void	spread_ray(t_raycast *ray)
{
	if (ray->side_dist_y < ray->side_dist_x)
	{
		ray->side_dist_y += ray->delta_y;
		ray->y += ray->step_y;
		ray->side = 0;
	}
	else
	{
		ray->side_dist_x += ray->delta_x;
		ray->x += ray->step_x;
		ray->side = 1;
	}
}

void	ray_casting(t_game *g)
{
	t_raycast ray;
	int i;

	i = 0;
	while(i < g->width)
	{
		set_ray(g, &ray, i);
		while(ray.hit == 0)
		{
			spread_ray(&ray);
			if (g->map[ray.y][ray.x] > '0')
				ray.hit = 1;
		}
		if (ray.side == 0)
			ray.how_long = (ray.y - g->y + (1 - ray.step_y) / 2) / ray.dir_y;
		else
			ray.how_long = (ray.x - g->x + (1 - ray.step_x) / 2) / ray.dir_x;
		ray.wall_height = (int)(g->height / ray.how_long);
		draw_wall(g, &ray, i);
		i++;
	}
}

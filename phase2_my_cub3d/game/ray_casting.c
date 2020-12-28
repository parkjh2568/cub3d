/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhypar <junhypar@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 20:39:29 by junhypar          #+#    #+#             */
/*   Updated: 2020/12/28 13:42:26 by junhypar         ###   ########.fr       */
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

	int	texNum = g->map[ray->y][ray->x] - 1 - '0';
	
	if (texNum == 0)
	{
		if(ray->side == 0 && ray->dir_x > 0)
			texNum += 3;
		else if (ray ->side == 0 & ray->dir_x < 0)
			texNum += 2;
		else if (ray->side == 1 && ray->dir_y >= 0)
			texNum += 1;

	}
	else
		texNum += 3;

	double wallX;
	if (ray->side == 0)
		wallX = g->y + ray->how_long * ray->dir_y;
	else
		wallX = g->x + ray->how_long * ray->dir_x;
	wallX -= floor(wallX);
	int texX = (int)(wallX * (double)g->wall[texNum].width);
	if (ray->side == 0 && ray->dir_x > 0)
		texX = g->wall[texNum].width - texX - 1;
	if (ray->side == 1 && ray->dir_y < 0)
		texX = g->wall[texNum].width - texX - 1;
	double step = 1.0 * g->wall[texNum].height / ray->wall_height;
	double texPos = (drawS - g->height / 2 + ray->wall_height / 2) * step;

	for (int y = drawS; y<drawE; y++)
	{
		int texY = (int)texPos & (g->wall[texNum].height - 1);
		texPos += step;


		int color = g->texture[texNum][g->wall[texNum].width * texY + texX];


		g->buf[y][i] = color;
	}

}

void	spread_ray(t_raycast *ray)
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
}

void	ray_casting(t_game *g)
{
//임시 배경칠
	for(int x = 0; x < g->width; x++)
	{
		for(int y = 0; y < g->height; y++)
		{
			g->buf[y][x] = g->bgcolor[0];
			g->buf[g->height - y - 1][x] = g->bgcolor[1];
		}
	}

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
			ray.how_long = (ray.x - g->x + (1 - ray.step_x) / 2) / ray.dir_x;
		else
			ray.how_long = (ray.y - g->y + (1 - ray.step_y) / 2) / ray.dir_y;
		ray.wall_height = (int)(g->height / ray.how_long);
		draw_wall(g, &ray, i);
		i++;
	}
}

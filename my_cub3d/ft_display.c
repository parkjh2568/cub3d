/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhypar <junhypar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:37:05 by junhypar          #+#    #+#             */
/*   Updated: 2020/10/28 20:48:45 by junhypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

void	set_ray(t_raycast *ray, int r, int w, t_game *g)
{
	ray->camera = 2 * r / w - 1;
	ray->x = g->x;
	ray->y = g->y;
	g->ray_dir_x = g->dir_x + g->plan_x * ray->camera;
	g->ray_dir_y = g->dir_y + g->plan_y * ray->camera;
	ray->delta_x = fabs(1/g->ray_dir_x);
	ray->delta_y = fabs(1/g->ray_dir_y);
	ray->hit = 0;
}

void	set_delta(t_raycast *ray, t_game *g)
{
	if (g->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_x = (g->x - ray->x) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_x = (ray->x + 1.0 - g->x) * ray->delta_x;
	}
	if (g->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_y = (g->y - ray->y) * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_y = (ray->y + 1.0 - g->y) * ray->delta_y;
	}
}

int		find_hit(t_raycast *ray, t_game *g)
{
	while(ray->hit == 0)
	{
		if (ray->side_x < ray->side_y)
		{
			ray->side_x += ray->delta_x;
			ray->x += ray->step_x;
			ray->plan = 0;
		}
		else
		{
			ray->side_y += ray->delta_y;
			ray->y += ray->step_y;
			ray->plan = 1;
		}
		if (g->map[ray->x][ray->y] > 0)
			ray->hit = 1;
	}
	return (g->map[ray->x][ray->y]);
}

void	draw_ray(t_game *g)
{
	t_raycast ray;
	int w;
	int r;

	r = 0;
	w = g->width / 2;
	while(r < w)
	{
		set_ray(&ray, r, w, g);
		set_delta(&ray, g);
		g->flag = find_hit(&ray,g);
		draw_screen(g,&ray,r);
		r++;
	}
}

int display(t_game *g)
{
	mlx_put_image_to_window(g->mlx, g->win, g->img.img, 0, 0);
//	draw_ray(g);
	return(0);
}

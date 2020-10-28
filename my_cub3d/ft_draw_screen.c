/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_screen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhypar <junhypar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 20:00:00 by junhypar          #+#    #+#             */
/*   Updated: 2020/10/28 20:39:53 by junhypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

void draw_wall(t_game *g, t_raycast *ray, int r, int j)
{
	if (g->flag == 1)
	{
		if (ray->plan == 0)
			mlx_pixel_put(g->mlx,g->win,r,j,0x000000);
		else
			mlx_pixel_put(g->mlx,g->win,r,j,0x0f0f0f);
	}
	else if (g->flag == 3)
	{
		if (ray->plan == 0)
			mlx_pixel_put(g->mlx,g->win,r,j,0xffd400);
		else
			mlx_pixel_put(g->mlx,g->win,r,j,0xe0c01f);
	}
	else if (g->flag == 4)
	{
		if (ray->plan == 0)
			mlx_pixel_put(g->mlx,g->win,r,j,0x00ff3d);
		else
			mlx_pixel_put(g->mlx,g->win,r,j,0x1fe04d);
	}

}

void draw_screen(t_game *g, t_raycast *ray, int r)
{
	double h;
	int	resol_w;
	int resol_h;
	int draw_start;
	int draw_end;

	if (ray->plan == 0)
		h = (ray->x - g->x + (1 - ray->step_x) / 2) / g->ray_dir_x;
	else
		h = (ray->y - g->y + (1 - ray->step_y) / 2) / g->ray_dir_y;

	resol_w = 1;
	resol_h = g->height / h;
	draw_start = g->height / 2 - resol_h / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = g->height / 2 - resol_h / 2;
	if (draw_end >= g->height)
		draw_end = g->height - 1;

/*	double wall_x;

	if (plan == 0)
		wall_x = g->y + h * g->ray_dir_y;
	else
		wall_x = g->x + h * g->ray_dir_x;

	wall_x -= floor((wall_x));

	int tex_x (int)(wall_x * g->user_img.width);

	if (plan == 0 && g->ray_dir_x > 0)
		tex_x = g->user_img.width - tex_x - 1;
	if (plan == 0 && g->ray_dir_y < 0)
		tex_x = g->user_img.width - tex_x - 1;
	
	double step = 1.0 * g->user_img.height / resol_h;

	double tex_pos = (draw_start - g->height / 2 + resol_h / 2)

	unsigned int color;*/
	int j = draw_start;
	while (j < draw_end)
	{
		/*int tex_y = (int)tex_pos & (g->user_img.height - 1);
		 * tex_pos += step;
		 * color = g->user_img.data[???];*/
		draw_wall(g,ray,r,j);
		j++;
	}
}

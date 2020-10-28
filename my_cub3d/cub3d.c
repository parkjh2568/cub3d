/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhypar <junhypar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 18:53:47 by junhypar          #+#    #+#             */
/*   Updated: 2020/10/28 21:00:03 by junhypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

void rotate_q(t_game *g, double rot)
{
	g->dir_x = g->old_dir_x * cos(rot) - g->old_dir_y * sin(rot);
	g->dir_y = g->old_dir_x * sin(rot) + g->old_dir_y * cos(rot);
	g->plan_x = g->old_plan_x * cos(rot) - g->old_plan_y * sin(rot);
	g->plan_y = g->old_plan_x * sin(rot) + g->old_plan_y * cos(rot);
}

void rotate_e(t_game *g, double rot)
{
	g->dir_x = g->old_dir_x * cos(rot * (-1)) - g->old_dir_y * sin(rot * (-1));
	g->dir_y = g->old_dir_x * sin(rot * (-1)) + g->old_dir_y * cos(rot * (-1));
	g->plan_x = g->old_plan_x * cos(rot * (-1)) -
		g->old_plan_y * sin(rot * (-1));
	g->plan_y = g->old_plan_x * sin(rot * (-1)) +
		g->old_plan_y * cos(rot * (-1));
}

int		k_close(t_game *g)
{
//	free_map(g);
	g->x = 0;
	exit(0);
}

int input_key(int key, t_game *g)
{
	double rot;

	rot = get_radian(10);
	g->old_dir_x = g->dir_x;
	g->old_dir_y = g->dir_y;
	g->old_plan_x = g->plan_x;
	g->old_plan_y = g->plan_y;

	if (key == KEY_ESC)
		exit(0);	
	else if (key == KEY_Q)
		rotate_q(g, rot);
	else if (key == KEY_E)
		rotate_e(g, rot);
	return(0);
}

void draw_back_screen(t_game *g)
{
	int k;
	int l;

	k = 0;
	l = 0;
	while(k < g->width)
	{
		l = 0;
		while(k < g->height)
		{
			if (k < g->width/2)
				g->img.data[(k)*(g->height) + l] = 0xffffff;
			else
				g->img.data[(k)*(g->height) + l] = 0xff9729;
			l++;
		}
		k++;
	}
}

void cub3d(t_game *g)
{
	
	g->mlx = mlx_init();
	g->win = mlx_new_window(g->mlx, g->width, g->height, "cub3D");
	g->img.img = mlx_new_image(g->mlx, g->width, g->height);
	g->img.data = (int *)mlx_get_data_addr(g->img.img, &g->img.bpp,
			&g->img.size_l, &g->img.endian);

	while(g->map[(int)g->x][(int)g->y] != 2)
	{
		g->y++;
		if (g->x < g->row && g->y >= g->col)
		{
			g->y = 0;
			g->x++;
		}
	}
	g->map[(int)g->x][(int)g->y] = 0;

	draw_back_screen(g);
	mlx_hook(g->win, 2, 0, &input_key, &g);
	mlx_hook(g->win, 17, 0, &k_close, &g);
	mlx_loop_hook(g->mlx,&display,&g);
	mlx_loop(g->mlx);
}

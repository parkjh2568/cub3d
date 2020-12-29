/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start_game.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhypar <junhypar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 17:32:51 by junhypar          #+#    #+#             */
/*   Updated: 2020/12/29 17:03:36 by junhypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	image_draw(t_game *g)
{
	int y;
	int x;

	y = 0;
	while (y < g->height)
	{
		x = 0;
		while (x < g->width)
		{
			g->img.data[y * g->width + x] = g->buf[y][x];
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(g->mlx, g->win, g->img.img, 0, 0);
}

int		display(t_game *g)
{
	key_action(g);
	ray_casting(g);
	draw_item(g);
	image_draw(g);
	return (0);
}

void	set_field(t_game *g)
{
	int i;
	int j;

	g->buf = (int **)malloc(sizeof(int *) * (g->height));
	i = 0;
	while (i < g->height)
	{
		g->buf[i] = (int *)malloc(sizeof(int) * (g->width));
		i++;
	}
	i = 0;
	while (i < g->height)
	{
		j = 0;
		while (j < g->width)
		{
			g->buf[i][j] = 0;
			j++;
		}
		i++;
	}
	g->texture = (int **)malloc(sizeof(int *) * WALL_NUM);
	put_in_texture(g);
}

void	ft_start_game(t_game *g)
{
	g->mlx = mlx_init();
	set_field(g);
	g->win = mlx_new_window(g->mlx, g->width, g->height, "plz start");
	g->img.img = mlx_new_image(g->mlx, g->width, g->height);
	g->img.data = (int *)mlx_get_data_addr(g->img.img, &g->img.bpp,
			&g->img.size_l, &g->img.endian);
	mlx_loop_hook(g->mlx, &display, g);
	mlx_hook(g->win, 2, 0, &press_key, g);
	mlx_hook(g->win, 3, 0, &release_key, g);
	mlx_hook(g->win, 17, 0, &input_esc, g);
	mlx_loop(g->mlx);
}
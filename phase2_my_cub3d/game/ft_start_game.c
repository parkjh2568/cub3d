/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start_game.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhypar <junhypar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 17:32:51 by junhypar          #+#    #+#             */
/*   Updated: 2020/12/28 13:36:54 by junhypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		input_key(int key, t_game *g)
{
	if (key == KEY_ESC)
	{
		free_all(g);
		exit(0);
	}
	if (key == KEY_W)
		ft_key_press_up_down(g, 1);
	if (key == KEY_S)
		ft_key_press_up_down(g, -1);
	if (key == KEY_A)
		ft_key_press_left_right(g, 1);
	if (key == KEY_D)
		ft_key_press_left_right(g, -1);
	if (key == KEY_Q || key == KEY_LEFT_ARROW)
		ft_key_press_rot_left_right(g, 1);
	if (key == KEY_E || key == KEY_RIGHT_ARROW)
		ft_key_press_rot_left_right(g, -1);
	return (0);
}

int		input_esc(t_game *g)
{
	free_all(g);
	exit(0);
}

//임시

void	imageDraw(t_game *g)
{
	for (int y = 0; y < g->height; y++)
		for (int x = 0; x < g->width; x++)
			g->img.data[y*g->width + x] = g->buf[y][x];

	mlx_put_image_to_window(g->mlx, g->win, g->img.img,0,0);
}

int		display(t_game *g)
{
	ray_casting(g);
	imageDraw(g);
	return(0);
}


//임시 
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
	mlx_hook(g->win, 2, 0, &input_key, g);
	mlx_hook(g->win, 17, 0, &input_esc, g);
	mlx_loop(g->mlx);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start_game.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhypar <junhypar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 17:32:51 by junhypar          #+#    #+#             */
/*   Updated: 2020/12/25 20:38:25 by junhypar         ###   ########.fr       */
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
		ft_key_press_rot_left_right(g, 1);
	if (key == KEY_D)
		ft_key_press_rot_left_right(g, -1);
	return (0);
}

int		input_esc(t_game *g)
{
	free_all(g);
	exit(0);
}

int		display(t_game *g)
{
	ray_casting(g);
	return(0);
}

void	ft_start_game(t_game *g)
{
	g->mlx = mlx_init();
	g->win = mlx_new_window(g->mlx, g->width, g->height, "plz start");
	mlx_loop_hook(g->mlx, &display, g);
	mlx_hook(g->win, 2, 0, &input_key, g);
	mlx_hook(g->win, 17, 0, &input_esc, g);
	mlx_loop(g->mlx);
}

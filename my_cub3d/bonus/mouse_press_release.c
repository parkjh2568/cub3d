/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_press_release.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhypar <junhypar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 19:54:16 by junhypar          #+#    #+#             */
/*   Updated: 2020/12/31 21:22:17 by junhypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "./bonus.h"

void	mos_position(t_game *g)
{
	int x;
	int y;

	x = 0;
	y = 0;
	mlx_mouse_get_pos(g->win, &x, &y);
	if (g->old_mous_x == x)
	{
		g->key_trig[KEY_Q] = 0;
		g->key_trig[KEY_E] = 0;
	}
	else if (g->old_mous_x > x)
	{
		g->key_trig[KEY_Q] = 1;
		g->key_trig[KEY_E] = 0;
	}
	else
	{
		g->key_trig[KEY_Q] = 0;
		g->key_trig[KEY_E] = 1;
	}
	mlx_mouse_move(g->win, g->old_mous_x, g->old_mous_y);
}

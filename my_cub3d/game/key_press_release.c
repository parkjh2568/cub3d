/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press_release.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhypar <junhypar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 16:42:14 by junhypar          #+#    #+#             */
/*   Updated: 2020/12/29 17:03:23 by junhypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		press_key(int key, t_game *g)
{
	if (key == KEY_ESC)
	{
		free_all(g);
		exit(0);
	}
	if (key == KEY_W && g->key_trig[KEY_W] == 0)
		g->key_trig[KEY_W] = 1;
	if (key == KEY_S && g->key_trig[KEY_S] == 0)
		g->key_trig[KEY_S] = 1;
	if (key == KEY_A && g->key_trig[KEY_A] == 0)
		g->key_trig[KEY_A] = 1;
	if (key == KEY_D && g->key_trig[KEY_D] == 0)
		g->key_trig[KEY_D] = 1;
	if ((key == KEY_Q || key == KEY_LEFT_ARROW) && g->key_trig[KEY_Q] == 0)
		g->key_trig[KEY_Q] = 1;
	if ((key == KEY_E || key == KEY_RIGHT_ARROW) && g->key_trig[KEY_E] == 0)
		g->key_trig[KEY_E] = 1;
	return (0);
}

int		release_key(int key, t_game *g)
{
	if (key == KEY_W && g->key_trig[KEY_W] == 1)
		g->key_trig[KEY_W] = 0;
	if (key == KEY_S && g->key_trig[KEY_S] == 1)
		g->key_trig[KEY_S] = 0;
	if (key == KEY_A && g->key_trig[KEY_A] == 1)
		g->key_trig[KEY_A] = 0;
	if (key == KEY_D && g->key_trig[KEY_D] == 1)
		g->key_trig[KEY_D] = 0;
	if ((key == KEY_Q || key == KEY_LEFT_ARROW) && g->key_trig[KEY_Q] == 1)
		g->key_trig[KEY_Q] = 0;
	if ((key == KEY_E || key == KEY_RIGHT_ARROW) && g->key_trig[KEY_E] == 1)
		g->key_trig[KEY_E] = 0;
	return (0);
}

void	key_action(t_game *g)
{
	if (g->key_trig[KEY_W])
		ft_key_press_up_down(g, 1);
	if (g->key_trig[KEY_S])
		ft_key_press_up_down(g, -1);
	if (g->key_trig[KEY_A])
		ft_key_press_left_right(g, 1);
	if (g->key_trig[KEY_D])
		ft_key_press_left_right(g, -1);
	if (g->key_trig[KEY_Q])
		ft_key_press_rot_left_right(g, 1);
	if (g->key_trig[KEY_E])
		ft_key_press_rot_left_right(g, -1);
}

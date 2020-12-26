/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_press.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhypar <junhypar@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 18:54:20 by junhypar          #+#    #+#             */
/*   Updated: 2020/12/26 16:30:38 by junhypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_key_press_up_down(t_game *g, int flag)
{
	double mv_x;
	double mv_y;

	mv_x = g->dir_x * g->mov_speed * flag;
	mv_y = g->dir_y * g->mov_speed * flag;
	if (!g->map[(int)(g->x + mv_x)][(int)g->y])
		g->x += mv_x;
	if (!g->map[(int)g->x][(int)(g->y + mv_y)])
		g->y += mv_y;
}

void	ft_key_press_rot_left_right(t_game *g, int flag)
{
	double	old_x;
	double	rot;

	old_x = g->dir_x;
	rot = g->rot_speed * flag;
	g->dir_x = g->dir_x * cos(rot) - g->dir_y * sin(rot);
	g->dir_y = old_x * sin(rot) + g->dir_y * cos(rot);
	old_x = g->plan_x;
	g->plan_x = g->plan_x * cos(rot) - g->plan_y * sin(rot);
	g->plan_y = old_x * sin(rot) + g->plan_y * cos(rot);
}

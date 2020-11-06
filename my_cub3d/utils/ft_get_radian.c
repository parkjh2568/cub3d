/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_radian.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhypar <junhypar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 18:40:42 by junhypar          #+#    #+#             */
/*   Updated: 2020/11/06 17:36:32 by junhypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	rotate_vector(t_game *g, int deg)
{
	double rot;

	rot = get_radian(deg);
	g->old_dir_x = g->dir_x;
	g->old_dir_y = g->dir_y;
	g->old_plan_x = g->plan_x;
	g->old_plan_y = g->plan_y;
	g->dir_x = g->old_dir_x * cos(rot) - g->old_dir_y * sin(rot);
	g->dir_y = g->old_dir_x * sin(rot) + g->old_dir_y * cos(rot);
	g->plan_x = g->old_plan_x * cos(rot) - g->old_plan_y * sin(rot);
	g->plan_y = g->old_plan_x * sin(rot) + g->old_plan_y * cos(rot);
}

double	get_radian(int deg)
{
	double cal;

	cal = deg * (PI / 180);
	return (cal);
}

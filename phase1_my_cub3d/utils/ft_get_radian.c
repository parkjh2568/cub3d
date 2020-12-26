/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_radian.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhypar <junhypar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 18:40:42 by junhypar          #+#    #+#             */
/*   Updated: 2020/12/25 19:13:17 by junhypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	rotate_vector(t_game *g, int deg)
{
	double		rot;
	t_old_dig	cocoa;

	rot = get_radian(deg);
	cocoa.old_dir_x = g->dir_x;
	cocoa.old_dir_y = g->dir_y;
	cocoa.old_plan_x = g->plan_x;
	cocoa.old_plan_y = g->plan_y;
	g->dir_x = cocoa.old_dir_x * cos(rot) - cocoa.old_dir_y * sin(rot);
	g->dir_y = cocoa.old_dir_x * sin(rot) + cocoa.old_dir_y * cos(rot);
	g->plan_x = cocoa.old_plan_x * cos(rot) - cocoa.old_plan_y * sin(rot);
	g->plan_y = cocoa.old_plan_x * sin(rot) + cocoa.old_plan_y * cos(rot);
}

double	get_radian(int deg)
{
	double cal;

	cal = deg * (M_PI / 180);
	return (cal);
}

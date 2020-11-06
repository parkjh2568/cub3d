/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dividemap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhypar <junhypar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 12:04:53 by junhypar          #+#    #+#             */
/*   Updated: 2020/10/30 16:40:48 by junhypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int map_resol(char *out, t_game *g)
{
	int i;
	int config;

	i = 0;
	g->width = 0;
	g->height = 0;
	no_space(out, &i);
	g->width = ft_atoi(out + i);
	config = skip_resol_word(out, &i);
	if (config != 0)
		return (WRONG_RESOL_INPUT);
	no_space(out, &i);
	g->height = ft_atoi(out + i);
	config = skip_resol_word(out, &i);
	if (config != 0)
		return (WRONG_RESOL_INPUT);
	if (check_remain(out, i) != 0)
		return (WRONG_RESOL_INPUT);
	return (0);
}

int map_wall(char *out, t_game *g, int flag)
{
	int i;

	i = 0;
	no_space(out, &i);
	word_dup(out, g, &i, flag);
	no_space(out, &i);
	if (check_remain(out, i) != 0)
		return (WRONG_NO_WALL_NAME_INPUT);
	return (0);
}

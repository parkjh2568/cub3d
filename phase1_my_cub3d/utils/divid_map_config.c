/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divid_map_config.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhypar <junhypar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 12:04:53 by junhypar          #+#    #+#             */
/*   Updated: 2020/12/25 22:13:05 by junhypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		map_resol(char *out, t_game *g)
{
	int i;
	int config;

	i = 0;
	g->width = 0;
	g->height = 0;
	i = no_space(out, i);
	g->width = ft_atoi(out + i);
	i = skip_resol_word(out, i, 0);
	if (i == -1)
		return (WRONG_RESOL_INPUT);
	i = no_space(out, i);
	g->height = ft_atoi(out + i);
	i = skip_resol_word(out, i, 0);
	if (i == -1)
		return (WRONG_RESOL_INPUT);
	if (check_remain(out, i) != 0)
		return (WRONG_RESOL_INPUT);
	return (0);
}

int		input_wall_name(char *out, t_game *g, int flag)
{
	int i;

	i = 0;
	i = no_space(out, i);
	i = word_dup(out, g, i, flag);
	i = no_space(out, i);
	if (check_remain(out, i) != 0)
		return (WRONG_IMAGE_NAME_INPUT);
	return (0);
}

int		input_bg_color2(char *out, t_game *g, int flag, int i)
{
	unsigned int	j;
	int				config;

	if ((j = ft_atoi(&out[i])) > 255 || ft_atoi(&out[i]) < 0)
		return (WRONG_BG_COLOR_INPUT);
	g->bgcolor[flag] += j;
	i = skip_resol_word(out, i, 1);
	if (i == -1)
		return (WRONG_BG_COLOR_INPUT);
	i = no_space(out, i);
	if (check_remain(out, i) != 0)
		return (WRONG_BG_COLOR_INPUT);
	return (0);
}

int		input_bg_color(char *out, t_game *g, int flag)
{
	int				i;
	unsigned int	j;
	int				config;

	i = 0;
	g->bgcolor[flag] = 0;
	i = no_space(out, i);
	if ((j = ft_atoi(&out[i])) > 255 || ft_atoi(&out[i]) < 0)
		return (WRONG_BG_COLOR_INPUT);
	g->bgcolor[flag] += (j * 16 * 16 * 16 * 16);
	i = skip_resol_word(out, i, 1);
	if (i == -1)
		return (WRONG_BG_COLOR_INPUT);
	i = find_rest(out, i);
	if ((j = ft_atoi(&out[i])) > 255 || ft_atoi(&out[i]) < 0)
		return (WRONG_BG_COLOR_INPUT);
	g->bgcolor[flag] += (j * 16 * 16);
	i = skip_resol_word(out, i, 1);
	if (i == -1)
		return (WRONG_BG_COLOR_INPUT);
	i = find_rest(out, i);
	return (input_bg_color2(out, g, flag, i));
}

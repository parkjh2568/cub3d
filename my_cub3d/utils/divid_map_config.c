/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divid_map_config.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhypar <junhypar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 12:04:53 by junhypar          #+#    #+#             */
/*   Updated: 2020/12/31 21:04:28 by junhypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		map_resol(char *out, t_game *g)
{
	int i;

	i = 0;
	g->width = 0;
	g->height = 0;
	i = no_space(out, i);
	if ((g->width = ft_atoi(out + i)) < 0)
		return (WRONG_RESOL_INPUT);
	i = skip_resol_word(out, i, 0);
	if (i == -1)
		return (WRONG_RESOL_INPUT);
	i = no_space(out, i);
	if ((g->height = ft_atoi(out + i)) < 0)
		return (WRONG_RESOL_INPUT);
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
	int len;

	i = 0;
	i = no_space(out, i);
	i = word_dup(out, g, i, flag);
	i = no_space(out, i);
	if (check_remain(out, i) != 0)
		return (WRONG_IMAGE_NAME_INPUT);
	len = ft_strlen(g->wall[flag].name);
	if (g->wall[flag].name[len - 1] == 'm' && g->wall[flag].name[len - 2] ==
			'p' && g->wall[flag].name[len - 3] == 'x' &&
			g->wall[flag].name[len - 4] == '.')
		return (0);
	return (WRONG_IMAGE_NAME_INPUT);
}

int		input_bg_color2(char *out, t_game *g, int flag, int i)
{
	unsigned int	j;

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

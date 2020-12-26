/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhypar <junhypar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 12:23:50 by junhypar          #+#    #+#             */
/*   Updated: 2020/12/25 22:17:36 by junhypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		no_space(char *out, int i)
{
	while (out[i] == ' ')
		i++;
	return (i);
}

int		find_rest(char *out, int i)
{
	while (out[i] != ',')
		i++;
	i++;
	i = no_space(out, i);
	return (i);
}

int		skip_resol_word(char *out, int i, int flag)
{
	while (out[i] != ' ')
	{
		if (flag == 1 && out[i] == ',')
			return (i);
		else if (out[i] >= '0' && out[i] <= '9')
			i++;
		else if (out[i] == '\0')
			return (i);
		else
			return (-1);
	}
	return (i);
}

int		word_dup(char *out, t_game *g, int i, int flag)
{
	int j;
	int k;
	int start;

	start = i;
	k = 0;
	j = 0;
	while (out[i] != ' ')
	{
		if (out[i] == '\0')
			break ;
		i++;
		j++;
	}
	g->wall[flag].name = malloc(sizeof(char) * (j + 1));
	ft_strlcpy(g->wall[flag].name, &out[start], j + 1);
	return (i);
}

int		check_remain(char *out, int i)
{
	if (out[i] != '\0')
		return (-1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init_matrix.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhypar <junhypar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 14:56:58 by junhypar          #+#    #+#             */
/*   Updated: 2020/11/06 15:54:50 by junhypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		reset_map(t_game *g)
{
	int i;
	int j;

	i = 0;
	if (!(g->map = (char **)malloc(sizeof(char *) * g->col)))
		return (MAP_IS_NOT_AVAILABLE);
	while (i < g->col)
	{
		j = 0;
		if (!(g->map[i] = (char *)malloc(sizeof(char) * (g->row + 2))))
			return (MAP_IS_NOT_AVAILABLE);
		g->map[i][g->row + 1] = '\0';
		while (j < g->row + 1)
		{
			g->map[i][j] = ' ';
			j++;
		}
		i++;
	}
	return (0);
}

int		find_sep(t_game *g)
{
	int i;

	i = 0;
	if (!(g->map_all))
		return (-1);
	while (g->map_all[i] != '\n')
		i++;
	g->map_all[i] = '\0';
	return (i);
}

void	cut_map_all(t_game *g, int j)
{
	char	*replace;
	int		len;

	len = ft_strlen(g->map_all + j + 1);
	if (len == 0)
	{
		free(g->map_all);
		g->map_all = 0;
	}
	else
	{
		replace = ft_strdup(g->map_all + j + 1);
		free(g->map_all);
		g->map_all = replace;
	}
}

void	input_map_data(t_game *g)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < g->col)
	{
		j = find_sep(g);
		if (j == -1)
			break ;
		ft_strlcpy(g->map[i], g->map_all, j + 1);
		g->map[i][j] = ' ';
		cut_map_all(g, j);
		i++;
	}
}

int		map_init_and_available_test(t_game *g)
{
	if (reset_map(g))
		return (MAP_IS_NOT_AVAILABLE);
	input_map_data(g);
	if (map_available_test(g))
		return (MAP_IS_NOT_AVAILABLE);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhypar <junhypar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 13:30:18 by junhypar          #+#    #+#             */
/*   Updated: 2020/11/06 15:51:19 by junhypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*ft_enter_strdup(char *str)
{
	int		len;
	char	*out;

	len = ft_strlen(str);
	if (!(out = malloc(sizeof(char) * (len + 2))))
		return (0);
	ft_strlcpy(out, str, len + 1);
	out[len] = '\n';
	out[len + 1] = '\0';
	free(str);
	str = 0;
	return (out);
}

int		init_map(char *out, t_game *g)
{
	int		len;

	len = ft_strlen(out);
	if (g->row < len)
		g->row = len;
	g->col = g->col + 1;
	g->map_all = ft_strjoin(g->map_all, out);
	if (!(g->map_all = ft_enter_strdup(g->map_all)))
		return (MAP_IS_NOT_AVAILABLE);
	return (0);
}

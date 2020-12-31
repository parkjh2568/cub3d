/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhypar <junhypar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 12:03:29 by junhypar          #+#    #+#             */
/*   Updated: 2020/12/31 21:37:16 by junhypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "./bonus.h"

void	free_all3(t_game *g)
{
	int i;

	i = 0;
	if (g->buf)
	{
		i = 0;
		while (i < g->height)
		{
			free(g->buf[i]);
			i++;
		}
		free(g->buf);
	}
	if (g->z_buf)
		free(g->z_buf);
	if (g->ex_texture)
	{
		i = 0;
		while (i < EX_OBJ_NUM)
		{
			free(g->ex_texture[i]);
			i++;
		}
		free(g->ex_texture);
	}
}

void	free_all2(t_game *g)
{
	int i;

	i = 0;
	if (g->map)
	{
		while (i < g->col)
		{
			if (g->map[i])
				free(g->map[i]);
			i++;
		}
		free(g->map);
	}
	if (g->texture)
	{
		i = 0;
		while (i < WALL_NUM)
		{
			free(g->texture[i]);
			i++;
		}
		free(g->texture);
	}
	free_all3(g);
}

void	free_all(t_game *g)
{
	int i;

	i = NO;
	while (i <= S)
	{
		if (g->wall[i].name)
			free(g->wall[i].name);
		i++;
	}
	if (g->map_all)
		free(g->map_all);
	free_all2(g);
}

int		main(int argc, char *argv[])
{
	t_game	g;
	int		er;

	reset_struct(&g);
	if ((argc == 3 && ft_strncmp(argv[2], "--save", 9)) || argc < 2 || argc > 3)
		ft_error(INPUT_ERROR, &g);
	if (argc == 3)
		g.save_flag = 1;
	if ((er = ft_read_map(&g, argv[1])))
		ft_error(er, &g);
	if ((er = map_init_and_available_test(&g)))
		ft_error(er, &g);
	ft_start_game(&g);
	free_all(&g);
	return (0);
}

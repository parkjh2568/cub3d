/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhypar <junhypar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 12:03:29 by junhypar          #+#    #+#             */
/*   Updated: 2020/12/31 22:19:20 by junhypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

void		free_all2(t_game *g)
{
	int i;

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
}

void		free_all(t_game *g)
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
	free_all2(g);
}

void		reset_struct2(t_game *g)
{
	int i;

	i = 0;
	while (i < 150)
	{
		g->key_trig[i] = 0;
		i++;
	}
	g->save_flag = 0;
	g->row = 0;
	g->col = 0;
	g->x = 0;
	g->y = 0;
	g->flag = 0;
	g->player_cnt = 0;
	g->dir_x = 0;
	g->dir_y = -1;
	g->plan_x = 0.66;
	g->plan_y = 0;
	g->mov_speed = 0.1;
	g->rot_speed = get_radian(10);
}

void		reset_struct(t_game *g)
{
	int i;

	g->map = 0;
	g->map_all = 0;
	i = NO;
	while (i <= S)
	{
		g->wall[i].name = 0;
		i++;
	}
	g->buf = 0;
	g->texture = 0;
	g->item_cnt = 0;
	g->z_buf = 0;
	reset_struct2(g);
}

int			main(int argc, char *argv[])
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

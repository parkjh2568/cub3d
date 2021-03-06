/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhypar <junhypar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 12:03:29 by junhypar          #+#    #+#             */
/*   Updated: 2020/12/28 13:35:33 by junhypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

void	free_all(t_game *g)
{
	int i;

	printf("\nwidth = %d, height= = %d",g->width, g->height);
	printf("\nNO_wall_name = %s",g->wall[NO].name);
	printf("\nSO_wall_name = %s",g->wall[SO].name);
	printf("\nWE_wall_name = %s",g->wall[WE].name);
	printf("\nEA_wall_name = %s",g->wall[EA].name);
	printf("\nSprite_name = %s",g->wall[S].name);
	printf("\nCeilling_color = %i",g->bgcolor[CEILLING]);
	printf("\nFloosr_color = %i",g->bgcolor[FLOOR]);
	printf("\ncol = %d, row = %d\n",g->col,g->row);
	printf("\n dir_x = %lf, dir_y = %lf\n",g->dir_x, g->dir_y);
	printf("\n plan_x = %lf, plan_y = %lf\n",g->plan_x, g->plan_y);
	printf("\n map_all = \n%s\n",g->map_all);
	printf("\n map_sep = \n");
	i = 0;
	while (i < WALL_NUM)
	{
		printf("wall[%d]name = %s, height = %d, width = %d\n",i,
				g->wall[i].name, g->wall[i].height, g->wall[i].width);
		i++;
	}
	i = 0;

	while(i < g->col)
	{
		printf("%s\n",g->map[i]);
		i++;
	}

	i = NO;
	while(i <= S)
	{
		if (g->wall[i].name)
		{
			free(g->wall[i].name);
		}
		i++;
	}
	if (g->map_all)
		free(g->map_all);
	i = 0;
	if (g->map)
	{
		while(i < g->col)
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
		while(i < WALL_NUM)
		{
			free(g->texture[i]);
			i++;
		}
		free(g->texture);
	}
	if (g->buf)
	{
		i = 0;
		while(i < g->height)
		{
			free(g->buf[i]);
			i++;
		}
		free(g->buf);
	}
}

void	reset_struct(t_game *g)
{
	int i;

	g->map = 0;
	g->map_all = 0;
	i = NO;
	while(i <= S)
	{
		g->wall[i].name = 0;
		i++;
	}
	g->buf = 0;
	g->texture = 0;


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

int		main(int argc, char *argv[])
{
	t_game	g;
	int		er;

	reset_struct(&g);
	if ((argc == 3 && ft_strncmp(argv[2], "--save", 9)) || argc < 2 || argc > 3)
		ft_error(INPUT_ERROR, &g);
	if ((er = ft_read_map(&g, argv[1])))
		ft_error(er, &g);
	if ((er = map_init_and_available_test(&g)))
		ft_error(er, &g);
	ft_start_game(&g);
	free_all(&g);
	return(0);
}

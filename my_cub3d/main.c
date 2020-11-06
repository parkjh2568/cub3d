/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhypar <junhypar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 12:03:29 by junhypar          #+#    #+#             */
/*   Updated: 2020/11/06 14:40:44 by junhypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

void	free_all(t_game *g)
{
	int i;

	i = NO;
	printf("\nwidth = %d, height= = %d",g->width, g->height);
	printf("\nNO_wall_name = %s",g->wall[NO].name);
	printf("\nSO_wall_name = %s",g->wall[SO].name);
	printf("\nWE_wall_name = %s",g->wall[WE].name);
	printf("\nEA_wall_name = %s",g->wall[EA].name);
	printf("\nSprite_name = %s",g->wall[S].name);
	printf("\nCeilling_color = %i",g->bgcolor[CEILLING]);
	printf("\nFloosr_color = %i",g->bgcolor[FLOOR]);
	printf("\n map = \n%s\n",g->map_all);
	while(i <= S)
	{
		if (g->wall[i].name)
			free(g->wall[i].name);
		i++;
	}
	if (g->map_all)
		free(g->map_all);
}

void	reset_struct(t_game *g)
{
	g->row = 0;
	g->col = 0;
	g->x = 0;
	g->y = 0;
	g->flag = 0;
}

int main(int argc, char *argv[])
{
	t_game	g;
	int		er;

	reset_struct(&g);
/*	if (argc == 3 || argc < 2 || argc > 3)
		ft_error(INPUT_ERROR);
	if (!(g.mlx = mlx_init()))
		ft_error(MLX_ERROR);*/
	if ((er = ft_read_map(&g, /*argv[1]*/"map.cub")))
		ft_error(er, &g);
	free_all(&g);
	return(0);
}

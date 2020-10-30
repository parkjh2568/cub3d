/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhypar <junhypar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 12:03:29 by junhypar          #+#    #+#             */
/*   Updated: 2020/10/30 15:39:20 by junhypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

int main(int argc, char *argv[])
{
	t_game	g;
	int		er;

/*	if (argc == 3 || argc < 2 || argc > 3)
		ft_error(INPUT_ERROR);
	if (!(g.mlx = mlx_init()))
		ft_error(MLX_ERROR);*/
	if ((er = ft_read_map(&g, /*argv[1]*/"map.cub")))
	//	ft_error(er);
		printf("er = %d",er);
	printf("\n width = %d, height= = %d",g.width, g.height);
	return(0);
}

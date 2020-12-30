/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_width_height.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhypar <junhypar@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 23:37:05 by junhypar          #+#    #+#             */
/*   Updated: 2020/12/31 00:05:01 by junhypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx_beta/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int		*config_width_height(int width, int height)
{
	void	*mlx;
	int		*data;

	data = malloc(sizeof(int) * 2);
	mlx = mlx_init();
	mlx_get_screen_size(mlx, &data[0], &data[1]);
	if (width < data[0])
		data[0] = width;
	if (height < data[1])
		data[1] = height;
	return (data);
}

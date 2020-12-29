/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_int_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhypar <junhypar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 09:33:45 by junhypar          #+#    #+#             */
/*   Updated: 2020/12/29 17:11:26 by junhypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	load_image2(t_game *g, int flag, t_img *img)
{
	int		x;
	int		y;

	g->wall[flag].height = img->height;
	g->wall[flag].width = img->width;
	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			g->texture[flag][img->width * y + (img->width - x - 1)] =
				img->data[img->width * y + x];
			x++;
		}
		y++;
	}
}

void	load_image(t_game *g, int flag, t_img *img)
{
	int		i;

	img->img = mlx_xpm_file_to_image(g->mlx, g->wall[flag].name,
			&img->width, &img->height);
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp,
			&img->size_l, &img->endian);
	i = 0;
	while (i < WALL_NUM)
	{
		g->texture[flag] =
			(int *)malloc(sizeof(int) * (img->height * img->width));
		i++;
	}
	i = 0;
	while (i < (img->height * img->width))
	{
		g->texture[flag][i] = 0;
		i++;
	}
	load_image2(g, flag, img);
	mlx_destroy_image(g->mlx, img->img);
}

void	put_in_texture(t_game *g)
{
	t_img	img;
	int		i;

	i = 0;
	while (i < WALL_NUM)
	{
		load_image(g, i, &img);
		i++;
	}
}

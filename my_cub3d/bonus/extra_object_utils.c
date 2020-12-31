/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_object_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhypar <junhypar@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 10:37:55 by junhypar          #+#    #+#             */
/*   Updated: 2020/12/31 16:13:30 by junhypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "./bonus.h"

void	find_extra_object_location(t_game *g, int i, int j)
{
	int		num;

	if (g->map[i][j] == 'M')
	{
		g->item[g->item_cnt].x = j + 0.5;
		g->item[g->item_cnt].y = i + 0.5;
		g->item[g->item_cnt].tex_num = 12;
		g->item[g->item_cnt].flag = 1;
		g->map[i][j] = '0';
		g->item_cnt += 1;
	}
	else
	{
		num = g->map[i][j] - '0';
		if (num >= BARRER)
		{
			g->item[g->item_cnt].x = j + 0.5;
			g->item[g->item_cnt].y = i + 0.5;
			g->item[g->item_cnt].tex_num = num;
			g->item[g->item_cnt].flag = 1;
			g->map[i][j] = '0';
			g->item_cnt +=1;
		}
	}
}

void	load_extra_image2(t_game *g, int flag, t_img *img)
{
	int		x;
	int		y;


	g->info_tex[flag].height = img->height;
	g->info_tex[flag].width = img->width;
	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			g->ex_texture[flag][img->width * y + (img->width - x - 1)] =
				img->data[img->width * y + x];
			x++;
		}
		y++;
	}
}

void	load_extra_image(t_game *g, int flag, char *name, t_img *img)
{
	int		i;

	i = 0;
	img->img = mlx_xpm_file_to_image(g->mlx, name, &img->width, &img->height);
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->size_l, 
			&img->endian);
	g->ex_texture[flag] = malloc(sizeof(int) * (img->height * img->width));
	while (i < (img->height * img->width))
	{
		g->ex_texture[flag][i] = 0;
		i++;
	}
	load_extra_image2(g, flag, img);
	mlx_destroy_image(g->mlx, img->img);
}

void	put_in_ex_texture(t_game *g)
{
	t_img	img;

	g->ex_texture = (int **)malloc(sizeof(int *) * EX_OBJ_NUM);
	load_extra_image(g, 0, "./tax/zavala.xpm", &img);
	load_extra_image(g, 1, "./tax/drifter.xpm", &img);
	load_extra_image(g, 2, "./tax/brick.xpm", &img);
	load_extra_image(g, 3, "./tax/blue.xpm", &img);
	load_extra_image(g, 4, "./tax/barrer.xpm", &img);
	load_extra_image(g, 5, "./tax/trap.xpm", &img);
	load_extra_image(g, 6, "./tax/potion.xpm", &img);
	load_extra_image(g, 7, "./tax/gun.xpm", &img);
	load_extra_image(g, 8, "./tax/gunfire.xpm", &img);
	load_extra_image(g, 9, "./tax/monster.xpm", &img);
	load_extra_image(g, 10, "./tax/monster_defend.xpm", &img);
	load_extra_image(g, 11, "./tax/lv.xpm", &img);
	load_extra_image(g, 12, "./tax/1.xpm", &img);
	load_extra_image(g, 13, "./tax/2.xpm", &img);
	load_extra_image(g, 14, "./tax/3.xpm", &img);
	load_extra_image(g, 15, "./tax/4.xpm", &img);
	load_extra_image(g, 16, "./tax/5.xpm", &img);
}

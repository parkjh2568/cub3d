/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhypar <junhypar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 11:18:03 by junhypar          #+#    #+#             */
/*   Updated: 2020/11/06 15:55:12 by junhypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		divdie_map_info(char *out, t_game *g)
{
	int i;

	i = 0;
	while (out[i] == ' ')
		i++;
	if (out[i] == 'R' && out[i + 1] == ' ')
		return (map_resol(&out[i + 2], g));
	else if (out[i] == 'N' && out[i + 1] == 'O' && out[i + 2] == ' ')
		return (input_wall_name(&out[i + 3], g, NO));
	else if (out[i] == 'S' && out[i + 1] == 'O' && out[i + 2] == ' ')
		return (input_wall_name(&out[i + 3], g, SO));
	else if (out[i] == 'W' && out[i + 1] == 'E' && out[i + 2] == ' ')
		return (input_wall_name(&out[i + 3], g, WE));
	else if (out[i] == 'E' && out[i + 1] == 'A' && out[i + 2] == ' ')
		return (input_wall_name(&out[i + 3], g, EA));
	else if (out[i] == 'S' && out[i + 1] == ' ')
		return (input_wall_name(&out[i + 2], g, S));
	else if (out[i] == 'F' && out[i + 1] == ' ')
		return (input_bg_color(&out[i + 2], g, FLOOR));
	else if (out[i] == 'C' && out[i + 1] == ' ')
		return (input_bg_color(&out[i + 2], g, CEILLING));
	return (WRONG_MAP);
}

int		divide_map_start(char *out, t_game *g, int *cnt)
{
	int i;

	i = 0;
	no_space(out, &i);
	if (out[i] == '\0')
	{
		if (*cnt <= 8)
			*cnt = *cnt - 1;
		return (0);
	}
	if (*cnt <= 8)
		return ((divdie_map_info(out, g)));
	else
		return ((init_map(out, g)));
	return (4);
}

int		check_error(int gnl_config, int divide_config)
{
	if (gnl_config == -1)
		return (GNL_ERROR);
	if (divide_config != 0)
		return (divide_config);
	return (0);
}

int		ft_read_map(t_game *g, char *map_name)
{
	int		fd;
	char	*out;
	int		gnl_config;
	int		divide_config;
	int		cnt;

	cnt = 0;
	fd = open(map_name, O_RDONLY);
	if (fd < 0)
		return (MAP_FILE_OPEN_ERROR);
	while (1)
	{
		gnl_config = get_next_line(fd, &out);
		if (gnl_config == -1)
			break ;
		cnt++;
		divide_config = divide_map_start(out, g, &cnt);
		if (gnl_config == 0 || divide_config != 0)
			break ;
		free(out);
	}
	free(out);
	close(fd);
	return (check_error(gnl_config, divide_config));
}
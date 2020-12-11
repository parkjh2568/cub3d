/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhypar <junhypar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 11:07:21 by junhypar          #+#    #+#             */
/*   Updated: 2020/10/30 13:04:41 by junhypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_error1(int err_code)
{
	if (err_code == INPUT_ERROR)
		write(1, "Error: Wrong Input\n", 19);
	else if (err_code == MLX_ERROR)
		write(1, "Error: Faile Mlx Init\n", 22);
	else if (err_code == MAP_FILE_OPEN_ERROR)
		write(1, "Error: Map File Open Error\n", 27);
	else if (err_code == GNL_ERROR)
		write(1, "Error: GNL Error\n", 17);
	else if (err_code == WRONG_MAP)
		write(1, "Error: Wrong Map File\n", 22);
}

void	ft_error(int err_code)
{
	if (err_code < 10)
		ft_error1(err_code);
	perror("");
	exit(1);
}

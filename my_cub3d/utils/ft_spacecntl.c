/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spacecntl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhypar <junhypar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 12:23:50 by junhypar          #+#    #+#             */
/*   Updated: 2020/10/30 15:50:36 by junhypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	no_space(char *out, int *i)
{
	while(out[*i] == ' ')
		*i = *i + 1;
}

int		skip_resol_word(char *out, int *i)
{
	while(out[*i] != ' ')
	{
		if (out[*i] >= '0' && out[*i] <= '9')
			*i = *i + 1;
		else if (out[*i] == '\0')
			return (0);
		else
			return (-1);
	}
	return (0);
}

int		skip_word(char *out, int *i)
{
	while(out[*i] != ' ')
	{
		if (out[*i] == '\0')
			return (0);
		else
			return (-1);
		*i = *i + 1;
	}
	return (0);
}

int		check_remain(char *out, int i)
{
	if (out[i] != '\0')
		return (-1);
	return (0);
}

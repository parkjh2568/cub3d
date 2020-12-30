/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhypar <junhypar@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 21:04:27 by junhypar          #+#    #+#             */
/*   Updated: 2020/12/30 22:38:41 by junhypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	BONUS_H
# define BONUS_H

# define DIVIDE_RGB 0
# define JOIN_RGB 1
# define MIX_ALPHA_RATIO_RGB 2
typedef struct	s_b_painter
{
	int			d_start_x;
	int			d_start_y;
	int			d_end_x;
	int			d_end_y;
	int			color;
	int			wanted_color;
	double		alpha_ratio;
	int			a;
	int			r;
	int			g;
	int			b;
}				t_b_painter;

void			start_bonus(t_game *g);
#endif

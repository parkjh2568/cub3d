/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhypar <junhypar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 21:04:27 by junhypar          #+#    #+#             */
/*   Updated: 2020/12/31 21:11:57 by junhypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_H
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
void			find_extra_object_location(t_game *g, int i, int j);
void			put_in_ex_texture(t_game *g);
void			check_div_move(t_game *g, t_painter *p);
void			draw_ex_item(t_game *g);
void			draw_sprite(t_game *g, t_painter *p, int i);
void			object_action(t_game *g);
void			draw_ex_wall(t_game *g, t_raycast *ray, t_painter *p, int j);
void			secret_door(t_game *g);
void			draw_lv(t_game *g);
void			check_lv_cops_div(t_game *g, t_painter *p);
int				press_mouse(int key, int *click);
int				release_mouse(int key, int *click);
void			mos_position(t_game *g);
void			reset_struct(t_game *g);
#endif

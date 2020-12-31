# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: junhypar <junhypar@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/28 10:41:18 by junhypar          #+#    #+#              #
#    Updated: 2020/12/31 21:12:16 by junhypar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3D

LIBNAME = libcub3D.a

SRCS	= ./gnl/get_next_line.c ./gnl/get_next_line_utils.c ./utils/ft_get_radian.c ./utils/ft_error.c ./utils/read_map_file.c ./utils/divid_map_config.c ./utils/string_control.c ./utils/init_map.c ./utils/map_init_matrix.c ./game/key_action.c ./game/put_int_texture.c ./game/key_press_release.c ./game/screenshort.c ./game/find_width_height.c

SRCS_O	= ./game/ft_start_game.c main.c ./utils/map_available_test.c ./game/ray_casting.c ./game/item_control.c ./game/draw_wall.c

SRCS_B	= ./bonus/ft_start_game.c ./bonus/main.c ./bonus/map_available_test.c ./bonus/start_bonus.c ./bonus/ray_casting.c ./bonus/extra_object_control.c ./bonus/extra_object_utils.c ./bonus/item_control.c ./bonus/object_action.c ./bonus/draw_wall.c ./bonus/draw_ex_wall.c ./bonus/secret_door.c ./bonus/draw_lv.c ./bonus/mouse_press_release.c ./bonus/reset_struct.c

OBJS	= ${SRCS:.c=.o}

OBJS_O	= ${SRCS_O:.c=.o}

OBJS_B	= ${SRCS_B:.c=.o}

CC		= gcc -Wall -Wextra -Werror 

CFLAG2	= -Lmlx -lmlx -L. -lmlx -framework OpenGL -framework AppKit -lm

all: ${NAME}

${NAME}:	${OBJS} ${OBJS_O}
			$(MAKE) bonus -C ./libft
			cp libft/libft.a ${LIBNAME}
			ar rc ${LIBNAME} ${OBJS} ${OBJS_O}
			${CC} ${CFLAG2} -o ${NAME} -L. -l${NAME} -L. -lmmlx


bo:			fclean ${OBJS} ${OBJS_B}
			$(MAKE) bonus -C ./libft
			cp libft/libft.a ${LIBNAME}
			ar rc ${LIBNAME} ${OBJS} ${OBJS_B}
			${CC} ${CFLAG2} -o ${NAME} -L. -l${NAME} -L. -lmmlx -I./bonus


clean:
		$(MAKE) clean -C ./libft
		rm -f ${OBJS}
		rm -f ${OBJS_O}
		rm -f ${OBJS_B}
		rm -f ${LIBNAME}

fclean:	clean
		$(MAKE) fclean -C ./libft
		rm -f ${NAME}

re:		fclean all

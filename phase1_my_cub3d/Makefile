# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: junhypar <junhypar@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/28 10:41:18 by junhypar          #+#    #+#              #
#    Updated: 2020/12/26 18:35:24 by junhypar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3D

LIBNAME = libcub3D.a

SRCS	= ./gnl/get_next_line.c ./gnl/get_next_line_utils.c ./utils/ft_get_radian.c main.c ./utils/ft_error.c ./utils/read_map_file.c ./utils/divid_map_config.c ./utils/string_control.c ./utils/init_map.c ./utils/map_init_matrix.c ./utils/map_available_test.c ./game/ft_key_press.c ./game/ft_start_game.c ./game/ray_casting.c

OBJS	= ${SRCS:.c=.o}

CC		= gcc 

CFLAG	= -Wall -Wextra -Werror

CFLAG2	= -Lmlx -lmlx -framework OpenGL -framework AppKit -lm

all: ${NAME}

${NAME}:	${OBJS}
			$(MAKE) bonus -C ./libft
			cp libft/libft.a ${LIBNAME}
			ar rc ${LIBNAME} ${OBJS}
			${CC} ${CFLAG} ${CFLAG2} -o ${NAME} -L. -l${NAME}

seg:		${OBJS}
			$(MAKE) bonus -C ./libft
			cp libft/libft.a ${LIBNAME}
			ar rc ${LIBNAME} ${OBJS}
			${CC} -g3 -fsanitize=address ${CFLAG} ${CFLAG2} -o ${NAME} -L. -l${NAME}


clean:
		$(MAKE) clean -C ./libft
		rm -f ${OBJS}
		rm -f ${LIBNAME}

fclean:	clean
		$(MAKE) fclean -C ./libft
		rm -f ${NAME}

re:		fclean all

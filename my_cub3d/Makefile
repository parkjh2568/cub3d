# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: junhypar <junhypar@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/28 10:41:18 by junhypar          #+#    #+#              #
#    Updated: 2020/10/28 20:32:41 by junhypar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3D

SRCS	= ./gnl/get_next_line.c ./gnl/get_next_line_utils.c ./utils/ft_get_radian.c ./main.c ./cub3d.c ./utils/ft_memcpy.c ./ft_draw_screen.c ./ft_display.c

OBJS	= ${SRCS:.c=.o}

CC		= gcc

CFLAG	= -Wall -Wextra -Werror -I.

CFLAG2	= -Lmlx -lmlx -framework OpenGL -framework AppKit -lm

all: ${NAME}

${NAME}:
		${CC} ${CFLAG} -o ${NAME} ${SRCS} ${CFLAG2} 

clean:
		rm -f ${OBJS}

fclean:	clean
		rm -f ${NAME}

re:		fclean all

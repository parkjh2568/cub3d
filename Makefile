# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: junhypar <junhypar@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/25 11:02:46 by junhypar          #+#    #+#              #
#    Updated: 2020/08/13 18:36:56 by junhypar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	cub3D

SRCS	=	

OBJS	=	${SRCS:.c=.o}

CC		=	gcc -Wall -Werror -Wextra 

all:		${NAME}

.c.o:
			${CC} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			$(MAKE) bonus -C ./libft
			cp libft/libft.a ${NAME}
			ar rc ${NAME} ${OBJS}

clean:
			$(MAKE) clean -C ./libft
			rm -f ${OBJS}

fclean:		clean
			$(MAKE) fclean -C ./libft
			rm -f ${NAME}

re:			fclean all

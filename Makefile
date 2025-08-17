# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: souaguen <souaguen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/06 08:44:02 by souaguen          #+#    #+#              #
#    Updated: 2025/08/17 22:32:23 by souaguen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc
CFLAGS=-Wall -Wextra -Werror -I./libft -I./minilibx-linux -I./ 
NAME=miniRT
SRC=parsing/ft_parsing_utils.c \
    parsing/ft_shapes.c \
    parsing/ft_plan_parsing.c \
    parsing/ft_light_parsing.c \
    parsing/ft_sphere_parsing.c \
    parsing/ft_cylinder_parsing.c \
    parsing/ft_camera_parsing.c \
    parsing/ft_ambient_parsing.c \
    parsing/ft_checkers.c \
    parsing/ft_others.c \
    parsing/ft_init.c \
    rendering/ft_sphere_utils.c \
    rendering/ft_cylinder_utils.c \
    rendering/ft_cylinder_extra.c \
    rendering/ft_plan_utils.c \
    rendering/ft_utils.c \
    rendering/ft_mlx_utils.c \
    rendering/ft_render_utils.c \
    rendering/ft_render.c \
    rendering/ft_axis_utils.c \
    main.c
OBJ=$(SRC:.c=.o)

$(NAME): $(OBJ)
	make -C minilibx-linux
	make -C ./libft all bonus
	$(CC) $(CFLAGS) $(OBJ) -g -o $(NAME) -L./libft -l:libft.a -L./minilibx-linux -l:libmlx.a -lmlx -lXext -lX11 -lm

all: $(NAME)

clean:
	make -C ./libft clean	
	make -C ./minilibx-linux clean
	rm -f $(OBJ)

fclean: clean
	make -C ./libft fclean
	rm -f $(NAME)

re: clean all

.PHONY: all clean fclean re

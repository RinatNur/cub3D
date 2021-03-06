# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jheat <jheat@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/17 15:41:11 by jheat             #+#    #+#              #
#    Updated: 2020/10/21 18:20:47 by jheat            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRC = check_file.c colors.c draw.c draw_sprite.c main.c parcer_init.c parcer.c\
        raycasting.c screenshot.c spr_and_map.c check_file_utils.c move.c\
        get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

OBJ = $(patsubst %.c,%.o,$(SRC))

HEADER = cub.h

FLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft
	@make -C mlx_dylib
	@cp libft/libft.a ./
	@cp mlx_dylib/libmlx.dylib ./
	@gcc $(FLAGS) libft.a libmlx.dylib -framework OpenGl -framework AppKit $(SRC) -o $(NAME)

bonus: all

%.o: %.c $(HEADER)
	gcc $(FLAGS) -c $< -o $@

clean:
	@make -C libft clean
	@make -C mlx_dylib clean
	@rm -f $(OBJ)

fclean: clean
	@make -C libft fclean
	@make -C mlx_dylib clean
	@rm -f libft.a
	@rm -f libmlx.dylib
	@rm -f $(NAME)

re: fclean all

run:
	./$(NAME) map.cub

scr_shot:
	./$(NAME) map.cub --save

norm :
	@norminette *.c *.h ./libft/*.c ./libft/*.h \
	get_next_line/*.c get_next_line/*.h

.PHONY: all bonus clean fclean re run scr_shot norminette

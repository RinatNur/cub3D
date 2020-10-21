cmake_minimum_required(VERSION 3.16.5)
project(cub3D C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -framework OpenGL -framework AppKit -I mlx_dylib -L../mlx_dylib -lmlx")

include_directories(.)
include_directories(get_next_line)
include_directories(libft)
include_directories(mlx_dylib)


add_executable(cub3D
        get_next_line/get_next_line.c
        get_next_line/get_next_line.h
        get_next_line/get_next_line_utils.c
        libft/ft_atoi.c
        libft/ft_bzero.c
        libft/ft_calloc.c
        libft/ft_isalnum.c
        libft/ft_isalpha.c
        libft/ft_isascii.c
        libft/ft_isdigit.c
        libft/ft_isprint.c
        libft/ft_itoa.c
        libft/ft_lstadd_back.c
        libft/ft_lstadd_front.c
        libft/ft_lstlast.c
        libft/ft_lstnew.c
        libft/ft_lstsize.c
        libft/ft_memccpy.c
        libft/ft_memchr.c
        libft/ft_memcmp.c
        libft/ft_memcpy.c
        libft/ft_memmove.c
        libft/ft_memset.c
        libft/ft_putchar_fd.c
        libft/ft_putendl_fd.c
        libft/ft_putnbr_fd.c
        libft/ft_putstr_fd.c
        libft/ft_split.c
        libft/ft_strchr.c
        libft/ft_strdup.c
        libft/ft_strjoin.c
        libft/ft_strlcat.c
        libft/ft_strlcpy.c
        libft/ft_strlen.c
        libft/ft_strmapi.c
        libft/ft_strncmp.c
        libft/ft_strnstr.c
        libft/ft_strrchr.c
        libft/ft_strtrim.c
        libft/ft_substr.c
        libft/ft_tolower.c
        libft/ft_toupper.c
        libft/libft.h
        colors.c
        draw.c
        cub.h
        main.c
        move.c
        spr_and_map.c
        parcer.c
        check_file.c
        draw_sprite.c
        raycasting.c
        screenshot.c
        check_file_utils.c
        parcer_init.c)

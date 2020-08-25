cmake_minimum_required(VERSION 3.16)
project(cub3D C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(mlx)
include_directories(libft/libft)
include_directories(get_next_line)
include_directories(includes)

set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -L. -lmlx -framework OpenGL -framework AppKit")

file(GLOB
        LIBFT "libft/libft/*.c")
file(GLOB
        SRCS "srcs/*.c" "srcs/parser/*.c" "srcs/utils/*.c")

add_executable(cub3D
        get_next_line/get_next_line.c
        get_next_line/get_next_line_utils.c
        get_next_line/get_next_line.h
        ${LIBFT}
        ${SRCS}
        ${PARSER}
        libft/libft/libft.h
        libft/libft/double_linked_lists/ft_my_lstnew.c
        libft/libft/double_linked_lists/ft_my_lstadd_back.c
        libft/libft/double_linked_lists/ft_my_lstlast.c
        libft/libft/double_linked_lists/ft_my_lstiter.c srcs/utils/get_pixel.c)

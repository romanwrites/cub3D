cmake_minimum_required(VERSION 3.16)
project(cub3D C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(mlx)
include_directories(libft/libft)
include_directories(get_next_line)
include_directories(includes)

set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -L. -lmlx -framework OpenGL -framework AppKit")
#set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")

file(GLOB
        LIBFT "libft/libft/*.c")
file(GLOB
        SRCS "*.c")

add_executable(cub3D
        get_next_line/get_next_line.c
        get_next_line/get_next_line_utils.c
        get_next_line/get_next_line.h
        ${LIBFT}
        ${SRCS}
        ${PARSER}
        libft/libft/libft.h
        draw_all_txt.c
        calculations.c
        dda.c
        create_txt_and_sprite_imgs.c
        utils.c)

cmake_minimum_required(VERSION 3.16)
project(cub3D C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(mlx)
include_directories(libft/libft)
include_directories(get_next_line)


set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -L. -lmlx -framework OpenGL -framework AppKit")

file(GLOB
        LIBFT "libft/libft/*.c")

add_executable(cub3D
        cub3d.c
        cub3d.h
        trgb_colors.c
        trgb_colors_operations.c
        drawings.c
        extra.c
        cub3d_extras.h
        exit_program.c
        parse_args.c
        parse_map.c
        parse_map_utils.c
        get_next_line/get_next_line.c
        get_next_line/get_next_line_utils.c
        get_next_line/get_next_line.h
        ${LIBFT}
        libft/libft/libft.h
        libft/libft/double_linked_lists/ft_my_lstnew.c
        libft/libft/double_linked_lists/ft_my_lstadd_back.c
        libft/libft/double_linked_lists/ft_my_lstlast.c
        libft/libft/double_linked_lists/ft_my_lstiter.c
        parse_textures.c
        parse_colors.c
        parse_line_content.c
        draw_map.c
        hooks.c
        init_structs.c)

NAME = cub3D

LIBFT = libft/libft/
FLAGS = -Wall -Wextra -Werror
CC = gcc

NORM = norminette *.c *.h
PARALLEL ?= -j

SRC =	cub3d.c \
		set_player_vectors.c \
		create_map_array.c \
		draw_sprites.c \
		draw_frame.c \
		draw_map.c \
		exit_program.c \
		ft_alloc_check.c \
		init_structs.c \
		keys.c \
		moves.c \
		render.c \
		turns.c \
		draw_utils.c \
		save_screenshot.c \
		parse.c \
        parse_args.c \
        parse_colors.c \
        parse_map.c \
        parse_map_utils1.c \
        parse_map_utils2.c \
        parse_resolution.c \
        parse_textures.c \
        read_map.c \
		get_next_line/get_next_line.c \
		get_next_line/get_next_line_utils.c \
		draw_all_txt.c \
		calculations.c \
		dda.c \
		draw_sprites_calc.c \


OBJ =	$(SRC:%.c=%.o)

all:	$(NAME)

MLX = -lmlx -lm -framework OpenGL -framework AppKit

$(NAME) : $(OBJ)
	@make -C ./mlx
	@cp mlx/libmlx.dylib .
	@$(MAKE) -C ./libft/libft
	@$(MAKE) bonus -C ./libft/libft
	@gcc $(OBJ) -I. -Wall -Wextra -Werror $(MLX) ./libft/libft/libft.a -o $(NAME)
	@echo "\033[33m[Done !]"



run:
	./cub3D map.cub


.PHONY: mlx clean_mlx norm fclean clean re all run

mlxclean:
		@cd mlx && make clean
		@cd mlx && rm -f *.swiftsourceinfo

minilibx:
		@make -C ./mlx
		@cp mlx/libmlx.dylib .

norm:	
		@echo "\tlibft\n" && cd libft/libft && $(NORM)
		@echo "\tget_next_line\n" && cd get_next_line && $(NORM)
		@echo "\tcub3D\n" && $(NORM)

clean:	#mlxclean
		rm -f $(OBJ)
		rm -f *.d
		cd libft/libft && make fclean
		

fclean:
		rm -f $(OBJ)
		rm -f *.d
		cd libft/libft && make fclean
		rm -f cub3D
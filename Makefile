NAME = cub3D

FLAGS = -Wall -Wextra -Werror
CC = gcc

NORM = norminette *.c *.h

SRC =	cub3d.c \
		trgb_colors.c \
		trgb_colors_operations.c \

OBJ =	$(SRC:.c=.o)

#D_FILES = $(patsubst %.o, %.d, $(OBJ))
#include $(wildcard $(D_FILES))

%.o: %.c
	$(CC) $(FLAGS) -Imlx -c $< -o $@

all: $(NAME)

$(NAME):	$(OBJ)
			$(CC) $(FLAGS) -I ./mlx $(SRC) -L. -lmlx -framework OpenGL -framework AppKit -o $(NAME)
#			@echo Compiling $(CLION_EXE_DIR)/$@ ...

.PHONY: mlx clean_mlx norm fclean clean re all

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
		rm -f cub3D

fclean:
		@rm -f libmlx.dylib

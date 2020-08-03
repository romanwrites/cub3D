NAME = cub3D

FLAGS = -Wall -Wextra -Werror
CC = gcc

HEADERS = -I./mlx -I.

NORM = norminette *.c *.h

SRC =	cub3d.c \
		trgb_colors.c \
		trgb_colors_operations.c \

OBJ =	$(SRC:.c=.o)

D_FILES = $(patsubst %.o, %.d, $(OBJ))

include $(wildcard $(D_FILES))

# assuming that you have the mlx source in a directory named mlx in the root of your project:
%.o: %.c
	$(CC) $(FLAGS) -Imlx -c $< -o $@

all: $(NAME)

# To link with the required internal MacOS API’s:
$(NAME):	$(OBJ)
			$(CC) $(FLAGS) -I ./mlx cub3d.c -L. -lmlx -framework OpenGL -framework AppKit -o $(NAME)
			@echo "cub3D\n"

# Do mind that you need the libmlx.dylib in the same directory as your build target as it is a dynamic library!

.PHONY: mlx, clean_mlx, norm, fclean, clean, re, all

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

fclean:
		@rm -f libmlx.dylib

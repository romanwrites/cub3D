
#include "cub3d.h"

void			ft_error_close(int error_code)
{
	if (error_code == ERR_MALLOC)
		write(2, "Error!\nMalloc() error.\n", 23); //7
	else if (error_code == ERR_ARGC_MIN)
		write(2, "Error!\nNo map passed.\n", 22);
	else if (error_code == ERR_FILENAME)
		write(2, "Error!\nIncorrect map extension.\n", 32);
	else if (error_code == ERR_ARG_SAVE)
		write(2, "Error!\nIncorrect save argument.\n", 32);
	else if (error_code == ERR_ARGC_MAX)
		write(2, "Error!\nToo many arguments.\n", 27);
	else if (error_code == ERR_READ_MAP)
		write(2, "Error!\nMap doesn't read.\n", 25);
	else if (error_code == ERR_MAP_VALIDITY)
		write(2, "Error!\nMap is not valid.\n", 25);
	else if (error_code == ERR_MAP_R)
		write(2, "Error!\nMap params are bad. Check R parameter.\n", 46);
	else if (error_code == ERR_MAP_T)
		write(2, "Error!\nMap params are bad. Check texture parameters.\n", 53);
	else if (error_code == ERR_MAP_C)
		write(2, "Error!\nMap params are bad. Check colours.\n", 42);
	else if (error_code == ERR_MAP_OPEN)
		write(2, "Error!\nMap borders are open.\n", 29);
	else if (error_code == ERR_MAP_BAD_ARG)
		write(2, "Error!\nMap arg is bad.\n", 23);
	exit(EXIT_FAILURE);
}

int				ft_close(int exit_code, t_game *sv)
{
	if (exit_code < 0)
		ft_error_close(exit_code);

	if (exit_code == 53)
	{
		printf("I am printing ESC when 53 is passed\n");
		mlx_destroy_image(sv->mlx, sv->img.img);
		mlx_destroy_window(sv->mlx, sv->win);
		exit(EXIT_SUCCESS);
	}

	return(0);
}

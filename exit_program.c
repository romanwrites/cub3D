
#include "cub3d.h"

void			ft_error_close(int error_code)
{
	if (error_code == ERR_MALLOC)
		write(2, "Error!\nmalloc() error\n", 22); //7
	else if (error_code == ERR_ARGC_MIN)
		write(2, "Error!\nNo map passed\n", 21);
	else if (error_code == ERR_FILENAME)
		write(2, "Error!\nIncorrect map extension\n", 31);
	else if (error_code == ERR_ARG_SAVE)
		write(2, "Error!\nIncorrect save argument\n", 31);
	else if (error_code == ERR_ARGC_MAX)
		write(2, "Error!\nToo many arguments\n", 26);
	else if (error_code == ERR_READ_MAP)
		write(2, "Error!\nMap doesn't read\n", 24);
	else if (error_code == ERR_MAP_VALIDITY)
		write(2, "Error!\nMap doesn't read\n", 24);
	exit(EXIT_FAILURE);
}

int				ft_close(int exit_code)
{
	if (exit_code < 0)
		ft_error_close(exit_code);
	if (exit_code == ESC)
		exit(EXIT_SUCCESS);
	return(0);
}

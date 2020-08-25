
#ifndef CUB3D_EXTRAS_H
# define CUB3D_EXTRAS_H

#include "cub3d.h"

void		draw_square(int i, int j, unsigned int *colours, t_data *img);
void 		set_line(int x0, int y0, int x1, int y1, unsigned int *colours, t_data *img);
void		draw_сircle_filled(int xm, int ym, int r, t_game *sv, unsigned int *colours);
void		draw_сircle(int xm, int ym, int r, t_data *data, unsigned int *colours);

#endif
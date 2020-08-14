#include "cub3d_extras.h"

void		draw_square(int i, int j, unsigned int *colours, t_data *img)
{
	unsigned int colour;

	while (i++ < 255)
	{
		while (j++ < 255)
		{
			my_mlx_pixel_put(img, j, i, colour);
		}
		j = 0;
		colours[1]--;
		colours[2]++;
		colours[3]++;
		colour = create_trgb(0, colours[1], colours[2], colours[3]);
	}
}

void		draw_сircle_filled(int xm, int ym, int r, t_data *data, unsigned int *colours)
{
	unsigned int 	colour = create_trgb(colours[0], colours[1], colours[2], colours[3]);

	int x = -r, y = 0, err = 2-2*r; /* II. Quadrant */
	do {
		my_mlx_pixel_put(data, xm-x, ym+y, colour); /*   I. Quadrant */
		my_mlx_pixel_put(data, xm-x, ym-y, colour); /*  II. Quadrant */
		my_mlx_pixel_put(data, xm+x, ym-y, colour); /* III. Quadrant */
		my_mlx_pixel_put(data, xm+x, ym+y, colour); /*  IV. Quadrant */
		draw_line_bresenham(xm-x, ym+y, xm-x, ym-y, colours, data); //draw line
		draw_line_bresenham(xm+x, ym-y, xm+x, ym+y, colours, data); //kek
//		if (colours[1] == 255)
//			colours[1] = 0;
//		colours[1] -= 1;
//		colours[2] -= 1;
//		colours[3] += 1;

		colour = create_trgb(colours[0], colours[1], colours[2], colours[3]);
		colour = add_shade(1, colour);
		r = err;
		if (r <= y) err += ++y*2+1;           /* e_xy+e_y < 0 */
		if (r > x || err > y) err += ++x*2+1; /* e_xy+e_x > 0 or no 2nd y-step */
	} while (x <= 0);
}

void		draw_сircle(int xm, int ym, int r, t_data *data, unsigned int *colours)
{
	unsigned int 	colour = create_trgb(colours[0], colours[1], colours[2], colours[3]);
	int x = -r;
	int y = 0;
	int err = 2 - 2 * r; /* II. Quadrant */

	do
	{
		my_mlx_pixel_put(data, xm - x, ym + y, colour); /*   I. Quadrant */
		my_mlx_pixel_put(data, xm - x, ym - y, colour); /*  II. Quadrant */
		my_mlx_pixel_put(data, xm + x, ym - y, colour); /* III. Quadrant */
		my_mlx_pixel_put(data, xm + x, ym + y, colour); /*  IV. Quadrant */
		r = err;
		if (r <= y)
		{
			y++;
			err += y * 2 + 1;
		}
		if (r > x || err > y)
		{
			x++;
			err += x * 2 + 1;
		}
	}
	while (x <= 0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <kukinpower@ya.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 03:24:11 by mkristie          #+#    #+#             */
/*   Updated: 2020/08/12 03:24:35 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		set_player_vectors(t_game *sv, int j, int i)
{
	sv->map.player_num = j;
	sv->map.pos_x = i;
	sv->map.pos_y = (j - i) / sv->map.max_len;
	if (sv->map.map_array[j] == 'N')
	{
		sv->map.dir_x = 0;
		sv->map.dir_y = -1;
	}
	else if (sv->map.map_array[j] == 'S')
	{
		sv->map.dir_x = 0;
		sv->map.dir_y = 1;
	}
	else if (sv->map.map_array[j] == 'W')
	{
		sv->map.dir_x = -1;
		sv->map.dir_y = 0;
	}
	else if (sv->map.map_array[j] == 'E')
	{
		sv->map.dir_x = 1;
		sv->map.dir_y = 0;
	}
	printf ("\nPOSITION-------------------------\nx: %f, y: %f, dir_x: %f, dir_y: %f\n\n", sv->map.pos_x,sv->map.pos_y,sv->map.dir_x,	sv->map.dir_y);
}

void		set_plane_and_time(t_game *sv)
{
	sv->map.plane_x = 0;
	sv->map.plane_y = 0.66; //the 2d raycaster version of camera plane
	sv->map.time = 0; //time of current frame
	sv->map.old_time = 0;; //time of previous frame

}

void		casting_frame(t_game *sv)
{
	for(int x = 0; x < sv->map.res_w; x++)
	{
		//calculate ray position and direction
		double camera_x = 2 * x / (double)sv->map.res_w - 1; //x-coordinate in camera space  double cameraX = 2 * x / (double)w - 1;
		double ray_dir_x = sv->map.dir_x  + sv->map.plane_x * camera_x;
		double ray_dir_y = sv->map.dir_y + sv->map.plane_y * camera_x;
		//which box of the map we're in
		int map_x = (int)sv->map.pos_x;
		int map_y = (int)sv->map.pos_y;

		//length of ray from current position to next x or y-side
		double side_dist_x;
		double side_dist_y;

		//length of ray from one x or y-side to next x or y-side
		double deltaDistX = abs(1 / ray_dir_x);
		double deltaDistY = abs(1 / ray_dir_y);
		double perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?
		//calculate step and initial sideDist
		if(ray_dir_x < 0)
		{
			stepX = -1;
			side_dist_x = (sv->map.pos_x - map_x) * deltaDistX;
		}
		else
		{
			stepX = 1;
			side_dist_x = (map_x + 1.0 - sv->map.pos_x) * deltaDistX;
		}
		if(ray_dir_y < 0)
		{
			stepY = -1;
			side_dist_y = (sv->map.pos_y - map_y) * deltaDistY;
		}
		else
		{
			stepY = 1;
			side_dist_y = (map_y + 1.0 - sv->map.pos_y) * deltaDistY;
		}
		//perform DDA
		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if(side_dist_x < side_dist_y)
			{
				side_dist_x += deltaDistX;
				map_x += stepX;
				side = 0;
			}
			else
			{
				side_dist_y += deltaDistY;
				map_y += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if(sv->map.map_array[map_x + map_y * sv->map.max_len] > 0)
				hit = 1; //map_array
		}
		//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		if(side == 0)
			perpWallDist = (map_x - sv->map.pos_x + (1 - stepX) / 2) / ray_dir_x;
		else
			perpWallDist = (map_y - sv->map.pos_y + (1 - stepY) / 2) / ray_dir_y;

		//Calculate height of line to draw on screen
		int line_height = (int)(sv->map.res_h / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -line_height / 2 + sv->map.res_h / 2;
		if(drawStart < 0)drawStart = 0;
		int drawEnd = line_height / 2 + sv->map.res_h / 2;
		if(drawEnd >= sv->map.res_h)drawEnd = sv->map.res_h - 1;

		//choose wall color
		unsigned int color;
		switch(sv->map.map_array[map_x + map_y * sv->map.max_len])
		{
			case 1:  color = create_trgb(0, 255, 0, 0);    break; //red
			case 2:  color = create_trgb(0, 0, 255, 0);  break; //green
			case 3:  color = create_trgb(0, 0, 0, 255);   break; //blue
			case 4:  color = create_trgb(0, 255, 255, 255);  break; //white
			default: color = create_trgb(0, 0, 255, 255); break; //yellow
		}

		//give x and y sides different brightness
		if(side == 1)
		{
			color = color / 2;
		}

		//draw the pixels of the stripe as a vertical line
		draw_line_bresenham(x, drawStart, x, drawEnd, color, &sv->img);
//		verLine(x, drawStart, drawEnd, color);
	}
}

void		create_map_array(t_game *sv)
{
	int		i;
	int 	j;

	i = 0;
	j = 0;
	if (!(sv->map.map_array = ft_calloc(1, sv->map.map_rows * sv->map.map_cols + 1)))
		ft_error_close(ERR_MALLOC);
	while (sv->lst)
	{
		while (((char *)sv->lst->content)[i])
		{
			if (((char *)sv->lst->content)[i] == 'N' || ((char *)sv->lst->content)[i] == 'S' || \
				((char *)sv->lst->content)[i] == 'W' || ((char *)sv->lst->content)[i] == 'E')
			{
				set_player_vectors(sv, j, i);
				sv->map.map_array[j] = '0';
			}
			else
				sv->map.map_array[j] = ((char *)sv->lst->content)[i];
			i++;
			j++;
		}
		i = 0;
		sv->lst = sv->lst->next;
	}
	sv->map.map_array[j] = '\0';
	printf("\n\nMAP-------------------------------%s\n\n", sv->map.map_array);
	set_plane_and_time(sv);
}

void draw_rectangle(t_game *sv, const int img_w, const int img_h, const int x, const int y, const int w, const int h, int color)
{
	for (int i=0; i<w; i++)
	{
		for (int j=0; j<h; j++)
		{
			size_t cx = x+i;
			size_t cy = y+j;
			if (cx >= img_w || cy >= img_h) continue; // no need to check negative values, (unsigned variables)
			sv->img.addr[cx + cy * img_w] = color;
		}
	}
}

void    draw_black_screen(t_game *sv, int win_h, int win_w, int color)
{
    for (size_t j = 0; j<win_h; j++) { // fill the screen with color gradients
        for (size_t i = 0; i<win_w; i++) {
            uint8_t r = 255 * j / (float)win_h; // varies between 0 and 255 as j sweeps the vertical
            uint8_t g = 255 * i / (float)win_w; // varies between 0 and 255 as i sweeps the horizontal
            uint8_t b = 0;
            sv->img.addr[i+j*win_w] = color;
        }
    }
}

void		draw_map(t_game *sv)
{
	int 	i;
	int 	j;
	int 	map_w = 16;
	int 	map_h = 16;
	int		rect_x;
	int		rect_y;

	i = 0;
	j = 0;

////	double player_x = 3.456; // player x position
////	double player_y = 2.345; // player y position
////	double player_a = 1.523; // player view direction
//    sv->player.player_x = 3; // player x position
//    sv->player.player_y = 2; // player y position
//    sv->player.player_a = 1; // player view direction
	const double fov = M_PI/3.; // field of view

	const int rect_w = sv->map.res_w / (map_w * 2);
	const int rect_h = sv->map.res_h / map_h;

	while (i < map_h)
	{
		while (j < map_w)
		{
			if (sv->map.map_array[i + j * map_w] == '0')
			{
				j++;
				continue ;
			}

			rect_x = i * rect_w;
			rect_y = j * rect_h;
			draw_rectangle(sv, sv->map.res_w, sv->map.res_h, rect_x, rect_y, rect_w, rect_h, create_trgb(0, 0, 255, 255));
			mlx_put_image_to_window(sv->mlx, sv->win, sv->img.img, 0, 0);
			j++;
		}
		j = 0;
		i++;
	}

	for (size_t i=0; i < (sv->map.res_w / 2); i++)
	{ // draw the visibility cone AND the "3D" view
		double angle = sv->player.player_a-fov/2 + fov * i / ((double)(sv->map.res_w / 2));
		for (double t=0; t<20; t+=.05)
		{
			double cx = sv->player.player_x + t * cos(angle);
			double cy = sv->player.player_y + t * sin(angle);

			int pix_x = cx * rect_w;
			int pix_y = cy * rect_h;
			sv->img.addr[pix_x + pix_y * sv->map.res_w] = create_trgb(0, 255, 0, 0); // this draws the visibility cone

			if (sv->map.map_array[((int)cx) + ((int)cy) * map_w] != '0')
			{ // our ray touches a wall, so draw the vertical column to create an illusion of 3D
				size_t column_height = sv->map.res_h / t;
				draw_rectangle(sv, sv->map.res_w, sv->map.res_h, sv->map.res_w / 2 + i, sv->map.res_h / 2 - column_height / 2, 1, column_height, create_trgb(0, 255, 255, 0));
				break;
			}
		}
	}
}


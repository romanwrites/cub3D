/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 11:03:51 by mkristie          #+#    #+#             */
/*   Updated: 2020/09/01 14:34:31 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <math.h>
# include <fcntl.h>
# include "get_next_line.h"
# include "libft.h"

# define FOV						tan(80/2 * M_PI/180)
# define MOVE_SPEED					0.15
# define ROT						0.15
# define PRINT_FRAME_NUMBER			0

# define KEY_PRESS_MASK				(1L<<0)
# define KEY_RELEASE_MASK			(1L<<1)
# define KEY_PRESS					2
# define KEY_RELEASE				3
# define BYTES_PER_PIXEL			4
# define FILE_HEADER_SIZE			14
# define INFO_HEADER_SIZE			40
# define UDIV						1
# define VDIV						1
# define VMOVE						150.0

enum		e_errors {
	ERR_ARGC_MIN = -15,
	ERR_ARGC_MAX,
	ERR_MAP_VALIDITY,
	ERR_MAP_BAD_ARG,
	ERR_MAP_C,
	ERR_MAP_OPEN,
};

enum				e_keys {
	A,
	S,
	D,
	W = 13,
	ESC = 53,
	LEFT = 123,
	RIGHT = 124,
};

typedef struct		s_data {
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_data;

typedef struct		s_conf {
	int				res_w;
	int				res_h;
	char			*no_path;
	int				no_w;
	int				no_h;
	int				so_w;
	int				so_h;
	int				ea_w;
	int				ea_h;
	int				we_w;
	int				we_h;
	int				sprite_w;
	int				sprite_h;
	char			*so_path;
	char			*we_path;
	char			*ea_path;
	char			*s_path;
	int				floor_rgb[3];
	int				floor_color;
	int				ceiling_rgb[3];
	int				ceiling_color;
	char			player_direction;
	_Bool			f_color_parse;
	_Bool			c_color_parse;
	char			*map_arr;
	size_t			map_cols;
	size_t			map_rows;
	size_t			max_len;
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	int				x;
	double			*z_buffer;
	double			camera_x;
	double			ray_dir_x;
	double			ray_dir_y;
	int				map_x;
	int				map_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			perp_wall_dist;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	int				line_height;
	double			wall_x;
	int				tex_x;
	int				s_tex_x;
	int				tex_y;
	int				s_tex_y;
	double			step;
	double			tex_pos;
	double			sprite_x;
	double			sprite_y;
	double			inv_det;
	double			transform_x;
	double			transform_y;
	int				sprite_screen_x;
	int				v_move_screen;
	int				sprite_height;
	int				draw_start_y;
	int				draw_end_y;
	int				sprite_width;
	int				draw_start_x;
	int				draw_end_x;
}					t_conf;

typedef struct		s_keys {
	_Bool			w;
	_Bool			s;
	_Bool			a;
	_Bool			d;
	_Bool			left;
	_Bool			right;
}					t_keys;

typedef	struct		s_sprite
{
	double			x;
	double			y;
	double			s_dist;
}					t_sprite;

typedef	struct		s_draw
{
	int				x;
	int				draw_start;
	int				draw_end;
	int				color;
	int				ceiling_y0;
	int				ceiling_y1;
	int				floor_y0;
	int				floor_y1;
}					t_draw;

typedef struct		s_game {
	void			*mlx;
	void			*win;
	t_data			img;
	t_conf			map;
	t_d_list	*head;
	t_d_list	*lst;
	t_d_list	*tmp;
	t_keys			keys;
	t_data			north;
	t_data			south;
	t_data			west;
	t_data			east;
	t_data			sprite;
	t_sprite		*sprites_on_map;
	t_draw			draw;
	int				sprites_count;
	char			*filename;
}					t_game;

void				parse_map(t_game *sv);
void				parse_args(int ac, char *filename, char *save);
void				read_map(const int fd, t_game *sv);
void				what_is_line_content(char *str, t_game *sv, \
										_Bool *map_started_flag);
_Bool				ft_all_isprint(const char *s);
_Bool				ft_all_digits(const char *s);
_Bool				is_valid_map_bit(char c);
void				all_map_bits_are_valid(t_game *sv);
void				check_horizontal_border(const char *str);
void				check_vertical_borders(t_game *sv);
void				check_sign(const char *str, const char *previous, \
										const char *next, t_game *sv);
void				check_map_params(t_game *sv);
void				parse_resolution(char *str, t_conf *map);
void				handle_textures(const char *str, t_conf *map);
void				handle_color(const char *str, t_conf *map);
void				parse_color(const char *str, t_conf *map);
unsigned char		*create_bmp_file_header(int height, int stride);
unsigned char		*create_bmp_info_header(int height, int width);
int					get_pixel(t_data *img, int x, int y);
void				set_sprites_coordinates(t_game *sv);
void				create_map_array(t_game *sv);
void				set_player_vectors(t_game *sv, int j, int i);
void				cast_frame(t_game *sv);
int					render_frame(t_game *sv);
void				init_game(t_game *sv);
int					press_key(int key, t_game *sv);
int					release_key(int key, t_game *sv);
void				check_buttons_state(t_game *sv);
void				move_w(t_game *sv);
void				move_a(t_game *sv);
void				move_s(t_game *sv);
void				move_d(t_game *sv);
void				turn_left(t_game *sv);
void				turn_right(t_game *sv);
void				ft_error_close(int error_code);
int					ft_close(int exit_code, t_game *sv);
void				ft_alloc_check(void *ptr);
int					create_trgb(unsigned int t, unsigned int r, \
								unsigned int g, unsigned int b);
int					add_shade(double distance, int color);
void				my_mlx_pixel_put(t_game *sv, int x, int y, \
											unsigned int color);
void				draw_ceiling_and_floor(t_game *sv);
void				draw_ver_line(t_game *sv, int draw_start, int draw_end);
void				exit_with_err_msg(char *str);
int					save_screenshot(t_game *sv, char *filename);
void				draw_all_txt(t_game *sv);
void				calc_wall_x(t_game *sv);
void				calc_lowest_and_highest_pixels(t_game *sv);
void				calc_dist_projected_on_camera_direction(t_game *sv);
void				calc_ray_pos_and_dir(t_game *sv);
void				calc_step_and_side_dst(t_game *sv);
void				perform_dda(t_game *sv);
void				draw_sprite_verline(t_game *sv, int stripe, int y);
void				loop_through_every_ver_sprite_on_the_screen(t_game *sv);
void				sort_sprites(t_game *sv);
void				count_sprite_dst(t_game *sv);
void				translate_sprite_pos(t_game *sv, int i);
void				transform_sprite_wt_inv_camera_mtrix(t_game *sv);
void				calc_min_max_sprite_pixels(t_game *sv);
void				calc_width_of_the_sprite(t_game *sv);
void				create_texture_imgs(t_game *sv);
void				create_sprite_img(t_game *sv);
void				free_lst_content(void *content);
#endif

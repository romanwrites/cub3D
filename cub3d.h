/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <kukinpower@ya.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 11:03:51 by mkristie          #+#    #+#             */
/*   Updated: 2020/08/05 22:59:13 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <mlx.h>
#include <math.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "libft.h"



/* temp */
#include <stdio.h>
/* temp */



/* errors */
//# define ERR_MALLOC -1
//# define ERR_ARGC_MIN -2
//# define ERR_ARGC_MAX -5
//# define ERR_FILENAME -3
//# define ERR_ARG_SAVE -4
//# define ERR_READ_MAP -6
//# define ERR_MAP_VALIDITY -7
//# define ERR_MAP_R -8
//# define ERR_MAP_BAD_ARG -9
//# define ERR_MAP_T -10
//# define ERR_BAD_MAP -11
//# define ERR_MAP_C -12
//# define ERR_MAP_OPEN -13

# define MOVE_SPEED 0.14
# define ROTATION_SPEED 0.07
# define NINETY_DEGREES 2 * M_PI / 4





enum		e_errors {
	ERR_MALLOC = -15,
	ERR_ARGC_MIN,
	ERR_ARGC_MAX,
	ERR_FILENAME,
	ERR_ARG_SAVE,
	ERR_READ_MAP,
	ERR_MAP_VALIDITY,
	ERR_MAP_R,
	ERR_MAP_BAD_ARG,
	ERR_MAP_T,
	ERR_BAD_MAP,
	ERR_MAP_C,
	ERR_MAP_OPEN,
};

/* keys */
enum		e_keys {
	A,
	S,
	D,
	W = 13,
	ESC = 53,
	LEFT = 123,
	RIGHT = 124,
};



/* structs */

//#include "libft.h"

typedef struct	s_data {
	void				*img;
	char		*addr;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
}				t_data;

typedef struct	s_conf {
	int			res_w;
	int			res_h;
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	char		*s_path;
	int			floor_color[3];
	int			ceiling_color[3];
	char		player_direction;
	char 		*map_array;
	int			map_cols;
	int			map_rows;
	int 		player_num;
	size_t		max_len;
	double 		pos_x;
	double 		pos_y; //x and y start position
	double 		dir_x;
	double 		dir_y; //x and y direction vector
	double		plane_x; //the 2d raycaster version of camera plane
	double		plane_y;
	double		time; //time of current frame
	double		old_time; //time of previous frame
	double move_speed;
	double rotation_speed;
}				t_conf;

typedef struct s_keys {
	_Bool		w;
	_Bool		s;
	_Bool		a;
	_Bool		d;
	_Bool		left;
	_Bool		right;
}				t_keys;


typedef struct s_player {
	double player_x; // player x position
	double player_y; // player y position
	double player_a;
}				t_player;

typedef struct		s_game {
	void			*mlx;
	void			*win;
	t_data 			img;
	t_conf			map;
	t_linked_list	*head;
	t_linked_list	*lst;
	t_linked_list	*tmp;
	t_keys			keys;
	t_player        player;
}					t_game;



/* parse */
void			parse_map(t_game *sv);
//_Bool 		is_valid_map_bit(char c);

_Bool		    parse_args(int ac, char *filename, char *save);
void			read_map(const int fd, t_game *sv);
void			what_is_line_content(const char *str, t_game *sv, _Bool *map_started_flag);

void			ft_put_map_line(char *s); //tmp
_Bool			ft_all_isprint(const char *s);
_Bool			ft_all_digits(const char *s);
_Bool 		    is_valid_map_bit(char c);

void			parse_textures(const char *str, t_conf *map);
_Bool 		    texture_paths_filled(t_conf *map);

void			parse_color(const char *str, t_conf *map);




/* draw_map */
void			draw_map(t_game *sv); // bad algorithm

void			create_map_array(t_game *sv);
void			draw_black_screen(t_game *sv, int win_h, int win_w, int color);


/* hooks and render */
void 			ft_event(int key, t_game *sv);
void			ft_put_map_line(char *s);
void		press_button(int key, t_game *sv);
void		release_button(int key, t_game *sv);
void		check_buttons_state(t_game *sv);

void			casting_frame(t_game *sv);

int		render_frame(t_game *sv);



/* init */

void			init_game(t_game *sv);
void		init_keys(t_game *sv);







/* exit */
void			ft_error_close(int error_code);
int				ft_close(int exit_code, t_game *sv);



/* colors */
unsigned int	create_trgb(unsigned int t, unsigned int r, \
								unsigned int g, unsigned int b);
unsigned int	get_t(unsigned int trgb);
unsigned int	get_r(unsigned int trgb);
unsigned int	get_g(unsigned int trgb);
unsigned int	get_b(unsigned int trgb);
unsigned int	add_shade(double distance, unsigned int color);
unsigned int	get_opposite(unsigned int color);

/* drawings */
void		my_mlx_pixel_put(t_game *sv, int x, int y, unsigned int color);
void		draw_line_bresenham(int x0, int y0, int x1, int y1, unsigned int colour, t_game *sv);

#endif
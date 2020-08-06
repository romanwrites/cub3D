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




/* temp */
#include <stdio.h>
/* temp */

/* keys */
# define W 13
# define S 1
# define A 0
# define D 2
# define LEFT 123
# define RIGHT 124
# define ESC 53

/* errors */
# define ERR_MALLOC -1
# define ERR_ARGC_MIN -2
# define ERR_ARGC_MAX -5
# define ERR_FILENAME -3
# define ERR_ARG_SAVE -4
# define ERR_READ_MAP -6
# define ERR_MAP_VALIDITY -7


/* structs */
//двусвязный
//#ifdef t_list
//#undef s_list
//#endif

#define s_list s_list
#include "libft.h"
#undef s_list
#define s_smthing

typedef struct		s_list
{
	void			*content;
	size_t			len;
	struct s_list	*next;
	struct s_list	*previous;
}					t_list;
//#include "libft.h"

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct  s_game {
	void        *mlx;
	void        *win;
	t_data 		img;
}               t_game;


/* parse */
//_Bool		parse_map(int ac, char *filename, char *save);
_Bool		parse_args(int ac, char *filename, char *save);
_Bool 		is_valid_map_bit(char c);
void			read_map(const int fd, t_list **map, t_game *sv);
void	ft_put_map_line(char *s); //tmp


/* exit */
int				ft_close(int exit_code);
void			ft_error_close(int error_code);


/* colors */
unsigned int		create_trgb(unsigned int t, unsigned int r, \
								unsigned int g, unsigned int b);
unsigned int		get_t(unsigned int trgb);
unsigned int		get_r(unsigned int trgb);
unsigned int		get_g(unsigned int trgb);
unsigned int		get_b(unsigned int trgb);
unsigned int		add_shade(double distance, unsigned int color);
unsigned int		get_opposite(unsigned int color);

/* drawings */
void		my_mlx_pixel_put(t_data *data, int x, int y, unsigned int color);
void		draw_line_bresenham(int x0, int y0, int x1, int y1, unsigned int *colours, t_data *img);


#endif
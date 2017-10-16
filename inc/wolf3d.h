/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmuller <nmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/22 06:24:52 by nmuller           #+#    #+#             */
/*   Updated: 2017/10/16 17:07:19 by nmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include <math.h>
# include <stdlib.h>
# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include "mlx.h"

# define WIN_WIDTH 640
# define WIN_HEIGH 480
# define MAP img->map
# define PLAYER img->player
# define ROT_SPEED 0.2
# define MVM_SPEED 0.2

# define WHITE 0x00ffffff
# define SKY_COLOR 0x00046380
# define GROUND_COLOR 0x00787746
# define RED 0x00ff0000
# define GREEN 0x0000ff00
# define BLUE 0x000000ff
# define COLOR_NORTH WHITE
# define COLOR_SOUTH BLUE
# define COLOR_EAST RED
# define COLOR_WEST GREEN

# define ESC 53
# define A 12
# define Z 13
# define E 14
# define Q 0
# define S 1
# define D 2
# define LEFT 123
# define RIGHT 124

typedef struct	s_map
{
	int		**map;
	int		width;
	int		heigh;
}				t_map;

typedef struct	s_ray
{
	double	posx;
	double	posy;
	double	dirx;
	double	diry;
	double	col;
	int		casex;
	int		casey;
	double	lenx;
	double	leny;
	double	deltax;
	double	deltay;
	int		incx;
	int		incy;
}				t_ray;

typedef struct	s_player
{
	double		posx;
	double		posy;
	double		dirx;
	double		diry;
	double		plx;
	double		ply;
}				t_player;

typedef struct	s_img
{
	void		*ptr;
	char		*buffer;
	int			bpp;
	int			line_s;
	int			e;
	void		*win;
	void		*mlx;
	t_map		*map;
	t_player	*player;
	int			side;
	int			color;
}				t_img;

void			destroy(t_img *img);
int				draw(t_img *img);
void			get_input(const char *file, t_img *img);
int				clean_quit(void *parram);
void			init(t_img *img);
void			destroy(t_img *img);
void			move(int key, t_img *img);
int				key_pressed(int key, void *parram);
void			do_raycasting(t_img *img);
void			put_pixel(t_img *img, int x, int y, int c);

void			disp_map(t_img *img);

#endif

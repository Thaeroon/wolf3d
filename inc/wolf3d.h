/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmuller <nmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/22 06:24:52 by nmuller           #+#    #+#             */
/*   Updated: 2017/10/13 00:03:28 by nmuller          ###   ########.fr       */
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

#include <stdio.h>

# define WIN_WIDTH 480
# define WIN_HEIGH 240
# define MAP img->map
# define PLAYER img->player
# define ROT_SPEED 0.2
# define MVM_SPEED 0.5

# define WHITE 0x00ffffff
# define SKY_COLOR 0x00046380
# define GROUND_COLOR 0x00787746

# define ESC 65307 //53
# define A 97 //12
# define Z 122 //13
# define E 101 //14
# define Q 113 //0
# define S 115 //1
# define D 100 //2
# define LEFT 65361
# define RIGHT 65363

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

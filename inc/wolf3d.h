/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmuller <nmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/22 06:24:52 by nmuller           #+#    #+#             */
/*   Updated: 2017/10/11 16:23:02 by nmuller          ###   ########.fr       */
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

# define WIN_WIDTH 1600
# define WIN_HEIGH 900
# define WHITE 0x00ffffff
# define MAP img->map
# define PLAYER img->player
# define ROT_SPEED 0.2
# define MVM_SPEED 10
# define TILE_S 64

typedef struct	s_point
{
	int		x;
	int		y;
}				t_point;

typedef struct	s_map
{
	int		**map;
	int		width;
	int		heigh;
}				t_map;

typedef struct	s_player
{
	int		posx;
	int		posy;
	int		dirx;
	int		diry;
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
}				t_img;

void			destroy(t_img *img);
int				draw(t_img *img);
void			get_input(const char *file, t_img *img);
int				clean_quit(void *parram);
void			init(t_img *img);
void			destroy(t_img *img);
void			move(int key, t_img *img);
int				key_pressed(int key, void *parram);

void			disp_map(t_img *img);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmuller <nmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 16:06:06 by nmuller           #+#    #+#             */
/*   Updated: 2017/10/16 17:01:06 by nmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		main(int argc, char const *argv[])
{
	t_img	*img;

	(!(img = (t_img*)malloc(sizeof(t_img)))) ? exit(-1) : 0;
	init(img);
	(argc == 2) ? get_input(argv[1], img) : exit(3);
	img->mlx = mlx_init();
	img->win = mlx_new_window(img->mlx, WIN_WIDTH, WIN_HEIGH, "wolf3d");
	img->ptr = mlx_new_image(img->mlx, WIN_WIDTH, WIN_HEIGH);
	img->buffer = mlx_get_data_addr(img->ptr, &(img->bpp), &(img->line_s),
																	&(img->e));
	mlx_hook(img->win, 2, 1L << 0, key_pressed, img);
	mlx_hook(img->win, 17, 0, clean_quit, img);
	mlx_expose_hook(img->win, draw, img);
	mlx_loop(img->mlx);
	destroy(img);
	return (0);
}

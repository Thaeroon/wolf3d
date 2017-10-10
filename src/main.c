/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmuller <nmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 16:06:06 by nmuller           #+#    #+#             */
/*   Updated: 2017/10/10 18:01:52 by nmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	init(t_img *img)
{
	(img->map = (t_map *)malloc(sizeof(t_map))) ? 0 : exit(-1);
}

int		key_pressed(int key, void *parram)
{
	/*t_img	*img;

	img = (t_img *)parram;
	if (key == 53)
		exit(0);
	else if (123 <= key && key <= 126)
		move(key, parram);
	else if (key == 40 && img->it_max > 0)
		img->it_max -= 1;
	else if (key == 34)
		img->it_max += 1;
	else if (key == 32)
		ft_zoom(img, 1);
	else if (key == 38)
		ft_zoom(img, 0);
	else if (key == 31 && img->color < WHITE)
		img->color += 1;
	else if (key == 37 && img->color > 1)
		img->color -= 1;
	else if (key == 12)
		img->mouse_state = (img->mouse_state == 0) ? 1 : 0;
	if ((123 <= key && key <= 126) || 31 == key || key == 34 || key == 37 ||
	key == 40 || key == 12 || key == 32 || key == 38)
		draw(parram);*/
		(void)key;
		(void)parram;
	return (0);
}

int		mouse_pressed(int key, int x, int y, void *parram)
{
	/*t_img	*img;

	img = (t_img*)parram;
	if (key == 5 || key == 3)
		ft_zoom(img, 1);
	else if (key == 4)
		ft_zoom(img, 0);
	if (key == 4 || key == 5 || key == 3)
	{
		img->r = (x * (img->x2 - img->x1)) / WIN_WIDTH + img->x1;
		img->i = (y * (img->y2 - img->y1)) / WIN_HEIGH + img->y1;
		draw(parram);
	}*/
	(void)key;
	(void)x;
	(void)y;
	(void)parram;
	return (0);
}

int		mouse_moved(int x, int y, void *parram)
{
	/*t_img	*img;

	img = (t_img *)parram;
	if (img->mouse_state == 1)
	{
		img->c_r = x * 2.0 / (double)WIN_WIDTH - 1.0;
		img->c_i = y * 2.0 / (double)WIN_HEIGH - 1.0;
		draw(img);
	}*/
	(void)x;
	(void)y;
	(void)parram;
	return (0);
}

int		clean_quit(void *parram)
{
	destroy(parram);
	exit(0);
	return (0);
}

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
	mlx_hook(img->win, 6, 1L << 6, mouse_moved, img);
	mlx_hook(img->win, 17, 0, clean_quit, img);
	mlx_mouse_hook(img->win, mouse_pressed, img);
	mlx_expose_hook(img->win, draw, img);
	mlx_loop(img->mlx);
	destroy(img);
	return (0);
}
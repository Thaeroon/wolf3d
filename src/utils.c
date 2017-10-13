/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmuller <nmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 18:03:10 by nmuller           #+#    #+#             */
/*   Updated: 2017/10/13 16:06:29 by nmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	destroy(t_img *img)
{
	int		y;

	y = -1;
	mlx_destroy_image(img->mlx, img->ptr);
	mlx_destroy_window(img->mlx, img->win);
	if (MAP)
		while (++y < MAP->heigh)
			free(MAP->map[y]);
	free(MAP->map);
	free(MAP);
	free(img->mlx);
	free(PLAYER);
	free(img);
}

int		clean_quit(void *parram)
{
	destroy(parram);
	exit(0);
	return (0);
}

void	init(t_img *img)
{
	(img->map = (t_map *)malloc(sizeof(t_map))) ? 0 : exit(-1);
	(img->player = (t_player *)malloc(sizeof(t_player))) ? 0 : exit(-1);
	PLAYER->dirx = 1;
	PLAYER->diry = 0;
	PLAYER->plx = 0;
	PLAYER->ply = -0.66;
}

void	disp_map(t_img *img)
{
	int		x;
	int		y;

	y = -1;
	while (++y < MAP->heigh)
	{
		x = -1;
		while (++x < MAP->width)
			ft_printf("%i ", MAP->map[y][x]);
		ft_printf("\n");
	}
}
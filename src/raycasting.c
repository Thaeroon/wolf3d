/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmuller <nmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 00:09:23 by nmuller           #+#    #+#             */
/*   Updated: 2017/10/12 00:42:10 by nmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	init_case_len(t_ray *ray)
{
	if (ray->dirx > 0)
	{
		ray->incx = 1;
		ray->lenx = (ray->casex + 1.0 - ray->posx) * ray->deltax;
	}
	else
	{
		ray->incx = -1;
		ray->lenx = (ray->posx - ray->casex) * ray->deltax;
	}
	if (ray->diry > 0)
	{
		ray->incy = 1;
		ray->leny = (ray->casey + 1.0 - ray->posy) * ray->deltay;
	}
	else
	{
		ray->incy = -1;
		ray->leny = (ray->posy - ray->casey) * ray->deltay;
	}
}

void	init_ray(t_img *img, t_ray *ray, int x)
{
	ray->posx = PLAYER->posx;
	ray->posy = PLAYER->posy;
	ray->col = (2 * x / (double)WIN_WIDTH) - 1;
	ray->dirx = PLAYER->dirx + PLAYER->plx * ray->col;
	ray->diry = PLAYER->diry + PLAYER->ply * ray->col;
	ray->deltax = sqrt(1 + (ray->diry * ray->diry) / (ray->dirx * ray->dirx));
	ray->deltay = sqrt(1 + (ray->dirx * ray->dirx) / (ray->diry * ray->diry));
	ray->casex = (int)ray->posx;
	ray->casey = (int)ray->posy;
	init_case_len(ray);
}

void	do_raycasting(t_img *img)
{
	int		x;
	int		y;
	t_ray	*ray;

	(ray = (t_ray *)malloc(sizeof(t_ray))) ? 0 : exit(-1);
	x = -1;
	while (++x < WIN_WIDTH)
	{
		init_ray(img, ray, x);
	}
	free(ray);
	(void)y;
}
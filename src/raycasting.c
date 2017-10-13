/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmuller <nmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 00:09:23 by nmuller           #+#    #+#             */
/*   Updated: 2017/10/13 16:16:53 by nmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	get_ray_len(t_ray *ray)
{
	if (ray->dirx < 0)
	{
		ray->incx = -1;
		ray->lenx = (ray->posx - ray->casex) * ray->deltax;
	}
	else
	{
		ray->incx = 1;
		ray->lenx = (ray->casex + 1.0 - ray->posx) * ray->deltax;
	}
	if (ray->diry < 0)
	{
		ray->incy = -1;
		ray->leny = (ray->posy - ray->casey) * ray->deltay;
	}
	else
	{
		ray->incy = 1;
		ray->leny = (ray->casey + 1.0 - ray->posy) * ray->deltay;
	}
}

void	init_ray(t_img *img, t_ray *ray, int x)
{
	ray->posx = PLAYER->posx;
	ray->posy = PLAYER->posy;
	ray->casex = (int)ray->posx;
	ray->casey = (int)ray->posy;
	ray->col = 2 * x / (double)WIN_WIDTH - 1;
	ray->dirx = PLAYER->dirx + PLAYER->plx * ray->col;
	ray->diry = PLAYER->diry + PLAYER->ply * ray->col;
	ray->deltax = sqrt(1.0 + (ray->diry * ray->diry) / (ray->dirx * ray->dirx));
	ray->deltay = sqrt(1.0 + (ray->dirx * ray->dirx) / (ray->diry * ray->diry));
	get_ray_len(ray);
}

int		get_wall_dist(t_ray *ray, t_img *img)
{
	int		wall_hit;
	int		wall_side_hit;

	wall_hit = 0;
	while (!wall_hit)
	{
		if (ray->lenx < ray->leny)
		{
			ray->lenx += ray->deltax;
			ray->casex += ray->incx;
			wall_side_hit = 0;
			img->color = (ray->incx < 0) ? COLOR_NORTH : COLOR_SOUTH;
		}
		else
		{
			ray->leny += ray->deltay;
			ray->casey += ray->incy;
			wall_side_hit = 1;
			img->color = (ray->incy < 0) ? COLOR_WEST : COLOR_EAST;
		}
		wall_hit = (MAP->map[ray->casey][ray->casex] > 0);
	}
	img->side = wall_side_hit;
	return (wall_side_hit);
}

void	draw_ray(t_img *img, int wall_height, int x)
{
	int		y;
	int		y1;
	int		y2;

	y1 = -wall_height / 2 + WIN_HEIGH / 2;
	y1 = (y1 > 0) ? y1 : 0;
	y2 = wall_height / 2 + WIN_HEIGH / 2;
	y2 = (y2 < WIN_HEIGH) ? y2 : WIN_HEIGH - 1;
	y = -1;
	while (++y < y1)
		put_pixel(img, x, y, SKY_COLOR);
	while (y < y2)
	{
		if (img->color == COLOR_NORTH)
			put_pixel(img, x, y++, COLOR_NORTH);
		else if (img->color == COLOR_SOUTH)
			put_pixel(img, x, y++, COLOR_SOUTH);
		else if (img->color == COLOR_EAST)
			put_pixel(img, x, y++, COLOR_EAST);
		else if (img->color == COLOR_WEST)
			put_pixel(img, x, y++, COLOR_WEST);
	}
	while (y < WIN_HEIGH)
		put_pixel(img, x, y++, GROUND_COLOR);
}

void	do_raycasting(t_img *img)
{
	int		x;
	t_ray	*ray;
	double	corr_dist;

	(ray = (t_ray *)malloc(sizeof(t_ray))) ? 0 : exit(-1);
	x = -1;
	while (++x < WIN_WIDTH)
	{
		init_ray(img, ray, x);
		corr_dist = (get_wall_dist(ray, img) == 0)
			? (ray->casex - ray->posx + (1.0 - ray->incx) / 2.0) / ray->dirx
			: (ray->casey - ray->posy + (1.0 - ray->incy) / 2.0) / ray->diry;
		draw_ray(img, (WIN_HEIGH / corr_dist), x);
	}
	free(ray);
}

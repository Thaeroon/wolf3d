/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmuller <nmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 00:09:23 by nmuller           #+#    #+#             */
/*   Updated: 2017/10/12 23:13:51 by nmuller          ###   ########.fr       */
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
		}
		else
		{
			ray->leny += ray->deltay;
			ray->casey += ray->incy;
			wall_side_hit = 1;
		}
		wall_hit = (MAP->map[ray->casey][ray->casex] > 0);
	}
	img->side = wall_side_hit;
	return (wall_side_hit);
}

void	draw_ray(t_img *img, double corr_dist, int x)
{
	int		y;
	int		y1;
	int		y2;
	int		wall_height;

	wall_height = (int)(WIN_HEIGH / corr_dist);
	y1 = -wall_height / 2 + WIN_HEIGH / 2;
	y1 = (y1 > 0) ? y1 : 0;
	y2 = wall_height / 2 + WIN_HEIGH / 2;
	y2 = (y2 < WIN_HEIGH) ? y2 : WIN_HEIGH - 1;

	y = -1;
	while (++y < y1)
		put_pixel(img, x, y, SKY_COLOR);
	while (y < y2)
	{
		if (img->side)
			put_pixel(img, x, y++, WHITE);
		else
			put_pixel(img, x, y++, WHITE / 2);
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
		draw_ray(img, corr_dist, x);
	}
	free(ray);
}

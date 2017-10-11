/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmuller <nmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 20:18:29 by nmuller           #+#    #+#             */
/*   Updated: 2017/10/12 00:41:26 by nmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	put_pixel(t_img *img, int x, int y, int c)
{
	char	*ptr_color;

	if (img == NULL || x < 0 || y < 0 || x >= WIN_WIDTH || y >= WIN_HEIGH)
		return ;
	ptr_color = img->buffer + (x * (img->bpp >> 3) + y * img->line_s);
	ptr_color[0] = (c >> 0x00) & 0xFF;
	ptr_color[1] = (c >> 0x08) & 0xFF;
	ptr_color[2] = (c >> 0x10) & 0xFF;
}

void	draw_line(t_img *img, t_point p0, t_point p1, int err2)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;

	if (img == NULL
		|| p0.x < 0 || p0.y < 0 || p1.x >= WIN_WIDTH || p1.y >= WIN_HEIGH)
		return ;
	dx = abs(p1.x - p0.x);
	sx = p0.x < p1.x ? 1 : -1;
	dy = abs(p1.y - p0.y);
	sy = p0.y < p1.y ? 1 : -1;
	err = ((dx > dy) ? dx : -dy) / 2;
	while (p0.x != p1.x || p0.y != p1.y)
	{
		put_pixel(img, p0.x, p0.y, WHITE);
		err2 = err;
		if (err2 > -dx)
			((err -= dy) || 1) && (p0.x += sx);
		if (err2 < dy)
			((err += dx) || 1) && (p0.y += sy);
	}
}

int		draw(t_img *img)
{
	ft_bzero(img->buffer, WIN_WIDTH * WIN_HEIGH * (img->bpp >> 3));
	printf("posx=%f, posy=%f\n", PLAYER->posx, PLAYER->posy);
	printf("dirx=%f, diry=%f\n\n", PLAYER->dirx, PLAYER->diry);
	do_raycasting(img);
	mlx_put_image_to_window(img->mlx, img->win, img->ptr, 0, 0);
	return (0);
}
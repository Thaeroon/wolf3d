/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmuller <nmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 20:18:29 by nmuller           #+#    #+#             */
/*   Updated: 2017/10/13 02:45:05 by nmuller          ###   ########.fr       */
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

int		draw(t_img *img)
{
	ft_bzero(img->buffer, WIN_WIDTH * WIN_HEIGH * (img->bpp >> 3));
	do_raycasting(img);
	mlx_put_image_to_window(img->mlx, img->win, img->ptr, 0, 0);
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmuller <nmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 17:08:33 by nmuller           #+#    #+#             */
/*   Updated: 2017/10/13 03:34:37 by nmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <fcntl.h>

void	get_map_size(const char *file, t_img *img)
{
	char	*line;
	int		ret;
	int		fd;
	int		tmp_width;

	((fd = open(file, O_RDONLY)) == -1) ? exit(-1) : 0;
	MAP->heigh = 0;
	MAP->width = 0;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		MAP->heigh++;
		tmp_width = 0;
		while (line[tmp_width])
			++tmp_width;
		MAP->width = (tmp_width > MAP->width) ? tmp_width : MAP->width;
	}
	MAP->width += 2;
	MAP->heigh += 2;
	free(line);
	close(fd);
	(ret < 0) ? exit(2) : 0;
}

void	populate_map(const char *file, t_img *img)
{
	char	*line;
	int		fd;
	int		x;
	int		y;

	((fd = open(file, O_RDONLY)) == -1) ? exit(-1) : 0;
	y = 0;
	x = -1;
	while (++x < MAP->width)
		MAP->map[0][x] = 9;
	while (get_next_line(fd, &line) > 0)
	{
		x = -1;
		MAP->map[y + 1][0] = 9;
		while (line[++x])
			MAP->map[y + 1][x + 1] = (line[x] - '0' > 0) ? line[x] - '0' : 0;
		while (x < MAP->width)
			++x;
		MAP->map[y + 1][x - 1] = 9;
		++y;
	}
	x = -1;
	while (++x < MAP->width)
		MAP->map[y + 1][x] = 9;
	free(line);
	close(fd);
}

int		place_player(t_img *img)
{
	int		x;
	int		y;

	y = -1;
	while (++y < MAP->heigh)
	{
		x = -1;
		while (++x < MAP->width)
		{
			if (MAP->map[y][x] == 0)
			{
				PLAYER->posx = x + 0.5;
				PLAYER->posy = y + 0.5;
				return (1);
			}
		}
	}
	return (0);
}

void	get_input(const char *file, t_img *img)
{
	int		i;

	i = -1;
	get_map_size(file, img);
	(MAP->map = (int **)malloc(sizeof(int *) * MAP->heigh)) ? 0 : exit(-1);
	while (++i < MAP->heigh)
		(MAP->map[i] = (int *)malloc(sizeof(int ) * MAP->width)) ? 0 : exit(-1);
	populate_map(file, img);

	disp_map(img);

	(place_player(img)) ? 0 : exit(1);
}
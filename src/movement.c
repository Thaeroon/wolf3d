/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmuller <nmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 13:24:56 by nmuller           #+#    #+#             */
/*   Updated: 2017/10/11 16:36:23 by nmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	move(int key, t_img *img)
{
	if (key == 13)
	{
		PLAYER->posx += PLAYER->dirx * MVM_SPEED;
		PLAYER->posy += PLAYER->diry * MVM_SPEED;
	}
	else if (key == 1)
	{
		PLAYER->posx -= PLAYER->dirx * MVM_SPEED;
		PLAYER->posy -= PLAYER->diry * MVM_SPEED;
	}
	else if (key == 12)
	{
		PLAYER->posx = PLAYER->diry * MVM_SPEED;
		PLAYER->posy = PLAYER->dirx * MVM_SPEED;
	}
	else if (key == 14)
	{
		PLAYER->posx = PLAYER->diry * MVM_SPEED;
		PLAYER->posy = PLAYER->dirx * MVM_SPEED;
	}
}

void	rotation(int key, t_img *img, int rot_speed)
{
	int		old_dirx;
	int		old_posx;

	old_dirx = PLAYER->dirx;
	PLAYER->dirx =
			PLAYER->dirx * cos(rot_speed) - PLAYER->diry * sin(rot_speed);
	PLAYER->diry = old_dirx * sin(rot_speed) + PLAYER->diry * cos(rot_speed);
	old_posx = PLAYER->posx;
	PLAYER->posx =
			PLAYER->posx * cos(rot_speed) - PLAYER->posy * sin(rot_speed);
	PLAYER->posy = old_posx * sin(rot_speed) + PLAYER->posy * cos(rot_speed);
}

int		key_pressed(int key, void *parram)
{
	t_img	*img;

	img = (t_img *)parram;
	if (key == 53)
		clean_quit(parram);
	else if (key == 0)
		rotation(key, img, -ROT_SPEED);
	else if (key == 2)
	rotation(key, img, ROT_SPEED);
	else if (key == 1 || (key >= 12 && key <=14))
		move(key, parram);
	if ((0 <= key && key <= 2) || (12 <= key && key <= 14))
		draw(parram);
	return (0);
}
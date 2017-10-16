/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmuller <nmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 13:24:56 by nmuller           #+#    #+#             */
/*   Updated: 2017/10/16 16:22:27 by nmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	move_for_back(int key, t_img *img)
{
	if (key == Z)
	{
		(!MAP->map[(int)PLAYER->posy][(int)(PLAYER->posx + PLAYER->dirx
			* MVM_SPEED)]) ? PLAYER->posx += PLAYER->dirx * MVM_SPEED : 0;
		(!MAP->map[(int)(PLAYER->posy + PLAYER->diry * MVM_SPEED)]
		[(int)PLAYER->posx]) ? PLAYER->posy += PLAYER->diry * MVM_SPEED : 0;
	}
	else if (key == S)
	{
		(!MAP->map[(int)PLAYER->posy][(int)(PLAYER->posx - PLAYER->dirx
			* MVM_SPEED)]) ? PLAYER->posx -= PLAYER->dirx * MVM_SPEED : 0;
		(!MAP->map[(int)(PLAYER->posy - PLAYER->diry * MVM_SPEED)]
		[(int)PLAYER->posx]) ? PLAYER->posy -= PLAYER->diry * MVM_SPEED : 0;
	}
}

void	move_side(int key, t_img *img)
{
	if (key == Q)
	{
		(!MAP->map[(int)PLAYER->posy][(int)(PLAYER->posx - PLAYER->plx
			* MVM_SPEED)]) ? PLAYER->posx -= PLAYER->plx * MVM_SPEED : 0;
		(!MAP->map[(int)(PLAYER->posy - PLAYER->ply * MVM_SPEED)]
		[(int)PLAYER->posx]) ? PLAYER->posy -= PLAYER->ply * MVM_SPEED : 0;
	}
	else if (key == D)
	{
		(!MAP->map[(int)PLAYER->posy][(int)(PLAYER->posx + PLAYER->plx
			* MVM_SPEED)]) ? PLAYER->posx += PLAYER->plx * MVM_SPEED : 0;
		(!MAP->map[(int)(PLAYER->posy + PLAYER->ply * MVM_SPEED)]
		[(int)PLAYER->posx]) ? PLAYER->posy += PLAYER->ply * MVM_SPEED : 0;
	}
}

void	rotation(t_img *img, double rot_speed)
{
	double		old_dirx;
	double		old_plx;

	old_dirx = PLAYER->dirx;
	PLAYER->dirx = PLAYER->dirx * cos(rot_speed)
	- PLAYER->diry * sin(rot_speed);
	PLAYER->diry = old_dirx * sin(rot_speed) + PLAYER->diry * cos(rot_speed);
	old_plx = PLAYER->plx;
	PLAYER->plx = PLAYER->plx * cos(rot_speed) - PLAYER->ply * sin(rot_speed);
	PLAYER->ply = old_plx * sin(rot_speed) + PLAYER->ply * cos(rot_speed);
}

int		key_pressed(int key, void *parram)
{
	t_img	*img;

	img = (t_img *)parram;
	if (key == ESC)
		clean_quit(parram);
	else if (key == A || key == LEFT)
		rotation(img, ROT_SPEED);
	else if (key == E || key == RIGHT)
		rotation(img, -ROT_SPEED);
	else if (key == S || key == Z)
		move_for_back(key, parram);
	else if (key == Q || key == D)
		move_side(key, parram);
	if (key == Q || key == S || key == D || key == A || key == Z || key == E
								|| key == LEFT || key == RIGHT)
		draw(parram);
	return (0);
}

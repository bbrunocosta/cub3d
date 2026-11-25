/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosta-b <bcosta-b@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 09:44:43 by bcosta-b          #+#    #+#             */
/*   Updated: 2026/11/25 09:44:43 by bcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_texture_pixel(t_texture *tex, int x, int y)
{
	char	*pixel;

	pixel = tex->addr + y * tex->line_length
		+ x * (tex->bits_per_pixel / 8);
	return (*(unsigned int *)pixel);
}

void	init_texdraw(t_texdraw *draw, int height, t_texture *tex)
{
	draw->height = height;
	draw->start = -height / 2 + WIN_HEIGHT / 2;
	draw->end = height / 2 + WIN_HEIGHT / 2;
	draw->step = (double)tex->height / height;
	draw->tex_pos = 0;
	if (draw->start < 0)
	{
		draw->tex_pos += -draw->start * draw->step;
		draw->start = 0;
	}
	if (draw->end >= WIN_HEIGHT)
		draw->end = WIN_HEIGHT - 1;
}

void	draw_textured_column(t_game *game, int x,
		t_texture *tex, t_texdraw *draw)
{
	int	color;

	draw->y = draw->start;
	while (draw->y <= draw->end)
	{
		draw->tex_y = (int)draw->tex_pos;
		if (draw->tex_y >= 0 && draw->tex_y < tex->height)
		{
			color = get_texture_pixel(tex, draw->tex_x,
					draw->tex_y);
			put_pixel(&game->img, x, draw->y, color);
		}
		draw->tex_pos += draw->step;
		draw->y++;
	}
}

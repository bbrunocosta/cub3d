/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosta-b <bcosta-b@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 09:44:43 by bcosta-b          #+#    #+#             */
/*   Updated: 2026/11/25 09:44:43 by bcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

int	load_texture(t_game *game, int id, char *path)
{
	t_texture	*tex;

	tex = &game->textures[id];
	tex->ptr = mlx_xpm_file_to_image(game->mlx, path,
			&tex->width, &tex->height);
	if (!tex->ptr)
		return (1);
	tex->addr = mlx_get_data_addr(tex->ptr,
			&tex->bits_per_pixel,
			&tex->line_length, &tex->endian);
	if (!tex->addr)
		return (1);
	return (0);
}

int	init_textures(t_game *game)
{
	if (load_texture(game, TEX_NO, game->config.no))
		return (1);
	if (load_texture(game, TEX_SO, game->config.so))
		return (1);
	if (load_texture(game, TEX_WE, game->config.we))
		return (1);
	if (load_texture(game, TEX_EA, game->config.ea))
		return (1);
	return (0);
}

double	get_wall_x(t_ray *ray, t_player *player)
{
	double	wall_x;

	if (ray->side == 0)
		wall_x = player->pos.y + ray->perp_dist * ray->dir.y;
	else
		wall_x = player->pos.x + ray->perp_dist * ray->dir.x;
	return (wall_x - floor(wall_x));
}

int	get_texture_x(t_ray *ray, t_texture *tex, double wall_x)
{
	int	tex_x;

	tex_x = (int)(wall_x * tex->width);
	if ((ray->side == 0 && ray->dir.x > 0)
		|| (ray->side == 1 && ray->dir.y < 0))
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
}

int	get_texture_id(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->dir.x > 0)
			return (TEX_EA);
		return (TEX_WE);
	}
	if (ray->dir.y > 0)
		return (TEX_SO);
	return (TEX_NO);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosta-b <bcosta-b@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 09:44:43 by bcosta-b          #+#    #+#             */
/*   Updated: 2026/11/25 09:44:43 by bcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

static void	dda_step(t_ray *ray)
{
	if (ray->side_dist.x < ray->side_dist.y)
	{
		ray->side_dist.x += ray->delta_dist.x;
		ray->map.x += ray->step.x;
		ray->side = 0;
	}
	else
	{
		ray->side_dist.y += ray->delta_dist.y;
		ray->map.y += ray->step.y;
		ray->side = 1;
	}
}

static void	perform_dda(t_ray *ray, t_game *game)
{
	ray->hit = 0;
	while (!ray->hit)
	{
		dda_step(ray);
		if (game->map[ray->map.y][ray->map.x] == '1')
			ray->hit = 1;
	}
}

static double	calculate_wall_dist(t_ray *ray)
{
	if (ray->side == 0)
		return (ray->side_dist.x - ray->delta_dist.x);
	return (ray->side_dist.y - ray->delta_dist.y);
}

static void	draw_wall(t_ray *ray, t_game *game, int x)
{
	t_texture	*tex;
	t_texdraw	draw;
	int			height;
	double		wall_x;

	ray->perp_dist = calculate_wall_dist(ray);
	height = (int)(WIN_HEIGHT / fmax(ray->perp_dist, 0.0001));
	if (height < 1)
		height = 1;
	tex = &game->textures[get_texture_id(ray)];
	wall_x = get_wall_x(ray, &game->player);
	init_texdraw(&draw, height, tex);
	draw.tex_x = get_texture_x(ray, tex, wall_x);
	draw_textured_column(game, x, tex, &draw);
}

void	cast_rays(t_game *game)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		init_ray(&ray, &game->player, x);
		perform_dda(&ray, game);
		draw_wall(&ray, game, x);
		x++;
	}
}

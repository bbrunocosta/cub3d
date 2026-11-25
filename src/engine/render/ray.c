/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosta-b <bcosta-b@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 09:44:43 by bcosta-b          #+#    #+#             */
/*   Updated: 2026/11/25 09:44:43 by bcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

static t_vec2	calculate_delta_dist(t_vec2 dir)
{
	t_vec2	delta;

	delta.x = 1e30;
	delta.y = 1e30;
	if (dir.x != 0)
		delta.x = fabs(1.0 / dir.x);
	if (dir.y != 0)
		delta.y = fabs(1.0 / dir.y);
	return (delta);
}

static t_vec2i	calculate_step(t_vec2 dir)
{
	t_vec2i	step;

	step.x = 1;
	step.y = 1;
	if (dir.x < 0)
		step.x = -1;
	if (dir.y < 0)
		step.y = -1;
	return (step);
}

static t_vec2	calculate_side_dist(t_ray *ray, t_vec2 pos)
{
	t_vec2	dist;

	if (ray->step.x < 0)
		dist.x = (pos.x - ray->map.x) * ray->delta_dist.x;
	else
		dist.x = (ray->map.x + 1.0 - pos.x) * ray->delta_dist.x;
	if (ray->step.y < 0)
		dist.y = (pos.y - ray->map.y) * ray->delta_dist.y;
	else
		dist.y = (ray->map.y + 1.0 - pos.y) * ray->delta_dist.y;
	return (dist);
}

void	init_ray(t_ray *ray, t_player *player, int x)
{
	ray->camera_x = 2.0 * x / WIN_WIDTH - 1.0;
	ray->dir.x = player->dir.x + player->plane.x * ray->camera_x;
	ray->dir.y = player->dir.y + player->plane.y * ray->camera_x;
	ray->map.x = (int)player->pos.x;
	ray->map.y = (int)player->pos.y;
	ray->delta_dist = calculate_delta_dist(ray->dir);
	ray->step = calculate_step(ray->dir);
	ray->side_dist = calculate_side_dist(ray, player->pos);
}

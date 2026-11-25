/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosta-b <bcosta-b@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 09:44:43 by bcosta-b          #+#    #+#             */
/*   Updated: 2026/11/25 09:44:43 by bcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

static t_vec2	rotate_vector(t_vec2 vec, double angle)
{
	t_vec2	result;

	result.x = vec.x * cos(angle) - vec.y * sin(angle);
	result.y = vec.x * sin(angle) + vec.y * cos(angle);
	return (result);
}

static void	rotate_player(t_player *player, double angle)
{
	player->dir = rotate_vector(player->dir, angle);
	player->plane = rotate_vector(player->plane, angle);
}

static void	move_player(t_game *game, t_vec2 dir, double speed)
{
	t_vec2	next;

	next.x = game->player.pos.x + dir.x * speed;
	next.y = game->player.pos.y + dir.y * speed;
	if (game->map[(int)game->player.pos.y][(int)next.x] == '0')
		game->player.pos.x = next.x;
	if (game->map[(int)next.y][(int)game->player.pos.x] == '0')
		game->player.pos.y = next.y;
}

void	update_movement(t_game *game)
{
	if (game->keys.w)
		move_player(game, game->player.dir, MOVE_SPEED);
	if (game->keys.s)
		move_player(game, game->player.dir, -MOVE_SPEED);
	if (game->keys.a)
		move_player(game, game->player.plane, -MOVE_SPEED);
	if (game->keys.d)
		move_player(game, game->player.plane, MOVE_SPEED);
}

void	update_rotation(t_game *game)
{
	if (game->keys.left)
		rotate_player(&game->player, -ROT_SPEED);
	if (game->keys.right)
		rotate_player(&game->player, ROT_SPEED);
}

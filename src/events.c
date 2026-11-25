/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosta-b <bcosta-b@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 09:44:43 by bcosta-b          #+#    #+#             */
/*   Updated: 2026/11/25 09:44:43 by bcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_key_state(t_keys *keys, int keycode, int state)
{
	if (keycode == KEY_W)
		keys->w = state;
	else if (keycode == KEY_A)
		keys->a = state;
	else if (keycode == KEY_S)
		keys->s = state;
	else if (keycode == KEY_D)
		keys->d = state;
	else if (keycode == KEY_LEFT)
		keys->left = state;
	else if (keycode == KEY_RIGHT)
		keys->right = state;
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		close_game(game);
	set_key_state(&game->keys, keycode, 1);
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	set_key_state(&game->keys, keycode, 0);
	return (0);
}

int	clear_keys(t_game *game)
{
	game->keys.w = 0;
	game->keys.a = 0;
	game->keys.s = 0;
	game->keys.d = 0;
	game->keys.left = 0;
	game->keys.right = 0;
	return (0);
}

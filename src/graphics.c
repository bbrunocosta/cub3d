/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosta-b <bcosta-b@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 09:44:43 by bcosta-b          #+#    #+#             */
/*   Updated: 2026/11/25 09:44:43 by bcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <sys/time.h>

static int	game_loop(t_game *game)
{
	struct timeval	now;
	long long		elapsed;

	if (gettimeofday(&now, NULL))
		return (0);
	elapsed = (now.tv_sec - game->last_frame.tv_sec) * 1000000LL
		+ now.tv_usec - game->last_frame.tv_usec;
	if (elapsed >= 0 && elapsed < 16000)
		return (0);
	game->last_frame = now;
	update_rotation(game);
	update_movement(game);
	render_frame(game);
	return (0);
}

static int	init_graphics(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (1);
	game->win = mlx_new_window(game->mlx,
			WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!game->win)
		return (1);
	game->img.ptr = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game->img.ptr)
		return (1);
	game->img.addr = mlx_get_data_addr(game->img.ptr,
			&game->img.bits_per_pixel,
			&game->img.line_length, &game->img.endian);
	if (!game->img.addr)
		return (1);
	return (0);
}

int	graphics_error(t_game *game)
{
	if (init_graphics(game))
		return (printf("Error\nMLX initialization failed\n"), 1);
	if (init_textures(game))
		return (printf("Error\nFailed to load wall textures\n"), 1);
	return (0);
}

void	run_game(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	mlx_hook(game->win, 10, 1L << 21, clear_keys, game);
	mlx_hook(game->win, 17, 0, close_game, game);
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_loop(game->mlx);
}

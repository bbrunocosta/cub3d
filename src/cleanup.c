/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosta-b <bcosta-b@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 09:44:43 by bcosta-b          #+#    #+#             */
/*   Updated: 2026/11/25 09:44:43 by bcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_scene(t_game *game)
{
	int	y;

	y = 0;
	while (y < game->rows)
		free(game->map[y++]);
	free(game->map);
	free(game->config.no);
	free(game->config.so);
	free(game->config.we);
	free(game->config.ea);
}

void	cleanup(t_game *game)
{
	int	i;

	if (game->mlx)
	{
		if (game->win)
			mlx_destroy_window(game->mlx, game->win);
		if (game->img.ptr)
			mlx_destroy_image(game->mlx, game->img.ptr);
		i = 0;
		while (i < 4)
		{
			if (game->textures[i].ptr)
				mlx_destroy_image(game->mlx, game->textures[i].ptr);
			i++;
		}
	}
	free_scene(game);
	destroy_mlx(game->mlx);
}

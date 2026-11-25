/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosta-b <bcosta-b@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 10:15:27 by bcosta-b          #+#    #+#             */
/*   Updated: 2026/11/25 10:15:27 by bcosta-b         ###   ########.fr       */
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

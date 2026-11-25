/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_context_mac.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosta-b <bcosta-b@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 09:44:43 by bcosta-b          #+#    #+#             */
/*   Updated: 2026/11/25 09:44:43 by bcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	destroy_mlx(void *mlx)
{
	(void)mlx;
}

int	close_game(t_game *game)
{
	cleanup(game);
	exit(0);
	return (0);
}

void	wait_for_frame(void *mlx)
{
	mlx_do_sync(mlx);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosta-b <bcosta-b@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 09:44:43 by bcosta-b          #+#    #+#             */
/*   Updated: 2026/11/25 09:44:43 by bcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_game(t_game *game)
{
	unsigned char	*bytes;
	size_t			i;

	bytes = (unsigned char *)game;
	i = 0;
	while (i < sizeof(*game))
		bytes[i++] = 0;
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (printf("Error\nUsage: ./cub3D map.cub\n"), 1);
	init_game(&game);
	if (parse_cub(argv[1], &game))
	{
		free_scene(&game);
		return (printf("Error\nInvalid .cub file\n"), 1);
	}
	if (graphics_error(&game))
	{
		cleanup(&game);
		return (1);
	}
	run_game(&game);
	cleanup(&game);
	return (0);
}

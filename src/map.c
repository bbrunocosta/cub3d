/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosta-b <bcosta-b@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 09:44:43 by bcosta-b          #+#    #+#             */
/*   Updated: 2026/11/25 09:44:43 by bcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <limits.h>

static int	grow_map(t_game *game)
{
	char	**map;
	int		i;
	int		capacity;

	if (game->capacity > INT_MAX / 2)
		return (1);
	capacity = 16;
	if (game->capacity)
		capacity = game->capacity * 2;
	map = malloc(sizeof(*map) * capacity);
	if (!map)
		return (1);
	i = -1;
	while (++i < game->rows)
		map[i] = game->map[i];
	free(game->map);
	game->map = map;
	game->capacity = capacity;
	return (0);
}

int	append_row(t_game *game, char *line)
{
	char	*row;

	if (game->rows == game->capacity && grow_map(game))
		return (1);
	row = ft_strtrim(line, "");
	if (!row)
		return (1);
	game->map[game->rows++] = row;
	return (0);
}

static void	set_spawn(t_player *player, int x, int y, char facing)
{
	player->pos.x = x + 0.5;
	player->pos.y = y + 0.5;
	player->dir.x = (facing == 'E') - (facing == 'W');
	player->dir.y = (facing == 'S') - (facing == 'N');
	player->plane.x = -0.66 * player->dir.y;
	player->plane.y = 0.66 * player->dir.x;
}

static int	validate_row(t_game *game, int y, size_t above, size_t below)
{
	char	*row;
	int		x;

	row = game->map[y];
	x = -1;
	while (row[++x])
	{
		if (row[x] == 'N' || row[x] == 'S' || row[x] == 'E' || row[x] == 'W')
		{
			if (game->player.pos.x != 0)
				return (1);
			set_spawn(&game->player, x, y, row[x]);
			row[x] = '0';
		}
		if (row[x] != '0' && row[x] != '1' && row[x] != ' ')
			return (1);
		if (row[x] == '0' && (x == 0 || row[x - 1] == ' '
				|| !row[x + 1] || row[x + 1] == ' '
				|| (size_t)x >= above || game->map[y - 1][x] == ' '
			|| (size_t)x >= below || game->map[y + 1][x] == ' '))
			return (1);
	}
	return (0);
}

int	validate_map(t_game *game)
{
	int		y;
	size_t	above;
	size_t	below;

	y = 0;
	above = 0;
	while (y < game->rows)
	{
		below = 0;
		if (y + 1 < game->rows)
			below = ft_strlen(game->map[y + 1]);
		if (validate_row(game, y, above, below))
			return (1);
		above = ft_strlen(game->map[y]);
		y++;
	}
	return (game->player.pos.x == 0);
}

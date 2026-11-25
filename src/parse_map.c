/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosta-b <bcosta-b@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 09:44:43 by bcosta-b          #+#    #+#             */
/*   Updated: 2026/11/25 09:44:43 by bcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <fcntl.h>
#include <unistd.h>

static int	config_complete(t_config *config)
{
	return (config->no && config->so && config->we && config->ea
		&& config->floor_color >= 0 && config->ceiling_color >= 0);
}

static int	parse_line(char *line, t_game *game)
{
	char	*value;

	value = line;
	while (is_space(*value))
		value++;
	if (game->rows || *value == '1' || *value == '0')
	{
		if (!config_complete(&game->config))
			return (1);
		return (append_row(game, line));
	}
	if (!*value)
		return (0);
	return (parse_config(value, &game->config));
}

static int	read_scene(t_reader *reader, t_game *game)
{
	char	*line;
	int		status;
	int		map_ended;

	map_ended = 0;
	status = get_next_line(reader, &line);
	while (status > 0)
	{
		if (!*line && game->rows)
			map_ended = 1;
		else if (map_ended || parse_line(line, game))
		{
			free(line);
			return (1);
		}
		free(line);
		status = get_next_line(reader, &line);
	}
	return (status < 0);
}

int	parse_cub(char *path, t_game *game)
{
	t_reader	reader;
	size_t		len;
	int			status;

	len = ft_strlen(path);
	if (len < 4 || ft_strncmp(path + len - 4, ".cub", 4))
		return (1);
	reader.pos = 0;
	reader.end = 0;
	reader.fd = open(path, O_RDONLY);
	if (reader.fd < 0)
		return (1);
	game->config.floor_color = -1;
	game->config.ceiling_color = -1;
	status = read_scene(&reader, game);
	close(reader.fd);
	if (status || !config_complete(&game->config))
		return (1);
	return (validate_map(game));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosta-b <bcosta-b@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 09:44:43 by bcosta-b          #+#    #+#             */
/*   Updated: 2026/11/25 09:44:43 by bcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	parse_texture(char *value, char **dest)
{
	char	*path;

	if (*dest || !is_space(*value))
		return (1);
	path = ft_strtrim(value, " \t");
	if (!path || !*path)
	{
		free(path);
		return (1);
	}
	*dest = path;
	return (0);
}

static int	parse_channel(char **value)
{
	int	channel;

	while (is_space(**value))
		(*value)++;
	if (**value < '0' || **value > '9')
		return (-1);
	channel = 0;
	while (**value >= '0' && **value <= '9')
	{
		channel = channel * 10 + *(*value)++ - '0';
		if (channel > 255)
			return (-1);
	}
	while (is_space(**value))
		(*value)++;
	return (channel);
}

static int	parse_color(char *value, int *dest)
{
	int	r;
	int	g;
	int	b;

	if (*dest >= 0 || !is_space(*value))
		return (1);
	r = parse_channel(&value);
	if (r < 0 || *value++ != ',')
		return (1);
	g = parse_channel(&value);
	if (g < 0 || *value++ != ',')
		return (1);
	b = parse_channel(&value);
	if (b < 0 || *value)
		return (1);
	*dest = (r << 16) | (g << 8) | b;
	return (0);
}

int	parse_config(char *line, t_config *config)
{
	if (!ft_strncmp(line, "NO", 2))
		return (parse_texture(line + 2, &config->no));
	if (!ft_strncmp(line, "SO", 2))
		return (parse_texture(line + 2, &config->so));
	if (!ft_strncmp(line, "WE", 2))
		return (parse_texture(line + 2, &config->we));
	if (!ft_strncmp(line, "EA", 2))
		return (parse_texture(line + 2, &config->ea));
	if (*line == 'F')
		return (parse_color(line + 1, &config->floor_color));
	if (*line == 'C')
		return (parse_color(line + 1, &config->ceiling_color));
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosta-b <bcosta-b@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 09:44:43 by bcosta-b          #+#    #+#             */
/*   Updated: 2026/11/25 09:44:43 by bcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>

# define WIN_WIDTH	800
# define WIN_HEIGHT	600

# ifdef __linux__
#  define KEY_ESC 65307
#  define KEY_LEFT 65361
#  define KEY_RIGHT 65363
#  define KEY_A 97
#  define KEY_S 115
#  define KEY_D 100
#  define KEY_W 119
# else
#  define KEY_ESC 53
#  define KEY_LEFT 123
#  define KEY_RIGHT 124
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define KEY_W 13
# endif
# define MOVE_SPEED	0.10
# define ROT_SPEED	0.10

# define TEX_NO			0
# define TEX_SO			1
# define TEX_WE			2
# define TEX_EA			3

typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
}	t_keys;

typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_config
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		floor_color;
	int		ceiling_color;
}	t_config;

typedef struct s_vec2i
{
	int	x;
	int	y;
}	t_vec2i;

typedef struct s_vec2
{
	double	x;
	double	y;
}	t_vec2;

typedef struct s_player
{
	t_vec2	pos;
	t_vec2	dir;
	t_vec2	plane;
}	t_player;

typedef struct s_texture
{
	void	*ptr;
	char	*addr;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_texture;

typedef struct s_texdraw
{
	int		height;
	int		start;
	int		end;
	int		tex_x;
	int		tex_y;
	int		y;
	double	step;
	double	tex_pos;
}	t_texdraw;

typedef struct s_game
{
	void			*mlx;
	void			*win;
	t_img			img;
	t_player		player;
	t_texture		textures[4];
	t_keys			keys;
	t_config		config;
	char			**map;
	int				rows;
	int				capacity;
	struct timeval	last_frame;
}	t_game;

typedef struct s_ray
{
	t_vec2	dir;
	t_vec2	delta_dist;
	t_vec2	side_dist;
	t_vec2i	map;
	t_vec2i	step;
	double	camera_x;
	double	perp_dist;
	int		side;
	int		hit;
}	t_ray;

typedef struct s_reader
{
	char	buffer[4096];
	int		fd;
	int		pos;
	int		end;
}	t_reader;

int		close_game(t_game *game);
void	cleanup(t_game *game);
void	destroy_mlx(void *mlx);
void	wait_for_frame(void *mlx);
void	free_scene(t_game *game);
int		graphics_error(t_game *game);
void	run_game(t_game *game);
void	put_pixel(t_img *img, int x, int y, int color);
void	render_frame(t_game *game);
void	cast_rays(t_game *game);
void	init_ray(t_ray *ray, t_player *player, int x);
void	update_rotation(t_game *game);
void	update_movement(t_game *game);
int		clear_keys(t_game *game);
int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);
int		init_textures(t_game *game);
int		get_texture_x(t_ray *ray, t_texture *tex, double wall_x);
void	draw_textured_column(t_game *game, int x,
			t_texture *tex, t_texdraw *draw);
void	init_texdraw(t_texdraw *draw, int height, t_texture *tex);
double	get_wall_x(t_ray *ray, t_player *player);
int		get_texture_id(t_ray *ray);
int		get_next_line(t_reader *reader, char **line);
int		parse_cub(char *path, t_game *game);
int		parse_config(char *line, t_config *config);
int		append_row(t_game *game, char *line);
int		validate_map(t_game *game);
int		is_space(char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *str);
char	*ft_strtrim(const char *s, const char *set);

#endif

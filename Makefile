NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = src/main.c src/graphics.c src/cleanup.c \
       src/events.c src/movement.c src/render.c src/cast.c src/ray.c \
       src/textures.c src/texture_draw.c src/parse_map.c src/parse_config.c \
       src/map.c src/utils.c src/gnl.c
OBJS = $(SRCS:.c=.o)

ifeq ($(shell uname -s),Darwin)
SRCS += src/mlx_context_mac.c
MLX_DIR = mlx_mac
MLX_LIB = $(MLX_DIR)/libmlx.dylib
MLX_SRC = $(wildcard $(MLX_DIR)/*.swift $(MLX_DIR)/*.c)
LDLIBS = -Wl,-rpath,@executable_path/mlx_mac
else
SRCS += src/mlx_context_linux.c
MLX_DIR = mlx_linux
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_SRC = $(wildcard $(MLX_DIR)/*.c) $(MLX_DIR)/Makefile.mk $(MLX_DIR)/configure
LDLIBS = -lXext -lX11 -lm -lz
endif

CPPFLAGS = -Iincludes -I$(MLX_DIR)

all: $(NAME)

$(NAME): $(OBJS) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_LIB) $(LDLIBS) -o $@
ifeq ($(MLX_DIR),mlx_mac)
	install_name_tool -change libmlx.dylib @rpath/libmlx.dylib $@
endif

$(MLX_LIB): $(MLX_SRC) $(MLX_DIR)/Makefile $(MLX_DIR)/mlx.h
ifeq ($(MLX_DIR),mlx_mac)
	$(MAKE) -C $(MLX_DIR) -j1
else
	$(MAKE) -C $(MLX_DIR)
endif

$(OBJS): includes/cub3d.h $(MLX_DIR)/mlx.h

clean:
	rm -f $(OBJS)
	@if [ "$(MLX_DIR)" = mlx_mac ] || [ -f $(MLX_DIR)/Makefile.gen ]; then \
		$(MAKE) -C $(MLX_DIR) clean; \
	fi

fclean: clean
	rm -f $(NAME)

re: fclean
	$(MAKE) all

mac: all

bonus: all

.PHONY: all clean fclean re mac bonus

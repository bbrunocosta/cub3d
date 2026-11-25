NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror

SCENE_SRCS = src/scene/gnl.c src/scene/map.c src/scene/parse_config.c
SCENE_SRCS += src/scene/parse_map.c src/scene/utils.c src/scene/free_scene.c

ENGINE_SRCS = src/engine/controls/events.c src/engine/controls/movement.c
ENGINE_SRCS += src/engine/render/cast.c src/engine/render/ray.c
ENGINE_SRCS += src/engine/render/render.c src/engine/render/texture_draw.c
ENGINE_SRCS += src/engine/render/textures.c src/engine/platform/cleanup.c
ENGINE_SRCS += src/engine/platform/graphics.c

SRCS = src/main.c $(SCENE_SRCS) $(ENGINE_SRCS)
OBJS = $(SRCS:.c=.o)

ifeq ($(shell uname -s),Darwin)
ENGINE_SRCS += src/engine/platform/mlx_context_mac.c
MLX_DIR = mlx_mac
MLX_LIB = $(MLX_DIR)/libmlx.dylib
MLX_SRC = $(wildcard $(MLX_DIR)/*.swift $(MLX_DIR)/*.c)
LDLIBS = -Wl,-rpath,@executable_path/mlx_mac
else
ENGINE_SRCS += src/engine/platform/mlx_context_linux.c
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

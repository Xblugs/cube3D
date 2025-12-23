CFLAGS		:=	-Wextra -Wall -Werror -O3

DEBUG		:=	src/debug/cube_debug.c						\

EXEC		:=	src/exec/cube_exec.c						\
				src/exec/cube_pos_init.c					\

RAYCAST		:=	src/exec/raycasting/cube_raycast_init.c		\
				src/exec/raycasting/cube_raycast_status.c	\
				src/exec/raycasting/cube_raycast.c			\

RENDER		:=	src/exec/rendering/cube_draw_line.c			\
				src/exec/rendering/cube_rendering.c			\
				src/exec/rendering/cube_select_texture.c	\
				src/exec/rendering/cube_texturing.c			\

HOOK		:=	src/hook/cube_hook.c						\
				src/hook/cube_key_hook.c					\
				src/hook/cube_mouse_hook.c					\
				src/hook/cube_move_handler.c				\
				src/hook/cube_move_handler2.c				\

PARSING		:=	src/parsing/1_read_map_file.c				\
				src/parsing/2_parse_texture.c				\
				src/parsing/3_parse_colors.c				\
				src/parsing/4_parsing_utils.c				\
				src/parsing/5_parsing_utils_bis.c			\
				src/parsing/6_parse_map.c					\
				src/parsing/7_map_prep.c					\
				src/parsing/8_map_copy.c					\
				src/parsing/9_check_map_chars.c				\
				src/parsing/10_check_if_one_spawn.c			\
				src/parsing/11_check_player_pos.c			\
				src/parsing/12_map_validating.c				\
				src/parsing/13_flood_prep.c					\
				src/parsing/14_init_parsing.c				\
				src/parsing/15_general_parsing.c			\
				src/parsing/16_free.c						\
				src/parsing/17_is_text_accessible.c			\
				src/parsing/cube_parsing.c					\

UTILS		:=	src/utils/clean_utils.c						\
				src/utils/cube_utils.c						\
				src/utils/mlx_utils.c						\
				src/utils/mlx_wrapper.c						\

SRC			:=	src/cube_data_init.c						\
				src/cube_welcome.c							\
				src/cube.c									\

EXEC_SRC	:=	$(EXEC) $(RAYCAST) $(RENDER)
PARSING_SRC	:=	$(PARSING)

SOURCES		:=	$(DEBUG) $(EXEC_SRC) $(HOOK) $(PARSING_SRC) $(UTILS) $(SRC)

NAME		:=	cube3D
OBJECTS		:=	$(SOURCES:.c=.o)


INCLUDES	:=	-I./libft/includes -I./includes -I./minilibx-linux
LDFLAGS		:= -L./libft/ -lft -lm -lXext -lX11 -L./minilibx-linux -lmlx_Linux

all: libs $(NAME)

$(NAME): $(OBJECTS)
	cc $(CFLAGS) $(OBJECTS) -o $(NAME) $(LDFLAGS)

%.o: %.c
	@cc $(CFLAGS) -c $(INCLUDES) $< -o $@

clean:
	make -sC ./libft clean
	make -sC ./minilibx-linux clean
	@rm -f $(OBJECTS)

fclean:
	make -sC ./libft fclean
	make -sC ./minilibx-linux clean
	@rm -f $(OBJECTS)
	@rm -f $(NAME)

libs:
	make -C ./libft
	make -sC ./minilibx-linux

re: fclean all

.PHONY: all clean fclean re


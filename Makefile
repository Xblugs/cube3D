CFLAGS		:=	-Wextra -Wall -Werror

DEBUG		:=	src/debug/cube_debug.c						\

EXEC		:=	src/exec/cube_exec.c						\
				src/exec/cube_pos_init.c					\

HOOK		:=	src/hook/cube_hook.c						\
				src/hook/cube_key_hook.c					\
				src/hook/cube_mouse_hook.c					\
				src/hook/cube_move_handler.c				\

PARSING		:=	src/parsing/placeholder.c					\

UTILS		:=	src/utils/clean_utils.c						\
				src/utils/cube_utils.c						\
				src/utils/math_utils.c						\
				src/utils/mlx_utils.c						\
				src/utils/mlx_wrapper.c						\

SRC			:=	src/cube.c									\
				src/cube_brick_wall.c						\
				src/cube_data_init.c						\
				src/cube_draw_line.c						\
				
SOURCES		:=	$(DEBUG) $(EXEC) $(HOOK) $(PARSING) $(UTILS) $(SRC)

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
	make -sC ./libft
	make -sC ./minilibx-linux

re: fclean all

.PHONY: all clean fclean re


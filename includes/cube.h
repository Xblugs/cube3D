/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cczerwin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 13:52:27 by cczerwin          #+#    #+#             */
/*   Updated: 2025/10/15 13:52:28 by cczerwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <unistd.h>

// MATH LIB - compile with -lm
# include <math.h>
# include <complex.h>
# include <tgmath.h>
# include <fenv.h>

# include "libft.h"
# include "mlx.h"
// # include "mlx_int.h"	// t_img conflict

// ERROR MACROS
# define ALLOC_FAIL 		"memory allocation error\n"
# define MLX_FAIL 			"MLX error\n"

// PREPARSING ERROR
# define MIN_ARGV_LEN		4
# define WRONG_ARGC 		"cube3D require a path to a map file (*.cub)\n"
# define WRONG_EXT 			"wrong extension (.cub required)\n"
# define FILE_NOT_FOUND 	"file not found\n"
# define OPEN_FAIL 			"failed to open file\n"

// PARSING ERROR
# define ERROR				"Error\n"
# define BAD_FORMAT 		"invalid map format\n"
# define BAD_WALL 			"map must be closed by walls\n"
# define BAD_ELEM 			"unknown element present [!= 0, 1, N, S, E, W]\n"
# define TEXT_NOT_FOUND 	"texture not found\n"
# define TEXT_OPEN_FAIL 	"failed to open texture file\n"

// OPEN ~ READ MACROS
# define OPEN_EXEC 			O_EXEC
# define OPEN_READ 			O_RDONLY
# define OPEN_REPLACE 		O_WRONLY
# define OPEN_APPEND 		O_APPEND

// PRINT MACROS
/*
	printf(RED"text goes here %s\n", END);

	[END] is called on %s to ensure the text format
	is reset before the next print (internal buffer issues)

	0; is for normal font
	1; is for bold font
	5; is for blinking font
*/
# define B_WHITE			"\e[1;37m"
# define WHITE				"\e[0;97m"
# define B_RED				"\e[1;31m"
# define RED				"\e[0;31m"
# define BLUE				"\e[0;96m"
# define GREEN				"\e[0;92m"
# define YELLOW				"\e[0;93m"
# define BLINK_YELLOW		"\e[5;93m"
# define PURPLE				"\e[0;35m"
# define CYAN				"\e[0;36m"
# define GRAY				"\e[0;37m"

# define END				"\e[0m"

// ASCII LOGO MACROS
# define ASCII_00 "            _           ___________ \n"
# define ASCII_01 "           | |         |____ |  _  \\\n"
# define ASCII_02 "  ___ _   _| |__   ___     / / | | |\n"
# define ASCII_03 " / __| | | | '_ \\ / _ \\    \\ \\ | | |\n"
# define ASCII_04 "| (__| |_| | |_) |  __/.___/ / |/ / \n"
# define ASCII_05 " \\___|\\__,_|_.__/ \\___|\\____/|___/  \n"

// COLOR CODE MACROS
# define C_PURPLE			0xFF00FF
# define C_ORANGE			0xFF9900
# define C_YELLOW			0xFFFF00
# define C_GREEN			0x00FF00
# define C_WHITE			0xFFFFFF
# define C_RED				0xFF0000
# define C_BLUE				0x0000FF
# define C_CYAN				0x00FFFF
# define C_LIME				0xBFFF00
# define C_BROWN			0x964B00

// MLX HOOK DEFINES
// ESC key as defined by X11/keysymdef.h
# define ESC				0xFF1B
# define ENTER				0xFF0D
# define SPACE				0x20

// FUNCTION KEYS
# define F1 				0xFFBE
# define F2 				0xFFBF
# define F3 				0xFFC0

// ARROW KEYS
# define UP 				0xFF52
# define DOWN 				0xFF54
# define LEFT 				0xFF51
# define RIGHT 				0xFF53

// NUMPAD KEYS
# define NUM_UP 			0xFF97
# define NUM_DOWN 			0xFF99
# define NUM_LEFT 			0xFF96
# define NUM_RIGHT 			0xFF98
# define NUM_MID 			0xFF9D
# define NUM_ZERO 			0xFF9E

// MOUSE
# define LMB				1
# define RMB				3
# define WHEEL_CLICK		2
# define WHEEL_UP			4
# define WHEEL_DOWN			5

// HOOK FLAGS
# define ON_ENTER			7
# define ON_LEAVE			8
# define ON_DESTROY			17

/*
	Used for array indexes for more code clarity
*/
// X, Y coordinates
# define X					0
# define Y					1

// Cardinal positions
# define N					0
# define W					1
# define S					2
# define E					3

// Red, Green, Blue for color coding
# define R					0
# define G					1
# define B					2

// Ray status
# define CASTING			0
# define OUT				1
# define HIT				2

// CUBE PRECOMPUTED VALUES
/*
	See math.md for explanations

	Also calc in math_utils.c
*/

// Texture size and half size
# define UNIT				64
# define HALF_UNIT			32
# define MOV_SPEED			8

// Resolutions definitions
# define MAX_WID			1600
# define MAX_HEI			900
# define MIN_WID			320
# define MIN_HEI			200

//	[	320*200	screen with 60° field of view	]
// # define FOV				60
// # define WIDTH				320
// # define HEIGHT				200

//	[	640*480	screen with 60° field of view	]
# define FOV				60
# define WIDTH				640
# define HEIGHT				480

//	[	800*600	screen with 60° field of view	]
// # define FOV				60
// # define WIDTH				800
// # define HEIGHT				600

typedef struct s_data		t_data;
typedef struct s_draw		t_draw;
typedef struct s_map		t_map;
typedef struct s_img		t_img;
typedef struct s_tex		t_tex;
typedef struct s_calc		t_calc;
typedef struct s_raycast	t_raycast;

/*
	t_img is expected to be window-sized (main frame)
	t_data encapsulate everything for easier cleanup / access

	Only one image is expected to be drawn at all times
*/
typedef struct s_data
{
	t_img		*img;				// rendered screen
	t_draw		*draw;				// data to draw for point A to B
	t_map		*map;				// data from map file
	t_tex		*tex;				// textures
	t_calc		*calc;				// precalculated math
	t_raycast	*rc;				// raycasting variables
	void		*mlx;
	void		*win;
}	t_data;

/*
	offset = y * line_lenght + x * (bpp / 8)
	img = 32bpp, 3200ll, 0endian
	800 x 4 byte = 3200 bit for one line (800*600)
*/
typedef struct s_img
{
	int			bpp;
	int			line_len;
	int			endian;
	int			x;
	int			y;
	void		*img;
	char		*addr;
}	t_img;

/*
	(x,y) are made to hold x0, x1 and dx for the draw_line function

		x0 = starting point
		x1 = destination
		dx is set internally
*/
typedef struct s_draw
{
	short		x[3];				// x0, x1, dx
	short		y[3];				// y0, y1, dy
	int			color;
}	t_draw;

/*
	Everything read from the map file
	hex_color = (R << 16) + (G << 8) + B
*/
typedef struct s_map
{
	char		**map;
	short		line;				// y
	short		col;				// x
	char		*path[4];			// path to N, W, S, E textures
	short		ceiling[3];			// R, G, B
	short		floor[3];			// R, G, B
	int			h_ceiling;			// color in hex format
	int			h_wall;				// last wall data used internally
	int			h_floor;			// color in hex format
}	t_map;

/*
	texture are assumed to be the exact same size (UNIT_SIZE)
	path is used only to load the texture once
	textures are kept in memory for the program entire lifetime
*/
typedef struct s_tex
{
	int			w;					// texture width  [set by mlx]
	int			h;					// texture height [set by mlx]
	void		*img[4];			// ptr to N, W, S, E textures
}	t_tex;

/*
	precalc values for dynamic window size
	define might be used in code for readability purposes
*/
typedef struct s_calc
{
	short		half_fov;
	short		half_width;			// screen size
	short		half_height;		// screen size
	short		max_width;			// projection size
	short		max_height;			// projection size
	short		dist_to_proj;		// distance in pixels
	double		angle_between_rays; // angle variation between rays in degree
}	t_calc;

/*
	short is used to reduce memory cost

	[ulimit -s] in bash to see stack size limit
*/
typedef struct s_raycast
{
	double		delta[2];			// delta[X, Y]
	double		ray[2];				// ray[X, Y]
	int			pos[2];				// player pos [x, y]
	double		ray_angle;			// raycasting angle
	short		ray_index;			// 0 to WIDTH - 1
	short		view_angle;			// player angle in degree
	short		wall_hit[WIDTH][2]; // in map coordinates (px / UNIT)
	double		wall_dist[WIDTH];	// distance to projected wall
	short		ray_status;			// ray current status
}	t_raycast;

/*
	Debug functions and info/tests
	dir: src/debug
*/
// 		-- src/debug/cube_debug.c --
void	size_of_struct(void);
void	print_pos(t_data *data, int x, int y);
void	print_raycast_hit_px(t_raycast *rc);
void	print_raycast_hit_index(t_raycast *rc);
void	print_raycast_dist(t_raycast *rc);

/*
	Exec and rendering functions
	dir: src/exec
*/
// 		-- src/exec/cube_exec.c --
void	exec_func(t_data *data);
int		exec_loop(t_data *data);

// 		-- src/exec/cube_pos_init.c --
void	start_pos_wrapper(t_data *data, t_map *map, t_raycast *rc);

/*
	Raycasting functions
	dir: src/exec/raycasting
*/
// 		-- src/exec/raycasting/cube_raycast_init.c --
void	raycast_init_wrapper(t_data *data, t_raycast *rc);

// 		-- src/exec/raycasting/cube_raycast_status.c --
void	ray_status_check_wrapper(t_data *data, t_raycast *rc);
int		wall_hit(t_data *data, t_raycast *rc);

// 		-- src/exec/raycasting/cube_raycast.c --
void	raycast_wrapper(t_data *data, t_raycast *rc);

/*
	Rendering functions
	dir: src/exec/rendering
*/
//		-- src/exec/rendering/cube_rendering.c --
void	render(t_data *data, t_raycast *rc);

//		-- src/exec/rendering/cube_select_texture.c --
void	select_texture_wrapper(t_data *data, t_raycast *rc, t_draw *draw);

//		-- src/exec/rendering/cube_texturing.c --
void	draw_texture(t_data *data, t_raycast *rc, t_draw *draw);

/*
	Everything related to actions through mlx_hook(...)
	dir: src/hook
*/
// 		-- src/hook/cube_hook.c --
void	set_hook(t_data *data);

// 		-- src/hook/cube_key_hook.c --
int		key_handler(int key, t_data *data);

// 		-- src/hook/cube_mouse_hook.c --
int		mouse_io(t_data *data);
int		mouse_handler(int button, int x, int y, t_data *data);

// 		-- src/hook/cube_move_handler.c --
void	move_handler(int key, t_data *data);
// void	brick_move_handler(int key, t_data *data);

/*
	Everything related to file parsing
	dir: src/parsing
*/
// 		-- src/parsing/placeholder.c --
int		parsing_placeholder(t_data *data, t_map *map);

/*
	Various generic utils files
	dir: src/utils
*/
// 		-- src/utils/clean_utils.c --
void	int_cleanup(int **intmap, int line);
void	char_cleanup(char **charmap, int line);

// 		-- src/utils/cube_utils.c --
size_t	ft_splitcheck(char **split, size_t wordcount);
size_t	ft_digitcount(char const *s, char c);
long	int_to_long(int x, int y);
void	long_to_int(long l, int *x, int *y);

// 		-- src/utils/math_utils.c --
double	deg_to_rad(double angle);
double	rad_to_deg(double radian);
void	precalc_val(t_data *data, t_calc *calc);

// 		-- src/utils/mlx_utils.c --
int		mlx_close(t_data *data);
void	clear_screen(t_data *data);
void	pixel_put(t_img *img, int x, int y, int color);

// 		-- src/utils/mlx_wrapper.c --
void	mlx_pitow(void *mlx, void *win, void *img, long wh);
void	*mlx_xpm_ftoi(void *mlx, char *file, int *width, int *height);

/*
	./src/ root folder
	dir: src/
*/
// 		-- src/cube_brick_wall.c --
// void	brick_wall(t_data *data);

// 		-- src/cube_data_init.c --
void	data_init(t_data *data, t_img *img, t_draw *draw);
void	mlx_data_init(t_data *data);

// 		-- src/cube_draw_line.c --
void	draw_line(t_img *img, t_draw *draw);

// 		-- src/cube_welcome.c --
void	cube_welcome(void);

// 		-- src/cube.c --
int		texture_init(t_data *data, t_tex *tex, t_map *map);

#endif

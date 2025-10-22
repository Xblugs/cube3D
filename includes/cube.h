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
// # include "mlx_int.h"

// ERROR MACROS
# define ALLOC_FAIL 		"memory allocation error\n"
# define MLX_FAIL 			"MLX error\n"

// PREPARSING ERROR
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
*/
# define B_WHITE			"\e[1;37m"
# define WHITE				"\e[0;97m"
# define RED				"\e[0;31m"
# define BLUE				"\e[0;96m"
# define GREEN				"\e[0;92m"
# define YELLOW				"\e[0;93m"
# define BLINK_YELLOW		"\e[5;93m"
# define PURPLE				"\e[0;35m"
# define CYAN				"\e[0;36m"
# define GRAY				"\e[0;37m"

# define END				"\e[0m"

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
# define WHEEL_CLICK		2
# define WHEEL_UP			4
# define WHEEL_DOWN			5

// HOOK FLAGS
# define ON_ENTER			7
# define ON_LEAVE			8
# define ON_DESTROY			17

// CUBE PRECOMPUTED VALUES
/*
	norm only allow for constant defines
	changing the screen resolution requires 
	to recalc parameters listed below
		See math.md for explanations

	Also calc in math_utils.c
*/

// Texture size and half size
# define UNIT_SIZE			64
# define HALF_UNIT_SIZE		32

//	[	320*200	screen with 60° field of view	]
// # define FOV				60
// # define FOV_HALF			30
// # define WIDTH				320
// # define HEIGHT				200
// # define HALF_WIDTH			160
// # define HALF_HEIGHT		100
// # define DIST_TO_PROJ		277
// # define ANGLE_BETWEEN_RAYS	0.1875

//	[	640*640	screen with 60° field of view	] // texture test mode
# define FOV				60
# define FOV_HALF			30
# define WIDTH				640
# define HEIGHT				640
# define HALF_WIDTH			320
# define HALF_HEIGHT		320
# define DIST_TO_PROJ		554
# define ANGLE_BETWEEN_RAYS	0.09375

//	[	800*600	screen with 60° field of view	]
// # define FOV				60
// # define FOV_HALF			30
// # define WIDTH				800
// # define HEIGHT				600
// # define HALF_WIDTH			400
// # define HALF_HEIGHT		300
// # define DIST_TO_PROJ		693		//692.8
// # define ANGLE_BETWEEN_RAYS	0.075

typedef struct s_data		t_data;
typedef struct s_draw		t_draw;
typedef struct s_map		t_map;
typedef struct s_img		t_img;
typedef struct s_tex		t_tex;
typedef struct s_calc		t_calc;

/*
	[DEPRECATED COMMENT FROM FDF]
	img is expected to be window-sized
	t_data encapsulate everything for easier cleanup
	pos are where your current image is located at
	only one image is expected to be drawn at all times
*/
typedef struct s_data
{
	int		x;
	int		y;
	int		pos_x;
	int		pos_y;
	t_img	*img;
	t_draw	*draw;
	t_map	*map;
	t_tex	*tex;
	t_calc	*calc;
	void	*mlx;
	void	*win;
}	t_data;

/*
	offset = y * line_lenght + x * (bpp / 8)
	img = 32bpp, 3200ll, 0endian
	800 x 4 byte = 3200 bit for one line (800*600)
*/
typedef struct s_img
{
	int		bpp;
	int		line_len;
	int		endian;
	int		x;
	int		y;
	void	*img;
	char	*addr;
}	t_img;

/*
	(x,y,z) are made to hold x0, x1 and dx for the draw_line function
	pix are the pixel between two data point
*/
typedef struct s_draw
{
	int		x[3];
	int		y[3];
	int		z[3];
	int		pix_x;
	int		pix_y;
	int		pix_z;
	int		off_x;
	int		off_y;
	int		angle;
	int		angle_off;
	int		scale;
	int		h_delta;
	int		color;
}	t_draw;

/*
	Everything read from the map file ends here hopefully
*/
typedef struct s_map
{
	int		**map;
	int		line;		// i
	int		col;		// j
}	t_map;

/*
	texture are assumed to be the exact same size (UNIT_SIZE)
	path is used only to load the texture once
	textures are kept in memory for the program entire lifetime

	TODO: move texture path to t_map once parsing is done for cleaner struct
*/
typedef struct s_tex
{
	int		w;
	int		h;
	char	*path1;
	char	*path2;
	char	*path3;
	char	*path4;
	void	*img1;
	void	*img2;
	void	*img3;
	void	*img4;
}	t_tex;

/*
	precalc values and possibly more later on
*/
typedef struct s_calc
{
	int		fov;
	int		half_fov;
	int		width;
	int		height;
	int		half_width;
	int		half_height;
	int		dist_to_proj;
	double	angle_betweem_rays;
}	t_calc;

/*
	Debug functions and info/tests
	dir: src/debug
*/
// 		-- src/debug/cube_debug.c --
void	size_of_struct(void);

/*
	Everything related to actions through mlx_hook(...)
	dir: src/hook
*/
// 		-- src/hook/cube_hook.c --
void	set_hook(t_data *data);

// 		-- src/hook/cube_key_hook.c --
int		key_handler(int keycode, t_data *data);

// 		-- src/hook/cube_mouse_hook.c --
int		mouse_io(t_data *data);
int		mouse_handler(int button, int x, int y, t_data *data);

/*
	Everything related to file parsing
	dir: src/parsing
*/
// 		-- src/parsing/placeholder.c --
int	parsing(void);

/*
	Various utils files
	dir: src/utils
*/
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
void	int_cleanup(int **intmap, int line);
void	char_cleanup(char **charmap, int line);

// 		-- src/utils/mlx_utils2.c --
void	mlx_pitow(void *mlx, void *win, void *img, long wh);
void	*mlx_xpm_ftoi(void *mlx, char *file, int *width, int *height);

/*
	./src/ root folder
	dir: src/
*/
// 		-- src/cube_brick_wall.c --
void	brick_wall(t_data *data);

// 		-- src/cube_data_init.c --
void	data_init(t_data *data, t_img *img, t_draw *draw, t_map *map);
void	mlx_data_init(t_data *data);

// 		-- src/cube_draw_line.c --
void	draw_line(t_img *img, t_draw *draw);
void	pixel_put(t_img *img, int x, int y, int color);

// 		-- src/cube.c --
void	brick_wall(t_data *data);

#endif

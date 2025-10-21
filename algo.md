# Pre-checking

(1) Exit if argv[1] [len < 4] (minimum file name is .cub)

(2) Check if the file a .cub map
	--> else exit with [WRONG_EXT]

(3)	Try to access the file (existence/read check)
	--> if file doesn't exist or can't be read exit with [FILE_NOT_FOUND] or [OPEN_FAIL]

(4) File exist, right extension and can be opened
	--> Get the file content

# Generic rule
(~) On any allocation error
	--> clean and exit with [ALLOC_FAIL] no question asked

# File checking
(~) If we get an error here, print [ERROR] before error message

(1) If anything matches the parameter we need, look format
	(2) If format is wrong	(i.e check texture extension)	
		--> clean and exit with [BAD_FORMAT]
 if right and not already present save it
 	--> else clean and exit [BAD_FORMAT]
--> Keep reading until map

(3) On map part, if all parameter are not set, 
	--> clean and exit with [BAD_FORMAT]
	Otherwise, get the entire map layout

# Map checking
(~) If we get an error here, print ERROR before error message

(1) Check map part validity, clean and exit if invalid
	(wall checks, only allowed element are present [0, 1, N, S, E, W])
		[BAD_WALL , BAD_ELEM]				(only one starting point allowed)

(2) Map is valid, try to access the texture (existence/read check)
	--> clean and exit on error [TEXT_NOT_FOUND] or [TEXT_OPEN_FAIL]

# Texture checking
(1) Check if texture exist and can be accessed

(2) Check if texture is the right format (.png renamed to .xpm)
						(--> Does mlx handle this ?)
# MLX init
(1) We have a correct map, init mlx and set its hooks
	-->on init error clean exit with [MLX_FAIL]

Once MLX is set we need to do the calculations to render the map

				[[ See math.md ]]

(2) Init player values in our representation facing the right side
	-->		x	y	fov angle
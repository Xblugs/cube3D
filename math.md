## Sources:
# https://wynnliam.github.io/blog/
	-> Part 1: Wall rendering
	-> Part 2: Sprite rendering
	-> Part 3: Floor / Ceiling / Sky rendering
	-> Part 4: Optimization (i.e lookup tables, using translated int)

# https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/
	-> Bunch of texture files
	-> Part  9: Drawing walls
	-> Part 12: Floor casting
	-> Part 19: Shading	
		Intensity = Object Intensity/Distance * Multiplier

# Assuming the following:
	- Projection on 320*200px screen [0 to 319, 199]
	- Every sprite is 64*64px
	- FOV is 60°
	- Player height is 32px
		--> Floor and Ceiling are equidistant 


		TOP	VIEW

(0, 0)		90       (X, 0)		
	╔═══════════════╗			
	║		┊		║			
	║	Q2	┊	Q1	║			
	║		┊		║			
180	║┈┈┈┈┈┈┈┊┈┈┈┈┈┈┈║ 0			
	║		┊		║			
	║	Q3	┊	Q4	║			
	║		┊		║			
	╚═══════════════╝			
(0, Y)	   270	     (X, Y)		

# Projection
	
	[0 --> column -->  320]

	The player’s rotation is theta

		the angle of the leftmost column is:
			[theta - (field of view / 2) = theta - 30]

	Likewise, the angle of the rightmost column is: 
			theta + (field of view / 2) = theta + 30
	
	curr_ray_angle = theta - 30
	-> 60 / 320 = 0.1875° per column of pixel
	distance to projection	=	(proj plane width / 2)	/ tan(fov / 2)
										160			  	/ tan(30)
							= 277px

	For example, suppose the ray at column 200 hits a wall slice at distance of 330 units. The projection of the slice will be 64 / 330 * 277 = 54 (rounded up).
Since the center of the projection plane is defined to be at 100. The middle of the wall slice should appear at this point. Hence, the top position where the wall slice should be drawn is 100-27=73. (where 27 is one half of 54). Finally, the projection of the slice will look something like the next 

# Raycasting

	Fire a ray for each column to be displayed
	-> If we hit a wall, it can be seen so we render it

	We move by [movement_magnitude] = 5px
	while the current ray has not hit a wall:
	current ray x += cos(ray_angle) * movement_magnitude
	current ray y += sin(ray_angle) * movement_magnitude
	-> We could go through a wall or calculate too many points

	Instead:

	c_h is the intersection ray & horizontal grid
	c_v is the intersection ray & vertical grid
	--> inter_h, inter_v as int [2] to have (x, y) to move to intersection

	d_h is how much we move c_h to join the grid	(multiple of 64 are on grid)
	d_v is 					c_v
		( depends on the current quadrant )
	--> mov_h, mov_v as int [2] to have (x, y) to handle both directions

	While we're not on a wall or out of bound:
		c_h += d_h			[c_h[X] += d_h[X] AND c_h[Y] += d_h[Y]]
		c_v += d_v			[c_v	   d_v		  c_v		d_v	  ]

	if both c_h and c_v intersect a wall:
		return the one closest to the player.
	if c_h is out of bounds:
		return c_v
	if c_v is out of bounds:
		return c_h
	if both c_h and c_v are out of bounds:
		return an error vector

	If both hit		:	Return closest
		one is out	:	Return other one
		both are out:	Return an error vector

	for each column: ray_angle = (view_angle - HALF_FOV) to (view_angle + HALF_FOV)
						(which might not be in the same quadrant calc)
	[should we calc every ray then use them or one at once?]

	Also tan() returns a double, make sure it doesn't mess up calculations form
			(implicit conversion somewhere)

## WALL RENDERING
# Computations for Quadrant 1 (0 < Ray Angle < 90)

    c_h.x = ((c_h.y - player.y) / Tan(alpha)) + player.x
    c_h.y = (floor(player_pos.y / 64) * 64) - 1
    d_h.y = -64 (Since we travel in the negative direction along the y-axis)
    d_h.x = 64 / Tan(alpha)
	
    c_v.x = (floor(player.x / 64) * 64) + 64
    c_v.y = Tan(alpha) * (c_v.x - player.x) + player.y
    d_v.x = 64
    d_v.y = -Tan(alpha)(d_v.x)

	floor if using floating numbers, int are auto rounded
	Alpha is the ray index [0 --> 360] - current quadrant start angle

# Q1 in code form

	--> Same formulas rewritten: (struct path to data is ignored for clarity)
	
	alpha = deg_to_rad(ray_angle - 0);
	inter_h[X] = ((inter_h[Y] - pos[Y]) / tan(alpha)) + pos[X];
    inter_h[Y] = ((pos[Y] / UNIT) * UNIT) - 1;
    mov_h[Y] = -UNIT;
    mov_h[X] = UNIT / tan(alpha);
	
    inter_v[X] = ((pos[X] / UNIT) * UNIT) + UNIT;
    inter_v[Y] = tan(alpha) * (inter_v[X] - pos[X]) + pos[Y];
    mov_v[X] = UNIT;
    mov_v[Y] = -tan(alpha) * (mov_v[X]);


# Computations for Quadrant 2 (91 < Ray Angle < 179)

    alpha = ray angle - 90
    c_h.y = (floor(player.y / 64) * 64) - 1
    c_h.x = Tan(alpha) * (player.y - c_h.y)
    d_h.y = -64 (Since we travel in the negative direction along the y-axis)
    d_h.x = -64 * Tan(alpha)
	
    c_v.x = (floor(player.x / 64) * 64) - 1
    c_v.y = player.y - ((player.x - c_v.x)/ Tan(alpha))
    d_v.x = -64
    d_v.y = -64 / Tan(alpha)

# Q2 in code form

	alpha = deg_to_rad(ray_angle - 90);
	inter_h[Y] = ((pos[Y] / UNIT) * UNIT) - 1;
	inter_h[X] = tan(alpha) * (pos[Y] - inter_h[Y]);
    mov_h[Y] = -UNIT;
    mov_h[X] = -UNIT * tan(alpha);
	
	inter_v[X] = ((pos[X] / UNIT) * UNIT) - 1;
	inter_v[Y] = pos[Y] - ((pos[X] - inter_v[X]) / tan(alpha));
    mov_v[X] = -UNIT;
    mov_v[Y] = -UNIT / tan(alpha);


# Computations for Quadrant 3 (181 < Ray Angle < 269)

    alpha = ray angle - 180
    c_h.y = (floor(player.y / 64) * 64) + 64
    c_h.x = player.x - (c_h.y - player.y) / Tan(alpha)
    d_h.y = 64 (Since we travel in the positive direction along the y-axis)
    d_h.x = -64 * Tan(alpha) (Since we travel in the negative direction along the x-axis)
	
    c_v.x = (floor(player.x / 64) * 64) - 1
    c_v.y = Tan(alpha)(player.x - c_v.x) + player.y
    d_v.x = -64
    d_v.y = 64 * Tan(alpha)

# Q3 in code form

	alpha = deg_to_rad(ray_angle - 180);
    inter_h[Y] = ((pos[Y] / UNIT) * UNIT) + UNIT;
    inter_h[X] = pos[X] - (inter_h[Y] - pos[Y]) / tan(alpha);
    mov_h[Y] = UNIT;
    mov_h[X] = -UNIT * tan(alpha);
	
    inter_v[X] = ((pos[X] / UNIT) * UNIT) - 1;
    inter_v[Y] = tan(alpha) * (pos[X] - inter_v[X]) + pos[Y];
    mov_v[X] = -UNIT;
    mov_v[Y] = UNIT * tan(alpha);


# Computations for Quadrant 4 (271 < Ray Angle < 359)

	alpha = ray angle - 270
    c_h.y = (floor(player.y / 64) * 64) + 64
    c_h.x = player.x + Tan(alpha)*(c_h.y - player.y)
    d_h.y = 64 (Since we travel in the positive y direction)
    d_h.x = 64 * Tan(alpha)

    c_v.x = (floor(player.x / 64) * 64) - 64
    c_v.y = player.y + (c_v.x - player.x) / Tan(alpha)
    d_v.x = 64 (Since we travel in the positive x direction)
    d_v.y = 64 / Tan(alpha)

# Q4 in code form

	alpha = deg_to_rad(ray_angle - 270);
    inter_h[Y] = ((pos[Y] / UNIT) * UNIT) + UNIT;
    inter_h[X] = pos[X] + tan(alpha) * (inter_h[Y] - pos[Y]);
    mov_h[Y] = UNIT;
    mov_h[X] = UNIT * tan(alpha);
	
    inter_v[X] = ((pos[X] / UNIT) * UNIT) - UNIT;
    inter_v[Y] = pos[Y] + (inter_v[X] - pos[X]) / tan(alpha);
    mov_v[X] = UNIT;
    mov_v[Y] = UNIT / tan(alpha);


# Performance considerations

	Some of those values need only to be computed once for each quadrant
	Which gives out:

		const static mov_h = (values for each quadrant)
						_v

	They are calculated ONCE instead of every column for every rendered frame
	Note: not all mov are constant values but in Q4 case

			 mov_h[Y] = UNIT;		mov_v[X] = UNIT;
	
	We can save calculations on those specific values on this specific quadrant
	other are not const static but calculated beforehand

	Form switches to: (for a single ray)	[Q4 as exemple]

	// (271 < ray_angle < 359)
	type	q4_raycast(type name, type name, ...)
	{
    	const static int	mov_h[Y] = UNIT;
    	const static int	mov_v[X] = UNIT;

		alpha = tan(deg_to_rad(ray_angle - 270));
    	mov_h[X] = UNIT * alpha;
    	mov_v[Y] = UNIT / alpha;
		inter_h[Y] = ((pos[Y] / UNIT) * UNIT) + UNIT;
    	inter_h[X] = pos[X] + alpha * (inter_h[Y] - pos[Y]);
    	inter_v[X] = ((pos[X] / UNIT) * UNIT) - UNIT;
    	inter_v[Y] = pos[Y] + (inter_v[X] - pos[X]) / alpha;
		while (not out of scope)
		{
			inter_h[X] += mov_h[X];
			inter_h[Y] += mov_h[Y];
			inter_v[X] += mov_v[X];
			inter_v[Y] += mov_v[Y];
		}
		return (depend on wall hit but map is closed sooooooo);
	}

	we essentially calc our values, find the grid then move on it
	without function declaration and structure calls it would fit the norm

	also [alpha] is always used in [tan(alpha)] form so we can melt it inside

	mov_h[Y] and mov_v[X] could simply be replaced to UNIT in calc
							(no idea what is better / more readable)
					--> [mov_h[Y] = UNIT] is incorrect, UNIT is easier to use

	Reminder from Raycasting part:

	if both [inter_h] and [inter_v] intersect a wall:
		return the one closest to the player.
	if [inter_h] is out of bounds:
		return [inter_v]
	if [inter_v] is out of bounds:
		return [inter_h]
	if both [inter_h] and [inter_v] are out of bounds:
		return an error vector

	If both ray hit	:	Return closest
		one is out	:	Return other one
		both are out:	Return an error vector

	[[ don't forget to add this part in the function]]
	
	While we're not on a wall or out of bound:
		inter_h[X] += mov_h[X];
		inter_h[Y] += mov_h[Y];
		inter_v[X] += mov_v[X];
		inter_v[Y] += mov_v[Y];

	Again technically we should never get out of bound but better handle the case

# Specific angles (undefined tan() results)

	ray angle 0 90 180 270
	Treat as +1

# Get back the distance to what we render (scaling)

	hit_dist = sqrt((player.x - hit.x)^2 + (player.y - hit.y)^2)
		hit is either c_v or c_h			(inter_v/h)

	projected wall height / distance from player to projection plane 
		= actual wall height / ray hit distance

	projected wall height / 277 = 64 / ray hit distance
	projected wall height = (64 / ray hit distance) * 277

# Correction for “Fisheye Effect”

	hit_dist * cos(theta)

	Cos(theta) = corrected_distance / hit_distance
	corrected_distance = Cos(theta) * hit_distance

	Where theta is the ray angle, not alpha

	**REMINDER**
	[[Alpha is the ray index [0 --> 360] - current quadrant start angle]]

## FLOOR & CEILING RENDERING

1. Cast a ray
2. If ray does not hit a wall: return
3. Otherwise, render wall slice ray hits.
4. For each pixel below the bottom of the wall slice on the screen:
	1. Project pixel location onto world.
	2. Render pixel of floor texture at screen position, but only
	if there is a floor texture to render.
5. For each pixel above the top of the wall slice on the screen:
	1. Project pixel location onto world.
	2. Render pixel of ceiling texture at screen position, but only
	if there is a ceiling texture to render.

	For us it means, once a wall is rendered, and our map in completely closed
	--> everything above is ceiling
				   below is floor
	Since we only have a color and not a texture to render this step is easy

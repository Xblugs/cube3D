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
	--> inter_h, inter_v

	d_h is how much we move c_h to join the grid
	d_v is 					c_v
		( depends on the current quadrant )

	While we're not on a wall or out of bound:
		c_h += d_h
		c_v += d_v

	If both hit		:	Return closest
		one is out	:	Return other one
		both are out:	Return an error vector

## WALL RENDERING
# Computations for Quadrant 1 (0 < Ray Angle < 90)

    c_h.x = ((c_h.y - player.y) / Tan(alpha)) + player.x
    c_h.y = c_h.y = (floor(player_pos.y / 64) * 64) - 1
    d_h.x = 64 / Tan(alpha)
    d_h.y = -64 (Since we travel in the negative direction along the y-axis)
    c_v.x = (floor(player.x / 64) * 64) + 64
    c_v.y = Tan(alpha)(c_v.x - player.x) + player.y
    d_v.x = 64
    d_v.y = -Tan(alpha)(d_v.x)

	floor if using floating numbers
	Alpha is the ray index [0 --> 360] - current quadrant start angle

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


# Computations for Quandrant 3 (181 < Ray Angle < 269)

    alpha = ray angle - 180
    c_h.y = (floor(player.y / 64) * 64) + 64
    c_h.x = player.x - (c_h.y - player.y) / Tan(alpha)
    d_h.y = 64 (Since we travel in the positive direction along the y-axis)
    d_h.x = -64 * Tan(alpha) (Since we travel in the negative direction along the x-axis)
    c_v.x = (floor(player.x / 64) * 64) - 1
    c_v.y = Tan(alpha)(player.x - c_v.x) + player.y
    d_v.x = -64
    d_v.y = 64 * Tan(alpha)

# Computations for Quandrant 4 (271 < Ray Angle < 359)

    alpha = ray angle - 270
    c_h.y = (floor(player.y / 64) * 64) + 64
    c_h.x = player.x + Tan(alpha)*(c_h.y - player.y)
    d_h.y = 64 (Since we travel in the positive y direction)
    d_h.x = 64 * Tan(alpha)
    c_v.x = (floor(player.x / 64) * 64) - 64
    c_v.y = player.y + (c_v.x - player.x) / Tan(alpha)
    d_v.x = 64 (Since we travel in the positive x direction)
    d_v.y = 64 / Tan(alpha)

ray angle 0 90 180 270 360
Treat as +1

	hit_dist = sqrt((player.x - hit.x)^2 + (player.y - hit.y)^2)
		hit is either c_v or c_h

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
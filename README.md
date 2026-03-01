*This project has been created as part of the 42 curriculum by alpascua, sarodrig*

# Description

We must create a “realistic” 3D graphical representation of the inside of a maze from a first-person perspective.

We have to create this representation using the ray-casting principles.

# Instructions

The program must be compiled using ``make``. After that, the file ``cub3D`` should be created.

To execute the program, you must include a map file (``.cub``) as the first (and only) parameter.

There should be indicated the textures (in ``.xpm`` format) for the walls and the RGB color of the floor and ceiling. After those instructions, a map using 0's and 1's indicating floor and walls, as well as a character indicating the initial orientation of the player (N, S, E, W).

Example:

```output
NO ./textures/eagle.xpm
SO ./textures/greystone.xpm
WE ./textures/purplestone.xpm
EA ./textures/red.xpm

F  255, 000, 000
C  100, 100, 100

11111111 111111111
100000011100000001
100000000000000011
1000000000E000001
111111011111110111
```

The program displays the image in a window and respects the following rules:

- The left and right arrow keys of the keyboard must allow you to look left and right in the maze.
- The W, A, S, and D keys must allow you to move the point of view through the maze.
- Shift allows you to run and ctrl makes you crouch.
- Pressing ESC must close the window and quit the program cleanly.
- Clicking on the cross on the window’s frame must close the window and quit the program cleanly.

# Resources

https://lodev.org/cgtutor/raycasting.html

# Bonus Feature List

The following bonus features have been included:

- Camera can be moved with the mouse
- Wall collisions

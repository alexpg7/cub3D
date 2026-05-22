# 🟥 cub3D ![Static Badge](https://img.shields.io/badge/Barcelona-black?style=for-the-badge&logo=42&logoColor=%23FFFFFF)
![Static Badge](https://img.shields.io/badge/c-grey?style=flat&logo=c)
![Static Badge](https://img.shields.io/badge/Makefile-green?style=flat&logo=AnkerMake)
![Static Badge](https://img.shields.io/badge/status-completed-green?style=flat)

*This project has been created as part of the 42 curriculum by [alpascua](https://github.com/alexpg7), [sarodrig](https://github.com/rodriguezparera)*

# Description

This project is about creating a 3D representation of a map, imitating the [Wolfenstein 3D](https://es.wikipedia.org/wiki/Wolfenstein_3D) graphic engine.

To do that, we have created the representation using the ray-casting principles.


# ⚒️ Compilation

Copy this repository in your machine:

```bash
https://github.com/alexpg7/cub3D.git cub3D
```

To compile the program, just use the ``make`` command, the file ``cub3D`` should be created.

# 🎮 How to use it

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

The program displays the image in a window and obeys the following rules:

- The left and right arrow keys of the keyboard must allow you to look left and right in the maze.
- The W, A, S, and D keys must allow you to move the point of view through the maze.
- Shift allows you to run and ctrl makes you crouch.
- Pressing ESC must close the window and quit the program cleanly.
- Clicking on the cross on the window’s frame must close the window and quit the program cleanly.

The window should look like this:

<img src="https://github.com/alexpg7/Images/blob/main/cub3D/cub3D.png" width="700">

We proportioned some textures in ./textures, but you can use whatever you want.

# 🛝 Play around

Now, you can use this program to create your own maps. You can even try to solve a maze from the inside by using a ``.cub`` file like this one:

```output
111111111111111
1S1010001000001
101010101110111
101000101010001
101111101010101
100010100000101
101010101110111
101010101010001
111010101011101
100000001000101
101111111110101
100000001000001
101010101110111
101010100010001
111111111111101
100000000000001
100000000000001
100000000000001
100000000000001
100000000000001
100000000000001
111111111111111
```

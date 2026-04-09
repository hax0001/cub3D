# cub3D

A simple 3D raycasting engine built in C using MiniLibX (42 project).

The program parses a `.cub` scene file, validates textures/colors/map closure, and renders a Wolfenstein-style first-person view with movement and mouse/keyboard rotation.

## Features

- Raycasting-based wall rendering
- Texture mapping for 4 wall directions (NO, SO, WE, EA)
- Floor and ceiling colors from RGB values
- Strict map validation (closed map, valid chars, single player spawn)
- Keyboard movement and rotation
- Mouse look support
- Minimap rendering

## Project Layout

- `main.c`: entry point, argument checks, parsing, game start
- `parse/`: `.cub` parsing and validation
- `ray_cast/` and `rendering/`: ray and wall rendering
- `mouvements/`: movement and keyboard input
- `start_game/`: MLX init, hooks, frame loop, textures, minimap
- `libft/`: custom C utility library
- `maps/`: sample valid/invalid maps
- `textures/`: XPM texture assets

## Requirements

- Linux
- C compiler (`cc`)
- MiniLibX + X11 development libraries

Typical packages on Debian/Ubuntu:

```bash
sudo apt update
sudo apt install -y build-essential libx11-dev libxext-dev libbsd-dev
```

## Build

From the repository root:

```bash
make
```

This builds:

- `libft/libft.a`
- `./cub3d`

## Run

```bash
./cub3d maps/good/subject_map.cub
```

The program expects exactly one `.cub` file argument.

## Controls

- `W` / `S`: move forward / backward
- `A` / `D`: strafe left / right
- `Left Arrow` / `Right Arrow`: rotate view
- `Mouse Move`: rotate camera
- `Esc`: exit

## `.cub` File Format

Expected identifiers:

- `NO path/to/north_texture.xpm`
- `SO path/to/south_texture.xpm`
- `WE path/to/west_texture.xpm`
- `EA path/to/east_texture.xpm`
- `F R,G,B` (floor color)
- `C R,G,B` (ceiling color)

Map rules enforced by parser:

- Allowed map characters: `0`, `1`, space, and one player spawn (`N`, `S`, `E`, `W`)
- Exactly one player spawn is required
- Map must be closed by walls
- Texture files must exist and use `.xpm`
- Colors must be valid RGB triplets in the `0-255` range

### Example of a simple `.cub` file:

```text
NO textures/wolfenstein/grey_stone.xpm
SO textures/wolfenstein/purple_stone.xpm
WE textures/wolfenstein/red_brick.xpm
EA textures/wolfenstein/wood.xpm

F 220,100,0
C 225,30,0

1111111
1000001
1011101
1000N01
1111111
```

## Useful Make Targets

```bash
make        # build
make clean  # remove object files
make fclean # clean + remove binary
make re     # rebuild from scratch
```

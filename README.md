# cub3D — 42 School Raycasting Project

A first-person 3D maze game inspired by Wolfenstein 3D, built from scratch in C using raycasting and the MiniLibX graphics library.

---

## Overview

**cub3D** is a project from [School 42](https://42.fr/) in which students implement a simple 3D engine using the **raycasting** technique — the same technique used by id Software's classic Wolfenstein 3D (1992).

The engine renders a 2D tile map as a textured 3D perspective view in real time. It includes:
- Textured walls with directional textures (North / South / East / West)
- Flat-colored floor and ceiling
- Smooth first-person player movement and mouse-look
- A minimap overlay (top-left corner)

### Authors
- **nait-bou** — nait-bou@student.42.fr
- **akajjou** — akajjou@student.42.fr

---

## Requirements

### Operating System
Linux (the project uses the Linux version of MiniLibX which links against X11).

### Dependencies

| Dependency | Purpose |
|---|---|
| `cc` (gcc / clang) | C compiler |
| `make` | Build system |
| **MiniLibX** (`mlx`) | 42's tiny graphics library (must be installed system-wide as `libmlx`) |
| `libX11`, `libXext` | X Window System (usually provided by `libx11-dev`, `libxext-dev`) |
| `libm` | Math library (standard, always present) |

#### Installing dependencies on Ubuntu / Debian

```bash
sudo apt-get update
sudo apt-get install gcc make libx11-dev libxext-dev
```

MiniLibX must be compiled from source and installed separately (follow the instructions at [42Paris/minilibx-linux](https://github.com/42Paris/minilibx-linux)).

---

## Building

```bash
git clone https://github.com/Nour-Eddin-01/cub3D.git
cd cub3D
make
```

This produces the `cub3d` executable in the project root.

Additional make targets:

| Target | Description |
|---|---|
| `make` / `make all` | Build the project |
| `make clean` | Remove object files |
| `make fclean` | Remove object files **and** the `cub3d` binary |
| `make re` | Full rebuild (`fclean` + `all`) |

---

## Running

```bash
./cub3d <path/to/map.cub>
```

### Example

```bash
./cub3d maps/good/subject_map.cub
```

The game opens a **1500 × 900** window.

---

## Controls

| Key | Action |
|---|---|
| `W` | Move forward |
| `S` | Move backward |
| `A` | Strafe left |
| `D` | Strafe right |
| `←` Left arrow | Rotate left |
| `→` Right arrow | Rotate right |
| Mouse move | Look left / right |
| `Esc` | Quit |

---

## Map Format (`.cub` files)

Maps are plain-text files with the `.cub` extension.  
The file has two sections: a **configuration header** followed by the **map grid**.

### Configuration identifiers

Each identifier occupies its own line (leading/trailing whitespace is allowed).

| Identifier | Value | Description |
|---|---|---|
| `NO` | `<path>.xpm` | Texture for **North**-facing walls |
| `SO` | `<path>.xpm` | Texture for **South**-facing walls |
| `WE` | `<path>.xpm` | Texture for **West**-facing walls |
| `EA` | `<path>.xpm` | Texture for **East**-facing walls |
| `F` | `R,G,B` | Floor color (0–255 each channel) |
| `C` | `R,G,B` | Ceiling color (0–255 each channel) |

All six identifiers **must** appear exactly once before the map.

### Map grid

After the configuration block, the grid is defined using these characters:

| Character | Meaning |
|---|---|
| `1` | Wall |
| `0` | Empty floor (walkable) |
| `N` | Player start position, facing **North** |
| `S` | Player start position, facing **South** |
| `E` | Player start position, facing **East** |
| `W` | Player start position, facing **West** |
| ` ` (space) | Outside the map (treated as void) |

**Rules:**
- The map must be enclosed by walls on all sides (no open edges).
- Exactly **one** player start character is required.
- The map must be at least 3×3 tiles.
- The `.cub` file must end with the map (nothing after the map grid).
- Rows can have different lengths; shorter rows are padded with spaces internally.

### Minimal valid example

```
NO textures/wolfenstein/grey_stone.xpm
SO textures/wolfenstein/purple_stone.xpm
WE textures/wolfenstein/red_brick.xpm
EA textures/wolfenstein/wood.xpm

F 220,100,0
C 225,30,0

111111
100001
1000N1
100001
111111
```

Sample maps (both valid and invalid) are provided in `maps/good/` and `maps/bad/`.

---

## Project Structure

```
cub3D/
├── Includes/
│   └── cub3d.h          # Main header — all structs, macros, prototypes
├── main.c               # Entry point
├── Makefile
│
├── parse/               # Map and config file parsing (parse_1.c … parse_7.c)
├── start_game/          # Game initialisation, texture loading, minimap
│   ├── cub3d.c          # MLX window setup, event hooks, game loop
│   ├── textures.c       # Texture loader (XPM → mlx image)
│   └── minimap.c        # Minimap renderer
├── ray_cast/            # Raycasting engine
│   ├── cast_rays.c
│   └── cast_rays_1.c
├── rendering/
│   └── render_wall.c    # Wall drawing with texture mapping + floor/ceiling
├── mouvements/
│   └── mouve.c          # Player movement, rotation, keyboard/mouse handling
├── error/
│   └── error.c          # Error printing helpers
├── gar_co/
│   └── gar_co.c         # Custom memory allocator / garbage collector
├── get_next_line/       # GNL helper (reads file line by line)
├── libft/               # 42 standard C library (libft.a)
│
├── maps/
│   ├── good/            # Valid test maps
│   └── bad/             # Invalid maps (for error-handling tests)
└── textures/
    ├── wolfenstein/     # Classic Wolfenstein-style wall textures (.xpm)
    ├── simonkraft/      # Alternative Minecraft-style textures (.xpm)
    ├── dyawli/          # Misc textures (.xpm)
    └── test/            # Test textures for map validation
```

---

## Engine Details

### Raycasting

For each vertical column of pixels on screen one ray is cast from the player position. The engine uses **DDA (Digital Differential Analysis)** to step through the map grid and find the first wall hit. The perpendicular distance to the hit is used to determine the height of the wall slice drawn on screen, producing the perspective-correct 3D view.

### Constants (configurable in `Includes/cub3d.h`)

| Macro | Default | Description |
|---|---|---|
| `S_W` | `1500` | Window width in pixels |
| `S_H` | `900` | Window height in pixels |
| `TILE_SIZE` | `30` | Map tile size (used for raycasting grid) |
| `FOV` | `60` | Horizontal field of view in degrees |
| `R_SPEED` | `0.020` | Rotation speed (radians per frame) |
| `P_SPEED` | `2` | Player movement speed (pixels per frame) |

---

## Troubleshooting

| Problem | Solution |
|---|---|
| `Error: Failed to initialize MLX` | MiniLibX is not installed or the X server is not running. Check that `libmlx` is installed and that a display is available (`echo $DISPLAY`). |
| `Error: Failed to load texture` | The texture path in the `.cub` file is wrong or the file is missing. Paths are relative to the directory where `cub3d` is run. |
| `Error: Bad extension` | The map file must have a `.cub` extension. |
| `Error: The Map Is Not Valid` | The map is not properly enclosed by walls, contains forbidden characters, has multiple/no player start positions, or the map section is not last in the file. Check `maps/bad/` for examples of each error case. |
| `Error: Invalid file format` | The `.cub` file is missing a required identifier (`NO`, `SO`, `WE`, `EA`, `F`, or `C`), has duplicates, or the color values are outside the 0–255 range. |
| Compilation fails with `-lmlx` not found | Install MiniLibX and ensure the library is in `/usr/lib`. Alternatively, adjust the `MLX` variable in the `Makefile`. |
| Black screen / wrong textures | Verify the `.xpm` texture files exist at the paths specified in your `.cub` file. |

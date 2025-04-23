# So_Long

## About

So_Long is a 2D game developed as part of the 42 School curriculum. The game is built using the MiniLibX library and challenges players to collect all collectibles before reaching the exit, while potentially avoiding enemies.

## Game Features

-   Player movement in four directions
-   Collectible items (coins) that must be gathered
-   Exit point that becomes accessible after all collectibles are collected
-   Wall obstacles that restrict movement
-   Character animations for enhanced gameplay experience
-   Enemy characters with movement patterns (in bonus version)
-   Bombs with explosion animations (in bonus version)

## Project Structure

```
./
├── bonus/            # Enhanced version with additional features
├── include/          # Header files
├── libft/            # Custom C library with various utilities
│   ├── bonus/        # Linked list implementations
│   ├── ft_printf/    # Custom printf implementation
│   └── gnl/          # Get Next Line for file reading
├── maps/             # Game maps in .ber format
├── minilibx-linux/   # Graphics library
├── src/              # Source code for the base game
└── textures/         # Game sprites and images
    ├── background/
    ├── bombs/
    ├── box/
    ├── coins/
    ├── enemy/
    ├── exit/
    ├── player/
    └── wall/

```
## Installation & Usage

### Prerequisites

-   GCC compiler
-   Make
-   X11 development libraries

### Installing MiniLibX

If you don't have MiniLibX installed, you'll need to install the required dependencies first:

```bash
# For Debian/Ubuntu
sudo apt-get update
sudo apt-get install gcc make xorg libxext-dev libbsd-dev

# For CentOS/RHEL/Fedora
sudo dnf install gcc make xorg-x11-server-devel libXext-devel libbsd-devel

# For macOS (using Homebrew)
brew install xquartz
```

### Compilation

To compile the basic version:

```bash
make
```

To compile the bonus version with additional features:

```bash
make bonus
```

### Running the Game

```bash
./so_long maps/map.ber
```

or for the bonus version:

```bash
./so_long_bonus maps/map.ber
```

### Map Format

Maps are defined in `.ber` files with the following elements:

-   `1` for walls
-   `0` for empty space
-   `P` for player starting position
-   `C` for collectibles
-   `E` for exit
-   `X` for enemies (bonus version only)

Example map:

```
1111111111111
10010000000C1
1000011111001
1P0011E000001
1111111111111
```

### Controls

-   `W` or Up Arrow: Move up
-   `A` or Left Arrow: Move left
-   `S` or Down Arrow: Move down
-   `D` or Right Arrow: Move right
-   `ESC`: Exit the game

## Bonus Features

The bonus version includes:

-   Enemy patrols that can end the game on contact
-   Bomb placement and explosions
-   Player movement counter displayed in the window
-   Smooth animations for all game elements
-   Multiple textures for visual enhancements

## Development

This project demonstrates skills in:

-   Graphics programming with MiniLibX
-   Memory management in C
-   Game logic implementation
-   File parsing and validation
-   Animation and sprite rendering
-   Event handling in a graphical environment

## Credits

Developed as part of the 42 School curriculum.

## License

This software is provided under the terms of the 42 School license.


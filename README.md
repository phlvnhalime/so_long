# so_long

A 2D game built using the MiniLibX Graphics Library, featuring textures, sprites, and maps.

---

## Index
- [What is so_long?](#what-is-so_long)
- [Requirements](#requirements)
- [How does it work?](#how-does-it-work)
- [Maps](#maps)
- [Controls](#controls)
- [How do I test it?](#how-do-i-test-it)
- [42 Cursus](#42-cursus)
- [Author](#author)

---

## What is so_long?

The `so_long` project is the fifth assignment in the 42 programming curriculum. It is the first graphical project and allows students to select from three options: FdF, Fractol, or so_long. All three projects introduce graphical programming, but so_long focuses on developing a 2D top-down game from scratch using the MiniLibX graphical library.

Key challenges include:
- Validating maps provided as arguments.
- Managing memory and preventing leaks.
- Engineering game mechanics, including event handling and sprite animations.
- Creating and managing graphical windows and rendering textures.

---

## Requirements

The project must adhere to the 42 "Norm" standards, which impose constraints such as:
- Functions with a maximum of 25 lines.
- Lines with a maximum of 80 characters, including comments.
- No use of prohibited constructs like `for`, `do...while`, `switch`, `goto`, ternary operators, or VLAs.

Norm compliance can be checked using the [norminette](https://github.com/42School/norminette) tool.

---

## How does it work?

### Compilation

To compile the project, run:
```
make
```

### Running the Game

Run the game executable with a valid `.ber` map:
```
./so_long maps/valid_map_2.ber
```

---

## Maps

The game reads `.ber` files to generate maps. These files must:
- Be rectangular.
- Be surrounded by walls (`1`).
- Contain at least one exit (`E`), one collectible (`C`), and one player start (`P`).

### Valid Characters

| Character | Object       |
|-----------|--------------|
| `1`       | Wall         |
| `0`       | Floor        |
| `C`       | Collectible  |
| `E`       | Exit         |
| `P`       | Player       |


Examples of valid maps are located in the `maps/` directory.

---

## Controls

| Key          | Action             |
|--------------|--------------------|
| `W` or ⬆️    | Move up           |
| `A` or ⬅️    | Move left         |
| `S` or ⬇️    | Move down         |
| `D` or ➡️    | Move right        |
| `Q` or `Esc` | Quit the game     |

The game ends when all collectibles are gathered, and the player reaches the exit. The game can be exited at any time by pressing `Q` or `Esc`, or clicking the red window close button.

---

## How do I test it?

1. Ensure the MLX42 library is installed.
2. Uncommand the 'atexit' function in the main function and checkleaks function above it.
2. Then compile the project using `make`.
3. Use provided `.ber` files in the `maps/` folder to test the game.
4. When you close the window, you can see the report of program.

```
leaks Report Version: 4.0
Process 55691: 41378 nodes malloced for 20406 KB
Process 55691: 0 leaks for 0 total leaked bytes.
```
---

## 42 Cursus

This project is part of the 42 curriculum, designed to teach low-level programming and graphical programming using C and MiniLibX.

---

## Author

Developed by [Halime P.](https://github.com/phlvnhalime) as part of the 42 programming school curriculum.

Repository: [so_long](https://github.com/phlvnhalime/so_long)


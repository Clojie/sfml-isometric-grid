# Isometric Grid

Animated isometric tile grid with a ripple wave effects. Written in C++ using SFML. Made this to practice SMFL and isometric rendering. 

## Requirements

- [SFML 2](https://www.sfml-dev.org/)
- A C++17 compiler

## Build & Run

### macOS (Apple Silicon)

Install SFML via Homebrew:

```bash
arch -arm64 brew install sfml@2
```

Then build and run:

```bash
make run
```

| Command      | Action             |
| ------------ | ------------------ |
| `make`       | Compile only       |
| `make run`   | Compile and launch |
| `make clean` | Remove the binary  |

### Windows
1. Download [SFML 2 for MinGW](https://www.sfml-dev.org/download/sfml/2.6.2/)
2. Compile:
   ```bash
   g++ main.cpp -IC:\SFML\include -LC:\SFML\lib -lsfml-graphics -lsfml-window -lsfml-system -o isometric_grid.exe
   ```
3. Copy the SFML `.dll` files next to `isometric_grid.exe` and run it.

> **Note:** Make sure `resources/block.png` is in the same directory as the executable when you run it.

## How It Works

Each frame, every tile at grid position $(c, r)$ is placed using an isometric projection and displaced by a radial sine wave.

### Wave

A donut-shaped ripple emanates from the grid center, where $d$ is the distance from the center tile and $t$ is the frame number:

$$\text{wave}(c, r, t) = 30\sin\!\left(\frac{\sqrt{10}}{5}\,d - \frac{t}{20}\right) + 30, \quad d = \sqrt{(c-25)^2 + (r-25)^2}$$

### Isometric Projection

Grid coordinates are mapped to screen pixels using a standard isometric transform:

$$x_{\text{screen}} = 8(c - r) + 400$$

$$y_{\text{screen}} = 4(c + r) + 200 + \text{wave}(c, r, t)$$

### Color

The wave amplitude drives the green and blue channels, while red stays fixed:

$$R = 255, \quad G = B = 4 \cdot \text{wave}(c, r, t)$$

Tiles fade from **red** at wave troughs to **white** at peaks.

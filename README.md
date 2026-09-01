# Isometric Grid

An animated isometric tile grid written in C++ using SFML. A radial sine wave ripples outward from the center of the grid, displacing tiles vertically and shifting their color in real time.

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

**Option 1 — Visual Studio**

1. Download [SFML 2 for MSVC](https://www.sfml-dev.org/download/sfml/2.6.2/) and extract it (e.g. to `C:\SFML`).
2. Create a new **Empty C++ Project** in Visual Studio and add `main.cpp`.
3. Under **Project → Properties**:
   - **C/C++ → Additional Include Directories:** `C:\SFML\include`
   - **Linker → Additional Library Directories:** `C:\SFML\lib`
   - **Linker → Additional Dependencies:** `sfml-graphics.lib;sfml-window.lib;sfml-system.lib`
4. Copy the SFML `.dll` files from `C:\SFML\bin` into the same folder as the built `.exe`.
5. Build and run with **`Ctrl+F5`**.

**Option 2 — MinGW (g++)**

1. Download [SFML 2 for MinGW](https://www.sfml-dev.org/download/sfml/2.6.2/) and extract it.
2. Compile:
   ```bash
   g++ main.cpp -IC:\SFML\include -LC:\SFML\lib -lsfml-graphics -lsfml-window -lsfml-system -o isometric_grid.exe
   ```
3. Copy the SFML `.dll` files next to `isometric_grid.exe` and run it.

> **Note:** In both cases, make sure `resources/block.png` is in the same directory as the executable when you run it.

## How It Works

Each frame, every tile at grid position $(c, r)$ is placed using an isometric projection and displaced by a radial sine wave.

### Wave

A donut-shaped ripple emanates from the grid center, where $d$ is the distance from the center tile and $t$ is the frame number:

$$\text{wave}(c, r, t) = 30\sin\!\left(\frac{\sqrt{10}}{5}\,d - \frac{t}{50}\right) + 30, \quad d = \sqrt{(c-25)^2 + (r-25)^2}$$

### Isometric Projection

Grid coordinates are mapped to screen pixels using a standard isometric transform:

$$x_{\text{screen}} = 8(c - r) + 400$$

$$y_{\text{screen}} = 4(c + r) + 200 + \text{wave}(c, r, t)$$

### Color

The wave amplitude drives the green and blue channels, while red stays fixed:

$$R = 255, \quad G = B = 4 \cdot \text{wave}(c, r, t)$$

Tiles fade from **red** at wave troughs to **white** at peaks.

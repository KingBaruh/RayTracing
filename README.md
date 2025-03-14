# Raytracing Simulation with SDL

This project is a simple 2D raytracing simulation using SDL2. It visualizes rays emanating from a light source and interacting with an obstacle.

## Features

- A moving light source controlled by the mouse.
- Rays cast from the light source, stopping upon hitting an obstacle.
- A dynamic obstacle that moves up and down in the scene.
- Frame rate control to maintain a smooth experience (\~60 FPS).

## Dependencies

To compile and run this project, you need:

- SDL2 library
- C compiler (e.g., `gcc`)

## Installation & Compilation

1. Install SDL2:

   - On Linux (Ubuntu/Debian):
     ```sh
     sudo apt-get install libsdl2-dev
     ```
   - On macOS:
     ```sh
     brew install sdl2
     ```
   - On Windows, download and install SDL2 from [https://www.libsdl.org/](https://www.libsdl.org/).

2. Compile the program:

   ```sh
   gcc -o raytracing main.c -lSDL2 -lm
   ```

3. Run the program:

   ```sh
   ./raytracing
   ```

## Controls

- **Mouse movement**: Move the light source around.
- **Close button**: Exit the program.

## Code Overview

- `FillCircle`: Draws a filled circle on the screen.
- `generate_rays`: Generates rays from the light source in all directions.
- `FillRays`: Simulates the rays moving outward until they hit an obstacle.
- `main`: Handles SDL initialization, event loop, rendering, and cleanup.

## License

This project is released under the MIT License.



# AsteroidGraphicsOPENGL

[](https://isocpp.org/)
[](https://www.opengl.org/)

**AsteroidGraphicsOPENGL** is a C++ visualization engine developed to render and simulate the trajectory of asteroids. Utilizing Cartesian coordinates derived from asteroid surface data, this project provides a 3D graphical representation of celestial bodies, originally developed as part of an undergraduate thesis.

## Project Overview

The primary goal of this software is the high-fidelity visualization of asteroid models. By processing surface coordinate data, the engine reconstructs the asteroid's geometry and maps its movement within a simulated spatial environment.

### Key Features

  * **Surface Reconstruction:** Renders complex asteroid topologies using Cartesian coordinate sets.
  * **Trajectory Visualization:** Simulates and displays the orbital path of the celestial body.
  * **OpenGL Pipeline:** Utilizes modern OpenGL for efficient real-time 3D rendering.
  * **Linear Interpolation:** (Optional/Related) Integration with surface interpolation methods for smoother mesh generation.

-----

## Technical Stack

  * **Language:** C++
  * **Graphics API:** OpenGL
  * **Windowing/Context:** GLFW or GLUT (Depending on specific implementation)
  * **Math Library:** GLM (OpenGL Mathematics)
  * **Build System:** CMake

-----

## Research Context

This project served as a visualization tool for my undergraduate physics thesis. It explores the intersection of computer graphics and orbital mechanics, specifically focusing on how discrete coordinate data can be translated into a performant 3D model for astronomical analysis.

-----

## Getting Started

### Prerequisites

Ensure you have a C++ compiler (GCC, Clang, or MSVC) and the following libraries installed:

  * **OpenGL 3.3+**
  * **GLFW** (Development headers)
  * **GLEW** or **GLAD** (Extension loader)
  * **GLM** (Mathematics library)

#### On Ubuntu/Debian:

```bash
sudo apt-get update
sudo apt-get install libglfw3-dev libglew-dev libglm-dev
```

### Installation

1.  **Clone the Repository:**

    ```bash
    git clone https://github.com/SyNikolai/AsteroidGraphicsOPENGL.git
    cd AsteroidGraphicsOPENGL
    ```

2.  **Build the Project:**
    This project uses CMake for cross-platform compatibility.

    ```bash
    mkdir build
    cd build
    cmake ..
    make
    ```

3.  **Run the Executable:**

    ```bash
    ./AsteroidGraphics
    ```

-----

## Usage

Upon launching, the application will initialize an OpenGL window.

  * **Data Input:** The application typically reads asteroid surface data (often in `.txt` or `.csv` format) containing $(x, y, z)$ coordinates. Ensure the data files are located in the designated `/data` directory.
  * **Controls:** (Standard defaults)
      * **WASD / Arrow Keys:** Navigate the camera.
      * **Mouse Move:** Rotate the view.
      * **Scroll:** Zoom in/out.

-----

## Project Structure

```text
AsteroidGraphicsOPENGL/
├── src/                # C++ Source files (.cpp)
├── include/            # Header files (.h)
├── shaders/            # GLSL Vertex and Fragment shaders
├── data/               # Coordinate data for asteroid models
├── CMakeLists.txt      # Build configuration
└── README.md           # Documentation
```



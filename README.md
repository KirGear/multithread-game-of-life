# Multithreaded Game of Life

A multithreaded C++ implementation of **Conway's Game of Life** with **OpenGL shader visualization**.
![image](https://github.com/user-attachments/assets/a83a8c1a-1360-4071-8fbf-f7d76f1aba65)

## Features
- **Multithreading**: Uses multiple threads for grid computation.
- **OpenGL Visualization**: Renders the game grid using fragment shaders.

## Default Settings
- **Threads**: 7 worker threads (+1 main thread)
- **Grid Size**: 400 x 300
- **Resolution**: 1200 x 900
- **Iteration Frequency**: 10 iterations per second (100ms delay)

You can change these values in `params.h`.

## Controls
- **Mouse Wheel**: Zoom in/out.
- **Left Mouse Button**: Drag to pan.
- **Space**: Pause or resume the simulation.
- **R**: Restart the simulation.
- **+/-**: Adjust game speed (increase or decrease by 10%).

## Building
Use **Visual Studio** to build and run the project.

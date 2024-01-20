# Game Development Basics with SDL and Raycasting

## Introduction

This is a simple repo to show how to use SDL to create a simple game. The game is a simple raycasting engine that uses the SDL library to render the game. It includes simple files that show how to use SDL features such as rendering images, playing sounds, and handling keyboard input.

## Requirements

To build and run this project, you will need the following libraries:
* SDL2
* SDL2_image
* SDL2_mixer
* SDL2_ttf

To install these libraries on Ubuntu, run the following command:

```bash
sudo apt install libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev
```

## Customize the Project

To edit the project, you will need the following tools:
* make
* gcc
* g++
* IDE of your choice

Edit the makefile to change the name of the output file at `OBJS` and `OBJ_NAME` to customize the name of the output file. Inlcude any additional source files in the `OBJS` variable. Include any additional linker flags in the `LINKER_FLAGS` variable such as `-lSDL2_image` or `-lSDL2_mixer`.

## Building

To build the project, run the following commands:

```
make all
```

## Running

To run the project, run the following command:

```bash
./<output_of_make> # ./game
```
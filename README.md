# 42 project: FdF (Wireframe Renderer)
FdF is a 3D wireframe renderer that displays a 3D map of a landscape in the form of a wireframe. It is implemented in C using the minilibx library, which is a simple and fast 2D graphics library provided by our school.

# Usage

## Run
To run the program, simply execute the following command in your terminal:

```bash
make
./fdf <map_file>
```
The map_file should be a valid map file that contains the 3D coordinates of the landscape. The file should have the following format:

```shell
$ cat test_maps/42.fdf
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0 10 10  0  0 10 10  0  0  0 10 10 10 10 10  0  0  0
0  0 10 10  0  0 10 10  0  0  0  0  0  0  0 10 10  0  0
0  0 10 10  0  0 10 10  0  0  0  0  0  0  0 10 10  0  0
0  0 10 10 10 10 10 10  0  0  0  0 10 10 10 10  0  0  0
0  0  0 10 10 10 10 10  0  0  0 10 10  0  0  0  0  0  0
0  0  0  0  0  0 10 10  0  0  0 10 10  0  0  0  0  0  0
0  0  0  0  0  0 10 10  0  0  0 10 10 10 10 10 10  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
```
Where each line represents a point in the 3D space, with x, y, z coordinates. An optional RGB color of the point can be specified after the coordinates as follow `10xFF00FF`.

## Commands

The program supports zooming, translation, and rotation of the map using the mouse.

+ `Scroll` - zoom in / out
+ `Left click` and drag - translate the map in the corresponding direction
+ `Right click` and drag - rotate the map around the x-axis
+ `Middle click` - switch between isometric and military projections.
+ `r` - reset the map to its original rotation
+ `+` / `-` - change the height scale.

# Credits
This project was developed by [valentinValep](https://github.com/valentinValep) as part of the curriculum at [École 42](https://42.fr/). The project was completed using the C programming language and the minilibx library.
# cub3D

<img src="img/cub3D.png" alt="cover"/>
Raycasting project (21-school / Ecole 42)


How it looks:

<img src="img/cub3D.gif" alt="gameplay"/>

## Setup and usage

```
git clone https://github.com/kukinpower/cub3D.git
cd cub3D/cub3D
make
./cub3D map.cub
```

### Controls
```
W A S D					move
←					turn left
→					turn right
```
### Configuration file `map.cub`
```
Config file called `map.cub`

R 					resolution
C					ceiling rgb color
F					floor rgb color
NO SO WE EA				paths to textures
S					path to sprite
					empty lines

valid map is surrounded by walls (1) and can contain these characters
1					wall
0					player can move here
2					sprite/item
N S E W					player position and view direction
space					empty space (player can't see them)

map can't be splitted by empty lines
```
Example of a valid config file:
<img src="img/conf.png" alt="valid configuration file"/>

## 🕵🏽‍♀️ Research

### Core

I built the graphics engine using this guide: [Lode's Computer Graphics Tutorial](https://lodev.org/cgtutor/raycasting.html)

And peer2peer communication

### Maths

* [Vector intro for linear algebra](https://www.khanacademy.org/math/linear-algebra/vectors-and-spaces/vectors/v/vector-introduction-linear-algebra)
* [Linear combinations and span](https://www.khanacademy.org/math/linear-algebra/vectors-and-spaces/linear-combinations/v/linear-combinations-and-span)
* [Rotation matrix](https://en.wikipedia.org/wiki/Rotation_matrix)

### Graphics
* [Lode's Computer Graphics Tutorial Raycasting](https://lodev.org/cgtutor/raycasting.html)
* [🎥 DDA Line Drawing Algorithm](https://www.youtube.com/watch?v=W5P8GlaEOSI)

### Generate BMP
* [Generate BMP on clean C](https://stackoverflow.com/a/47785639)
* [Man open()](https://man7.org/linux/man-pages/man2/open.2.html)
* [O_CREAT mode argument](https://stackoverflow.com/a/28466757)
### Others (not used in final project)
* [🎥 Bresenham's Line Drawing Algorithm](https://www.youtube.com/watch?v=RGB-wlatStc)


### Texture credits
* Art: [Wassily Kandinsky](https://en.wikipedia.org/wiki/Wassily_Kandinsky)
* Lego: <span>Photo by <a href="https://unsplash.com/@omarg247?utm_source=unsplash&amp;utm_medium=referral&amp;utm_content=creditCopyText">Omar Flores</a> on <a href="https://unsplash.com/s/photos/lego?utm_source=unsplash&amp;utm_medium=referral&amp;utm_content=creditCopyText">Unsplash</a></span>
* Pink bricks: <span>Photo by <a href="https://unsplash.com/@pawel_czerwinski?utm_source=unsplash&amp;utm_medium=referral&amp;utm_content=creditCopyText">Paweł Czerwiński</a> on <a href="https://unsplash.com/s/photos/pink-brick?utm_source=unsplash&amp;utm_medium=referral&amp;utm_content=creditCopyText">Unsplash</a></span>
* Binary: [me](https://twitter.com/Kukinpower)
* Coin: [https://creazilla.com/nodes/60815-golden-dollar-coin-clipart](https://creazilla.com/nodes/60815-golden-dollar-coin-clipart)
* Crate: [MostafaElTurkey36](https://pixabay.com/vectors/box-crate-wooden-box-wooden-wood-4989961/)

# Author
## Roman Kukin
developer <br/> school 21 (Ecole 42) student

[linkedin](https://www.linkedin.com/in/roman-kukin/)
<span style="margin: 50px">[github](https://github.com/kukinpower)</span>
[twitter](http://twitter.com/kukinpower)

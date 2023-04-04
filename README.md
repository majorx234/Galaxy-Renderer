[![GitHub issues](https://img.shields.io/github/issues/beltoforion/Galaxy-Renderer.svg?maxAge=360)](https://github.com/beltoforion/Galaxy-Renderer/issues)
[![Version](https://img.shields.io/github/release/beltoforion/Galaxy-Renderer.svg?maxAge=360)](https://github.com/beltoforion/Galaxy-Renderer/blob/master/CHANGELOG)
[![Github All Releases](https://img.shields.io/github/downloads/beltoforion/Galaxy-Renderer/total.svg)](https://github.com/beltoforion/Galaxy-Renderer/releases/tag/v1.1.0)

# Fork of Spiral Galaxy Renderer
- add cmake build 
- added CLI with fullscreen-mode

## dependencies:
- install sdl2, sdl2_ttf, glm, consolas-font

## ToDo
- add assets
- better check for some dependencies (better info message)

# Info
A Program for modelling a two dimensional galaxy based on the density wave theory. This archive contains the source code for an 
article at beltoforion.de about Simulating a Galaxy with the density wave theory.

For more Details please read the Articles.

* https://beltoforion.de/en/spiral_galaxy_renderer [english]
* https://beltoforion.de/de/rendern_von_spiralgalaxien [german]

A typescript implementation of this code is available here:

* https://github.com/beltoforion/Galaxy-Renderer-Typescript

An online demo of the typescript version can be viewed here:

* https://beltoforion.de/en/spiral_galaxy_renderer/spiral-galaxy-renderer.html

The output of the C++ version is virtually the same.

![galaxy-renderer-cpp](https://user-images.githubusercontent.com/2202567/183997359-e4480044-986e-445d-935c-a50d55db21f3.jpg)

Hers is a list of galaxies created by the algorithm:
![galaxy-renderer-overview](https://user-images.githubusercontent.com/2202567/183997403-eff97429-b0d2-4933-a49e-ac16e0cab27c.jpg)

-----------

For old system or GPU unsupported OpenGL 3.3 use overload MESA version for running application.
In Linux.
```
MESA_GL_VERSION_OVERRIDE=3.3 MESA_GLSL_VERSION_OVERRIDE=330 ./galaxy_rendere
```


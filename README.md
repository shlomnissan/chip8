# 👾 Chip-8

This repository contains an implementation of a Chip-8 interpreter written in modern C++. It supports the complete set of the standard Chip-8 instructions with unit tests but doesn't include support for Super Chip-48.

![invaders](https://user-images.githubusercontent.com/3165988/192060358-899a1318-2888-43eb-9905-a89ece4d6244.gif)

## Dependencies
All the dependencies are included in this repository as submodules.
- [SDL2](https://github.com/libsdl-org/SDL) - Graphics, audio, input
- [gflags](https://github.com/gflags/gflags) - Parsing command line arguments 
- [GoogleTest](https://github.com/google/googletest) - Unit testing

## Building with CMake
```
$ git clone https://github.com/shlomnissan/chip8.git
$ cd chip8
$ git submodule update --init # download dependencies
$ mkdir build
$ cd build
$ cmake ..
$ make
```
If the build was successful, the build folder should contain the `chip8` executable. 

## Usage

```
chip8 -rom roms/invaders.c8 -cycles_per_sec 10
```
- `-rom` path to a valid Chip-8 program (required)
- `-cycles-per-sec` cycles per second (optional, default value: 10)

## MIT licence
```
Copyright (c) 2022 Shlomi Nissan

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
```


Dependencies:
* C++17
* SDL2
* SDL2 mixer
* SDL2 image
* SDL2 ttf
* sqlite
* curl

Cloning the code:
```
git clone git@github.com:Ponup/thiefcatcher.git
git submodule update --init
```

How to build on Windows:

```
cmake -G "Visual Studio 14 2015" .
```

How to build on Linux/Macos:

```
cmake .
make
```

If you want to build with debug symbols use:
```
cmake -DCMAKE_BUILD_TYPE=debug
```


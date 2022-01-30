
Dependencies:
* CMake
* conan
* C++17
* SDL2
* SDL2 mixer
* SDL2 image
* SDL2 ttf
* SDL2 gfx 
* sqlite
* TinyXML2
* curl

Cloning the code:
```
git clone git@github.com:Ponup/thiefcatcher.git
git submodule update --init
```

## How to build

### ...on Windows:

```shell
cmake -G "Visual Studio 14 2015" .
```

### ...on Linux/Macos:

```shell
cmake .
make
```

If you want to build with debug symbols use:
```
cmake -DCMAKE_BUILD_TYPE=debug
```

## How to run

```shell
cd Core
pushd dev && ./create_db.sh && cp game.db ../data/ && popd
bin/ThiefCatcher
```

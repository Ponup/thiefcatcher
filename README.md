
Dependencies:
* CMake (3.25 or greater)
* conan (2.11.0 or greater)
* C++ 23
* SDL2
* SDL2 mixer
* SDL2 image
* SDL2 ttf
* SDL2 gfx 
* sqlite3
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
cmake -G "Visual Studio 17 2022" .
```

### ...on Linux/Macos:

```shell
pushd Core && conan install . && popd
cmake .
make
```

If you want to build with debug symbols use:
```
cmake -DCMAKE_BUILD_TYPE=debug .
```

## How to run

```shell
cd Core
bin/ThiefCatcher
```

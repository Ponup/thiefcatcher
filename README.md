
Cloning the code:
```
git clone git@github.com:Ponup/thiefcatcher.git
git submodule update --init
```

How to build in Windows:

```
cmake -G "Visual Studio 14 2015"
```

How to build on Linux:

```
cmake .
make
```

If you want to build with debug symbols use:
```
cmake -DCMAKE_BUILD_TYPE=debug
```


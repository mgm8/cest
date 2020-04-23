# CEST - Centroid Extractor for Star Trackers

<img align="left" width="400" height="300" src="https://raw.githubusercontent.com/mgm8/cest/master/doc/stars-image.png"> <img align="right" width="400" height="300" src="https://raw.githubusercontent.com/mgm8/cest/master/doc/stars-image-centroids.png">

## Dependencies

To compile the library, the following dependencies are required:

* [OpenCV 4](https://opencv.org/)
* [ghdl](http://ghdl.free.fr/)
* [CMake](https://cmake.org/)

## Compilation

Execute the commands below to compile the library:

```
mkdir build
cd build
cmake ..
make -j4
```

## Installation

After compiling, execute the following command:

```
sudo make install
```

## Running the simulation

To run the simulation, an image must be passed as argument:

```
./csim image.png
```

> NOTE: For now, the image resolution must be 800x600.

## License

This software is licensed under GPL license, version 3.

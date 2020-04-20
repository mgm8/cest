# CEST - Centroid Extractor for Star Trackers

## Dependencies

To compile and run the simulation, the following dependencies are required:

* [OpenCV 3](https://opencv.org/)
* [ghdl](http://ghdl.free.fr/)
* [CMake](https://cmake.org/)

## Compilation

Execute the commands below to compile the simulation:

```
mkdir build
cd build
cmake ..
make -j4
```

## Running the simulation

To run the simulation, an image must be passed as argument:

```
./csim image.png
```

> NOTE: For now, the image resolution must be 800x600.

## License

This software is licensed under GPL license, version 3.

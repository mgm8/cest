# CEST - Centroid Extractor for Star Trackers

## Summary

CEST (Centroid Extractor for Star Trackers) is an algorithm for identifying and determining the stars centroid in an image without storing the entire captured image and without the need for external memories or buffer. By implementeing CEST using dedicated hardware, it is possible to reduced the complexity of the processing steps of the captured images.

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

## Example

<p align="center">
<img src="https://raw.githubusercontent.com/mgm8/cest/master/doc/result-demo.png">
</p>

## License

This software is licensed under LGPL license, version 3.

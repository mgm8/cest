# CEST - Centroid Extractor for Star Trackers

## Summary

CEST (Centroid Extractor for Star Trackers) is a library to detect stars and its centroids in a starry sky image. This library was developed to be used in star trackers sensors present in satellites and rockets.

The algorithm developed on this library has the advantage of detect the centroids in a pixel streaming, without storing the entire captured image and without the need for external memories or buffer. This characteristic improves the performance considerably.

It is possible to reduced the complexity of the processing steps of the captured images and the overall performance of a star tracker sensor, by implementing it using dedicated hardware. A VHDL example simulating an image sensor interface is also provided

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

## Example

To run the available example, after the compilation, execute the following command:

```
./cest-example <star-image>
```

Where ```<star-image>``` could be any starry sky image (the file [stars-image.png](https://github.com/mgm8/cest/blob/master/doc/stars-image.png) from the [doc](https://github.com/mgm8/cest/tree/master/doc) directory can be used).

After running the example with the available image example, the result can be seen below (left: original image, right: results with the detected stars and position index according to its brightness).

<p align="center">
<img src="https://raw.githubusercontent.com/mgm8/cest/master/doc/result-demo.png">
</p>

## License

This software is licensed under LGPL license, version 3.

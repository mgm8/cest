/*
 * main.h
 * 
 * Copyright (C) 2020, Gabriel Mariano Marcelino <gabriel.mm8@gmail.comk>
 * 
 * This file is part of CEST library.
 * 
 * CEST library is free software: you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 * 
 * CEST library is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with CEST library. If not, see <http://www.gnu.org/licenses/>.
 * 
 */

/**
 * \brief CEST example.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.1.0
 * 
 * \date 25/04/2020
 * 
 * \defgroup example Example
 * \ingroup cest
 * \{
 */

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <cest/cest.h>

#define STAR_THRESHOLD_VALUE            150
#define GAIN_WEIGHT                     0.8
#define MAX_NUMBER_OF_CENTROIDS         60

using namespace std;
using namespace cv;
using namespace cest;

void RunSim(Mat img, StarFilter *star_filter, Centroider *centroider, const char *label)
{
    vector<StarPixel> star_pixels = star_filter->GetStarPixels(img);

    vector<Centroid> centroids = centroider->ComputeFromList(star_pixels, GAIN_WEIGHT);

    centroider->SaveCentroids("centroids.csv");

    imshow(label, centroider->PrintCentroids(img, centroids, true));
    waitKey(0);
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        cout << "No image provided!" << endl;

        return -1;
    }

    Mat img = imread(argv[1], IMREAD_GRAYSCALE);

    cout << "Running software implementation..." << endl;
    RunSim(img, new StarFilterSW(STAR_THRESHOLD_VALUE), new Centroider(MAX_NUMBER_OF_CENTROIDS), "SW Simulation Result");

    cout << "Running hardware and software implementation..." << endl;
    RunSim(img, new StarFilterHW(STAR_THRESHOLD_VALUE), new Centroider(MAX_NUMBER_OF_CENTROIDS), "HW/SW Simulation Result");

    return 0;
}

//! \} End of example group

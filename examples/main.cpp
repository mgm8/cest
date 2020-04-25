#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

#include <cest/star_pixel.hpp>
#include <cest/centroid.hpp>

#include <cest/star_filter.h>
#include <cest/star_filter_sw.h>
#include <cest/star_filter_hw.h>
#include <cest/centroider.h>

#define STAR_THRESHOLD_VALUE            150
#define KALMAN_GAIN_WEIGHT              0.8
#define MAX_NUMBER_OF_CENTROIDS         60

using namespace std;
using namespace cv;
using namespace cest;

void RunSim(Mat img, StarFilter *star_filter, Centroider *centroider, const char *label)
{
    vector<StarPixel> star_pixels = star_filter->GetStarPixels(img);

    vector<Centroid> centroids = centroider->ComputeFromList(star_pixels, KALMAN_GAIN_WEIGHT);

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

/*
 * centroider.h
 * 
 * Copyright (C) 2020, Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * This file is part of CEST library.
 * 
 * CEST library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * CEST library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with CEST library. If not, see <http://www.gnu.org/licenses/>.
 * 
 */

/**
 * \brief Centroid computation definition.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.1.0
 * 
 * \date 06/10/2018
 * 
 * \defgroup centroider Centroider
 * \ingroup cest
 * \{
 */

#ifndef CENTROIDER_H_
#define CENTROIDER_H_

#include <vector>
#include <opencv2/opencv.hpp>

#include "cdpu.h"
#include "star_pixel.hpp"
#include "centroid.hpp"

#define CENTROIDER_DEFAULT_MAX_CDPUS                20
#define CENTROIDER_DEFAULT_DISTANCE_THRESHOLD       10

#define CENTROIDER_CDPU_DEFAULT_CORRECTION_FACTOR   0.8

/**
 * \brief Centroider class.
 */
class Centroider
{
    private:

        /**
         * \brief CDPUs list.
         */
        std::vector<CDPU> cdpus;

        /**
         * \brief Number of CDPUs.
         */
        unsigned int max_cdpus;

        /**
         * \brief Distance threshold between two pixels to become a star.
         */
        unsigned int distance_threshold;

    public:

        /**
         * \brief Class constructor.
         *
         * \return None.
         */
        Centroider();

        /**
         * \brief Class constructor.
         *
         * \param[in] n is the number of CDPUs.
         *
         * \return None.
         */
        Centroider(unsigned int n);

        /**
         * \brief Class destructor.
         *
         * \return None.
         */
        ~Centroider();

        /**
         * \brief Sets the number of CDPUs.
         *
         * \param[in] n is the new number of CDPUs.
         *
         * \return None.
         */
        void SetNumberOfCDPUs(unsigned int n);

        /**
         * \brief Sets the Manhattan distance threshold between two pixels to become a star.
         *
         * \param[in] d is the new distance threshold value.
         *
         * \return None.
         */
        void SetDistanceThreshold(unsigned int d);

        /**
         * \brief Computes a new star pixel.
         *
         * \param[in] star_pix is the star pixel to compute.
         *
         * \param[in] a is an optimal constant to minimize the centroid position error.
         *
         * \return None.
         */
        void Compute(cest::StarPixel star_pix, float a=CENTROIDER_CDPU_DEFAULT_CORRECTION_FACTOR);

        /**
         * \brief Computes the centroids from a list of star pixels.
         *
         * \param[in] stars is a list of star pixels to compute the centroids.
         *
         * \param[in] a is an optimal constant to minimize the centroid position error.
         *
         * \return A vector with all the computed centroids.
         */
        std::vector<cest::Centroid> ComputeFromList(std::vector<cest::StarPixel> stars, float a=CENTROIDER_CDPU_DEFAULT_CORRECTION_FACTOR);

        /**
         * \brief Gets the last computed centroids.
         *
         * \return A vector with all the last computed centroids.
         */
        std::vector<cest::Centroid> GetCentroids();

        /**
         * \brief Sorts a vector with centroids by their brightness.
         *
         * \param[in] centroids is a vector with unordered centroids.
         *
         * \return A vector with centroids ordered by their brightness.
         */
        std::vector<cest::Centroid> SortCentroids(std::vector<cest::Centroid> centroids);

        /**
         * \brief Resets the CDPUs.
         *
         * \return None.
         */
        void Reset();

        /**
         * \brief Prints a pack of centroids to a given image.
         *
         * \param[out] img is the image to print the list of centroids.
         *
         * \param[in] centroids is the list of centroids to print.
         *
         * \param[in] print_id is a flag to print or not the centroids ID.
         *
         * \return The result image.
         */
        cv::Mat PrintCentroids(cv::Mat img, std::vector<cest::Centroid> centroids, bool print_id=false);

        /**
         * \brief Save the detected centroids in a CSV file.
         *
         * Column 1 = Number of pixels to compute the centroid
         * Column 2 = The intensity of the centroid
         * Column 3 = The position in the x-axis
         * Column 4 = The position in the y-axis
         *
         * \param[in] file_name is the name of the CSV file to save the list of centroids.
         *
         * \return None.
         */
        void SaveCentroids(const char *file_name);
};

#endif // CENTROIDER_H_

//! \} End of centroider group

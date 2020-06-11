/*
 * cdpu.h
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
 * \brief CentroiD Processor Unit class definition.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.1.0
 * 
 * \date 05/03/2018
 * 
 * \defgroup cdpu CDPU
 * \ingroup cest
 * \{
 */

#ifndef CDPU_H_
#define CDPU_H_

#include <stdint.h>
#include <cmath>

#include "centroid.hpp"

/**
 * \brief Pixel distance threshold value (Euclidean distance).
 */
#define DISTANCE_THRESHOLD                  5

/**
 * \brief Pixel distance threshold value (Manhattan distance).
 */
#define DISTANCE_THRESHOLD_MAN              (2*sqrt(pow(DISTANCE_THRESHOLD, 2))/sqrt(2))

/**
 * \brief Default value of the optimal constant to minimize the centroid position error.
 */
#define CDPU_DEFAULT_CORRECTION_FACTOR      0.8

/**
 * \brief Class to implement a CentroiD Processor Unit.
 */
class CDPU
{
    private:

        /**
         * \brief Calculated centroid.
         */
        cest::Centroid centroid;

        /**
         * \brief Number of pixel of the centroid.
         */
        unsigned int pixels;

        /**
         * \brief Pixel weight.
         */
        float G;

    public:

        /**
         * \brief Constructor.
         *
         * \return None.
         */
        CDPU();

        /**
         * \brief Destructor.
         *
         * \return None.
         */
        ~CDPU();

        /**
         * \brief Updates the centroid estimation.
         *
         * \param[in] x_new is the x position of the new pixel of a star.
         *
         * \param[in] y_new is the y position of the new pixel of a star.
         *
         * \param[in] color_new is the color value of the new pixel of a star.
         *
         * \param[in] a is an optimal constant to minimize the centroid position error.
         *
         * \return None.
         */
        void Update(unsigned int x_new, unsigned int y_new, uint8_t color_new, float a=CDPU_DEFAULT_CORRECTION_FACTOR);

        /**
         * \brief Sets the values of the centroid.
         *
         * \param[in] x_new is the new x position reference.
         *
         * \param[in] y_new is the new y position reference
         *
         * \param[in] color_new is the new color (8-bit) value reference.
         *
         * \return None.
         */
        void SetCentroid(unsigned int x_new, unsigned int y_new, uint8_t color_new);

        /**
         * \brief Gets the final calculated centroid of a star.
         *
         * \return The estimated centroid of the given star.
         */
        cest::Centroid GetCentroid();

        /**
         * \brief Calculates the Manhattan distance from the current centroid estimation to a given point.
         *
         * \param[in] x_comp is the x-axis position of a point.
         *
         * \param[in] y_comp is the y-axis position of a point.
         *
         * \return The distance in pixels.
         */
        float DistanceFrom(unsigned int x_comp, unsigned int y_comp);

        /**
         * \brief Gets the number of pixels used to calculate the centroid parameters.
         *
         * \return The number of pixels used to calculate the centroid.
         */
        uint8_t GetPixels();
};

#endif // CDPU_H_

//! \} End of cdpu group

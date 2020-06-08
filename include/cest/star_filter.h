/*
 * star_filter.h
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
 * \brief Star filter definition.
 *
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.1.0
 * 
 * \date 04/10/2018
 * 
 * \defgroup star-filter Star Filter
 * \ingroup cest
 * \{
 */

#ifndef STAR_FILTER_H_
#define STAR_FILTER_H_

#include <vector>
#include <stdint.h>
#include <opencv2/opencv.hpp>

#include "star_pixel.hpp"

#define STAR_FILTER_DEFAULT_THRESHOLD_VAL   150         /**< Default value of the threshold filter (0 to 255). */

/**
 * \brief A class to read the star pixels from a memory region.
 */
class StarFilter
{
    protected:

        /**
         * \brief Threashold filter value.
         */
        uint8_t threshold;

    public:

        /**
         * \brief Class constructor without memory initialization.
         *
         * \return None.
         */
        StarFilter();

        /**
         * \brief Class destructor.
         *
         * \return None.
         */
        ~StarFilter();

        /**
         * \brief Sets the threshold value of the threshold filter.
         *
         * \param[in] val is the new threshold value.
         *
         * \return None.
         */
        virtual void SetThreshold(uint8_t val);

        /**
         * \brief Gets the threshold value of the threshold filter.
         *
         * \return The current threshold value.
         */
        uint8_t GetThreshold();

        /**
         * \brief Gets star pixels from a given image.
         *
         * \param[in] img is the image to search for the star pixels.
         *
         * \return A set of star pixels.
         */
        virtual std::vector<cest::StarPixel> GetStarPixels(cv::Mat img);
};

#endif // STAR_FILTER_H_

//! \} End of star-filter group

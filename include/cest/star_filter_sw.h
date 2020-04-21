/*
 * star_filter_sw.h
 * 
 * Copyright (C) 2018, Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 * 
 */

/**
 * \brief Star filter (using software) definition.
 *
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.1.0
 * 
 * \date 11/11/2018
 * 
 * \defgroup star-filter-sw Star Filter (software)
 * \{
 */

#ifndef STAR_FILTER_SW_H_
#define STAR_FILTER_SW_H_

#include "star_filter.h"

/**
 * \brief A class to filter star pixels from a image.
 */
class StarFilterSW: public StarFilter
{
    public:

        /**
         * \brief Class constructor.
         *
         * \return None.
         */
        StarFilterSW();

        /**
         * \brief Class constructor (overload).
         *
         * \param[in] thr is the threshold value.
         *
         * \return None.
         */
        StarFilterSW(uint8_t thr);

        /**
         * \brief Gets star pixels from a given image.
         *
         * \param[in] img is the image to search for the star pixels.
         *
         * \return A set of star pixels.
         */
        std::vector<cest::StarPixel> GetStarPixels(cv::Mat img);

        /**
         * \brief Gets star pixels from a given image with a custom threshold value.
         *
         * \param[in] img is the image to search for the star pixels.
         *
         * \return A set of star pixels.
         */
        std::vector<cest::StarPixel> GetStarPixels(cv::Mat img, uint8_t thr);

        /**
         * \brief Sets the threshold value of the threshold filter.
         *
         * \param[in] val is the new threshold value.
         *
         * \return None.
         */
        void SetThreshold(uint8_t val);
};

#endif // STAR_FILTER_SW_H_

//! \} End of star-filter-sw group

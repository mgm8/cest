/*
 * centroid.hpp
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
 * \brief Centroid structure.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 1.0
 * 
 * \date 10/05/2018
 * 
 * \defgroup centroid Centroid
 * \{
 */

#ifndef CENTROID_HPP_
#define CENTROID_HPP_

/**
 * \brief Star tracker namespace.
 */
namespace st
{
    /**
     * \brief Centroid structure.
     */
    class Centroid
    {
        public:

            /**
             * \brief Class constructor.
             *
             * \return None.
             */
            Centroid()
            {
                this->value     = 0;
                this->pixels    = 0;
                this->x         = 0;
                this->y         = 0;
            }

            /**
             * \brief Class constructor with initialization.
             *
             * \param[in] val is the centroid pixel value.
             * \param[in] x_pos is the x-axis position.
             * \param[in] y_pos is the y-axis position.
             *
             * return None.
             */
            Centroid(unsigned int val, double x_pos, double y_pos)
            {
                this->value     = val;
                this->pixels    = 1;
                this->x         = x_pos;
                this->y         = y_pos;
            }

            /**
             * \brief Class destructor.
             *
             * \return None.
             */
            ~Centroid()
            {

            }

            /**
             * \brief Centroid value (sum of pixel values).
             */
            unsigned int value;

            /**
             * \brief X-axis position.
             */
            double x;

            /**
             * \brief Y-axis position.
             */
            double y;

            /**
             * \brief Number of pixels used to estimate the centroid.
             */
            unsigned int pixels;
    };
}

#endif // CENTROID_HPP_

//! \} End of centroid group

/*
 * star_pixel.hpp
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
 * \brief Star pixel class.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.1.0
 * 
 * \date 04/10/2018
 * 
 * \defgroup star-pixel Star Pixel
 * \ingroup cest
 * \{
 */

#ifndef STAR_PIXEL_HPP_
#define STAR_PIXEL_HPP_

/**
 * \brief CEST namespace.
 */
namespace cest
{
    /**
     * \brief Star pixel structure.
     */
    class StarPixel
    {
        public:

            /**
             * \brief Class constructor.
             *
             * \return None.
             */
            StarPixel()
            {
                this->value = 0;
                this->x     = 0;
                this->y     = 0;
            }

            /**
             * \brief Class constructor with initialization.
             *
             * \param[in] val is the pixel value.
             *
             * \param[in] x_pos is the x-axis position.
             *
             * \param[in] y_pos is the y-axis position.
             *
             * return None.
             */
            StarPixel(unsigned int val, unsigned int x_pos, unsigned int y_pos)
            {
                this->value = val;
                this->x     = x_pos;
                this->y     = y_pos;
            }

            /**
             * \brief Class destructor.
             *
             * \return None.
             */
            ~StarPixel()
            {

            }

            /**
             * \brief Pixel value.
             */
            unsigned int value;

            /**
             * \brief X-axis position.
             */
            unsigned int x;

            /**
             * \brief Y-axis position.
             */
            unsigned int y;
    };
}

#endif // STAR_PIXEL_HPP_

//! \} End of star-pixel group

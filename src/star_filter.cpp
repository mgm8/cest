/*
 * star_filter.cpp
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
 * \brief Star filter implementation.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.1.0
 * 
 * \date 11/11/2018
 * 
 * \addtogroup star-filter
 * \{
 */

#include <cest/star_filter.h>

using namespace std;
using namespace cv;
using namespace cest;

StarFilter::StarFilter()
{

}

StarFilter::~StarFilter()
{

}

void StarFilter::SetThreshold(uint8_t val)
{
    this->threshold = val;
}

uint8_t StarFilter::GetThreshold()
{
    return this->threshold;
}

vector<StarPixel> StarFilter::GetStarPixels(Mat img)
{
    return vector<StarPixel>();
}

//! \} End of star-filter group

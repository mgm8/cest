/*
 * star_filter_sw.cpp
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with CEST library. If not, see <http://www.gnu.org/licenses/>.
 * 
 */

/**
 * \brief Star filter (using software) implementation.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.1.0
 * 
 * \date 11/11/2018
 * 
 * \addtogroup star-filter-sw
 * \{
 */

#include <cest/star_filter_sw.h>

using namespace std;
using namespace cv;
using namespace cest;

StarFilterSW::StarFilterSW()
    : StarFilter()
{

}

StarFilterSW::StarFilterSW(uint8_t thr)
    : StarFilter()
{
    this->SetThreshold(thr);
}

vector<StarPixel> StarFilterSW::GetStarPixels(Mat img)
{
    vector<StarPixel> star_pixels;

    for(unsigned int i=0; i<img.rows; i++)
    {
        for(unsigned int j=0; j<img.cols; j++)
        {
            uint8_t pix_color;

            if (img.channels() > 1)
            {
                pix_color = img.at<Vec3b>(i,j)[1];  // Green channel
            }
            else
            {
                pix_color = img.at<uchar>(i,j);
            }

            // Pixel threshold
            if (pix_color > this->GetThreshold())
            {
                star_pixels.push_back(StarPixel(pix_color, j, i));
            }
        }
    }

    return star_pixels;
}

vector<StarPixel> StarFilterSW::GetStarPixels(Mat img, uint8_t thr)
{
    this->SetThreshold(thr);

    return this->GetStarPixels(img);
}

void StarFilterSW::SetThreshold(uint8_t val)
{
    this->threshold = val;
}

//! \} End of star-filter-sw group

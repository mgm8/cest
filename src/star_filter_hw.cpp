/*
 * star_filter_hw.cpp
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
 * \brief Star filter (using hardware) implementation.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.1.0
 * 
 * \date 11/11/2018
 * 
 * \addtogroup star-filter-hw
 * \{
 */

#include <cstdio>
#include <algorithm>
#include <memory>

#include "star_filter_hw.h"
#include "csv.hpp"

using namespace std;
using namespace cv;
using namespace st;

StarFilterHW::StarFilterHW()
    : StarFilter()
{

}

StarFilterHW::StarFilterHW(uint8_t thr)
{
    this->SetThreshold(thr);
}

StarFilterHW::~StarFilterHW()
{

}

void StarFilterHW::Clear()
{
    system("rm -f " STAR_FILTER_HW_BUFFER_IMG);
    system("rm -f " STAR_FILTER_HW_BUFFER_STAR_PIXELS);
}

vector<StarPixel> StarFilterHW::GetStarPixels(Mat img)
{
    this->Clear();

    this->RunSimulation(img);

    return this->ReadStarPixelsFromFile(STAR_FILTER_HW_BUFFER_STAR_PIXELS);
}

vector<StarPixel> StarFilterHW::GetStarPixels(Mat img, uint8_t thr)
{
    this->SetThreshold(thr);

    return this->GetStarPixels(img);
}

void StarFilterHW::SetThreshold(uint8_t val)
{
    this->threshold = val;
}

void StarFilterHW::RunSimulation(Mat img)
{
    imwrite(STAR_FILTER_HW_BUFFER_IMG, img, vector<int>(CV_IMWRITE_PXM_BINARY));

    string ghdl_cmd = "make";

    ghdl_cmd += " STOP_TIME=";
    ghdl_cmd += STAR_FILTER_HW_SIM_MAX_TIME_US;
    ghdl_cmd += "us";

    ghdl_cmd += " THRESHOLD=";
    ghdl_cmd += to_string(this->GetThreshold());
    ghdl_cmd += " -C ";
    ghdl_cmd += STAR_FILTER_HW_VHDL_FILES_DIR;

    ghdl_cmd += " -s -i";       // Silent mode and ignore errors

    shared_ptr<FILE> pipe(popen(ghdl_cmd.c_str(), "r"), pclose);

    if (!pipe)
    {
        string error_text = "popen() failed in ";
        error_text += __func__;
        error_text += " method from ";
        error_text += __FILE__;
        error_text += " file!";

        throw runtime_error(error_text.c_str());
    }
}

vector<StarPixel> StarFilterHW::ReadStarPixelsFromFile(const char *file)
{
    CSV<unsigned int> star_pixels_csv(file);

    vector<StarPixel> star_pixels;
 
    for(unsigned int i=0; i<star_pixels_csv.GetRows(); i++)
    {
        star_pixels.push_back(StarPixel(star_pixels_csv.ReadCell(STAR_FILTER_STAR_PIXELS_ROW_VAL, i),
                                        star_pixels_csv.ReadCell(STAR_FILTER_STAR_PIXELS_ROW_X, i),
                                        star_pixels_csv.ReadCell(STAR_FILTER_STAR_PIXELS_ROW_Y, i)));
    }

    return star_pixels;
}

//! \} End of star-filter-sw group

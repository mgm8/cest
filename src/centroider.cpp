/*
 * centroider.cpp
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
 * \brief Centroid computation implementation.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.1.0
 * 
 * \date 06/10/2018
 * 
 * \addtogroup centroider
 * \{
 */

#include <algorithm>

#include <cest/centroider.h>
#include <cest/csv.hpp>

using namespace std;
using namespace cest;
using namespace cv;

Centroider::Centroider()
{
    this->SetNumberOfCDPUs(CENTROIDER_DEFAULT_MAX_CDPUS);
    this->SetDistanceThreshold(CENTROIDER_DEFAULT_DISTANCE_THRESHOLD);
}

Centroider::Centroider(unsigned int n)
    : Centroider()
{
    this->SetNumberOfCDPUs(n);
}

Centroider::~Centroider()
{
}

void Centroider::SetNumberOfCDPUs(unsigned int n)
{
    this->max_cdpus = n;
}

void Centroider::SetDistanceThreshold(unsigned int d)
{
    this->distance_threshold = d;
}

void Centroider::Compute(StarPixel star_pix, float gain)
{
    if (this->cdpus.size() < this->max_cdpus)
    {
        bool pix_capt = false;
        for(unsigned int k=0; k<this->cdpus.size(); k++)
        {
            if (this->cdpus[k].DistanceFrom(star_pix.x, star_pix.y) < this->distance_threshold)
            {
                pix_capt = true;
            }
        }

        if (!pix_capt)
        {
            this->cdpus.push_back(CDPU());
            this->cdpus[this->cdpus.size()-1].SetCentroid(star_pix.x, star_pix.y, star_pix.value);
        }
    }

    for(unsigned int k=0; k<this->cdpus.size(); k++)
    {
        this->cdpus[k].Update(star_pix.x, star_pix.y, star_pix.value, gain);
    }
}

vector<Centroid> Centroider::ComputeFromList(vector<StarPixel> stars, float gain)
{
    this->Reset();

    for(unsigned int i=0; i<stars.size(); i++)
    {
        this->Compute(stars[i], gain);
    }

    return this->GetCentroids();
}

vector<Centroid> Centroider::GetCentroids()
{
    vector<Centroid> centroids;

    for(unsigned int i=0; i<cdpus.size(); i++)
    {
        centroids.push_back(cdpus[i].GetCentroid());
    }

    return centroids;
}

vector<Centroid> Centroider::SortCentroids(vector<Centroid> centroids)
{
    sort(centroids.begin(), centroids.end(), [this](Centroid a, Centroid b) {return ((a.value*a.pixels) > (b.value*b.pixels)); });

    return centroids;
}

void Centroider::Reset()
{
    this->cdpus.clear();
}

Mat Centroider::PrintCentroids(Mat img, vector<Centroid> centroids, bool print_id)
{
    Mat img_res;

    img.copyTo(img_res);

    if (img.channels() == 1)
    {
        cvtColor(img_res, img_res, COLOR_GRAY2BGR);
    }

    for(unsigned int i=0; i<centroids.size(); i++)
    {
        circle(img_res, Point2f(centroids[i].x, centroids[i].y), 5, Scalar(0, 255, 0));
    }

    if (print_id)
    {
        sort(centroids.begin(), centroids.end(), [this](Centroid a, Centroid b) {return ((a.value*a.pixels) > (b.value*b.pixels)); });

        for(unsigned int i=0; i<centroids.size(); i++)
        {
            putText(img_res, to_string(i+1).c_str(), Point2f(centroids[i].x+10, centroids[i].y+10), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255));
        }
    }

    return img_res;
}

void Centroider::SaveCentroids(const char *file_name)
{
    CSV<double> centroids;

    for(unsigned int i=0; i<cdpus.size(); i++)
    {
        vector<double> centroid;

        centroid.push_back(cdpus[i].GetCentroid().pixels);
        centroid.push_back(cdpus[i].GetCentroid().value);
        centroid.push_back(cdpus[i].GetCentroid().x);
        centroid.push_back(cdpus[i].GetCentroid().y);

        centroids.AppendRow(centroid);
    }

    centroids.Write(file_name);
}

//! \} End of centroider group

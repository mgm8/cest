/*
 * cdpu.cpp
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
 * \brief CentroiD Processor Unit class implementation.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.1.0
 * 
 * \date 05/03/2018
 * 
 * \addtogroup cdpu
 * \{
 */

#include <cest/cdpu.h>

using namespace cest;

CDPU::CDPU()
{
    this->centroid.x        = 0;
    this->centroid.y        = 0;
    this->centroid.value    = 0;
    this->centroid.pixels   = 0;
    this->pixels            = 0;
    this->G                 = 1;
}

CDPU::~CDPU()
{

}

void CDPU::Update(unsigned int x_new, unsigned int y_new, uint8_t color_new, float a)
{
    if (this->DistanceFrom(x_new, y_new) < DISTANCE_THRESHOLD_MAN)
    {
        this->G *= a;
        this->centroid.x = (this->G*this->centroid.x) + ((1-this->G)*x_new);
        this->centroid.y = (this->G*this->centroid.y) + ((1-this->G)*y_new);

        this->centroid.value = (this->G*this->centroid.value) + ((1-this->G)*color_new);
        this->centroid.pixels++;

        // Pixel counter
        this->pixels++;
    }
}

void CDPU::SetCentroid(unsigned int x_new, unsigned int y_new, uint8_t color_new)
{
    this->centroid.x = x_new;
    this->centroid.y = y_new;
    this->centroid.value += color_new;
    this->centroid.pixels = 1;
}

Centroid CDPU::GetCentroid()
{
    return this->centroid;
}

float CDPU::DistanceFrom(unsigned int x_comp, unsigned int y_comp)
{
    return abs(this->centroid.x - x_comp) + abs(this->centroid.y - y_comp);
}

uint8_t CDPU::GetPixels()
{
    return this->pixels;
}

//! \} End of cdpu group
